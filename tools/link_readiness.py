#!/usr/bin/env python3
"""Symbol-level link readiness of the game objects (PLAN P1 gate: zero
unresolved symbols).  Runs llvm-nm over every compiled game object
(cmake/game.cmake OBJECT libraries) and classifies each undefined symbol
that no game object defines.

    python tools/link_readiness.py [--build build/i686-windows]

Writes <build>/link_readiness.tsv (symbol, class, refs, example object,
detail) and prints the class totals.  Classes:

  data-missing          D_xxxxxxxx: a MAIN data global; the snapshot has no
                        generated data C (src/main_data, data2c d784320c)
  overlay-data-missing  <ov>_D_xxxxxxxx (ovlsyms prefix): an overlay's own data
  excluded-asm:<lib>    listed in game/EXCLUDED.tsv (asm body cut, transform 6):
                        bind to src/sce or an override
  cxx-mangled           a C++-mangled reference (should be C linkage)
  overlay-import        func_/FUN_ name at an overlay address: bound by the
                        overlay manager's registry (gen_overlay_registry.py)
  main-address-alias    func_/FUN_ name at a MAIN address: needs an alias to the
                        MAIN symbol defined there (detail names it)
  crt                   C runtime / compiler helper (libcmt provides it)
  port-runtime          rg_* / hw_* / port helpers (src/ps2, src/sce)
  hosted-static         a hosted guest (config/hosted.txt): `static` in its host's
                        file, yet referenced from another unit
  asm-only-unit         a MAIN function the snapshot still links from asm/main.s
                        (census/asm_bodies.tsv asm_only_unit; no C yet)
  other                 everything else (detail: why it is unknown)

Also lists symbols DEFINED by more than one game object (`duplicate-def`,
strong definitions only; COMDAT/inline duplicates are fine).
"""
from __future__ import annotations

import argparse
import collections
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parent.parent
NM = Path(os.environ.get("LLVM_ROOT", "../tools/llvm")) / "bin" / "llvm-nm.exe"
IMAGES = ("main", "title", "insmenu", "normal", "factory", "insect")
OVL_BASE = 0x004E9E80
CRT = {
    "memcpy", "memset", "memmove", "memcmp", "strcpy", "strcat", "strcmp", "strlen",
    "strncpy", "strncmp", "strchr", "strrchr", "strstr", "sprintf", "vsprintf", "printf",
    "snprintf", "vsnprintf", "sscanf", "atoi", "atof", "abs", "labs", "rand", "srand",
    "sqrtf", "sinf", "cosf", "tanf", "atan2f", "atanf", "asinf", "acosf", "fabsf", "floorf",
    "ceilf", "fmodf", "powf", "expf", "logf", "log10f", "sqrt", "sin", "cos", "tan", "atan2",
    "atan", "asin", "acos", "fabs", "floor", "ceil", "fmod", "pow", "exp", "log", "log10",
    "malloc", "free", "calloc", "realloc", "qsort", "bsearch", "toupper", "tolower",
    "isdigit", "isspace", "isalpha", "isalnum", "isupper", "islower", "isprint", "puts",
    "putchar", "_fltused", "_alldiv", "_allrem", "_allmul", "_aulldiv", "_aullrem",
    "_allshl", "_allshr", "_aullshr", "_ftol2", "_ftol2_sse", "_ftoul3", "_ultod3",
    "_dtoul3", "_ltod3", "_dtol3", "_chkstk", "__chkstk", "_alloca_probe", "__security_cookie",
    "@__security_check_cookie@4", "__CxxFrameHandler3", "_CxxThrowException",
    "__std_terminate", "??2@YAPAXI@Z", "??3@YAXPAX@Z", "??3@YAXPAXI@Z", "??_U@YAPAXI@Z",
    "??_V@YAXPAX@Z", "_purecall", "atexit", "__ExceptionPtrDestroy", "_tls_index",
    "__tls_array", "_Init_thread_header", "_Init_thread_footer", "_Init_thread_epoch",
    "__fltused", "__dtoui3", "__ultod3", "__dtol3", "__ltod3", "__dtoul3", "__ftoui3",
    "__ftoul3", "__ultof3", "__ltof3", "__uitod3", "__uitof3", "__ftol3", "__alldiv",
    "__allrem", "__allmul", "__aulldiv", "__aullrem", "__allshl", "__allshr", "__aullshr",
    "__aulldvrm", "__alldvrm"}


def nm(obj: Path) -> tuple[list, list]:
    r = subprocess.run([str(NM), "--no-sort", str(obj)], capture_output=True, text=True,
                       encoding="utf-8", errors="replace")
    defs, unds = [], []
    for ln in r.stdout.splitlines():
        parts = ln.split()
        if len(parts) == 2 and parts[0] == "U":
            unds.append(parts[1])
        elif len(parts) == 3:
            t, s = parts[1], parts[2]
            if t in ("T", "D", "B", "R", "C", "W", "V", "S", "A", "I"):
                defs.append((s, t))
    return defs, unds


def cname(sym: str) -> str:
    """Undecorate a cdecl COFF name (`_Foo` -> `Foo`); keep mangled names."""
    if sym.startswith("?") or sym.startswith("@"):
        return sym
    return sym[1:] if sym.startswith("_") else sym


def snapshot_symbols(game: Path) -> dict:
    """{image: {name: addr}} and {(image, addr): name} from the pinned snapshot."""
    snap = {}
    for ln in (game / "SNAPSHOT.txt").read_text(encoding="utf-8").splitlines():
        f = ln.split("\t")
        if len(f) == 2:
            snap[f[0]] = f[1]
    out: dict = {}
    for img in IMAGES:
        r = subprocess.run(["git", "-C", snap["source"], "show",
                            f"{snap['rev']}:config/{img}.symbols.txt"],
                           capture_output=True, text=True, encoding="utf-8", errors="replace")
        m = {}
        for ln in r.stdout.splitlines():
            f = ln.split("//")[0].split("=")
            if len(f) == 2 and f[1].strip().rstrip(";").startswith("0x"):
                m[f[0].strip()] = int(f[1].strip().rstrip(";"), 16)
        out[img] = m
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--build", type=Path, default=PORT / "build" / "i686-windows")
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--out", type=Path)
    a = ap.parse_args()
    out = a.out or (a.build / "link_readiness.tsv")
    # the compile set (cmake/game.cmake, tools/gamesrcs.py): MANIFEST kind unit/data,
    # an overrides/<path> replacing game/<path>; stale objects in the build tree are ignored
    objs, missing_obj = [], []
    for ln in (a.game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split(chr(9))
        if f[3] not in ("unit", "data") or not f[0].endswith((".c", ".cpp")):
            continue
        d = a.build / "CMakeFiles" / f"rg_game_{f[2]}.dir"
        ovr = (PORT / "overrides" / f[0]).exists()
        o = d / ("overrides" if ovr else "game") / (f[0] + ".obj")
        (objs if o.exists() else missing_obj).append((f[2], o))
    if missing_obj:
        print(f"WARNING: {len(missing_obj)} compile-set objects not built, e.g. {missing_obj[0][1]}")
    with ThreadPoolExecutor(12) as ex:
        res = list(ex.map(lambda io: (io[0], io[1], nm(io[1])), objs))
    defined: dict[str, list] = collections.defaultdict(list)
    undef: dict[str, list] = collections.defaultdict(list)
    for img, p, (defs, unds) in res:
        rel = p.relative_to(a.build / "CMakeFiles").as_posix()
        for s, t in defs:
            defined[s].append((rel, t))
        for s in unds:
            undef[s].append(rel)
    excluded = {}
    ex_tsv = a.game / "EXCLUDED.tsv"
    for ln in ex_tsv.read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split("\t")
        excluded[f[0]] = f[4]
    # MAIN functions the snapshot still links from asm/main.s (no registered C
    # file defines them; census/asm_bodies.tsv `asm_only_unit`)
    asm_only = set()
    cen = PORT / "census" / "asm_bodies.tsv"
    if cen.exists():
        for ln in cen.read_text(encoding="utf-8").splitlines():
            f = ln.split(chr(9))
            if len(f) > 5 and f[5] == "asm_only_unit":
                asm_only.add(f[2])
    hosted = {}
    hp = a.game / "config" / "hosted.txt"
    if hp.exists():
        for ln in hp.read_text(encoding="utf-8").splitlines():
            f = ln.split("#")[0].split()
            if len(f) >= 2:
                hosted[f[0]] = f[1]
    syms = snapshot_symbols(a.game)
    by_addr = {img: {v: k for k, v in m.items()} for img, m in syms.items()}
    rows = []
    tally = collections.Counter()
    for s in sorted(undef):
        if s in defined:
            continue
        c = cname(s)
        detail = ""
        m_addr = re.fullmatch(r"(?:func|FUN)_([0-9A-Fa-f]{6,8})(?:_e\d+)?", c)
        if s.startswith("?") or s.startswith("@"):
            if s in CRT:
                cls = "crt"
            else:
                cls = "cxx-mangled"
                mm = re.match(r"\?(\w+)@@", s)
                detail = (f"C name {mm.group(1)}" + (" (defined as C)" if "_" + mm.group(1) in defined else "")) if mm else ""
        elif re.fullmatch(r"D_[0-9A-Fa-f]{8}", c):
            cls = "data-missing"
        elif re.fullmatch(r"(title|insmenu|normal|factory|insect)_D_[0-9A-Fa-f]{8}", c):
            cls = "overlay-data-missing"
        elif c in excluded:
            cls = f"excluded-asm:{excluded[c]}"
        elif c in hosted:
            cls = "hosted-static"
            detail = f"static inside its host {hosted[c]} (config/hosted.txt) but called from other units"
        elif c in asm_only:
            cls = "asm-only-unit"
            detail = "linked from asm/main.s in this snapshot (not yet C); clean snapshot should have C"
        elif m_addr:
            addr = int(m_addr.group(1), 16)
            if addr >= OVL_BASE:
                cls = "overlay-import"
            else:
                cls = "main-address-alias"
                tgt = by_addr["main"].get(addr)
                detail = f"main symbol at 0x{addr:08X}: {tgt or '(none: interior entry / data)'}"
                if tgt and "_" + tgt in defined:
                    detail += " (defined)"
                elif tgt and tgt in excluded:
                    detail += f" (excluded-asm:{excluded[tgt]})"
        elif c in CRT or s in CRT or c.lstrip("_") in CRT:
            cls = "crt"
        elif re.match(r"(rg_|hw_|ps2_|sce|RG_)", c):
            cls = "port-runtime"
        else:
            cls = "other"
            img_hit = [img for img, m in syms.items() if c in m]
            if img_hit:
                detail = f"snapshot symbol of {','.join(img_hit)} with no compiled definition"
            elif c.startswith("__vt__") or c.startswith("__"):
                detail = "compiler/runtime name"
        tally[cls.split(":")[0] if not cls.startswith("excluded") else cls] += 1
        rows.append((c, cls, len(undef[s]), undef[s][0], detail))
    dups = []
    for s, ds in defined.items():
        strong = [d for d in ds if d[1] in ("T", "D", "B", "R")]
        comdat = s.startswith(("?", "_real@", "__real@", "__xmm@", "__ymm@", "__mask@", "$SG"))
        if len(strong) > 1 and not comdat:
            dups.append((cname(s), "duplicate-def", len(strong), strong[0][0],
                         " ".join(d[0] for d in strong[1:4])))
    tally["duplicate-def"] = len(dups)
    out.parent.mkdir(parents=True, exist_ok=True)
    with open(out, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("# link readiness: undefined symbols no game object defines (tools/link_readiness.py)\n")
        fh.write("symbol\tclass\trefs\texample_object\tdetail\n")
        for r in rows + sorted(dups):
            fh.write("\t".join(str(x) for x in r) + "\n")
    ndef = len(defined)
    print(f"{len(objs)} objects, {ndef} defined symbols, {len(undef)} distinct undefined, "
          f"{len(rows)} unresolved by game objects")
    for k, v in sorted(tally.items(), key=lambda kv: -kv[1]):
        print(f"  {k:28s} {v}")
    print(f"wrote {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

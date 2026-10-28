#!/usr/bin/env python3
"""Census 1: assembly-bodied code in the registered linked units.

Rows (one per site):
  asm_function     `asm <ret> f(...) { ... }` -- the whole body is mwcc asm
  asm_block        `asm [volatile] { ... }` statement inside a C function
  gnu_asm_stmt     `__asm__ [volatile] ("...")` / `asm("...")` statement
  reg_binding      `<decl> asm("vfN")` register binding (no code; mwcc VU0
                   intrinsic plumbing -- listed so the port knows the decls)
  vu0inline_call   a function that calls a helper from a header whose helpers
                   are themselves asm (include/vu0inline.h, libvu0.h) and has
                   no asm of its own -> header swap, no override needed
  asm_only_unit    a function in config/<image>.symbols.txt that NO registered
                   C/C++ file defines -- it is still linked from reference
                   assembly (asm/main.s parts, overlay .s)

body column (instruction classes inside the asm text):
  cop2_only   only COP2/VU0 macro ops (lqc2/sqc2/qmfc2/qmtc2/cfc2/ctc2/v*/vcallms)
              plus glue (nop, sync, mfc1/mtc1 moves) -> C/SSE vu0 helpers
  cop2_mixed  COP2 plus ordinary EE ops
  mmi         128-bit MMI ops (lq/sq/p*/qfsrv) and no COP2
  ee          plain EE/FPU code
  nops        only nop/sync (the overlay `<ovl>_entry` pads: not functions)
  (`jr` counts as `ret`, not EE, so a leaf VU0 routine reads cop2_only)
  (empty)     no instruction text (asm_only_unit, reg_binding)
"""
from __future__ import annotations

import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

COP2_EXACT = {"lqc2", "sqc2", "qmfc2", "qmtc2", "cfc2", "ctc2", "vcallms",
              "vcallmsr", "bc2f", "bc2t", "bc2fl", "bc2tl"}
GLUE = {"nop", "sync", "sync.p", "sync.l", "mfc1", "mtc1", "ssnop", "ehb"}
MMI_EXACT = {"lq", "sq", "qfsrv", "mfsa", "mtsa", "mtsab", "mtsah", "pref"}
MMI_PREFIX = ("padd", "psub", "pext", "pcpy", "pand", "por", "pnor", "pxor",
              "pmax", "pmin", "pceq", "pcgt", "psll", "psrl", "psra", "pmf",
              "pmt", "pmadd", "pmsub", "pmult", "pdiv", "pinth", "pinte",
              "pexe", "prev", "prot", "plzcw", "pabs", "phmadh", "phmsbh",
              "ppac", "pexc")
MNEM = re.compile(r"^\s*(?:[A-Za-z_.$]\w*\s*:\s*)*([a-z][a-z0-9.]*)\b", re.I)
HW = re.compile(r"0x1[02]00[0-9A-Fa-f]{4}\b")


def mnemonics(asm_text: str) -> list[str]:
    out = []
    for stmt in re.split(r"[;\n]", asm_text):
        s = stmt.strip()
        if not s or s.startswith(".") or s.startswith("#"):
            continue
        s = re.sub(r"^(?:[A-Za-z_$][\w$]*\s*:\s*)+", "", s)
        if not s or s.startswith("."):
            continue
        m = re.match(r"([A-Za-z][A-Za-z0-9.]*)", s)
        if m:
            out.append(m.group(1).lower())
    return out


def classify(mn: list[str]) -> tuple[str, Counter]:
    cls = Counter()
    for m in mn:
        base = m.split(".")[0]
        if m in COP2_EXACT or base in COP2_EXACT or m.startswith("v"):
            cls["cop2"] += 1
        elif m in GLUE:
            cls["glue"] += 1
        elif m == "jr":
            cls["ret"] += 1
        elif m in MMI_EXACT or base.startswith(MMI_PREFIX):
            cls["mmi"] += 1
        elif m == "syscall":
            cls["syscall"] += 1
        else:
            cls["ee"] += 1
    if not mn:
        return "", cls
    if not (cls["cop2"] or cls["ee"] or cls["mmi"] or cls["syscall"]):
        return "nops", cls
    if cls["cop2"] and not (cls["ee"] or cls["mmi"] or cls["syscall"]):
        return "cop2_only", cls
    if cls["cop2"]:
        return "cop2_mixed", cls
    if cls["mmi"]:
        return "mmi", cls
    return "ee", cls


def match_brace(s: str, i: int) -> int:
    depth = 0
    for k in range(i, len(s)):
        if s[k] == "{":
            depth += 1
        elif s[k] == "}":
            depth -= 1
            if depth == 0:
                return k
    return len(s) - 1


def match_paren(s: str, i: int) -> int:
    depth = 0
    for k in range(i, len(s)):
        if s[k] == "(":
            depth += 1
        elif s[k] == ")":
            depth -= 1
            if depth == 0:
                return k
    return len(s) - 1


BLOCK = re.compile(r"\basm\s*(?:volatile\s*|__volatile__\s*)?\{")
GNU = re.compile(r"\b(__asm__|__asm|asm)\s*(volatile|__volatile__)?\s*\(")


def scan_file(sf: S.SrcFile, rows: list, asm_helpers: dict) -> None:
    code, nostr = sf.code, sf.nostr
    in_asm_func: list[tuple[int, int]] = []
    for f in sf.funcs:
        if f.kind == "func" and f.is_asm:
            body = code[f.body_open + 1:f.body_close]
            mn = mnemonics(body)
            cat, cnt = classify(mn)
            rows.append(dict(file=sf.path, line=sf.line(f.start + len(f.header) - len(f.header.lstrip())),
                             symbol=f.name, image=sf.image, lib=sf.lib,
                             lib_reason=sf.lib_reason, category="asm_function",
                             body=cat, ninsn=len(mn),
                             hw_regs="yes" if HW.search(body) else "",
                             syscall="yes" if cnt["syscall"] else "",
                             detail=" ".join(f"{k}={v}" for k, v in sorted(cnt.items()))))
            in_asm_func.append((f.body_open, f.body_close))

    def inside_asm_func(o):
        return any(a <= o <= b for a, b in in_asm_func)

    for m in BLOCK.finditer(nostr):
        if inside_asm_func(m.start()):
            continue
        end = match_brace(nostr, m.end() - 1)
        body = code[m.end():end]
        mn = mnemonics(body)
        cat, cnt = classify(mn)
        fn = sf.enclosing(m.start())
        rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                         image=sf.image, lib=sf.lib, lib_reason=sf.lib_reason,
                         category="asm_block", body=cat, ninsn=len(mn),
                         hw_regs="yes" if HW.search(body) else "",
                         syscall="yes" if cnt["syscall"] else "",
                         detail=("static-inline-helper " if fn and re.search(r"\binline\b", fn.header) else "")
                         + " ".join(f"{k}={v}" for k, v in sorted(cnt.items()))))
        if fn and sf.kind == "header":
            asm_helpers.setdefault(fn.name, sf.path)
    for m in GNU.finditer(nostr):
        if inside_asm_func(m.start()):
            continue
        # is this a declaration register binding?  `<declarator> asm("...")`
        before = nostr[max(0, m.start() - 80):m.start()].rstrip()
        close = match_paren(nostr, m.end() - 1)
        inner = code[m.end():close]
        after = nostr[close + 1:close + 4].lstrip()
        strs = "".join(re.findall(r'"((?:[^"\\]|\\.)*)"', inner))
        is_bind = (re.search(r"[\w\]\)]$", before) is not None
                   and not re.search(r"\b(return|else|do)$", before)
                   and (after.startswith(";") or after.startswith(",") or after.startswith("="))
                   and re.fullmatch(r"\s*\$?[a-z]{1,3}\d{0,2}\s*", strs or "x") is not None)
        if is_bind:
            rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                             image=sf.image, lib=sf.lib, lib_reason=sf.lib_reason,
                             category="reg_binding", body="", ninsn=0, hw_regs="", syscall="",
                             detail=f'asm("{strs}")'))
            continue
        asm_text = strs.replace("\\n", "\n").replace("\\t", " ")
        mn = mnemonics(asm_text)
        cat, cnt = classify(mn)
        fn = sf.enclosing(m.start())
        rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                         image=sf.image, lib=sf.lib, lib_reason=sf.lib_reason,
                         category="gnu_asm_stmt", body=cat, ninsn=len(mn),
                         hw_regs="yes" if HW.search(asm_text) else "",
                         syscall="yes" if cnt["syscall"] else "",
                         detail=" ".join(f"{k}={v}" for k, v in sorted(cnt.items()))))
        if fn and sf.kind == "header":
            asm_helpers.setdefault(fn.name, sf.path)


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)
    rows: list[dict] = []
    helpers: dict[str, str] = {}
    for sf in snap.headers:
        scan_file(sf, rows, helpers)
    for sf in snap.files:
        scan_file(sf, rows, helpers)

    # vu0inline callers: functions with no own asm that call an asm helper
    own_asm = {(r["file"], r["symbol"]) for r in rows
               if r["category"] in ("asm_function", "asm_block", "gnu_asm_stmt")}
    if helpers:
        hx = re.compile(r"\b(" + "|".join(map(re.escape, sorted(helpers))) + r")\s*\(")
        for sf in snap.files:
            per: dict[str, list] = defaultdict(list)
            for m in hx.finditer(sf.nostr):
                fn = sf.enclosing(m.start())
                if fn is None or fn.body_open > m.start():
                    continue  # the declaration/definition itself
                per[fn.name].append((m.start(), m.group(1)))
            for fname, hits in per.items():
                cat = "vu0inline_call"
                note = "" if (sf.path, fname) not in own_asm else "also-has-own-asm "
                rows.append(dict(file=sf.path, line=sf.line(hits[0][0]), symbol=fname,
                                 image=sf.image, lib=sf.lib, lib_reason=sf.lib_reason,
                                 category=cat, body="cop2_via_header", ninsn="",
                                 hw_regs="", syscall="",
                                 detail=note + "helpers=" + ",".join(sorted({h for _, h in hits}))
                                 + " header=" + ",".join(sorted({helpers[h] for _, h in hits}))))

    # functions still linked from reference assembly (no C definition anywhere)
    defined: dict[str, set] = defaultdict(set)
    deffile: dict[tuple, S.SrcFile] = {}
    for sf in snap.files:
        for u in sf.units:
            deffile[(sf.image, u)] = sf
    for sf in snap.files:
        for f in sf.funcs:
            if f.kind == "func":
                defined[sf.image].add(f.name.split("::")[-1])
        for u in sf.units:
            defined[sf.image].add(u)
    for img in S.IMAGES:
        spans = sorted((snap.symbols[img][n], snap.symbols[img][n] + S.SIZES.get((img, n), 0), n)
                       for n in defined[img] if n in snap.symbols[img])
        starts = [sp[0] for sp in spans]
        import bisect
        for name, addr in sorted(snap.symbols[img].items(), key=lambda kv: kv[1]):
            if name in defined[img] or name in snap.hosted:
                continue
            k = bisect.bisect_right(starts, addr) - 1
            if k >= 0 and spans[k][0] <= addr < spans[k][1]:
                continue  # interior label of a defined multi-entry function
            if k >= 0:
                host = deffile.get((img, spans[k][2]))
                if host is not None and name in host.text:
                    continue  # named by the preceding unit as one of its own entries (switch-case "functions")
            lib, why = S.classify_lib("asm/x", img, [addr])
            rows.append(dict(file=f"(asm) {img} @0x{addr:08X}", line=0, symbol=name,
                             image=img, lib=lib, lib_reason=why, category="asm_only_unit",
                             body="", ninsn="", hw_regs="", syscall="",
                             detail="in symbols.txt, defined by no registered C/C++ file"))

    for r in rows:
        if r["category"] in ("asm_function", "asm_block", "gnu_asm_stmt") and r["lib"] == "game":
            r["port_action"] = ("vu0-header-swap" if r["body"] == "cop2_only" else
                                "override(ee-asm)")
        elif r["category"] == "vu0inline_call":
            r["port_action"] = "vu0-header-swap"
        elif r["category"] == "reg_binding":
            r["port_action"] = "vu0-intrinsic-decl"
        elif r["category"] == "asm_only_unit":
            r["port_action"] = "sce/ reimpl" if r["lib"] != "game" else "needs-C-or-override"
        else:
            r["port_action"] = "sce/ reimpl (exclude unit)"
    rows.sort(key=lambda r: (r["category"], r["image"], r["file"], int(r["line"] or 0)))
    cols = S.BASE_COLS + ["body", "ninsn", "hw_regs", "syscall", "port_action",
                          "lib_reason", "detail"]
    out = Path(a.out) / "asm_bodies.tsv"
    S.write_tsv(out, cols, rows, S.meta(snap, "asm_bodies"))
    c = Counter((r["category"], r["lib"]) for r in rows)
    for k, v in sorted(c.items()):
        print(f"{k[0]:16s} {k[1]:8s} {v}")
    print(f"wrote {out} ({len(rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

#!/usr/bin/env python3
"""Provider coverage for every symbol in game/EXCLUDED.tsv (PLAN.md transform 6).

    python tools/excluded_coverage.py [--objdir build/i686-windows]
                                      [--out build/bind-i686/excluded_coverage.tsv]
                                      [--md]   # also rewrite the table in docs/BINDINGS.md

For each excluded symbol:

* **referenced?**  An undefined symbol of a compiled game object (llvm-nm over
  every CMakeFiles/rg_game_*.dir/**/*.obj under --objdir; C names `_X`, C++
  names `?X@...` both count), or a `jal`/`j` target / call inside an excluded
  GAME-scope file (those files are replaced by overrides, which will need the
  same callees).
* **provider**, first match wins:
    drop:not-a-function   `<ovl>_entry` nop pads (docs: overlay entry pad)
    override:<path>       overrides/<file> exists for the symbol's file
    port:<src path>       a src/ file defines the symbol (text scan for a C
                          definition `NAME(...) {`, plus llvm-nm of built
                          non-game objects under build/*)
    drop:unreferenced     nothing references it
    todo:crt / todo:sce-<family> / todo:override   referenced, no provider yet

Columns: symbol image lib family role refs ref_images ref_by provider detail.
`refs` = number of game objects referencing it; `ref_by` = up to 3 examples
(objects, or `asm:<excluded symbol>`).

Exit status 0; the summary is printed and (with --md) written between the
`<!-- coverage:begin -->`/`<!-- coverage:end -->` markers in docs/BINDINGS.md.
"""
from __future__ import annotations

import argparse
import collections
import csv
import re
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parent.parent
NM = Path("../tools/llvm/bin/llvm-nm.exe")
SURFACE = PORT / "census" / "platform_sdk_surface.tsv"
EXCLUDED = PORT / "game" / "EXCLUDED.tsv"
BINDINGS_MD = PORT / "docs" / "BINDINGS.md"
# src/ trees that are not linked into the game executable
NOT_LINKED = {"extract"}
# unsuffixed libc names the game calls that the host CRT provides unchanged
HOST_CRT = {"memcpy", "memmove", "memset", "strcat", "strcmp", "strcpy", "strlen",
            "strncmp", "strncpy"}
RUNTIME_FAMILIES = {"libc", "libm", "libgcc", "mwcc-rt", "msl-c++", "crt0"}


def base_name(sym: str) -> str | None:
    """Undecorated identifier of an i686 COFF symbol (C `_X`, C++ `?X@@...`)."""
    if sym.startswith("__imp_"):
        sym = sym[6:]
    if sym.startswith("??"):
        return None  # operators/ctors/vtables: never an excluded game name
    if sym.startswith("?"):
        return sym[1:].split("@", 1)[0]
    if sym.startswith("_"):
        return sym[1:].split("@", 1)[0]
    return sym


def run_nm(objs: list[Path]) -> list[tuple[str, str, str]]:
    """(object, type, symbol) for every symbol of every object."""
    import tempfile
    rows = []
    for i in range(0, len(objs), 2000):
        chunk = [str(o).replace("\\", "/") for o in objs[i:i + 2000]]
        with tempfile.NamedTemporaryFile("w", suffix=".rsp", delete=False) as rsp:
            rsp.write("\n".join(f'"{c}"' for c in chunk))
        r = subprocess.run([str(NM), "-A", "@" + rsp.name], capture_output=True, text=True,
                           encoding="utf-8", errors="replace")
        Path(rsp.name).unlink()
        for ln in r.stdout.splitlines():
            # "<obj>: <addr> T sym" or "<obj>:          U sym"
            head, _, rest = ln.rpartition(": ")
            p = rest.split()
            if len(p) >= 2:
                rows.append((head, p[-2], p[-1]))
    return rows


def game_objects(objdir: Path) -> list[Path]:
    """Objects of the CURRENT compile list (<objdir>/game_sources.cmake).  An
    object whose source is no longer compiled (a game/ file since replaced by
    an override, a dropped missing/ stand-in) stays in the build tree and
    must not count."""
    objs = sorted(p for p in (objdir / "CMakeFiles").glob("rg_game_*.dir/**/*.obj"))
    lst = objdir / "game_sources.cmake"
    if not lst.is_file():
        return objs
    srcs = {ln.strip().strip('"').lower() for ln in lst.read_text(encoding="utf-8").splitlines()
            if ln.strip().startswith('"')}
    keep = []
    for o in objs:
        rel = o.relative_to(objdir / "CMakeFiles").as_posix().split("/", 1)[1]  # drop rg_game_<img>.dir
        if (PORT / rel.removesuffix(".obj")).as_posix().lower() in srcs:
            keep.append(o)
    return keep


def obj_to_game_path(obj: str) -> str:
    o = obj.replace("\\", "/")
    for key in ("/game/", "/overrides/", "/missing/"):
        if key in o:
            return ("" if key == "/game/" else key[1:]) + \
                o.split(key, 1)[1].removesuffix(".obj")
    return o


DEF_RE_CACHE: dict[str, re.Pattern] = {}


def scan_src_definitions(names: set[str]) -> dict[str, str]:
    """name -> src/ path that defines it as a C/C++ function (text scan)."""
    found: dict[str, str] = {}
    ident = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")
    for f in sorted((PORT / "src").rglob("*")):
        if f.suffix not in (".c", ".cpp", ".cc", ".h", ".inc", ".S", ".s"):
            continue
        if f.relative_to(PORT / "src").parts[0] in NOT_LINKED:
            continue
        text = f.read_text(encoding="utf-8", errors="replace")
        # blank comments (keep offsets) so commented-out names never count
        text = re.sub(r"/\*.*?\*/", lambda m: " " * len(m.group(0)), text, flags=re.S)
        text = re.sub(r"//[^\n]*", lambda m: " " * len(m.group(0)), text)
        for m in ident.finditer(text):
            n = m.group(1)
            if n not in names or n in found:
                continue
            # balanced parens, then '{' => definition; also accept alias macros
            i, depth = m.end(), 1
            while i < len(text) and depth:
                depth += {"(": 1, ")": -1}.get(text[i], 0)
                i += 1
            rest = text[i:i + 200].lstrip()
            prev = text[max(0, m.start() - 2):m.start()]
            if rest.startswith("{") and not prev.endswith((".", "->")):
                found[n] = f.relative_to(PORT).as_posix()
    return found


def scan_built_providers(names: set[str]) -> dict[str, str]:
    """name -> src path, from llvm-nm of built non-game, non-test objects."""
    objs = []
    for b in (PORT / "build").glob("*"):
        for o in b.glob("src/**/CMakeFiles/*.dir/**/*.obj"):
            objs.append(o)
    found: dict[str, str] = {}
    for obj, t, sym in run_nm(objs):
        if t in ("U", "a", "w") or t.islower() and t not in ("t", "d", "b", "r"):
            continue
        if t.islower():
            continue  # local symbols do not provide
        n = base_name(sym)
        if n in names and n not in found:
            o = obj.replace("\\", "/")
            rel = o.split("/build/", 1)[-1].split("/", 1)[-1]
            src_dir, _, tail = rel.partition("/CMakeFiles/")
            if src_dir.split("/")[1:2] and src_dir.split("/")[1] in NOT_LINKED:
                continue
            src_file = tail.split(".dir/", 1)[-1].removesuffix(".obj")
            found[n] = f"{src_dir}/{src_file}"
    return found


CALL_RE = re.compile(r"^\s*(?:jal|j|jalr)\s+([A-Za-z_][A-Za-z0-9_]*)\s*;", re.M)
CCALL_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*_[0-9a-fA-F]{5,6})\s*\(")


def excluded_file_callees(path: Path) -> set[str]:
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return set()
    return set(CALL_RE.findall(text)) | set(CCALL_RE.findall(text))


def load_surface() -> dict[str, dict]:
    out = {}
    with open(SURFACE, encoding="utf-8") as fh:
        rows = [ln for ln in fh if not ln.startswith("#")]
    for r in csv.DictReader(rows, delimiter="\t"):
        out[r["symbol"]] = r
    return out


# ---------------------------------------------------------------- ABI screen
# MIPS passes/returns ints and floats in different register files, so a
# caller that declares the wrong type still worked on the EE.  Under i686
# cdecl a float/double return comes back in x87 ST0 and an int in EAX (64-bit
# in EDX:EAX), and a 64-bit parameter takes two stack slots.  Every excluded
# symbol's caller-side declarations are screened for those mismatches.
DECL_RE = re.compile(r"^[ \t]*(?:extern[ \t]+(?:\"C\"[ \t]+)?)?((?:const[ \t]+)?(?:unsigned[ \t]+|signed[ \t]+)?"
                     r"(?:struct[ \t]+)?[A-Za-z_]\w*(?:[ \t]*\*+)?)[ \t\*]*\b([A-Za-z_]\w*)[ \t]*\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)[ \t]*;",
                     re.M)
F32 = {"f32", "float", "const f32", "const float"}
F64 = {"f64", "double", "long double"}
I64 = {"s64", "u64", "long long", "unsigned long long", "int64_t", "uint64_t", "__int64"}


def ret_class(t: str) -> str:
    t = " ".join(t.replace("*", " * ").split())
    if "*" in t:
        return "int"
    if t in F32:
        return "float"
    if t in F64:
        return "double"
    if t in I64 or t.endswith(("64", "long long")):
        return "int64"
    if t == "void":
        return "void"
    return "int"


def param_classes(plist: str) -> str:
    plist = plist.strip()
    if plist in ("", "void"):
        return ""
    out = []
    for p in plist.split(","):
        p = " ".join(p.replace("*", " * ").split())
        if "*" in p or "(" in p:
            out.append("i")
            continue
        words = [w for w in p.split() if w not in ("const", "volatile", "register")]
        # drop a trailing parameter name
        base = words
        if len(words) > 1 and words[-1] not in ("int", "long", "char", "short") and                 not words[-1].startswith(("s", "u", "f")) or len(words) > 2:
            base = words[:-1] if len(words) > 1 else words
        t = " ".join(base)
        if t in F32:
            out.append("f")
        elif t in F64:
            out.append("d")
        elif t in I64 or t.endswith("long long"):
            out.append("q")
        elif t == "...":
            out.append("...")
        else:
            out.append("i")
    return "".join(out)


def abi_screen(names: set[str], providers: dict[str, str]) -> list[dict]:
    rows = [ln.split("\t") for ln in
            (PORT / "game" / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    decl: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    where: dict[tuple, str] = {}
    for r in rows:
        rel, kind = r[0], r[3]
        if kind not in ("unit", "data") or not rel.endswith((".c", ".cpp")):
            continue
        f = (PORT / "overrides" / rel)
        if not f.is_file():
            f = PORT / "game" / rel
        text = f.read_text(encoding="utf-8", errors="replace")
        for m in DECL_RE.finditer(text):
            n = m.group(2)
            if n not in names:
                continue
            rt = m.group(1).strip()
            if rt in ("return", "else", "goto"):
                continue
            key = (ret_class(rt), param_classes(m.group(3)))
            decl[n][key] += 1
            where.setdefault((n,) + key, rel)
    out = []
    for n, c in sorted(decl.items()):
        rets = {k[0] for k in c}
        # widths of each parameter position (i/f: 4 bytes; d/q: 8 bytes)
        widths = {tuple(8 if ch in "dq" else 4 for ch in k[1].replace("...", "")) for k in c}
        ret_bad = (len(rets - {"void", "int"}) > 1 or
                   (rets & {"float", "double"} and rets & {"void", "int", "int64"}) or
                   ("int64" in rets and "int" in rets))
        width_bad = len(widths) > 1 and len({len(w) for w in widths}) == 1
        if not (ret_bad or width_bad):
            continue
        out.append({"symbol": n, "provider": providers.get(n, ""),
                    "kind": ",".join(k for k, b in (("return", ret_bad), ("param-width", width_bad)) if b),
                    "decls": "; ".join(f"{r} ({p or 'void'}) x{v} e.g. {where[(n, r, p)]}"
                                       for (r, p), v in c.most_common())})
    return out


def family_of(r: dict, sf: dict) -> str:
    """Census family, or for the SDK-band files the census does not cover
    (0x13BC20..0x140000: Level-5's own vector/matrix/GS-packet library)."""
    if sf.get("family"):
        return sf["family"]
    if r["lib"] == "game":
        return "game"
    f = r["file"]
    if "/gs/" in f:
        return "l5-gspkt"
    if any(k in f for k in ("/math/", "/matrix/", "/vec/", "/camera/", "/gfx/")):
        return "l5-math"
    return r["lib"]


def md_section(md: str, name: str, body: str) -> str:
    b, e = f"<!-- {name}:begin -->", f"<!-- {name}:end -->"
    if b not in md or e not in md:
        return md
    pre, _, rest = md.partition(b)
    _, _, post = rest.partition(e)
    return pre + b + "\n" + body.strip("\n") + "\n" + e + post


def gamescope_table(rows: list[dict], lane_dir: Path) -> str:
    """The game-scope rows (lib=game) with their plan: lane notes from
    build/bind-i686/lane_*.tsv (symbol, relpath, status, signature, note)."""
    notes: dict[str, tuple[str, str]] = {}
    for f in sorted(lane_dir.glob("lane_*.tsv")):
        for ln in f.read_text(encoding="utf-8", errors="replace").splitlines():
            p = ln.split("\t")
            if len(p) >= 5 and not ln.startswith(("#", "symbol\t")):
                notes[p[0]] = (p[2], p[4])
    out = ["| Symbol | Body | Refs | Provider | Plan / note |", "| --- | --- | ---: | --- | --- |"]
    for r in rows:
        if r["lib"] != "game":
            continue
        st, note = notes.get(r["symbol"], ("", ""))
        prov = r["provider"]
        if prov.startswith("override:"):
            prov = "override"
        if not note:
            if prov == "drop:not-a-function":
                note = "`<overlay>_entry` nop pad, not a function"
            elif prov == "drop:unreferenced":
                note = "no caller in compiled game code or excluded files"
        refs = int(r["refs"]) + int(r["asm_refs"])
        note = note.replace("|", "\\|")
        out.append(f"| `{r['symbol']}` | {r['detail'].split(';')[0]} | {refs} | `{prov}` | {note} |")
    return "\n".join(out) + "\n"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--objdir", type=Path, default=PORT / "build" / "i686-windows")
    ap.add_argument("--out", type=Path,
                    default=PORT / "build" / "bind-i686" / "excluded_coverage.tsv")
    ap.add_argument("--md", action="store_true", help="update docs/BINDINGS.md table")
    a = ap.parse_args()

    with open(EXCLUDED, encoding="utf-8") as fh:
        ex = list(csv.DictReader(fh, delimiter="\t"))
    names = {r["symbol"] for r in ex}
    surface = load_surface()

    objs = game_objects(a.objdir)
    if not objs:
        print(f"no game objects under {a.objdir}; build rg_game_objs first", file=sys.stderr)
        return 2
    obj_def: dict[str, set[str]] = collections.defaultdict(set)
    obj_und: dict[str, set[str]] = collections.defaultdict(set)
    for obj, t, sym in run_nm(objs):
        n = base_name(sym)
        if not n:
            continue
        o = obj_to_game_path(obj)
        if t == "U":
            obj_und[o].add(n)
        elif t.isupper() and t not in ("A",):
            obj_def[o].add(n)
    # library-band compiled objects (their stem is a census library function):
    # reached only through what game code needs, and cut off where a port
    # module provides the library function itself.
    def stem(o: str) -> str:
        return o.rsplit("/", 1)[-1].split(".", 1)[0]
    lib_objs = {o for o in set(obj_def) | set(obj_und) if stem(o) in surface}
    definer: dict[str, str] = {}
    for o, ds in obj_def.items():
        for n in ds:
            definer.setdefault(n, o)

    src_defs = scan_src_definitions(names | {stem(o) for o in lib_objs})
    built_defs = scan_built_providers(names | {stem(o) for o in lib_objs})
    port_def = {**built_defs, **src_defs}

    # callees of excluded files ported as overrides (the overrides need them)
    asm_callees: dict[str, set[str]] = {}
    for r in ex:
        # files that are (or will be) replaced by overrides: game scope, the
        # Level-5 library in the SDK band, and anything already overridden
        if (r["lib"] == "game" or family_of(r, surface.get(r["symbol"], {})).startswith("l5-")
                or (PORT / "overrides" / r["file"]).is_file()):
            asm_callees[r["symbol"]] = {c for c in excluded_file_callees(PORT / "game" / r["file"])
                                        if c != r["symbol"]}

    # reachability from game code
    refs: dict[str, set[str]] = collections.defaultdict(set)      # game objects
    lib_refs: dict[str, set[str]] = collections.defaultdict(set)  # library-band objects
    asm_refs: dict[str, set[str]] = collections.defaultdict(set)  # excluded game files
    work = []
    for o, us in obj_und.items():
        if o in lib_objs:
            continue
        for n in us:
            refs[n].add(o)
            work.append(n)
    for g, cs in asm_callees.items():
        for c in cs:
            asm_refs[c].add(g)
            work.append(c)
    seen = set()
    while work:
        n = work.pop()
        if n in seen:
            continue
        seen.add(n)
        if n in port_def:
            continue  # the port module replaces it, internals and all
        o = definer.get(n)
        if o in lib_objs:
            for u in obj_und.get(o, ()):
                lib_refs[u].add(o)
                work.append(u)
        if n in asm_callees:
            work.extend(asm_callees[n])
    needed = seen

    out_rows = []
    for r in ex:
        s = r["symbol"]
        sf = surface.get(s, {})
        family = family_of(r, sf)
        role = sf.get("role", "")
        objs_ref = refs.get(s, set())
        asm_ref = asm_refs.get(s, set())
        lref = lib_refs.get(s, set())
        imgs = sorted({("main" if "/main/" in o else o.split("/overlays/")[-1].split("/")[0])
                       for o in objs_ref})
        ovr = PORT / "overrides" / r["file"]
        if r["detail"] == "nops":
            prov = "drop:not-a-function"
        elif ovr.exists():
            prov = "override:" + ovr.relative_to(PORT).as_posix()
        elif s in port_def:
            prov = "port:" + port_def[s]
        elif s in HOST_CRT:
            prov = "host-crt"
        elif s in definer:
            prov = "game:" + definer[s]
        elif s not in needed:
            prov = "drop:lib-internal" if s in lib_refs or any(s in obj_und[o] for o in lib_objs)                 else "drop:unreferenced"
        elif r["lib"] == "game":
            prov = "todo:override"
        elif family in RUNTIME_FAMILIES:
            prov = "todo:crt"
        else:
            prov = "todo:" + family
        ex_by = sorted(objs_ref)[:3] + [f"asm:{x}" for x in sorted(asm_ref)[:3]] +             [f"lib:{stem(x)}" for x in sorted(lref)[:3]]
        out_rows.append({
            "symbol": s, "image": r["image"], "lib": r["lib"], "family": family,
            "role": role, "refs": str(len(objs_ref)), "asm_refs": str(len(asm_ref)),
            "lib_refs": str(len(lref)),
            "ref_images": ",".join(imgs), "provider": prov,
            "ref_by": " ".join(ex_by), "file": r["file"], "detail": r["detail"],
        })

    a.out.parent.mkdir(parents=True, exist_ok=True)
    cols = ["symbol", "image", "lib", "family", "role", "refs", "asm_refs", "lib_refs", "ref_images",
            "provider", "ref_by", "file", "detail"]
    with open(a.out, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("\t".join(cols) + "\n")
        for row in out_rows:
            fh.write("\t".join(row[c] for c in cols) + "\n")

    def pclass(p: str) -> str:
        if p.startswith("port:"):
            parts = p[5:].split("/")
            return "port:" + "/".join(parts[:3] if parts[0] == "src" else parts[:2])
        if p.startswith("override:"):
            return "override"
        return p
    tab = collections.Counter((pclass(r["provider"]), r["lib"]) for r in out_rows)
    provs = sorted({k[0] for k in tab}, key=lambda p: (p.split(":")[0] != "port",
                                                       p.split(":")[0] != "override",
                                                       p.startswith("drop"), p))
    libs = ["sdk", "library", "game"]
    lines = ["| Provider | sdk | library | game | total |", "| --- | ---: | ---: | ---: | ---: |"]
    for p in provs:
        v = [tab.get((p, l), 0) for l in libs]
        lines.append(f"| `{p}` | " + " | ".join(str(x) for x in v) + f" | {sum(v)} |")
    tot = [sum(tab.get((p, l), 0) for p in provs) for l in libs]
    lines.append("| **total** | " + " | ".join(str(x) for x in tot) + f" | {sum(tot)} |")
    nref = sum(1 for r in out_rows if r["symbol"] in needed)
    summary = "\n".join(lines)
    print(summary)
    print(f"\nreferenced: {nref} of {len(out_rows)}; wrote {a.out}")
    todo = collections.Counter(r["provider"] for r in out_rows if r["provider"].startswith("todo"))
    for k, v in sorted(todo.items()):
        print(f"  {k}: {v}")

    conflicts = abi_screen(names, {r["symbol"]: r["provider"] for r in out_rows})
    cf = a.out.parent / "abi_conflicts.tsv"
    with open(cf, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("symbol\tprovider\tkind\tdecls\n")
        for c in conflicts:
            fh.write(f"{c['symbol']}\t{c['provider']}\t{c['kind']}\t{c['decls']}\n")
    print(f"ABI screen: {len(conflicts)} excluded symbols with conflicting caller "
          f"declarations; wrote {cf}")

    if a.md and BINDINGS_MD.exists():
        md = BINDINGS_MD.read_text(encoding="utf-8")
        cov = (f"\n{summary}\n\nReferenced: **{nref}** of {len(out_rows)} excluded "
               f"symbols (game objects + excluded game-file callees).\n")
        md = md_section(md, "coverage", cov)
        md = md_section(md, "gamescope", gamescope_table(out_rows, a.out.parent))
        abi = ["", "| Symbol | Provider | Conflict | Caller declarations: return (params) x count |",
               "| --- | --- | --- | --- |"]
        for c in conflicts:
            d = c["decls"].replace("|", "\\|")
            abi.append(f"| `{c['symbol']}` | `{c['provider']}` | {c['kind']} | {d} |")
        abi.append("")
        abi.append("Param classes: i = 32-bit int/pointer, f = float, d = double, q = 64-bit int.")
        md = md_section(md, "abi", "\n".join(abi) + "\n")
        BINDINGS_MD.write_text(md, encoding="utf-8", newline="\n")
        print(f"updated {BINDINGS_MD}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

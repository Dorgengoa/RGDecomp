#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""x64 source census (P7, docs/X64-PLAN.md): what in the ingested game tree
assumes 4-byte pointers.  Text-level (comments/strings blanked, braces
tracked); the compiler-level counts come from tools/census/x64_probe.py.

    python tools/census/x64_census.py [--out build/x64-probe] [--roots game/src overrides/src missing/src]

Writes <out>/census_sites.tsv (one row per site: class, file, line, context,
area, text) and <out>/census_summary.txt (counts by class x area).

Classes (ctx = fn: inside a function body, init: file-scope initializer,
rec: struct/union/class member list, file: other file scope):
  addr-cast32      `(u32|s32|int|...)&X` -- an address stored as a 32-bit int.
                   In ctx init this is a static initializer: a hard error on
                   x64 (not a link-time constant once pointers are 64-bit).
  int-ptr-arith    `(T *)((u32)p + n)` -- pointer arithmetic done in ints
  ptrptr-deref     `*(T **)x` / `((T **)x)[i]` -- a pointer LOADED through a
                   cast: 8-byte read of a 4-byte slot on x64
  sizeof-ptr       `sizeof(T *)` -- pointer-size arithmetic
  inplace-reloc    `p->f = (s32)((u8 *)base + p->f)` -- a file offset turned
                   into a pointer IN the loaded asset (in-place relocation; the
                   slot is 4 bytes in the on-disc format)
  rec-ptr-member   a pointer-typed member of a struct/union/class body
  rec-fnptr-member a function-pointer member
  rec-u32-vptr     `VC_VPTR_MEMBER` / `vc_u32 __vptr` (devirt: already 4 bytes)
  cxx-virtual      a real C++ `virtual` (compiler vptr: 8 bytes on x64)
  global-ptr-decl  file-scope pointer-typed variable / extern (aliases data2c
                   u32 words or MAIN bss: 8-byte read on x64)
  long-type        plain `long` (4 bytes on Win64 = i686; 8 on Linux x64)
  inline-asm       asm statements (game side should be none)
  varargs          va_start / va_arg sites (portable since stage gccvarargs)
  int128           rg_u128 / rg_s128 uses (portable: _BitInt(128))
Plus per-record rows (class `rec`): records with >=1 pointer member, and
whether the record is offset-coded (pad*/unk* members, i.e. it encodes retail
offsets: any size change after its first pointer member is a wrong view).
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from x64_probe import area  # noqa: E402

INT32 = r"(?:u32|s32|int|unsigned|unsigned\s+int|signed\s+int|u_int|uint|uint32_t|int32_t|vc_u32|long|unsigned\s+long)"


def blank(s: str) -> str:
    """Comments, string and char literals -> spaces (offsets and newlines kept)."""
    out = list(s)
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if c == "/" and i + 1 < n and s[i + 1] == "/":
            j = s.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c == "/" and i + 1 < n and s[i + 1] == "*":
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and s[j] != c and s[j] != "\n":
                j += 2 if s[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                out[k] = " "
            i = j + 1
        elif c == "#" and (i == 0 or s[i - 1] == "\n"):
            # preprocessor line: blank it (keep line structure); continuation lines too
            j = i
            while True:
                e = s.find("\n", j)
                e = n if e < 0 else e
                if e > 0 and s[e - 1] == "\\" and e < n:
                    j = e + 1
                    continue
                break
            for k in range(i, e):
                if out[k] != "\n":
                    out[k] = " "
            i = e
        else:
            i += 1
    return "".join(out)


REC_HDR = re.compile(r"\b(struct|union|class|enum)\b[^;{}()=]*$")


def contexts(code: str) -> tuple[list[tuple[int, int, str]], list[tuple[int, int]]]:
    """Brace blocks as (open, close, kind) with kind in fn/init/rec/enum/other,
    plus the record member-list spans [(open, close)] (outermost member level)."""
    blocks = []
    stack = []  # (open, kind)
    for i, ch in enumerate(code):
        if ch == "{":
            parent = stack[-1][1] if stack else None
            if parent in ("fn", "init", "enum"):
                kind = parent
            else:
                k = i - 1
                while k >= 0 and code[k] in " \t\r\n":
                    k -= 1
                prev = code[k] if k >= 0 else ""
                line_start = max(code.rfind(";", 0, i), code.rfind("}", 0, i), code.rfind("{", 0, i))
                head = code[line_start + 1:i]
                if prev in "=,":
                    kind = "init" if parent is None or parent in ("other",) else ("init" if parent != "rec" else "rec")
                    if parent == "rec":
                        kind = "fn"  # default member initializer braces: treat as code
                    kind = "init" if prev == "=" or parent in ("init",) else kind
                elif prev == ")" or re.search(r"\)\s*(const|override|noexcept|final)\s*$", head):
                    kind = "fn"
                elif re.search(r"\benum\b", head):
                    kind = "enum"
                elif REC_HDR.search(head.strip()) or re.search(r"\b(struct|union|class)\b", head):
                    kind = "rec"
                else:
                    kind = "other"  # extern "C" {, namespace X {
            stack.append((i, kind))
        elif ch == "}" and stack:
            o, kind = stack.pop()
            blocks.append((o, i, kind))
    return blocks, [(o, c) for o, c, k in blocks if k == "rec"]


def ctx_at(blocks_sorted, pos: int) -> str:
    """Innermost block kind containing pos (linear scan is fine per file)."""
    best = None
    for o, c, k in blocks_sorted:
        if o < pos < c and (best is None or o > best[0]):
            best = (o, k)
    return best[1] if best else "file"


PATS = [
    ("addr-cast32", re.compile(r"\(\s*" + INT32 + r"\s*\)\s*\(?\s*&\s*[A-Za-z_]")),
    ("int-ptr-arith", re.compile(r"\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*\*+\s*\)\s*\(\s*\(\s*" + INT32
                                 + r"\s*\)")),
    ("ptrptr-deref", re.compile(r"\*\s*\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*\*\s*(?:const\s*)?\*\s*\)"
                                r"|\(\s*\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*\*\s*\*\s*\)\s*[\w>.\-()]+\s*\)\s*\[")),
    ("sizeof-ptr", re.compile(r"\bsizeof\s*\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*\*+\s*\)")),
    # lvalue = (s32|u32|T *)(base + (cast)lvalue): a stored offset turned into a pointer
    # in place (asset relocation: ModelResRelocate_14bfd0, MotResRelocateBlockList_14bbc0)
    ("inplace-reloc", re.compile(r"([A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+|\s*\[[^\]\n]{1,30}\])+)\s*=\s*"
                                 r"\(\s*(?:u32|s32|int|[A-Za-z_]\w*(?:\s+\w+)*\s*\*+)\s*\)\s*\(\s*\(?"
                                 r"[^;]{0,40}?\+\s*(?:\([^)]*\)\s*)?\1\b")),
    ("rec-u32-vptr", re.compile(r"\bVC_VPTR_MEMBER\b|\bvc_u32\s+__vptr\b")),
    ("cxx-virtual", re.compile(r"\bvirtual\b")),
    ("long-type", re.compile(r"(?<!long\s)(?<!long)\blong\b(?!\s+long\b)(?!\s+double\b)")),
    ("inline-asm", re.compile(r"\b(?:__asm__|__asm|asm)\s*(?:volatile\s*|__volatile__\s*)?[({]")),
    ("varargs", re.compile(r"\bva_(?:start|arg)\s*\(")),
    ("int128", re.compile(r"\brg_[us]128\b")),
]
FN_HINT = re.compile(r"\b[A-Za-z_]\w*_[0-9a-f]{5,6}\b")


def member_decls(code: str, o: int, c: int, nested: list[tuple[int, int]]):
    """Split a record body into top-level member declarations (skipping nested braces)."""
    depth, start = 0, o + 1
    i = o + 1
    while i < c:
        ch = code[i]
        if ch in "{(":
            depth += 1
        elif ch in "})":
            depth -= 1
        elif ch == ";" and depth == 0:
            yield start, code[start:i]
            start = i + 1
        i += 1


def scan_file(path: Path, rows: list, recs: list):
    try:
        raw = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return
    code = blank(raw)
    blocks, recspans = contexts(code)
    blocks_sorted = sorted(blocks)
    nl = [0]
    for i, ch in enumerate(code):
        if ch == "\n":
            nl.append(i + 1)
    import bisect

    def line(off):
        return bisect.bisect_right(nl, off)

    rp = str(path.relative_to(ROOT)).replace("\\", "/")
    ar = area(rp)
    for cls, rx in PATS:
        for m in rx.finditer(code):
            ctx = ctx_at(blocks_sorted, m.start())
            if cls == "long-type" and ctx == "file" and "typedef" in code[max(0, m.start() - 80):m.start()]:
                pass
            ln = line(m.start())
            txt = raw[m.start():m.start() + 60].replace("\t", " ").replace("\n", " ")
            rows.append((cls, rp, ln, ctx, ar, txt))
    # file-scope pointer declarations (outside any brace block)
    for m in re.finditer(r"(?:^|;|\})\s*((?:extern\s+|static\s+|const\s+|volatile\s+)*"
                         r"[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*(?:const\s*)?([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*"
                         r"(?:__attribute__\s*\(\(.*?\)\)\s*)?(?:=|;))", code):
        pos = m.start(1)
        # generated code puts file-scope declarations at column 0 and locals indented;
        # #if branches can unbalance the brace tracker, so column 0 is the test
        if pos > 0 and code[pos - 1] != chr(10):
            continue
        if ctx_at(blocks_sorted, pos) not in ("file", "other"):
            continue
        decl = m.group(1)
        if re.match(r"\s*(typedef|return)\b", decl):
            continue
        rows.append(("global-ptr-decl", rp, line(pos), "file", ar,
                     decl.strip()[:60].replace("\n", " ")))
    # record member census
    for o, c in recspans:
        # skip records nested in another record's member list counted at their own level
        nptr = nfn = 0
        offset_coded = False
        name = code[max(0, code.rfind(";", 0, o), code.rfind("}", 0, o), code.rfind("{", 0, o)) + 1:o].strip()
        name = re.sub(r"\s+", " ", name)[:50]
        for s, d in member_decls(code, o, c, []):
            dd = d.strip()
            if not dd or dd.startswith(("typedef", "static ", "friend", "using ", "public", "private",
                                        "protected", "enum")):
                continue
            if re.search(r"\b(?:pad|unk|_pad|filler|field)\w*\b", dd):
                offset_coded = True
            if "{" in dd:
                continue  # nested record / inline method body
            if re.search(r"\(\s*\*+\s*\w+\s*\)\s*\(", dd) or re.search(r"\(\s*\w+\s*::\s*\*\s*\w+\s*\)", dd):
                nfn += 1
                rows.append(("rec-fnptr-member", rp, line(s), "rec", ar, dd[:60].replace("\n", " ")))
                continue
            if "(" in dd:
                continue  # method declaration
            if re.search(r"\*", dd.split("=")[0]):
                nptr += 1
                rows.append(("rec-ptr-member", rp, line(s), "rec", ar, dd[:60].replace("\n", " ")))
        if nptr or nfn:
            recs.append((rp, line(o), name, nptr, nfn, int(offset_coded), ar))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", default="build/x64-probe")
    ap.add_argument("--roots", nargs="*", default=["game/src", "overrides/src", "missing/src",
                                                   "game/include"])
    ap.add_argument("--db", default="build/soak2-i686",
                    help="i686 build dir: only .c/.cpp files in its compile_commands.json are "
                         "scanned (excluded asm units and overridden originals are not built); "
                         "'' scans every file")
    a = ap.parse_args()
    out = Path(a.out)
    if not out.is_absolute():
        out = ROOT / out
    out.mkdir(parents=True, exist_ok=True)
    built = None
    if a.db:
        import json
        db = Path(a.db)
        db = db if db.is_absolute() else ROOT / db
        built = {str(Path(e["file"])).lower() for e in
                 json.loads((db / "compile_commands.json").read_text(encoding="utf-8"))}
    rows, recs = [], []
    nfiles = 0
    for r in a.roots:
        for p in sorted((ROOT / r).rglob("*")):
            if p.suffix in (".c", ".cpp", ".h", ".hpp", ".inc"):
                if built is not None and p.suffix in (".c", ".cpp") and str(p).lower() not in built:
                    continue
                scan_file(p, rows, recs)
                nfiles += 1
    with open(out / "census_sites.tsv", "w", encoding="utf-8") as fo:
        fo.write("class\tfile\tline\tctx\tarea\ttext\n")
        for r in rows:
            fo.write("\t".join(str(x) for x in r) + "\n")
    with open(out / "census_records.tsv", "w", encoding="utf-8") as fo:
        fo.write("file\tline\trecord\tptr_members\tfnptr_members\toffset_coded\tarea\n")
        for r in recs:
            fo.write("\t".join(str(x) for x in r) + "\n")
    L = []
    w = L.append
    w(f"x64 source census: {nfiles} files under {' '.join(a.roots)}")
    byc = Counter(r[0] for r in rows)
    byctx = Counter((r[0], r[3]) for r in rows)
    files = defaultdict(set)
    for r in rows:
        files[r[0]].add(r[1])
    w("class                 sites   files   by context")
    for cls, n in byc.most_common():
        cx = ", ".join(f"{k[1]}={v}" for k, v in byctx.items() if k[0] == cls)
        w(f"  {cls:18s} {n:7d} {len(files[cls]):7d}   {cx}")
    w("")
    areas = Counter()
    for r in rows:
        areas[(r[0], r[4])] += 1
    for cls in ("addr-cast32", "rec-ptr-member", "global-ptr-decl", "ptrptr-deref", "int-ptr-arith",
                "inplace-reloc"):
        parts = sorted(((ar, n) for (c, ar), n in areas.items() if c == cls), key=lambda x: -x[1])
        w(f"{cls} by area: " + ", ".join(f"{ar}={n}" for ar, n in parts[:14]))
    w("")
    w(f"records with pointer members: {len(recs)} (definitions, per file); "
      f"offset-coded (pad/unk members): {sum(r[5] for r in recs)}; "
      f"pointer members {sum(r[3] for r in recs)}, fn-pointer members {sum(r[4] for r in recs)}")
    # static-initializer address words by target kind (function / data / other)
    tk = Counter()
    for r in rows:
        if r[0] == "addr-cast32" and r[3] == "init":
            m = re.search(r"&\s*([A-Za-z_]\w*)", r[5])
            nm = m.group(1) if m else ""
            if re.match(r"D_[0-9A-Fa-f]{8}$", nm) or nm.startswith(("data2c_", "D_")):
                tk["data"] += 1
            elif re.search(r"_[0-9a-f]{5,6}$|^func_[0-9A-F]{8}", nm):
                tk["function"] += 1
            else:
                tk["other:" + ("named" if nm else "?")] += 1
    w("static-initializer address words by target: " + ", ".join(f"{k}={v}" for k, v in tk.most_common()))
    ak = Counter()
    for r in rows:
        if r[0] == "inline-asm":
            t = r[5]
            k = ("x86-naked-thunk" if "movl" in t or "jmp" in t else
                 "datareloc-toplevel-asm" if "RG_DR_ASYM" in t or ".bss" in t else
                 "mips-asm-block" if "{" in t.split("asm", 1)[-1][:12] else
                 "asm-label/reg-binding" if re.search(r'asm\s*\(\s*"(?:r|vf|vi)\d', t) else "other")
            ak[(k, r[1])] += 1
    kk = Counter()
    kf = Counter()
    for (k, f), n in ak.items():
        kk[k] += n
        kf[k] += 1
    w("inline-asm by kind (sites/files): " + ", ".join(f"{k}={kk[k]}/{kf[k]}" for k in kk))
    (out / "census_summary.txt").write_text("\n".join(L) + "\n", encoding="utf-8")
    print("\n".join(L))
    return 0


if __name__ == "__main__":
    sys.exit(main())

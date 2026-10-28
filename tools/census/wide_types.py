#!/usr/bin/env python3
"""Census 6: 128-bit types, 128-bit loads/stores, MMI instructions.

One row per (line, category).  Categories:
  typedef       a typedef that creates a 128-bit type (u128/s128 via
                __int128 or __attribute__((mode(TI))), or a union over one)
  mem_access    `*(u128 *)expr` / `*(s128 *)` / `((u128 *)p)[i]` -- a 128-bit
                load or store (mwcc emits lq/sq; needs 16-byte alignment)
  decl          a variable / field / parameter / return of a 128-bit type
  expr          any other line naming a 128-bit type (casts, sizeof, ...)
  asm_lqsq      lq / sq inside an asm body
  asm_mmi       other MMI (p*, qfsrv, pcpyld ...) inside an asm body
  asm_cop2_q    lqc2 / sqc2 / qmfc2 / qmtc2 inside an asm body (128-bit VU0
                regs: same alignment/layout concern)
Type names matched: u128 s128 __int128 long128 u_long128 qword plus any local
typedef name found to alias one of them in the same file.
"""
from __future__ import annotations

import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S
from asm_bodies import MMI_PREFIX, mnemonics

BASE = ["u128", "s128", "__int128", "long128", "u_long128", "qword"]


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)
    rows = []
    for sf in snap.all():
        s = sf.nostr
        names = set(BASE)
        # local aliases: typedef ... <128-bit> ... NAME;   and mode(TI)
        for m in re.finditer(r"\btypedef\b([^;]*);", s):
            body = m.group(1)
            nm = re.search(r"(\w+)\s*(?:__attribute__\s*\(\(.*\)\))?\s*$", body.strip())
            if not nm:
                continue
            if re.search(r"\b(" + "|".join(names) + r")\b", body) or "mode(TI)" in body.replace(" ", ""):
                names.add(nm.group(1))
        typ = re.compile(r"\b(" + "|".join(sorted(map(re.escape, names))) + r")\b")
        asm_spans = [(f.body_open, f.body_close) for f in sf.funcs if f.is_asm]
        asm_spans += [(m.end(), s.find("}", m.end())) for m in
                      re.finditer(r"\basm\s*(?:volatile\s*)?\{", s)]
        seen = set()

        def add(off, cat, detail):
            ln = sf.line(off)
            if (ln, cat) in seen:
                return
            seen.add((ln, cat))
            rows.append(dict(file=sf.path, line=ln, symbol=sf.symbol_at(off), image=sf.image,
                             lib=sf.lib, category=cat, detail=detail,
                             context=S.snippet(sf.line_text(ln, "code"))))
        in_asm = lambda o: any(x <= o <= y for x, y in asm_spans)
        for m in typ.finditer(s):
            if in_asm(m.start()):
                continue
            ln = sf.line(m.start())
            line = sf.line_text(ln, "nostr")
            if re.match(r"\s*typedef\b", line) or re.search(r"\btypedef\b", s[max(0, m.start() - 200):m.start()].split(";")[-1]):
                add(m.start(), "typedef", m.group(1))
            elif re.search(r"M2C_FIELD\s*\([^,()]*(\([^()]*\))?[^,()]*,\s*$", s[max(0, m.start() - 60):m.start()]):
                add(m.start(), "mem_access", m.group(1) + " M2C_FIELD")
            elif re.match(r"\s*\*?\s*\)", s[m.end():m.end() + 4]) and re.search(r"\(\s*(const\s+|volatile\s+|unsigned\s+|signed\s+)*$", s[max(0, m.start() - 30):m.start()]):
                # (u128 *)  -> pointer cast; deref?
                pre = s[max(0, m.start() - 30):m.start()]
                post = s[m.end():m.end() + 80]
                if re.search(r"\*\s*\(\s*(const\s+|volatile\s+|unsigned\s+|signed\s+)*$", pre) or re.match(r"\s*\*\s*\)\s*[\w(][^;]*?\)\s*\[", post) \
                        or re.match(r"\s*\*\s*\)", post) and re.search(r"\*\s*\(\s*(const\s+|volatile\s+)*$", pre):
                    add(m.start(), "mem_access", m.group(1) + " *")
                elif re.match(r"\s*\*\s*\)", post):
                    add(m.start(), "mem_access" if re.search(r"\(\s*\(\s*$", pre) else "expr", m.group(1) + " * cast")
                else:
                    add(m.start(), "expr", m.group(1) + " cast")
            elif re.match(r"\s*\**\s*\w+\s*[;,=\[)(]", s[m.end():m.end() + 60]):
                add(m.start(), "decl", m.group(1))
            else:
                add(m.start(), "expr", m.group(1))
        for x, y in asm_spans:
            body = sf.code[x:y]
            base_line = sf.line(x)
            for k, ln_txt in enumerate(body.split("\n")):
                for mn in mnemonics(ln_txt):
                    off = x + sum(len(t) + 1 for t in body.split("\n")[:k])
                    if mn in ("lq", "sq"):
                        add(off, "asm_lqsq", mn)
                    elif mn.split(".")[0].startswith(MMI_PREFIX) or mn in ("qfsrv", "mtsab", "mtsah", "mfsa", "mtsa"):
                        add(off, "asm_mmi", mn)
                    elif mn in ("lqc2", "sqc2", "qmfc2", "qmtc2"):
                        add(off, "asm_cop2_q", mn.split(".")[0])
    rows.sort(key=lambda r: (r["category"], r["image"], r["file"], r["line"]))
    cols = S.BASE_COLS + ["detail", "context"]
    out = Path(a.out) / "wide_types.tsv"
    S.write_tsv(out, cols, rows, S.meta(snap, "wide_types"))
    print(Counter((r["category"], r["lib"]) for r in rows))
    print(f"wrote {out} ({len(rows)} rows, {len({r['file'] for r in rows})} files)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

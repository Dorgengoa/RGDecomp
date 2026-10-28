#!/usr/bin/env python3
"""Census 7: #pragma, __attribute__, __declspec and compiler builtins.

category  pragma | attribute | declspec | builtin
kind      pragma name (optimization_level, opt_propagation, ...),
          attribute name (section, aligned, mode, ...), builtin name
group     matching   -- codegen-only knobs, harmless to drop on the host
          semantic   -- changes meaning or ABI; the port must decide
                        (divbyzerocheck, fast_fptosi, usefloatacc,
                        vu0_mmi_reg_binding, mode(TI), aligned, packed,
                        mwcc varargs builtins)
          placement  -- section("...") placement; drop on host but keep the
                        data (it is how .sdata/.lit objects were pinned)
          other      -- anything not classified
value     the rest of the pragma line / the attribute argument
"""
from __future__ import annotations

import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

SEMANTIC_PRAGMA = {"divbyzerocheck", "fast_fptosi", "usefloatacc", "vu0_mmi_reg_binding",
                   "pack", "align", "cplusplus", "exceptions", "RTTI", "ANSI_strict",
                   "enumsalwaysint", "unsigned_char", "longlong"}
MATCHING_PRAGMA = re.compile(r"^(optimization_level|opt_\w+|peephole|schedule|inline_\w+|"
                             r"auto_inline|always_inline|dont_inline|tailcall|optimize_for_size|"
                             r"no_branch_likely|push|pop|warn_\w+|scheduling|global_optimizer|"
                             r"once|mark|unused)$")
SEMANTIC_ATTR = {"aligned", "mode", "packed", "vector_size", "transparent_union", "noreturn"}


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)
    rows = []
    for sf in snap.all():
        code = sf.code
        for m in re.finditer(r"^[ \t]*#[ \t]*pragma[ \t]+(\w+)([^\n]*)", code, re.M):
            kind = m.group(1)
            grp = ("semantic" if kind in SEMANTIC_PRAGMA else
                   "matching" if MATCHING_PRAGMA.match(kind) else "other")
            rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                             image=sf.image, lib=sf.lib, category="pragma", kind=kind,
                             group=grp, value=S.snippet(m.group(2), 60)))
        for m in re.finditer(r"\b__attribute__\s*\(\(", sf.nostr):
            # split the attribute list
            depth, k = 0, m.end() - 2
            for k in range(m.end() - 2, len(code)):
                if code[k] == "(":
                    depth += 1
                elif code[k] == ")":
                    depth -= 1
                    if depth == 0:
                        break
            inner = code[m.end():k - 1]
            for am in re.finditer(r"(\w+)\s*(\(([^()]*(\([^()]*\))?[^()]*)\))?", inner):
                kind = am.group(1).strip("_")
                val = (am.group(3) or "").strip()
                grp = ("placement" if kind == "section" else
                       "semantic" if kind in SEMANTIC_ATTR else "other")
                rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                                 image=sf.image, lib=sf.lib, category="attribute", kind=kind,
                                 group=grp, value=S.snippet(val, 60)))
        for m in re.finditer(r"\b__declspec\s*\(\s*(\w+)\s*(\(([^)]*)\))?", sf.nostr):
            rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                             image=sf.image, lib=sf.lib, category="declspec", kind=m.group(1),
                             group="other", value=m.group(3) or ""))
        for m in re.finditer(r"\b(__builtin_\w+)\s*\(", sf.nostr):
            kind = m.group(1)
            grp = "semantic" if kind in ("__builtin_args_info", "__builtin_next_arg",
                                         "__builtin_va_info", "__builtin_align") else "other"
            rows.append(dict(file=sf.path, line=sf.line(m.start()), symbol=sf.symbol_at(m.start()),
                             image=sf.image, lib=sf.lib, category="builtin", kind=kind,
                             group=grp, value=S.snippet(sf.line_text(sf.line(m.start()), "code"), 80)))
    rows.sort(key=lambda r: (r["category"], r["group"], r["kind"], r["file"], r["line"]))
    cols = S.BASE_COLS + ["kind", "group", "value"]
    out = Path(a.out) / "pragmas_attrs.tsv"
    S.write_tsv(out, cols, rows, S.meta(snap, "pragmas_attrs"))
    c = Counter((r["category"], r["group"], r["kind"]) for r in rows)
    for k, v in sorted(c.items(), key=lambda kv: -kv[1]):
        print(*k, v)
    print(f"wrote {out} ({len(rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

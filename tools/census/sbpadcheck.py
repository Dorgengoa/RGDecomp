#!/usr/bin/env python3
"""Check the protos stack-block rule's padded slots against retail's frame.

A `stack-block` row with "padded slot(s)" says a callee writes past every C
local the stage placed, so the block pads that slot.  The pad is wrong if
retail kept ANOTHER local there (one the C declares elsewhere, never handed to
a call): then the function itself touches the slot by `$sp` offset.  For every
padded row of PROTOS.tsv this lists the definition's own `$sp`-relative
accesses (loads, stores, address-of) that fall in a padded slot.

    python tools/census/sbpadcheck.py out/sblock2/pre.pkl out/sblock2/p8/PROTOS.tsv

Verdict per row: `pad-clean` (no own access: the slot is the callee's
continuation of the passed object) or `pad-touched` (review the listed
instructions).  docs/PROTOS.md "Stack-block census".
"""
from __future__ import annotations

import pickle
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "stages"))
import protos  # noqa: E402
import asmflow  # noqa: E402


def main() -> int:
    d = pickle.load(open(sys.argv[1], "rb"))
    st = protos.ProtoStage()
    st.addr_table = d["addr_table"]
    fl = st._flow()
    rows = [ln.rstrip("\n").split("\t") for ln in open(sys.argv[2], encoding="utf-8")]
    for r in rows:
        if len(r) < 5 or r[3] != "stack-block" or "padded slot" not in r[4]:
            continue
        rel, nm, msg = r[0], r[2], r[4]
        img = st.image_of(rel) if hasattr(st, "image_of") else "main"
        base = int(re.search(r"from sp\+0x(-?[0-9a-f]+)", msg).group(1), 16)
        pads = [int(x, 16) for x in re.search(r"padded slot\(s\) ([0-9a-fx, ]+)", msg).group(1).split(",")]
        cfg = fl.cfg(f"{img}:{nm}")
        if cfg is None:
            print(f"{nm}: no listing")
            continue
        F = 0
        for op, ops in cfg.ins[:8]:
            if op == "addiu" and ops[:2] == ["$29", "$29"]:
                im = asmflow._imm(ops[2])
                F = -im[1] if im and im[0] == "int" and im[1] < 0 else F
                break
        hits = []
        for i, (op, ops) in enumerate(cfg.ins):
            off = None
            if op in ("addiu", "daddiu") and len(ops) == 3 and ops[1] == "$29" and ops[0] != "$29":
                im = asmflow._imm(ops[2])
                off = im[1] if im and im[0] == "int" else None
                w = 1
            elif ops and len(ops) == 2 and re.fullmatch(r"-?\w+\(\$29\)", ops[1]) and \
                    op in asmflow.Flow.WIDTH:
                im = asmflow._imm(ops[1][:-5])
                off = im[1] if im and im[0] == "int" else None
                w = asmflow.Flow.WIDTH[op]
            if off is None:
                continue
            e = off - F           # entry-sp relative, like the stage's offsets
            for p in pads:
                lo = base + p
                if lo <= e < lo + 16 or (e < lo and e + w > lo):
                    hits.append(f"@{i} {op} {', '.join(ops)} (entry sp{e:+#x}, slot {p:#x})")
        print(f"{nm}: base sp{base:+#x}, padded {', '.join(hex(p) for p in pads)}: "
              + ("pad-clean" if not hits else "pad-touched"))
        for h in hits:
            print("    " + h)
    return 0


if __name__ == "__main__":
    sys.exit(main())

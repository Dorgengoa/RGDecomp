#!/usr/bin/env python3
"""Print retail listings (as the protos stage parses them) from a protos_pre pickle.

    python tools/census/sblisting.py out/sblock2/pre.pkl NAME [NAME ...] [--img main]

NAME may be `img:name`.  Instruction indices are the asmflow CFG indices (the
`insn` of census escapes).  Used to review stack-block census rows.
"""
import pickle, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "stages"))
import protos  # noqa: E402

d = pickle.load(open(sys.argv[1], "rb"))
st = protos.ProtoStage()
st.addr_table = d["addr_table"]
fl = st._flow()
for nm in sys.argv[2:]:
    img, _c, n = nm.rpartition(":")
    img = img or "main"
    cfg = fl.cfg(f"{img}:{n}")
    print(f"== {img}:{n}")
    if cfg is None:
        print("  (no listing)")
        continue
    for i, (op, ops) in enumerate(cfg.ins):
        print(f"  {i:4d} {op:8s} {', '.join(ops)}")

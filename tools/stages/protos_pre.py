#!/usr/bin/env python3
"""Re-run the protos stage alone on its exact ingest input (fast iteration).

    # once: dump the protos stage's input during a scratch ingest
    RG_INGEST_PRE_PROTOS=out/sblock/pre.pkl python tools/ingest.py --out out/sblock/g0
    # then, any number of times (~1/5 of an ingest):
    python tools/stages/protos_pre.py out/sblock/pre.pkl --out out/sblock/p1 [--files RX]

Writes PROTOS.tsv (and, with --files, the staged files whose path matches RX)
under --out.  The env switches of protos.py apply (RG_PROTOS_SB_TRACE,
RG_PROTOS_SB_CENSUS, RG_PROTOS_NO_*).  The pickle must be re-dumped when the
snapshot or an earlier stage changes.
"""
from __future__ import annotations

import argparse
import pickle
import re
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import protos  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("pkl", type=Path)
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--files", help="regex of relpaths whose staged text to write")
    a = ap.parse_args()
    t0 = time.time()
    d = pickle.load(open(a.pkl, "rb"))
    st = protos.ProtoStage()
    st.addr_table = d["addr_table"]
    st.prepare(dict(d["outputs"]))
    print(f"prepared in {time.time() - t0:.1f}s")
    a.out.mkdir(parents=True, exist_ok=True)
    for p, b in st.extra_outputs().items():
        q = a.out / p
        q.parent.mkdir(parents=True, exist_ok=True)
        q.write_bytes(b)
    if a.files:
        for p in d.get("apply", d["outputs"]):
            b = d["outputs"][p]
            if re.search(a.files, p):
                q = a.out / p
                q.parent.mkdir(parents=True, exist_ok=True)
                q.write_bytes(st.apply(p, b)[0])
    return 0


if __name__ == "__main__":
    sys.exit(main())

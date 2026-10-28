#!/usr/bin/env python3
"""Apply the transform-2 stage (tools/stages/protos.py) to a COPY of game/.

    python tools/stages/run_protos.py [--game game] [--out out/protos-test] [--no-write]

Reads game/MANIFEST.tsv (an un-staged ingest), runs ProtoStage.prepare() over
every ingested file, applies it the way ingest.py applies a Stage (kind unit
and data only), and writes the full tree + include/port/game_protos.h +
PROTOS.tsv under --out.  Prints the per-rule census.
"""
from __future__ import annotations

import argparse
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
sys.path.insert(0, str(HERE))
import protos  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--out", type=Path, default=PORT / "out" / "protos-test")
    ap.add_argument("--no-write", action="store_true")
    a = ap.parse_args()
    t0 = time.time()
    rows = [ln.split("\t") for ln in
            (a.game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    kinds = {r[0]: r[3] for r in rows}
    with ThreadPoolExecutor(16) as ex:
        datas = dict(zip(kinds, ex.map(lambda p: (a.game / p).read_bytes(), kinds)))
    print(f"read {len(datas)} files in {time.time() - t0:.1f}s")
    st = protos.ProtoStage()
    snap = dict(ln.split("\t", 1) for ln in
                (a.game / "SNAPSHOT.txt").read_text(encoding="utf-8").splitlines()
                if "\t" in ln)
    if "source" in snap and "rev" in snap:   # addr-alias renames need MAIN's address table
        st.addr_table = protos.snapshot_addr_table(snap["source"], snap["rev"])
    st.prepare(datas)
    print(f"prepared in {time.time() - t0:.1f}s")
    outputs, changed, sites = {}, 0, 0
    for p in sorted(datas):
        d = datas[p]
        if kinds[p] in ("unit", "data"):
            n, k = st.apply(p, d)
            changed += n != d
            sites += k
            # idempotence: a second application is a no-op
            assert st.apply(p, n)[0] == n, p
            d = n
        outputs[p] = d
    outputs.update(st.extra_outputs())
    print(f"stage {st.name}: files_changed={changed} sites={sites}")
    for k, v in sorted(st.stats.items()):
        print(f"  {k:24s} {v}")
    if a.no_write:   # still drop the header + log for inspection
        for p, d in st.extra_outputs().items():
            (a.out / p).parent.mkdir(parents=True, exist_ok=True)
            (a.out / p).write_bytes(d)
    else:
        def w(item):
            p, d = item
            f = a.out / p
            if f.exists() and f.read_bytes() == d:
                return 0
            f.parent.mkdir(parents=True, exist_ok=True)
            f.write_bytes(d)
            return 1
        with ThreadPoolExecutor(16) as ex:
            n = sum(ex.map(w, outputs.items()))
        print(f"wrote {n} files under {a.out} ({time.time() - t0:.1f}s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())

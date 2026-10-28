#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Run parity.py over several scenarios and summarise (docs/TEST-FIXTURES.md "Retail parity").

    python tools/parity/sweep.py --exe EXE --out D [SCEN ...] [--env K=V] [--skip-retail]
                                 [--summary-only]

Default scenarios: battle2 and every walk_* card scenario.  Per scenario D/SCEN/ holds the
port/retail frame streams, logs and compare.txt; D/summary.tsv has one row per scenario:
frames compared, retail long frames, identical fields, the first frame where rng differs and
the first divergence (frame, object, values).  --skip-retail reuses D/SCEN/retail.jsonl
(retail does not depend on the exe: rerun only the port after a port change).
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import parity  # noqa: E402


def summarise(d: Path) -> dict:
    t = (d / "compare.txt").read_text(encoding="utf-8") if (d / "compare.txt").exists() else ""
    row = {"frames": "", "retail_long": "", "identical": "", "rng": "", "first": ""}
    m = re.search(r": (\d+) frames compared", t)
    if m:
        row["frames"] = m.group(1)
    m = re.search(r"retail longer frames: (\d+)", t)
    if m:
        row["retail_long"] = m.group(1)
    m = re.search(r"identical fields: (\S+); rng first differs at (\S+)", t)
    if m:
        row["identical"], row["rng"] = m.group(1), m.group(2)
    m = re.search(r"^  frame +(\d+) \(vbl[^)]*\) (.*)$", t, re.M)
    if m:
        row["first"] = f"{m.group(1)}: {m.group(2)[:140]}"
    return row


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("scenarios", nargs="*")
    ap.add_argument("--exe", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--env", action="append", default=[])
    ap.add_argument("--skip-retail", action="store_true")
    ap.add_argument("--summary-only", action="store_true")
    a = ap.parse_args(argv)
    names = a.scenarios or ["battle2"] + [k for k in parity.SCENARIOS if k.startswith("walk_")]
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    rows = []
    for n in names:
        d = out / n
        if not a.summary_only:
            envs = sum((["--env", e] for e in a.env), [])
            cmds = [["port", n, "--exe", a.exe, "--out", str(d)] + envs]
            if not (a.skip_retail and (d / "retail.jsonl").exists()):
                cmds.append(["retail", n, "--out", str(d)])
            cmds.append(["compare", str(d)])
            for c in cmds:
                print(f"== {n}: {c[0]}", flush=True)
                r = subprocess.run([sys.executable, str(HERE / "parity.py")] + c, capture_output=True, text=True,
                                   errors="replace")
                d.mkdir(parents=True, exist_ok=True)
                with open(d / "sweep.log", "a", encoding="utf-8") as f:
                    f.write(" ".join(c) + "\n" + r.stdout + r.stderr + "\n")
                if r.returncode:
                    print(f"   FAILED ({r.returncode}); see {d / 'sweep.log'}", flush=True)
                    break
        rows.append((n, summarise(d)))
        print(f"   {n}: {rows[-1][1]}", flush=True)
    with open(out / "summary.tsv", "w", encoding="utf-8") as f:
        f.write("scenario\tframes\tretail_long_frames\tidentical_fields\trng_first_diff\tfirst_divergence\n")
        for n, r in rows:
            f.write(f"{n}\t{r['frames']}\t{r['retail_long']}\t{r['identical']}\t{r['rng']}\t{r['first']}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
"""Which same-file calls carry VU0 register values (docs/NATIVE-CPU.md section 4,
docs/PROTOS.md `vu0frame`).

    python tools/stages/vu0frame_census.py [--jobs 2] [--only SUBSTR] [--out census/vu0frame_callfed.tsv]

Runs tools/native/vu0_census.py's per-function register events and, per
function F, follows which writer last defined each lane: F itself or a
same-file callee G.  A read of a lane G wrote is a CALL-FED read (F consumes
G's output registers), so G must run on F's register file, not on a fresh one.
Together with the census's `tu-helper` rows (G reads what F left) this is the
list of functions the `vu0frame` stage passes the caller's frame to
(`rg_vu0_state *rg_vu0_p_`).  Rows: path, caller, callee, register.lanes,
read statement.  Also lists every function with live-in or kept-lane reads.
"""
from __future__ import annotations

import argparse
import sys
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "native"))
import vu0_census as vc  # noqa: E402


def callfed(fns):
    """fns: scan_file's function tuples -> [(caller, callee, reg, lanes, txt)]"""
    byname = {f[0]: f for f in fns}
    out = []
    for name, written, livein, lanein, addr, callees, first, stmts in fns:
        src: dict[str, dict[int, str]] = defaultdict(dict)   # reg -> lane -> writer
        for R, W, A, txt, sc in stmts:
            hw = []
            for cal in sc:
                if cal in byname and cal != name:
                    for reg, m in byname[cal][1].items():
                        hw.append((reg, m, cal))
            for reg, m in R:
                if reg == "vf0":
                    continue
                if not reg.startswith(("vf", "acc", "g")):
                    m = 1
                for k in range(4):
                    if m & (1 << k) and src[reg].get(k, "self") != "self":
                        out.append((name, src[reg][k], reg, k, txt))
            for reg, m, cal in hw:
                if not reg.startswith(("vf", "acc", "g")):
                    m = 1
                for k in range(4):
                    if m & (1 << k):
                        src[reg][k] = cal
            for reg, m in W:
                if not reg.startswith(("vf", "acc", "g")):
                    m = 1
                for k in range(4):
                    if m & (1 << k):
                        src[reg][k] = "self"
    # merge lanes
    agg: dict[tuple, list] = {}
    for caller, callee, reg, k, txt in out:
        key = (caller, callee, reg)
        if key not in agg:
            agg[key] = [0, txt]
        agg[key][0] |= 1 << k
    return [(c, g, r, "".join("xyzw"[k] for k in range(4) if v[0] & (1 << k)), v[1])
            for (c, g, r), v in agg.items()]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--jobs", type=int, default=2)
    ap.add_argument("--only", default="")
    ap.add_argument("--out", type=Path, default=PORT / "census" / "vu0frame_callfed.tsv")
    a = ap.parse_args()
    env = vc.msvc_env()
    files = []
    for kind, p in vc.compile_set():
        if a.only and a.only not in p.as_posix():
            continue
        try:
            s = p.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if vc.TOKENS.search(s):
            files.append((kind, p))
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda f: vc.scan_file(f[0], f[1], env), files))
    rows = []
    for kind, p, c, fns in res:
        rel = p.relative_to(PORT).as_posix()
        for caller, callee, reg, lanes, txt in callfed(fns):
            rows.append(("callfed", rel, caller, callee, f"{reg}.{lanes}", txt))
        local_called = {cal for f in fns for cal in f[5] if cal != f[0]}
        for name, written, livein, lanein, addr, callees, first, _st in fns:
            if livein:
                rows.append(("livein" + ("-helper" if name in local_called else ""), rel, name, "",
                             vc.lanes_str(livein), first))
            if lanein:
                rows.append(("lanein", rel, name, "", vc.lanes_str(lanein), ""))
    a.out.parent.mkdir(parents=True, exist_ok=True)
    with a.out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("kind\tpath\tfunction\tcallee\tregs\tstmt\n")
        for r in sorted(rows):
            f.write("\t".join(r) + "\n")
    n = defaultdict(int)
    for r in rows:
        n[r[0]] += 1
    print(f"vu0frame_census: {len(files)} files; " + ", ".join(f"{k}={v}" for k, v in sorted(n.items()))
          + f" -> {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

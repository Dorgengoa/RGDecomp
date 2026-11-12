#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Determinism check of a fixture set (docs/TEST-FIXTURES.md "Determinism").

    python tools/fixtures/verify.py [--exe EXE] [--only battle] [--trace]

Needs a set made with `regen.py --check K [--trace]`: the power-on run saved
each milestone N and N + K and shot the display at N + K.  For each milestone
this loads N, runs K fields and compares with the power-on run:
  run_hash   the runtime's run hash at N + K (kernel trace hash, audio, pad
             words, virtual time, folded every field) vs the check state's
  frame      the --shot hash of the display at N + K
  trace      (--trace) port_trace.py compare --key vbl of the loaded run's
             state trace against the power-on trace over their common vbls
Exit 0 when everything matches.
"""
from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fxlib  # noqa: E402


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe")
    ap.add_argument("--only")
    ap.add_argument("--trace", action="store_true")
    a = ap.parse_args(argv)
    exe_src = fxlib.exe_path(a.exe)
    d = fxlib.fixture_dir(exe_src)
    man = fxlib.load_manifest(d)
    if not man or not man.get("checks"):
        fxlib.say(f"verify: {d} has no checks; run regen.py --check K first")
        return 2
    exe = d / man["exe"]
    names = a.only.split(",") if a.only else list(man["checks"])
    bad = 0
    for n in names:
        e, c = man["milestones"][n], man["checks"][n]
        work = d / "verify" / n
        shutil.rmtree(work, ignore_errors=True)
        (work / "saves").mkdir(parents=True)
        shot = work / "loaded.png"
        cmd = [str(exe), "--headless", "--fields", str(c["field"]), "--saves", str(work / "saves"),
               "--input", str(fxlib.GOLDEN), "--load-state", str(d / e["file"]),
               "--shot", f"{c['field']}:{shot}"]
        extra = {}
        if a.trace:
            extra = {"RG_TRACE_OUT": str(work / "loaded.trace.tsv"),
                     "RG_TRACE_REGIONS": str(fxlib.PORT / "tools" / "trace" / "regions_symbols.cfg"),
                     "RG_TRACE_PORTCFG": str(fxlib.PORT / "tools" / "trace" / "port_regions.cfg"),
                     "RG_TRACE_INPUT": str(fxlib.GOLDEN), "RG_TRACE_EVERY": "5"}
        r = subprocess.run(cmd, env=fxlib.game_env(extra), cwd=str(work), capture_output=True, text=True,
                           encoding="utf-8", errors="replace")
        (work / "run.log").write_text(r.stdout + r.stderr, encoding="utf-8")
        rh = re.search(r"run_hash=(\w+)\s*$", r.stdout, re.M)
        sh = re.search(r"SHOT field=\d+ \S+ hash=(\w+)", r.stderr)
        rh, sh = (rh.group(1) if rh else None), (sh.group(1) if sh else None)
        ok_h, ok_s = rh == c["run_hash"], sh == c.get("shot_hash")
        line = (f"{n:7s} load {e['field']} -> {c['field']}: run_hash {rh} vs {c['run_hash']} "
                f"{'OK' if ok_h else 'DIFF'}; frame {sh} vs {c.get('shot_hash')} {'OK' if ok_s else 'DIFF'}")
        ok_t = True
        if a.trace and c.get("trace"):
            t = subprocess.run([sys.executable, str(fxlib.PORT / "tools" / "trace" / "port_trace.py"), "compare",
                                str(d / c["trace"]), str(work / "loaded.trace.tsv")],
                               capture_output=True, text=True)
            (work / "trace_compare.txt").write_text(t.stdout + t.stderr, encoding="utf-8")
            ok_t = t.returncode == 0
            first = [x for x in t.stdout.splitlines() if x.startswith(("vbls:", "IDENTICAL", "FIRST"))]
            line += "; trace " + ("IDENTICAL" if ok_t else "DIFF") + " (" + " | ".join(first) + ")"
        fxlib.say(line)
        bad += not (ok_h and ok_s and ok_t and r.returncode == 0)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

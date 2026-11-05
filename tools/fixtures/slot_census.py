#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""slot_census.py: which ctests start rg-game, and is each under tools/fixtures/slotwatch.py?

    slot_census.py --ctest <ctest exe> --build <build dir> [--check]

Reads `ctest --show-only=json-v1` of the build.  A test "starts rg-game" when an argument of its
command is an rg-game executable (rg-game, rg-game-oracle, .exe or not; maps and other files do
not count).  Each such test must go through slotwatch.py (headless rg-game runs wait for an
rg_slots slot; a plain ctest TIMEOUT counts those waits: docs/TEST-FIXTURES.md "Slot waits"),
unless NO_RUN below says why it runs no game.  --check exits 1 on an unwrapped one (ctest
fixtures.slot_census).  Scripts that find the exe on their own are not seen: pass the exe as an
argument (as every fixture test does) so the census sees it.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys

NO_RUN = {
    "fixtures.cli": "run_from.py argument handling (--print): runs no game",
}
EXE = re.compile(r"(^|[\\/])rg-game(-oracle)?(\.exe)?$", re.I)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ctest", default="ctest")
    ap.add_argument("--build", required=True)
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args(argv)
    r = subprocess.run([a.ctest, "--show-only=json-v1"], cwd=a.build, capture_output=True, text=True,
                       errors="replace")
    if r.returncode:
        print(r.stdout + r.stderr)
        return 2
    tests = json.loads(r.stdout)["tests"]
    bad = n = 0
    for t in tests:
        cmd = t.get("command") or []
        if not any(EXE.search(c) for c in cmd):
            continue
        n += 1
        props = {p["name"]: p["value"] for p in t.get("properties", [])}
        wrapped = any(c.replace("\\", "/").endswith("tools/fixtures/slotwatch.py") for c in cmd)
        if wrapped:
            i = cmd.index("--active-timeout") if "--active-timeout" in cmd else -1
            state = f"slotwatch active {cmd[i + 1] if i >= 0 else '?'} s, ctest TIMEOUT {props.get('TIMEOUT')}"
        elif t["name"] in NO_RUN:
            state = "no run: " + NO_RUN[t["name"]]
        else:
            state = f"UNWRAPPED (ctest TIMEOUT {props.get('TIMEOUT')} counts slot waits)"
            bad += 1
        print(f"{t['name']:32} {state}")
    print(f"slot_census: {n} test(s) start rg-game, {bad} unwrapped")
    return 1 if a.check and bad else 0


if __name__ == "__main__":
    sys.exit(main())

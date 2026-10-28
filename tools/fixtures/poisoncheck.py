#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Stale-packet regression: run fixtures with RG_NR_POISON (docs/NATIVE-RENDER.md "Remembered
packets"; history 2026-10-26 (rpkt)).

    python tools/fixtures/poisoncheck.py --exe EXE [--suite shop,boot,drivers,soak] [--out DIR]
                                         [--mode 1|2] [--soak-fields N] [--skip-missing] [--control]

RG_NR_POISON=1 makes DrawListFrameBegin fill a frame packet stack's dead contents with a poison
pattern before the game resets it, and every native-renderer walker (nr_const, nr_fx, nr_mesh,
nr_im) reports a read of that pattern ("nr: POISON: ..."): a renderer read through a pointer
into a packet stack the game has already reset, i.e. the 1025b shop-close class (a light /
view packet remembered by address).  Mode 2 aborts at the first hit (the crash report then
names the reader).

Suites (each runs its own tool with the variable set; the tool's own verdict must hold too):
  shop     tools/fixtures/shopcrash.py --api d3d11 (the 1025b regression route)
  boot     tools/fixtures/bootcheck.py --all (the card library: boot, menu, walk)
  drivers  tools/fixtures/soak.py drivers (insectstory, insectrun, factory production)
  soak     tools/fixtures/soak.py run --all --fields N (long; default 1500 per card)
Poison catches a read of dead memory the game has not rewritten yet; memory already reused (the
1025b case: the menu's packets over the field's stack) reads as live data, and a walk through
it is caught by nr_game_ptr's refusals instead, so both count ("counted" below).
PASS = every suite's tool passes, no "nr: POISON" line and no refused walker read in any log,
and the poison was armed
(the stats line of at least one run shows poisoned qwords > 0).  Runs under poison are
diagnostic: the game's own reads of dead memory see the pattern too, so run hashes are not
compared.  --control: the negative control, RG_NR_NOTE_COPY=0 (the pre-1025c re-reads): PASS
when poisoned or refused reads ARE reported (proves the detectors see the shop-close class).
Exit 0 PASS, 1 FAIL, 77 skip (--skip-missing without the cards).
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PY = sys.executable
HIT = re.compile(r"nr: POISON: .*")
ARMED = re.compile(r"native render game memory: (\d+) walker reads refused.*poison mode (\d+): (\d+) qwords poisoned, (\d+) poisoned reads")


def scan(paths):
    hits, armed, reads = [], 0, 0
    for p in paths:
        try:
            t = p.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        hits += [f"{p.name}: {m.group(0)}" for m in HIT.finditer(t)]
        for m in ARMED.finditer(t):
            armed += int(m.group(3))
            reads += int(m.group(4)) + int(m.group(1))   # poisoned + refused (unreadable) walker reads
    return hits, armed, reads


def run(cmd, log: Path):
    log.parent.mkdir(parents=True, exist_ok=True)
    p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, errors="replace")
    log.write_text(p.stdout + p.stderr, encoding="utf-8")
    return p.returncode, p.stdout + p.stderr


def suite(name, a, out: Path):
    d = out / name
    d.mkdir(parents=True, exist_ok=True)
    exe = str(Path(a.exe).resolve())
    if name == "shop":
        rc, t = run([PY, "tools/fixtures/shopcrash.py", "--exe", exe, "--api", "d3d11", "--out", str(d)], d / "tool.txt")
        ok = rc == 0 and "shopcrash d3d11: PASS" in t
    elif name == "boot":
        rc, t = run([PY, "tools/fixtures/bootcheck.py", "--all", "--exe", exe, "--keep-logs", str(d / "logs")], d / "tool.txt")
        ok = rc == 0 and not re.search(r"^\s*FAIL\s", t, re.M)
    elif name == "drivers":
        rc, t = run([PY, "tools/fixtures/soak.py", "drivers", "--exe", exe, "--out", str(d / "run")], d / "tool.txt")
        ok = rc == 0 and not re.search(r"\bFAIL\b", t)
    elif name == "soak":
        rc, t = run([PY, "tools/fixtures/soak.py", "run", "--exe", exe, "--out", str(d / "run"), "--all",
                     "--fields", str(a.soak_fields)], d / "tool.txt")
        ok = rc == 0
    else:
        raise SystemExit(f"unknown suite {name}")
    logs = [p for p in d.rglob("*") if p.is_file() and p.suffix in (".log", ".txt", ".tsv", ".json", "")]
    hits, armed, reads = scan(logs)
    return ok, hits, armed, reads, t


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--suite", default="shop,boot")
    ap.add_argument("--out", default="out/poisoncheck")
    ap.add_argument("--mode", default="1", choices=["1", "2"])
    ap.add_argument("--soak-fields", type=int, default=1500)
    ap.add_argument("--skip-missing", action="store_true")
    ap.add_argument("--control", action="store_true", help="RG_NR_NOTE_COPY=0: expect poisoned / refused reads")
    a = ap.parse_args(argv)
    if a.skip_missing and not (ROOT / "out/fixtures/cards/zuser1025/card1").is_dir():
        print("poisoncheck: SKIP (card library / zuser1025 card missing)")
        return 77
    os.environ["RG_NR_POISON"] = a.mode
    if a.control:
        os.environ["RG_NR_NOTE_COPY"] = "0"
    out = Path(a.out).resolve()
    bad, armed_all = 0, 0
    for s in a.suite.split(","):
        ok, hits, armed, reads, t = suite(s, a, out)
        armed_all += armed
        verdict = (bool(hits) or reads > 0) if a.control else (ok and not hits and not reads)
        bad += not verdict
        print(f"poisoncheck {s}: {'PASS' if verdict else 'FAIL'} (tool {'ok' if ok else 'FAILED'}, "
              f"{len(hits)} poisoned reads logged, {reads} poisoned + refused counted, {armed} qwords poisoned)", flush=True)
        for h in hits[:10]:
            print("   ", h)
        if not ok:
            print("    tool tail:", " | ".join(t.strip().splitlines()[-3:]))
    if armed_all == 0:
        print("poisoncheck: FAIL: the poison never armed (no run reported poisoned qwords)")
        bad += 1
    print(f"poisoncheck{' (control: poisoned / refused reads expected)' if a.control else ''}: {'PASS' if not bad else 'FAIL'}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

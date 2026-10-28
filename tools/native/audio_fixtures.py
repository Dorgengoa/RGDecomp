#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Native audio on the golden route's milestones (docs/NATIVE-AUDIO.md section 3).

    python tools/native/audio_fixtures.py --nat-exe EXE_N --cmp-exe EXE_C [--only title,field,battle]
                                          [--run title=1200,field=1500,battle=900] [--out out/naudio/fx]

Needs two fixture sets (tools/fixtures/regen.py): one generated with RG_AUDIO=native
(--nat-exe) and one with RG_AUDIO=compare (--cmp-exe, a byte-appended copy of the same
exe so its set gets its own id; the audio mode is part of the saved state).  For each
milestone it starts both sets with tools/fixtures/run_from.py and runs K fields:

  compare run  RG_AUDIO_WAV (the HLE, heard) vs RG_AUDIO_NATIVE_WAV (the engine, same
               commands, same frames): sample metric (audio_compare.py, SNR / windows / lag)
  native run   RG_AUDIO=native output vs the compare run's HLE: envelope metric (levels
               per 50 ms, semitone-band spectra per second; native mode may move events by
               a few ms)
  native again the same native run a second time: run hash and WAV must be identical

One rg-game at a time.  Prints a table; exit 1 if any check fails.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import re
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
RUN_FROM = PORT / "tools" / "fixtures" / "run_from.py"
CMP = PORT / "tools" / "native" / "audio_compare.py"


def run(milestone: str, exe: str, k: int, env_extra: dict, log: Path) -> str:
    env = dict(os.environ)
    env.update(env_extra)
    env.setdefault("RG_IOP_QUIET", "1")
    cmd = [sys.executable, str(RUN_FROM), milestone, "--run", str(k), "--exe", exe, "--no-regen"]
    with log.open("w", encoding="utf-8") as f:
        subprocess.run(cmd, env=env, stdout=f, stderr=subprocess.STDOUT, check=False)
    m = re.findall(r"run_hash=([0-9a-f]+)", log.read_text(encoding="utf-8", errors="replace"))
    return m[-1] if m else "?"


def compare(args: list[str], log: Path) -> tuple[int, str]:
    p = subprocess.run([sys.executable, str(CMP)] + args, capture_output=True, text=True)
    log.write_text(p.stdout + p.stderr, encoding="utf-8")
    keep = [ln for ln in p.stdout.splitlines() if ln.startswith(("snr", "level", "semitone", "peak"))]
    return p.returncode, " | ".join(keep)


def md5(path: Path) -> str:
    return hashlib.md5(path.read_bytes()).hexdigest()[:12] if path.exists() else "-"


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--nat-exe", required=True)
    ap.add_argument("--cmp-exe", required=True)
    ap.add_argument("--only", default="title,field,battle")
    ap.add_argument("--run", default="title=1200,field=1500,battle=900")
    ap.add_argument("--out", default=str(PORT / "out" / "naudio" / "fx"))
    a = ap.parse_args(argv)
    runs = dict((kv.split("=")[0], int(kv.split("=")[1])) for kv in a.run.split(","))
    out = Path(a.out)
    bad = 0
    rows = []
    for m in a.only.split(","):
        k = runs.get(m, 600)
        d = out / m
        d.mkdir(parents=True, exist_ok=True)
        hc = run(m, a.cmp_exe, k, {"RG_AUDIO_WAV": str(d / "hle.wav"), "RG_AUDIO_NATIVE_WAV": str(d / "cmp_native.wav"),
                                   "RG_AUDIO_CMDLOG": str(d / "cmdlog.tsv")}, d / "cmp.log")
        rc1, s1 = compare([str(d / "hle.wav"), str(d / "cmp_native.wav"), "--align", "start"], d / "compare.txt")
        hn = run(m, a.nat_exe, k, {"RG_AUDIO_WAV": str(d / "native.wav")}, d / "nat.log")
        rc2, s2 = compare([str(d / "hle.wav"), str(d / "native.wav"), "--align", "start", "--envelope"], d / "envelope.txt")
        hn2 = run(m, a.nat_exe, k, {"RG_AUDIO_WAV": str(d / "native2.wav")}, d / "nat2.log")
        same = hn == hn2 and md5(d / "native.wav") == md5(d / "native2.wav")
        bad += (rc1 != 0) + (rc2 != 0) + (not same)
        rows.append((m, k, "PASS" if rc1 == 0 else "FAIL", s1, "PASS" if rc2 == 0 else "FAIL", s2,
                     f"{'same' if same else 'DIFFERENT'} {hn}", hc))
        print(f"{m} +{k}: compare {rows[-1][2]} ({s1})\n    native envelope {rows[-1][4]} ({s2})\n"
              f"    native rerun {rows[-1][6]}; compare run hash {hc}", flush=True)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

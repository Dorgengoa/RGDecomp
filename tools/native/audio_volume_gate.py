#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Per-source volume gate (docs/NATIVE-AUDIO.md "Source volumes", PLAN.md P6 ground rules).

    python tools/native/audio_volume_gate.py --exe build/p6audio-i686/rg-game.exe [--fields 31700]
           [--out out/p6audio/gate] [--config "audio.music_volume=30,audio.voice_volume=0"]...

Runs the golden route (fxlib.GOLDEN) headless once per configuration -- the Original preset
first, then each --config (default: three non-Original volume mixes) -- with $RG_HASH_LOG and
$RG_AUDIO_SRCLOG, and compares the final run hash and the hash log's audio part against the
first run.  A per-source volume is presentation only: both must be identical.  Also prints the
PCM stream source census of the first run (which stream paths played on which port and the
source each was classified as).  Exit 0 = all identical.

One rg-game process at a time (shared machine).  The saves folder of every run is a fresh
directory under --out (the route writes a memory card).
"""
from __future__ import annotations

import argparse
import collections
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fxlib  # noqa: E402

DEFAULT_CONFIGS = [
    "audio.music_volume=30,audio.effects_volume=55,audio.voice_volume=0,audio.movie_volume=70",
    "audio.music_volume=0,audio.effects_volume=0,audio.voice_volume=0,audio.movie_volume=0",
    "audio.music_volume=100,audio.effects_volume=5,audio.voice_volume=100,audio.movie_volume=0",
]
SRC = {"0": "music", "1": "effects", "2": "voice"}


def run(exe: Path, fields: int, inp: Path, sets: list[str], out: Path, tag: str) -> dict:
    d = out / tag
    if d.exists():
        shutil.rmtree(d)
    (d / "saves").mkdir(parents=True)
    env = fxlib.game_env({"RG_HASH_LOG": str(d / "hash.tsv"), "RG_AUDIO_SRCLOG": str(d / "sources.tsv"),
                          "RG_QUIET": "1"})
    cmd = [str(exe), "--headless", "--fields", str(fields), "--saves", str(d / "saves"), "--input", str(inp),
           "--preset", "original"]
    for s in sets:
        cmd += ["--set", s]
    with open(d / "port.log", "w", encoding="utf-8", errors="replace") as log:
        rc = subprocess.run(cmd, env=env, stdout=log, stderr=subprocess.STDOUT, cwd=str(PORT)).returncode
    text = (d / "port.log").read_text(encoding="utf-8", errors="replace")
    m = re.search(r"run_hash=([0-9a-f]{16})", text)
    last = None
    with open(d / "hash.tsv", encoding="utf-8") as f:
        for line in f:
            if line[:1].isdigit():
                last = line.rstrip("\n").split("\t")
    return {"tag": tag, "sets": sets, "rc": rc, "run_hash": m.group(1) if m else None,
            "field": last[0] if last else None, "audio": last[3] if last else None, "dir": d}


def census(path: Path) -> None:
    if not path.exists():
        print("  (no PCM stream sources logged)")
        return
    rows = collections.Counter()
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith("#") or not line.strip():
            continue
        frame, port, src, p = line.split("\t", 3)
        q = p.replace("\\", "/").upper()
        q = re.sub(r"\d", "n", q.split(";")[0])
        rows[(SRC.get(src, src), q)] += 1
    print("  PCM stream sources (source, path with digits as n: starts)")
    for (s, q), n in sorted(rows.items()):
        print(f"    {s:8s} {n:5d}  {q}")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--fields", type=int, default=31700)
    ap.add_argument("--input", default=str(fxlib.GOLDEN))
    ap.add_argument("--out", default=str(PORT / "out" / "p6audio" / "gate"))
    ap.add_argument("--config", action="append", help="comma list of id=value (repeatable)")
    ap.add_argument("--expect", help="run hash the first run must have (e.g. b0632cdfa80153de)")
    a = ap.parse_args()
    exe, out = Path(a.exe).resolve(), Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    configs = a.config or DEFAULT_CONFIGS
    res = [run(exe, a.fields, Path(a.input), [], out, "original")]
    for i, c in enumerate(configs):
        res.append(run(exe, a.fields, Path(a.input), [s for s in c.split(",") if s], out, f"cfg{i + 1}"))
    base = res[0]
    ok = base["run_hash"] is not None and base["rc"] == 0
    print(f"{'run':10s} {'rc':>3s} {'field':>6s} {'run_hash':16s} {'audio part':16s}  settings")
    for r in res:
        same = r["run_hash"] == base["run_hash"] and r["audio"] == base["audio"] and r["field"] == base["field"]
        ok = ok and same and r["rc"] == 0
        print(f"{r['tag']:10s} {r['rc']:3d} {r['field'] or '-':>6s} {r['run_hash'] or '-':16s} "
              f"{r['audio'] or '-':16s}  {','.join(r['sets']) or '(original)'}{'' if same else '  DIFFERS'}")
    if a.expect and base["run_hash"] != a.expect:
        print(f"first run hash {base['run_hash']} != expected {a.expect}")
        ok = False
    census(base["dir"] / "sources.tsv")
    print("PASS" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())

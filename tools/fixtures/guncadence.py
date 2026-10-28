#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Gun cadence: scripted SQUARE patterns -> gun shots per VBlank, port vs retail
(docs/BRINGUP.md "User play-test 2", item 2).

    python tools/fixtures/guncadence.py port --exe EXE [--out D]      # save2_battle2 fight
    python tools/fixtures/guncadence.py retail-input --base GOLDEN --at 24760 --out F
    python tools/fixtures/guncadence.py retail JSONL --at 24760        # probe.py --fn Shot:0x229bc0
    python tools/fixtures/guncadence.py port-log LOG --at 4900         # re-read a kept port log

Pattern (offsets from AT, VBlanks): A = taps every 10 (3 down) for 250; B = SQUARE held
for 200 from +340; C = taps every 6 (3 down) for 200 from +640.  A shot = an entry of
CharaCmdShot_229bc0 (the leader's gun command; port: RG_BREAK on its RVA from the map,
retail: probe.py --fn).  The report lists, per pattern, the shot VBlanks relative to AT,
the intervals and how many presses produced no shot.
Port: boots save2 with boot_save2_battle2.input.txt up to the fight (its SQUARE lines
replaced by the pattern at AT = 4900); --exe needs its .map beside it.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402

PORT = HERE.parents[1]
B2 = PORT / "tools" / "trace" / "goldens" / "boot_save2_battle2.input.txt"


def pattern(at: int) -> list[tuple[int, int, str]]:
    out = [(at + k, at + k + 2, "A") for k in range(0, 250, 10)]
    out.append((at + 340, at + 540, "B"))
    out += [(at + 640 + k, at + 642 + k, "C") for k in range(0, 200, 6)]
    return out


def lines(at: int) -> list[str]:
    return [f"{a} {b} SQUARE  # gun cadence {p}" for a, b, p in pattern(at)]


def report(shots: list[int], at: int, title: str) -> str:
    out = [f"== {title}: {len(shots)} shots"]
    for a0, a1, name in ((0, 330, "A taps/10"), (340, 630, "B held"), (640, 900, "C taps/6")):
        s = [v - at for v in shots if a0 <= v - at < a1]
        iv = [b - a for a, b in zip(s, s[1:])]
        presses = [a - at for a, _, p in pattern(at) if p == name[0]]
        hit = set()
        for v in s:   # the press that produced it: the last press start <= v
            cand = [p for p in presses if p <= v]
            if cand:
                hit.add(max(cand))
        out.append(f"  {name}: {len(s)} shots at {s}")
        out.append(f"    intervals {iv}")
        if name[0] != "B":
            out.append(f"    presses {len(presses)}, without a shot {len(presses) - len(hit)}: "
                       f"{[p for p in presses if p not in hit]}")
    return "\n".join(out)


def port_shots(log: str) -> list[int]:
    return [int(m.group(1)) for m in re.finditer(r"^BRK rva=\S+ vbl=(\d+)", log, re.M)]


def run_port(exe: Path, out: Path, at: int = 4900) -> str:
    out.mkdir(parents=True, exist_ok=True)
    src = [ln for ln in B2.read_text().splitlines()
           if not (re.match(r"^\d+ \d+ ", ln) and int(ln.split()[0]) >= at)]
    inp = out / "gun.input.txt"
    inp.write_text("\n".join(src + lines(at)) + "\n")
    rva = None
    for line in open(Path(exe).with_suffix(".map"), encoding="latin-1"):
        m = re.match(r"\s*0001:[0-9a-f]+\s+_CharaCmdShot_229bc0\s+([0-9a-f]{16})", line)
        if m:
            rva = int(m.group(1), 16) - 0x400000
    env = fxlib.game_env({"RG_BREAK": hex(rva), "RG_BREAK_FROM_VBL": str(at - 10), "RG_BREAK_MAX": "1000"})
    cmd = [sys.executable, str(HERE / "run_from.py"), "--boot-save", "save2", "--input", str(inp),
           "--exe", str(exe), "--fields", str(at + 900)]
    p = subprocess.run(cmd, env=env, capture_output=True, text=True, errors="replace")
    log = p.stdout + p.stderr
    (out / "port.log").write_text(log, encoding="utf-8")
    return report(port_shots(log), at, f"port {exe}")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("port")
    p.add_argument("--exe", required=True)
    p.add_argument("--out", default=str(PORT / "out" / "play2" / "gun" / "port"))
    p.add_argument("--at", type=int, default=4900)
    r = sub.add_parser("retail-input")
    r.add_argument("--base", required=True)
    r.add_argument("--at", type=int, required=True)
    r.add_argument("--out", required=True)
    j = sub.add_parser("retail")
    j.add_argument("jsonl")
    j.add_argument("--at", type=int, required=True)
    pl = sub.add_parser("port-log")
    pl.add_argument("log")
    pl.add_argument("--at", type=int, default=4900)
    a = ap.parse_args(argv)
    if a.cmd == "port":
        print(run_port(Path(a.exe).resolve(), Path(a.out), a.at))
    elif a.cmd == "retail-input":
        Path(a.out).write_text(Path(a.base).read_text().rstrip("\n") + "\n" + "\n".join(lines(a.at)) + "\n")
    elif a.cmd == "retail":
        shots = []
        for ln in open(a.jsonl):
            try:
                rec = json.loads(ln)
            except ValueError:
                continue
            if rec.get("fn") == "Shot" and rec.get("kind", "entry") == "entry":
                shots.append(rec["vbl"])
        print(report(sorted(shots), a.at, f"retail {a.jsonl}"))
    else:
        print(report(port_shots(Path(a.log).read_text(errors="replace")), a.at, a.log))
    return 0


if __name__ == "__main__":
    sys.exit(main())

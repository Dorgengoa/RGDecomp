#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""ctest driver for the save-state tests (label `fixtures`, docs/TEST-FIXTURES.md).

    fixture_test.py save      EXE WORK   power-on 120 fields, states at 60 and 120
    fixture_test.py roundtrip EXE WORK   load 60, run to 120: run_hash == the saver's at 120
    fixture_test.py cli       EXE WORK   run_from.py argument handling (--print, no game run):
        options before and after the milestone, "--" passthrough, unknown
        milestone / missing game-save fixture refused
    fixture_test.py refuse    EXE WORK KIND   KIND = corrupt | truncated | foreign
        Control (registered WILL_FAIL): exits 1 when rg-game REFUSED the bad
        state cleanly (exit 3, the expected message, nothing ran), else 0.

Needs the extracted data ($RG_DATA or <port>/data); exits 77 (skip) without it.
"""
from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fxlib  # noqa: E402

FIELDS = 120


def run(exe, work, args, tag):
    saves = Path(work) / f"saves-{tag}"
    shutil.rmtree(saves, ignore_errors=True)
    saves.mkdir(parents=True)
    env = fxlib.game_env()
    env["RG_GPU"] = os.environ.get("RG_FIXTURES_TEST_GPU", "0")   # software GS: no GPU needed
    cmd = [exe, "--headless", "--saves", str(saves), "--input", str(fxlib.GOLDEN)] + args
    r = subprocess.run(cmd, env=env, capture_output=True, text=True, encoding="utf-8", errors="replace")
    (Path(work) / f"{tag}.log").write_text(" ".join(cmd) + "\n" + r.stdout + r.stderr, encoding="utf-8")
    shutil.rmtree(saves, ignore_errors=True)
    return r


def cli(exe) -> int:
    rf = [sys.executable, str(PORT / "tools" / "fixtures" / "run_from.py")]
    bad = 0
    for args in (["battle", "--fields", "23010", "--exe", exe, "--print", "--", "--shot", "23005:x.png"],
                 ["--exe", exe, "--fields", "23010", "battle", "--print", "--", "--shot", "23005:x.png"]):
        r = subprocess.run(rf + args, capture_output=True, text=True)
        line = [x for x in r.stdout.splitlines() if x.startswith("run_from: ") and "--load-state" in x]
        ok = r.returncode == 0 and line and "--fields 23010" in line[-1] and line[-1].endswith("--shot 23005:x.png")
        print(("ok  " if ok else "BAD ") + " ".join(args))
        print("    " + (line[-1] if line else r.stdout + r.stderr))
        bad += not ok
    for args, want in ((["nosuch", "--exe", exe, "--print"], "unknown milestone"),
                       (["--boot-save", "nosuch", "--exe", exe, "--print"], "no game-save fixture")):
        r = subprocess.run(rf + args, capture_output=True, text=True)
        ok = r.returncode == 2 and want in r.stdout
        print(("ok  " if ok else "BAD ") + " ".join(args) + f" -> exit {r.returncode}")
        bad += not ok
    return 1 if bad else 0


def main() -> int:
    mode, exe, work = sys.argv[1], sys.argv[2], Path(sys.argv[3])
    if mode == "cli":
        return cli(exe)
    data = os.environ.get("RG_DATA") or str(PORT / "data")
    if not (Path(data) / "MANIFEST.tsv").exists():
        print(f"no extracted data at {data}: skipped")
        return 77
    os.environ["RG_DATA"] = data
    work.mkdir(parents=True, exist_ok=True)
    s60, s120 = work / "s60.rgstate", work / "s120.rgstate"
    if mode == "save":
        r = run(exe, work, ["--fields", str(FIELDS), "--save-state", f"60:{s60}",
                            "--save-state", f"{FIELDS}:{s120}"], "save")
        print(r.stderr[-2000:])
        ok = r.returncode == 0 and s60.exists() and s120.exists()
        if ok:
            h = fxlib.peek(s120)
            print(f"saved: s60 {s60.stat().st_size} bytes, s120 run_hash {h['run_hash']}")
        return 0 if ok else 1
    if mode == "roundtrip":
        want = fxlib.peek(s120)["run_hash"]
        r = run(exe, work, ["--fields", str(FIELDS), "--load-state", str(s60)], "roundtrip")
        m = re.search(r"run_hash=(\w+)\s*$", r.stdout, re.M)
        got = m.group(1) if m else None
        print(r.stderr[-1500:])
        print(f"loaded at 60, ran to {FIELDS}: run_hash {got}, power-on run {want}")
        return 0 if r.returncode == 0 and got == want else 1
    if mode == "refuse":
        kind = sys.argv[4]
        bad = work / f"bad-{kind}.rgstate"
        b = s60.read_bytes()
        if kind == "corrupt":
            i = len(b) // 2
            bad.write_bytes(b[:i] + bytes([b[i] ^ 0x5A]) + b[i + 1:])
            expect = r"checksum|corrupt|truncated"
        elif kind == "truncated":
            bad.write_bytes(b[: len(b) - 4096])
            expect = r"truncated|trailer|checksum"
        elif kind == "foreign":
            fxlib.rewrite_header(s60, bad, build_id="0123456789abcdef0123456789abcdef")
            expect = r"different build"
        else:
            print("unknown kind")
            return 0
        r = run(exe, work, ["--fields", str(FIELDS), "--load-state", str(bad)], f"refuse-{kind}")
        print(r.stderr[-1500:])
        refused = (r.returncode == 3 and re.search(expect, r.stderr) is not None
                   and "fields=" not in r.stdout)
        print(f"{kind}: exit {r.returncode}, {'refused cleanly' if refused else 'NOT refused as expected'}")
        return 1 if refused else 0
    print("unknown mode")
    return 2


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Build targets in a lane's build dir with the play-test toolchain environment (vcvars x86 +
LLVM + ninja, as tools/playtest/build_playtest.py; vcvars x64 for an x64 build dir), configuring
an i686 one first with the play-test configuration when it has no build.ninja yet.  THE way to
rebuild a lane's build dir incrementally (plain ninja outside vcvars links another MSVC CRT:
docs/TOOLCHAIN.md "Wrong CRT / STL"; tools/native/bx.sh wraps it for lane scripts).  Prints the errors (if any) and the last line.

    python tools/native/lane_build.py build/interpfast-i686 [TARGET ...] [--jobs 6]
    (default target rg-game)"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "playtest"))
import build_playtest as bp  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("build")
    ap.add_argument("targets", nargs="*", default=["rg-game"])
    ap.add_argument("--jobs", type=int, default=6)
    a = ap.parse_args()
    b = (ROOT / a.build).resolve()
    cache = b / "CMakeCache.txt"
    ctext = cache.read_text(encoding="utf-8", errors="replace") if cache.exists() else ""
    # x64 build dirs (tools/build.ps1 -Arch x64) need vcvars x64, everything else vcvars x86
    arch = "x64" if re.search(r"^CMAKE_TOOLCHAIN_FILE:\w+=.*toolchain-x64", ctext, re.M) else "x86"
    env = bp.vc_env(arch)
    if arch == "x86" and not (b / "build.ninja").exists():
        rc = subprocess.run([bp.CMAKE, "-S", str(ROOT), "-B", str(b), "-G", "Ninja"] + bp.CONFIG, env=env).returncode
        if rc:
            return rc
    p = subprocess.run([bp.CMAKE, "--build", str(b), "-j", str(a.jobs), "--target"] + a.targets, env=env,
                       capture_output=True, text=True, errors="replace")
    out = p.stdout + p.stderr
    errs = [l for l in out.splitlines() if re.search(r"\berror\b|FAILED", l)]
    for l in errs[:40]:
        print(l)
    lines = [l for l in out.splitlines() if l.strip()]
    print(lines[-1] if lines else "", f"\nexit {p.returncode}")
    return p.returncode


if __name__ == "__main__":
    sys.exit(main())

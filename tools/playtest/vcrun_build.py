#!/usr/bin/env python3
"""Run cmake --build (or ctest) on a build tree inside the x86 MSVC environment that
tools/playtest/build_playtest.py uses (vcvarsall x86 + the repo's LLVM / Ninja).

  python tools/playtest/vcrun_build.py build/p6pad-i686 [--target T ...] [-j 4]
  python tools/playtest/vcrun_build.py build/p6pad-i686 --ctest -- -j2 -L input
"""
import argparse
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_playtest as bp  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("build")
    ap.add_argument("--target", action="append", default=[])
    ap.add_argument("-j", type=int, default=4)
    ap.add_argument("--ctest", action="store_true", help="run ctest instead; extra args after --")
    a, rest = ap.parse_known_args()
    env = bp.vc_env()
    rest = [x for x in rest if x != "--"]
    if a.ctest:
        ctest = str(Path(bp.CMAKE).with_name("ctest.exe"))
        cmd = [ctest, "--test-dir", a.build] + rest
    else:
        cmd = [bp.CMAKE, "--build", a.build, "-j", str(a.j)]
        for t in a.target:
            cmd += ["--target", t]
        cmd += rest
    return subprocess.run(cmd, cwd=bp.ROOT, env=env).returncode


if __name__ == "__main__":
    sys.exit(main())

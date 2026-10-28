#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Run a command with the x86 Visual C++ environment build_playtest.py uses (vcvarsall x86) and
its cmake / ninja on PATH: full builds and ctest of a play-test build dir from an agent shell.

    python tools/playtest/vcrun.py BUILD_DIR -- cmake --build . -j 4
    python tools/playtest/vcrun.py BUILD_DIR -- ctest -j2 --output-on-failure
    python tools/playtest/vcrun.py BUILD_DIR -- ctest -L settings

Runs in BUILD_DIR; `cmake` / `ctest` / `ninja` resolve to build_playtest.py's CMAKE / NINJA.
Exit code = the command's.
"""
import os
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_playtest as bp  # noqa: E402


def main(argv=None) -> int:
    argv = sys.argv[1:] if argv is None else argv
    if len(argv) < 3 or argv[1] != "--":
        print(__doc__)
        return 2
    bdir, cmd = Path(argv[0]).resolve(), argv[2:]
    env = bp.vc_env()
    tools = {"cmake": bp.CMAKE, "ctest": str(Path(bp.CMAKE).with_name("ctest.exe")), "ninja": bp.NINJA}
    cmd[0] = tools.get(cmd[0], cmd[0])
    env["PATH"] = os.pathsep.join([str(Path(bp.CMAKE).parent), str(Path(bp.NINJA).parent), env.get("PATH", "")])
    return subprocess.run(cmd, cwd=bdir, env=env).returncode


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compiler launcher for a measurement tree (docs/PERF-3D.md "EE game code at -O2"):
    cmake ... "-DCMAKE_C_COMPILER_LAUNCHER=python;tools/perf3d/o2wrap.py"
              "-DCMAKE_CXX_COMPILER_LAUNCHER=python;tools/perf3d/o2wrap.py"
Runs the compiler command unchanged, except that for sources under game/
(the decompiled game) the optimisation level -O1 (PLAN.md D2) becomes
$RG_GAME_OPT (default -O2).  Never used by the normal build."""
import os, subprocess, sys

cmd = sys.argv[1:]
opt = os.environ.get("RG_GAME_OPT", "-O2")
if any(("/game/" in a.replace("\\", "/") or "/game-gen/" in a.replace("\\", "/")) and
       a.endswith((".c", ".cpp", ".cc")) for a in cmd):
    cmd = [opt if a == "-O1" else a for a in cmd]
sys.exit(subprocess.call(cmd))

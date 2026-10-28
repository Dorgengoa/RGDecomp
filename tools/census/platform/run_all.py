#!/usr/bin/env python3
"""Run every platform census (PLAN.md step 2b) in dependency order.

  python tools/census/platform/run_all.py [--rebuild]

--rebuild drops out/platform_cache.pkl (snapshot facts + retail call graph)
and rebuilds it from the pinned commit in common.PIN.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

if "--rebuild" in sys.argv:
    C.cached(rebuild=True)
import sdk_surface, ee_syscalls, sif_rpc, gs, vu1, misc  # noqa: E402,E401

for mod in (sdk_surface, ee_syscalls, sif_rpc, gs, vu1, misc):
    print(f"== {mod.__name__}")
    mod.main([]) if mod is sdk_surface else mod.main()

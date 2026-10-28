#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Syntax-check a trial ingest tree against a build dir's compile commands,
before paying for the real rebuild (docs/BRINGUP.md 2026-10-18 b).

    python tools/bringup/trial_syntax.py --trial out/x/game-trial [--build-dir build/battle-i686]
        [--all] [-j 4] [FILE...]

Each game file that differs between game/ and the trial tree (or FILE..., or
every unit with --all) is compiled with its own command from
<build-dir>/compile_commands.json, `-fsyntax-only`, the trial tree in place of
game/ (source and include path, so the trial game_protos.h is the one seen).
An override (overrides/<path>) replaces its game file as in the build.
Prints the files that fail with their first errors; exit 1 if any fails.
"""
from __future__ import annotations

import argparse
import json
import os
import shlex
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--trial", type=Path, required=True)
    ap.add_argument("--build-dir", type=Path, default=PORT / "build" / "battle-i686")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-j", type=int, default=4)
    ap.add_argument("files", nargs="*")
    a = ap.parse_args()
    trial = a.trial.resolve()
    game = PORT / "game"
    cc = {}
    for e in json.loads((a.build_dir / "compile_commands.json").read_text(encoding="utf-8")):
        cc[os.path.normcase(os.path.normpath(e["file"]))] = e
    if a.files:
        rels = a.files
    else:
        rels = []
        for p in trial.rglob("*"):
            if p.suffix not in (".c", ".cpp") or not p.is_file():
                continue
            rel = p.relative_to(trial).as_posix()
            g = game / rel
            if a.all or not g.exists() or g.read_bytes() != p.read_bytes():
                rels.append(rel)
    try:
        import relink
        env = relink.vc_env()
    except Exception:          # noqa: BLE001 -- clang finds the SDK itself on most setups
        env = dict(os.environ)
    tg = str(trial).replace("\\", "/")
    gg = str(game).replace("\\", "/")

    def one(rel):
        e = cc.get(os.path.normcase(os.path.normpath(str(game / rel))))
        if e is None:      # an overridden file compiles from overrides/<rel>
            e = cc.get(os.path.normcase(os.path.normpath(str(PORT / "overrides" / rel))))
        if e is None:
            return rel, None
        src = PORT / "overrides" / rel
        if not src.exists():
            src = trial / rel
        args = shlex.split(e["command"], posix=False)
        oi = args.index("-o")
        del args[oi:oi + 2]
        args = [x.replace(gg, tg).replace(gg.replace("/", "\\"), tg) for x in args]
        args[-1] = str(src)
        args.insert(1, "-fsyntax-only")
        r = subprocess.run(args, cwd=e["directory"], env=env, capture_output=True, text=True,
                           errors="replace")
        if r.returncode:
            errs = [ln for ln in r.stderr.splitlines() if "error" in ln][:4]
            return rel, "\n    ".join(errs) or r.stderr[:400]
        return rel, ""

    with ThreadPoolExecutor(a.j) as ex:
        res = list(ex.map(one, rels))
    bad = [(r, m) for r, m in res if m]
    skip = [r for r, m in res if m is None]
    for r, m in bad:
        print(f"FAIL {r}\n    {m}")
    print(f"{len(res)} files: {len(res) - len(bad) - len(skip)} ok, {len(bad)} failed, "
          f"{len(skip)} without a compile command")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

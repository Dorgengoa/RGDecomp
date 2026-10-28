#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Land re-timed goldens / milestones / cards prepared in a staging copy of the tree, in one
quick step (other lanes read the goldens and cards while a re-time is being prepared).

    python tools/fixtures/stage_swap.py --stage out/eefpu/stage --backup out/eefpu/swap_backup \
        --file tools/trace/goldens/newgame_save2.input.txt --file tools/fixtures/fxlib.py \
        --dir out/fixtures/cards/save2 [--dir ...] [--dry-run]

Staging = a copy of the needed parts of the tree under STAGE with the same relative paths
(tools/fixtures and tools/trace copied, out/fixtures/cards copied, a `data` junction to the
real data, RG_DATA set); the fixture tools resolve everything from their own location, so
they run there unchanged (docs/TEST-FIXTURES.md "Re-timing the route").
Every target is first copied next to itself (".swapnew"), then all are switched with
os.replace / two renames per directory, so the switch takes milliseconds; the previous
versions go to BACKUP (same relative paths).  Prints the UTC time of the switch.
"""
from __future__ import annotations

import argparse
import datetime
import os
import shutil
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--stage", required=True)
    ap.add_argument("--backup", required=True)
    ap.add_argument("--file", action="append", default=[])
    ap.add_argument("--dir", action="append", default=[])
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args(argv)
    stage, backup = Path(a.stage).resolve(), Path(a.backup).resolve()
    items = [(r, False) for r in a.file] + [(r, True) for r in a.dir]
    for rel, is_dir in items:
        if not (stage / rel).exists():
            sys.exit(f"stage_swap: missing in stage: {rel}")
    if a.dry_run:
        for rel, is_dir in items:
            print(("dir  " if is_dir else "file ") + rel)
        return 0
    # 1. copy the new versions next to the targets
    for rel, is_dir in items:
        new = PORT / (rel + ".swapnew")
        new.parent.mkdir(parents=True, exist_ok=True)
        if is_dir:
            if new.exists():
                shutil.rmtree(new)
            shutil.copytree(stage / rel, new)
        else:
            shutil.copy2(stage / rel, new)
    # 2. back up the old versions (copies, so the targets never disappear for files)
    for rel, is_dir in items:
        dst, bak = PORT / rel, backup / rel
        bak.parent.mkdir(parents=True, exist_ok=True)
        if dst.exists() and not is_dir:
            shutil.copy2(dst, bak)
    # 3. switch
    t = datetime.datetime.now(datetime.timezone.utc)
    for rel, is_dir in items:
        dst, new, bak = PORT / rel, PORT / (rel + ".swapnew"), backup / rel
        if is_dir:
            if bak.exists():
                shutil.rmtree(bak)
            if dst.exists():
                os.replace(dst, bak) if dst.drive == bak.drive else shutil.move(str(dst), str(bak))
            os.replace(new, dst)
        else:
            os.replace(new, dst)
    t2 = datetime.datetime.now(datetime.timezone.utc)
    print(f"stage_swap: {len(items)} items switched {t.isoformat(timespec='seconds')} "
          f"({(t2 - t).total_seconds() * 1000:.0f} ms); local {datetime.datetime.now():%Y-%m-%d %H:%M:%S}; "
          f"backup {backup}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

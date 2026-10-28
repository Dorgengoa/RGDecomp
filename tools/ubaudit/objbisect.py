#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Find the game object(s) whose build-B version changes a run (docs/UB-AUDIT.md).

    python tools/ubaudit/objbisect.py --good build/o2-i686/o1 --bad build/o2-i686/o2 \
        --out out/ubaudit/bisect --fields 8300 --ref out/fixtures/<o1-set>/field+300.poweron.png
        [--filter SUBSTR] [--hash-field run_hash]

Both build dirs must hold the same tree built with different flags (e.g. -O1 /
-O2).  rg-game is relinked from GOOD's link line (tools/fixtures/relink.py
link_block) with a subset of the game objects (CMakeFiles/rg_game_*.dir/...)
taken from BAD, then run headless from power-on on the route input to
--fields with a --shot there.  A run is GOOD when the shot's pixels equal
--ref's (or, with --run-hash H, when the exit run hash is H).  Bisection
halves the candidate set until one object is left (assumes one culprit; with
several it finds one of them -- rerun with --exclude to find the next).
Links take ~1 min, runs ~20-30 s; ~15 rounds for 25k objects.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import relink  # noqa: E402


def pix_hash(png: Path) -> str:
    from PIL import Image
    return hashlib.sha256(Image.open(png).convert("RGB").tobytes()).hexdigest()[:16]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--good", required=True)
    ap.add_argument("--bad", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--fields", type=int, required=True)
    ap.add_argument("--ref", help="PNG of the good run's display at --fields")
    ap.add_argument("--run-hash", help="the good run's exit run hash instead of --ref")
    ap.add_argument("--filter", default="", help="only objects whose path contains this")
    ap.add_argument("--exclude", action="append", default=[])
    ap.add_argument("--link-only", action="store_true",
                    help="just link OUT/rg-game.exe with every candidate object from BAD (a "
                         "same-host-code comparison exe) and stop")
    a = ap.parse_args()
    good, bad, out = Path(a.good).resolve(), Path(a.bad).resolve(), Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    env = relink.vc_env()
    ins, var = relink.link_block(good)
    game = [k for k, t in enumerate(ins) if "CMakeFiles/rg_game_" in t.replace("\\", "/")
            and a.filter in t.replace("\\", "/") and not any(x in t for x in a.exclude)]
    print(f"objbisect: {len(game)} candidate objects")
    ref = pix_hash(Path(a.ref)) if a.ref else None
    rnd = [0]

    def link(subset: list[int]) -> Path:
        s = set(subset)
        mixed = [(bad / t).as_posix() if k in s else t for k, t in enumerate(ins)]
        rsp = out / "mixed.rsp"
        rsp.write_text(" ".join(f'"{t}"' if " " in t else t for t in mixed) + " " +
                       var.get("LINK_PATH", "") + " " + var.get("LINK_LIBRARIES", ""), encoding="utf-8")
        exe = out / "rg-game.exe"
        cmd = (f'../tools\\llvm\\bin\\clang++.exe --target=i686-pc-windows-msvc -nostartfiles -nostdlib '
               f'{var.get("FLAGS", "")} {var.get("LINK_FLAGS", "")} @{rsp.as_posix()} -o {exe.as_posix()} '
               f'-Xlinker /MANIFEST:EMBED -Xlinker /implib:{out / "rg-game.lib"} -Xlinker /pdb:{out / "rg-game.pdb"}')
        lr = subprocess.run(cmd, cwd=good, env=env, shell=True, capture_output=True, text=True,
                            errors="replace")
        if lr.returncode:
            raise SystemExit("objbisect: link failed\n" + (lr.stdout + lr.stderr)[-3000:])
        return exe

    def run(subset: list[int]) -> bool:
        rnd[0] += 1
        exe = link(subset)
        saves = out / "saves"
        saves.mkdir(exist_ok=True)
        for f in saves.iterdir():
            if f.is_file():
                f.unlink()
        shot = out / "shot.png"
        if shot.exists():
            shot.unlink()
        genv = dict(os.environ, RG_DATA=str(PORT / "data"), RG_GPU="hw")
        r = subprocess.run([str(exe), "--headless", "--fields", str(a.fields), "--saves", str(saves),
                            "--input", str(PORT / "tools/trace/goldens/newgame_save2.input.txt"),
                            "--shot", f"{a.fields}:{shot}"], env=genv, capture_output=True, text=True,
                           errors="replace")
        rh = next((l.split("=")[1].strip() for l in r.stdout.splitlines() + r.stderr.splitlines()
                   if "run_hash=" in l), "?")
        ok = (pix_hash(shot) == ref) if ref else (rh == a.run_hash)
        print(f"  round {rnd[0]}: {len(subset)} objects from BAD -> {'good' if ok else 'BAD'} (run_hash {rh})",
              flush=True)
        return ok

    if a.link_only:
        link(game)
        print(f"objbisect: linked {out / 'rg-game.exe'} with {len(game)} objects from BAD")
        return 0
    if run([]) is False:
        raise SystemExit("objbisect: the all-GOOD link is not good (reference wrong?)")
    if run(game):
        raise SystemExit("objbisect: the all-BAD set of candidates is good (culprit outside --filter?)")
    cand = game
    while len(cand) > 1:
        half = cand[:len(cand) // 2]
        cand = cand[len(cand) // 2:] if run(half) else half
    print(f"objbisect: culprit {ins[cand[0]]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

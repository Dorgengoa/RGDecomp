#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Play-test wide-layout gate: the widescreen screens of a new play-test exe vs the PREVIOUS one.

Added 2026-11-01 (lane pt1101b) after play-test 1101a shipped a 16:9 menu / HUD layout regression
(out/menuret/REPORT.md: an override rewrite dropped the rg_layout_task brackets, so the menu's
packets reached the layout with task=0 and were laid out as scene, not as menu) that every other
gate missed: they all run at 4:3 or compare against a golden that is not laid out.

    python tools/playtest/widegate.py --exe NEW.exe --prev out/playtest/rg-game-1031a.exe --out DIR
           [--aspects 16:9,21:9] [--ui keep] [--only menu,item,itemgrid] [--explain FILE]
           [--set graphics.anisotropic=off ...]

Runs, per exe and aspect, with --set graphics.ui_layout=UI and RG_LAYOUT_LOG:
  s3/   tools/wide/stage3shots.py (every scenario: menus, save, item, shop, pause, battle,
        factory, insect, world map, allies, equip, strategy, menu rows, revelation, battle
        menu, Dorgenark)
  s2/   tools/wide/stage2shots.py --only battle2 (results / map help / field at the stage 2 fields)
  ig/   the item-grid route of tools/playtest/menuret.sh (card zuser1031, item_grid_cursor, 17 shots)
The previous exe's runs are cached in out/widegate/cache/<sha256[:16] of the exe>/ (reused when
complete).  The two exes run side by side (rg_slots limits the machine to two rg-game anyway).

Per shot: differing pixels of the presented (-view) and the native PNG; per shot field, from the
layout log: `cover` (the frame line), menu packets total / task=0 (no rg_layout_task bracket) /
suppressed; per run: run hash of both exes.
FAIL (exit 1) when any of these is not explained:
  - a shot differs (px > 0) or is missing,
  - LAYOUT COVERAGE changed at a shot field: cover differs, or the tasked share of the packets
    (task != 0) drops by more than 2 points, or the task=0 count grows by > 5 % and > 8 packets,
  - the run hashes of the two exes differ (expected equal: layout is presentation only).
--explain FILE: lines `GLOB  reason` (GLOB over `run/state` or `run/state@aspect`, e.g.
`ig/t0*  item models animate since 1101a (f32args dt fix)`).  An explained line covers px
diffs only; a coverage change needs `layout:` at the start of the reason.  Report:
OUT/widegate.txt (+ .tsv); sheets of the differing shots: OUT/diff_<run>_<state>_<aspect>.png
(prev | new | diff mask) for the worst 12.
--set K=V (repeatable, lane glare169 11-01): extra settings for BOTH exes, e.g.
`--set graphics.anisotropic=off` to take the native anisotropic filter (p6gfx, default 16x, active
in every exe from p6gfx on; 1031a and older ignored it) out of a compare against a pre-11-01 exe.
A run with --set is cached apart (cache/<sha16>-<hash of the sets>/).
"""
from __future__ import annotations

import argparse
import fnmatch
import hashlib
import os
import re
import shutil
import subprocess
import sys
import threading
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WIDE = ROOT / "tools" / "wide"
sys.path.insert(0, str(WIDE))
import stage2shots  # noqa: E402
import stage3shots  # noqa: E402

RUN_FROM = ROOT / "tools" / "fixtures" / "run_from.py"
GOLD = ROOT / "tools" / "trace" / "goldens"
ASPECTS = {"4:3": "4x3", "16:9": "16x9", "16:10": "16x10", "21:9": "21x9", "32:9": "32x9"}
IG_OFFS = [10, 20, 30, 45, 60, 90, 150, 250, 310, 320, 330, 345, 360, 390, 450, 550, 1267]
IG_BASE = 4733   # port TRIANGLE (menuret.sh)


def sha16(p):
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()[:16]


def plan(tmp: Path):
    """{run: {state: field}} for the three groups; run names prefixed by group"""
    tmp.mkdir(parents=True, exist_ok=True)
    p = {}
    for name, _card, _s, _end, shots in stage3shots.scenarios(tmp):
        p[f"s3/{name}"] = shots
    for name, _s, _end, shots in stage2shots.scripts(tmp):
        if name == "battle2":
            p[f"s2/{name}"] = shots
    p["ig/itemgrid"] = {f"t{o:04d}": IG_BASE + o for o in IG_OFFS}
    return p


SETS: list = []   # --set K=V for both exes (main)


def run_exe(exe: Path, d: Path, aspects, ui, only, logf):
    """all runs of one exe into d (s3/, s2/, ig/); d/DONE marks a complete set"""
    if (d / "DONE").exists() and (d / "DONE").read_text().strip() == f"{','.join(aspects)} {ui}":
        print(f"widegate: cached {d}", file=logf, flush=True)
        return
    extra = ["--extra", "--set", f"graphics.ui_layout={ui}"] + [x for kv in SETS for x in ("--set", kv)]
    asp = ",".join(aspects)
    for g in ("s3", "s2"):
        (d / g).mkdir(parents=True, exist_ok=True)
    sel = lambda g, names: [n for n in names if not only or f"{g}/{n}" in only or n in only]
    s3n = sel("s3", [n for n, *_ in stage3shots.scenarios(d / "s3")])
    if s3n:
        subprocess.run([sys.executable, str(WIDE / "stage3shots.py"), "--exe", str(exe), "--out",
                        str(d / "s3"), "--aspects", asp, "--log", "--only", ",".join(s3n)] + extra,
                       stdout=logf, stderr=subprocess.STDOUT)
    if sel("s2", ["battle2"]):
        subprocess.run([sys.executable, str(WIDE / "stage2shots.py"), "--exe", str(exe), "--out",
                        str(d / "s2"), "--aspects", asp, "--log", "--only", "battle2"] + extra,
                       stdout=logf, stderr=subprocess.STDOUT)
    if sel("ig", ["itemgrid"]):
        ig = d / "ig"
        ig.mkdir(parents=True, exist_ok=True)
        for a in aspects:
            tag = ASPECTS[a]
            cmd = [sys.executable, str(RUN_FROM), "--boot-save", "zuser1031", "--input",
                   str(GOLD / "item_grid_cursor.input.txt"), "--fields", str(IG_BASE + IG_OFFS[-1] + 10),
                   "--exe", str(exe), "--"] + stage3shots.aspect_args(a) + \
                ["--set", f"graphics.ui_layout={ui}"] + [x for kv in SETS for x in ("--set", kv)]
            for o in IG_OFFS:
                cmd += ["--shot", f"{IG_BASE + o}:{ig / f't{o:04d}_{tag}.png'}"]
            env = dict(os.environ, RG_LAYOUT_LOG=str(ig / f"itemgrid_{tag}.layout.log"))
            p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env)
            (ig / f"itemgrid_{tag}.log").write_text(p.stdout + p.stderr, encoding="utf-8")
            print(f"  itemgrid {a} exit {p.returncode}", file=logf, flush=True)
    if not only:
        (d / "DONE").write_text(f"{asp} {ui}\n")


def layout_stats(log: Path, fields):
    """{field: (cover, packets, task0, suppressed_pk)} at the given fields"""
    want = set(fields)
    st = {f: ["?", 0, 0, 0] for f in want}
    if not log.exists():
        return {}
    with open(log, "rb") as fh:
        for raw in fh:
            sp = raw.find(b" ")
            if sp <= 0:
                continue
            try:
                f = int(raw[:sp])
            except ValueError:
                continue
            if f not in want:
                continue
            if raw.startswith(b"frame", sp + 1):
                m = re.search(rb"cover=(\S+)", raw)
                st[f][0] = m.group(1).decode() if m else "?"
            elif raw.startswith(b"pk task=", sp + 1):
                st[f][1] += 1
                if raw.startswith(b"00000000", sp + 9):
                    st[f][2] += 1
                if b"suppress" in raw:
                    st[f][3] += 1
    return {f: tuple(v) for f, v in st.items()}


def pxdiff(a: Path, b: Path):
    from PIL import Image
    import numpy as np
    if not a.exists() or not b.exists():
        return None, None
    x = np.asarray(Image.open(a).convert("RGB"))
    y = np.asarray(Image.open(b).convert("RGB"))
    if x.shape != y.shape:
        return x.shape[0] * x.shape[1], None
    m = (x != y).any(axis=2)
    return int(m.sum()), m


def run_hash(log: Path):
    if not log.exists():
        return "?"
    h = re.findall(r"run_hash=(\w+)", log.read_text(errors="replace"))
    return h[-1] if h else "?"


def sheet(prev: Path, new: Path, mask, out: Path):
    from PIL import Image
    import numpy as np
    a, b = Image.open(prev).convert("RGB"), Image.open(new).convert("RGB")
    w, h = a.size
    s = Image.new("RGB", (w * 3, h))
    s.paste(a, (0, 0))
    s.paste(b, (w, 0))
    s.paste(Image.fromarray((mask * 255).astype(np.uint8)).convert("RGB"), (2 * w, 0))
    if w > 1280:
        s = s.resize((s.width * 1280 // w, s.height * 1280 // w))
    s.save(out)


def load_explain(path):
    rows = []
    if path:
        for ln in Path(path).read_text(encoding="utf-8").splitlines():
            ln = ln.strip()
            if ln and not ln.startswith("#"):
                g, _, why = ln.partition(" ")
                rows.append((g, why.strip()))
    return rows


def explained(rows, key, layout=False):
    for g, why in rows:
        if fnmatch.fnmatch(key, g) or fnmatch.fnmatch(key.split("@")[0], g):
            if not layout or why.startswith("layout:"):
                return why
    return None


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--prev", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--aspects", default="16:9,21:9")
    ap.add_argument("--ui", default="keep")
    ap.add_argument("--only", help="comma list: run names (menu,item,itemgrid,battle2) or group/run")
    ap.add_argument("--explain")
    ap.add_argument("--set", action="append", default=[], metavar="K=V",
                    help="extra setting for both exes (repeatable), e.g. graphics.anisotropic=off")
    ap.add_argument("--compare-only", action="store_true", help="do not run, compare existing dirs")
    ap.add_argument("--warm", action="store_true",
                    help="only fill the --prev cache (e.g. while the new exe still builds; --exe ignored)")
    a = ap.parse_args(argv)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    exe, prev = Path(a.exe).resolve(), Path(a.prev).resolve()
    aspects = a.aspects.split(",")
    only = set(a.only.split(",")) if a.only else None
    cache = ROOT / "out" / "widegate" / "cache"
    SETS[:] = a.set
    sfx = ("-" + hashlib.sha256(" ".join(sorted(a.set)).encode()).hexdigest()[:8]) if a.set else ""
    dnew = out / "new" if only else cache / (sha16(exe) + sfx)   # every exe's full set is cached by hash
    dprev = cache / (sha16(prev) + sfx)
    done = dprev / "DONE"
    if only and not (done.exists() and set(aspects) <= set(done.read_text().split()[0].split(","))
                     and done.read_text().split()[1] == a.ui):
        dprev = out / "prev"   # a partial run: not the cache (unless the cache has these aspects)
    if a.warm:
        with open(out / "run_prev.log", "a") as lf:
            run_exe(prev, dprev, aspects, a.ui, None, lf)
        (dprev / "EXE.txt").write_text(f"{prev}\n")
        print(f"widegate: cache {dprev} filled")
        return 0
    if not a.compare_only:
        if dnew == out / "new" and dnew.exists():
            shutil.rmtree(dnew)
        logs = [open(out / "run_new.log", "w"), open(out / "run_prev.log", "a")]
        th = [threading.Thread(target=run_exe, args=(exe, dnew, aspects, a.ui, only, logs[0]))]
        if dnew != out / "new":
            dnew.mkdir(parents=True, exist_ok=True)
            (dnew / "EXE.txt").write_text(str(exe) + chr(10))
        if dprev == out / "prev" or not done.exists():
            th.append(threading.Thread(target=run_exe, args=(prev, dprev, aspects, a.ui,
                                                              only if dprev == out / "prev" else None, logs[1])))
        for t in th:
            t.start()
        for t in th:
            t.join()
        for f in logs:
            f.close()
        if dprev != out / "prev":
            (dprev / "EXE.txt").write_text(f"{prev}\n")
    ex = load_explain(a.explain)
    p = plan(out / "tmp")
    rows, fails, diffs = [], [], []
    for run, shots in p.items():
        if only and not (run in only or run.split("/")[1] in only):
            continue
        grp, name = run.split("/")
        for asp in aspects:
            tag = ASPECTS[asp]
            lg = f"{name}_{tag}.layout.log"
            ls_p = layout_stats(dprev / grp / lg, shots.values())
            ls_n = layout_stats(dnew / grp / lg, shots.values())
            hp, hn = run_hash(dprev / grp / f"{name}_{tag}.log"), run_hash(dnew / grp / f"{name}_{tag}.log")
            if hp != hn or hp == "?":
                why = explained(ex, f"{run}/hash@{asp}")
                rows.append((run, "hash", asp, "-", "-", f"{hp} vs {hn}", why or ""))
                if not why:
                    fails.append(f"{run}@{asp}: run hash {hp} vs {hn}")
            for st, f in shots.items():
                key = f"{run}/{st}@{asp}"
                pv, mv = pxdiff(dprev / grp / f"{st}_{tag}-view.png", dnew / grp / f"{st}_{tag}-view.png")
                pn, _ = pxdiff(dprev / grp / f"{st}_{tag}.png", dnew / grp / f"{st}_{tag}.png")
                cp, cn = ls_p.get(f), ls_n.get(f)
                lay = "no log"
                cov_bad = False
                if cp and cn:
                    sh_p = 1 - cp[2] / cp[1] if cp[1] else 1.0
                    sh_n = 1 - cn[2] / cn[1] if cn[1] else 1.0
                    cov_bad = (cp[0] != cn[0] or sh_n < sh_p - 0.02
                               or (cn[2] > cp[2] * 1.05 and cn[2] - cp[2] > 8))
                    lay = (f"cover {cp[0]}->{cn[0]} pk {cp[1]}->{cn[1]} task0 {cp[2]}->{cn[2]} "
                           f"tasked {100 * sh_p:.0f}%->{100 * sh_n:.0f}%")
                why = ""
                if pv is None or pn is None:
                    w = explained(ex, key)
                    why = w or ""
                    if not w:
                        fails.append(f"{key}: shot missing")
                elif pv or pn:
                    diffs.append((pv, run, st, asp, mv, grp, tag))
                    w = explained(ex, key)
                    why = w or ""
                    if not w:
                        fails.append(f"{key}: {pv} px (view) / {pn} px (native) differ")
                if cov_bad:
                    w = explained(ex, key, layout=True)
                    why = (why + "; " if why else "") + (w or "")
                    if not w:
                        fails.append(f"{key}: LAYOUT COVERAGE {lay}")
                rows.append((run, st, asp, "-" if pv is None else pv, "-" if pn is None else pn,
                             lay + (" COVERAGE-CHANGED" if cov_bad else ""), why))
    diffs.sort(key=lambda r: -r[0])
    for pv, run, st, asp, mv, grp, tag in diffs[:12]:
        if mv is not None:
            sheet(dprev / grp / f"{st}_{tag}-view.png", dnew / grp / f"{st}_{tag}-view.png", mv,
                  out / f"diff_{run.replace('/', '_')}_{st}_{tag}.png")
    with open(out / "widegate.tsv", "w", encoding="utf-8") as f:
        f.write("run\tstate\taspect\tpx_view\tpx_native\tlayout\texplained\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")
    shots = [r for r in rows if r[1] != "hash"]
    nd = sum(1 for r in shots if r[3] not in (0, "-"))
    lines = [f"widegate: {exe.name} vs {prev.name} ({sha16(prev)}), aspects {a.aspects}, ui_layout {a.ui}",
             f"shots {len(shots)}, differing {nd}, coverage changed "
             f"{sum('COVERAGE-CHANGED' in r[5] for r in shots)}, unexplained {len(fails)}"]
    for r in rows:
        lines.append(f"  {r[0]:14s} {r[1]:11s} {r[2]:5s} px {str(r[3]):>8s} / {str(r[4]):>8s}  {r[5]}"
                     + (f"  [explained: {r[6]}]" if r[6] else ""))
    lines += [f"FAIL {x}" for x in fails]
    lines.append(f"widegate: {'PASS' if not fails else 'FAIL'} ({len(fails)} unexplained)")
    (out / "widegate.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("\n".join(lines[:2] + lines[-min(len(fails), 30) - 1:]))
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Transition-stutter report (docs/PERF-3D.md "Transition stutter").

    python tools/perf3d/stutter.py report DIR [--win NAME:A-B ...] [--top N] [--thr MS]
    python tools/perf3d/stutter.py run DIR --exe EXE (--state F.rgstate | --boot-save NAME)
                                   --fields N [--input SCRIPT] [--headless] [--env K=V ...]
                                   [-- extra rg-game args]
    python tools/perf3d/stutter.py compare DIR_A DIR_B [--win ...]

`run` starts rg-game (windowed by default, RG_GPU=hw, the shipping defaults) with
RG_FIELD_TIMES=DIR/times.tsv, RG_FIELD_STATS=DIR/stats.tsv and RG_STATUS_EVERY=1 (game mode /
overlay per field in DIR/run.log), then writes DIR/report.md.  `report` re-reads a run.

What it reports, per window (default: transitions found from the STATUS lines, game mode or
overlay changes, -30 .. +120 fields, plus the whole run):
  * presented frames: interval between presents (what the player sees), the work in it
    (interval minus the pacing sleep), frames over --thr ms (default 50) and over 2x the
    window median;
  * the worst --top frames with every millisecond attributed: EE step (game code + render
    submission + waits for the GS worker inside the step), sync (waits for the worker before
    presenting), present, pump, audio, post, out (between fields), pace (sleep), and the
    counters of $RG_FIELD_STATS summed over the frame's fields: process / main-thread CPU,
    page faults, private bytes, file reads (count, KB, ms), sound banks, GS traffic, GPU
    target creates / loads / write-backs, upload / download KB, read-back waits, flushes,
    texture decodes, native-renderer mesh uploads and decodes, and per-thread CPU;
  * a cause ranking: ms per category summed over the frames above the threshold minus the
    window's median frame (what made them long).

Windows: --win battle_start:22840-22990 (absolute fields).  Also loads $RG_FIELD_TIMES files
of older exes (no stats file: the counters are blank)."""
from __future__ import annotations

import argparse
import os
import re
import statistics
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

TIME_COLS = ["wall", "step", "read", "present", "gs_wait", "pace", "sync", "pump", "audio", "post", "out"]


def load_times(p: Path):
    rows = {}
    for ln in open(p):
        if not ln[:1].isdigit():
            continue
        f = ln.rstrip("\n").split("\t")
        v = [float(x) for x in f[1:]]
        v += [0.0] * (len(TIME_COLS) - len(v))
        rows[int(f[0])] = dict(zip(TIME_COLS, v))
    return rows


def load_stats(p: Path):
    rows, cols, base = {}, None, 0
    if not p.exists():
        return rows, [], 0
    for ln in open(p):
        if ln.startswith("# image_base="):
            base = int(ln.split("=")[1], 16)
            continue
        if ln.startswith("# field"):
            cols = ln[2:].rstrip("\n").split("\t")
            continue
        if not ln[:1].isdigit() or not cols:
            continue
        f = ln.rstrip("\n").split("\t")
        d = {}
        for c, x in zip(cols[1:-1], f[1:-1]):
            d[c] = float(x)
        thr = {}
        if len(f) == len(cols) and f[-1] != "-":
            for t in f[-1].split(","):
                a = t.split(":")
                if len(a) == 3:
                    key = a[0] + ":" + a[1]
                    ms = a[2]
                    main = ms.endswith("m")
                    thr[key] = (float(ms.rstrip("m")), main)
        d["_thr"] = thr
        rows[int(f[0])] = d
    return rows, (cols[1:-1] if cols else []), base


def load_status(p: Path):
    st = {}
    if not p.exists():
        return st
    rx = re.compile(r"STATUS field=(\d+) vbl=\d+ ovl=(-?\d+) sysmode=(-?\d+) gamemode=(-?\d+)/(-?\d+)")
    for ln in open(p, errors="replace"):
        m = rx.search(ln)
        if m:
            st[int(m.group(1))] = (int(m.group(2)), int(m.group(4)), int(m.group(5)))
    return st


def transitions(st, lo_pad=30, hi_pad=120):
    out = []
    prev = None
    for f in sorted(st):
        ovl, gm, sub = st[f]
        if prev is not None and (ovl != prev[0] or gm != prev[1]):
            out.append(("ovl%d_mode%d->%d@%d" % (ovl, prev[1], gm, f), f - lo_pad, f + hi_pad))
        prev = (ovl, gm)
    return out


def frames(times, lo, hi):
    """group fields into presented frames: a frame ends at a field with a present"""
    fr, cur = [], []
    for f in range(lo, hi + 1):
        if f not in times:
            continue
        cur.append(f)
        if times[f]["present"] > 0.0 or times[f]["read"] > 0.0:
            fr.append(cur)
            cur = []
    if cur:
        fr.append(cur)
    return fr


def thread_names(stats):
    """label threads: 'main' (the field loop's thread) and T1.. by total CPU"""
    tot = {}
    main = set()
    for d in stats.values():
        for k, (ms, m) in d["_thr"].items():
            tot[k] = tot.get(k, 0.0) + ms
            if m:
                main.add(k)
    names = {}
    i = 1
    for k, _ in sorted(tot.items(), key=lambda kv: -kv[1]):
        if k in main:
            names[k] = "main"
        else:
            names[k] = "T%d(%s)" % (i, k.split(":")[1])
            i += 1
    return names


STAT_SHOW = ["fstats_ms", "proc_cpu_ms", "main_cpu_ms", "page_faults", "private_kb", "fs_reads", "fs_kb", "fs_ms",
             "snd_banks", "snd_kb", "gsq_kb", "h2l_kpx", "lazy_mat_kb", "clut_loads", "rt_creates", "rt_loads",
             "rt_writebacks", "up_kb", "down_kb", "downloads", "download_ms", "kick_ms", "tex_decodes",
             "nr_tex_decodes", "nr_mesh_uploads", "nr_lazy_decodes", "presents", "new_images"]


def frame_row(fr, times, stats, tnames):
    t = {c: sum(times[f][c] for f in fr) for c in TIME_COLS}
    s = {}
    thr = {}
    for f in fr:
        d = stats.get(f)
        if not d:
            continue
        for c in STAT_SHOW:
            s[c] = s.get(c, 0.0) + d.get(c, 0.0)
        for k, (ms, _) in d["_thr"].items():
            n = tnames.get(k, k)
            thr[n] = thr.get(n, 0.0) + ms
    return t, s, thr


def fmt_stats(s):
    out = []
    for c in STAT_SHOW:
        v = s.get(c, 0.0)
        if c in ("proc_cpu_ms", "main_cpu_ms"):
            out.append("%s %.1f" % (c.replace("_ms", ""), v))
        elif v:
            out.append("%s %s" % (c, ("%.1f" % v) if c.endswith("_ms") else "%d" % v))
    return ", ".join(out)


def window_report(name, lo, hi, times, stats, tnames, thr_ms, top, lines):
    fr = frames(times, lo, hi)
    if not fr:
        return None
    iv = [sum(times[f]["wall"] for f in x) for x in fr]
    work = [sum(times[f]["wall"] - times[f]["pace"] for f in x) for x in fr]
    med = statistics.median(iv)
    medw = statistics.median(work)
    srt = sorted(iv)
    p99 = srt[min(len(srt) - 1, int(len(srt) * 0.99))]
    over = [i for i, v in enumerate(iv) if v > thr_ms]
    over2 = [i for i, v in enumerate(iv) if v > 2 * med and v > 25]
    lines.append("### %s (fields %d-%d)" % (name, lo, hi))
    lines.append("")
    lines.append("frames %d, interval median %.1f / p99 %.1f / max %.1f ms, work median %.1f ms; "
                 "frames > %.0f ms: %d, > 2x median: %d; fields/frame median %d"
                 % (len(fr), med, p99, max(iv), medw, thr_ms, len(over), len(over2),
                    statistics.median([len(x) for x in fr])))
    lines.append("")
    img = None
    if stats and any(stats.get(f, {}).get("new_images", 0) for f in range(lo, hi + 1)):
        # what the player sees: intervals between presents of a NEW game image (the game's
        # display buffer changed), whatever the presents in between showed
        ifr, cur = [], []
        for f in range(lo, hi + 1):
            if f not in times:
                continue
            cur.append(f)
            if stats.get(f, {}).get("new_images", 0) > 0:
                ifr.append(cur)
                cur = []
        ii = [sum(times[f]["wall"] - stats.get(f, {}).get("fstats_ms", 0.0) for f in x) for x in ifr[1:]]
        if ii:
            si = sorted(ii)
            img = dict(n=len(ii), med=statistics.median(ii), p99=si[min(len(si) - 1, int(len(si) * 0.99))],
                       max=max(ii), over=sum(1 for v in ii if v > thr_ms), over40=sum(1 for v in ii if v > 40.0))
            lines.append("new images %d, interval median %.1f / p99 %.1f / max %.1f ms; > 40 ms: %d, > %.0f ms: %d "
                         "(intervals exclude $RG_FIELD_STATS's own sampling)"
                         % (img["n"], img["med"], img["p99"], img["max"], img["over40"], thr_ms, img["over"]))
            lines.append("")
    # cause ranking over the long frames (excess over the window's median frame)
    long_ = [i for i in range(len(fr)) if iv[i] > thr_ms]
    if long_:
        mt = {c: statistics.median([sum(times[f][c] for f in x) for x in fr]) for c in TIME_COLS}
        exc = {c: 0.0 for c in TIME_COLS}
        for i in long_:
            for c in TIME_COLS:
                exc[c] += sum(times[f][c] for f in fr[i]) - mt[c]
        lines.append("excess ms over the median frame, summed over the %d frames > %.0f ms: %s" % (
            len(long_), thr_ms, ", ".join("%s %.0f" % (c, exc[c]) for c in
                                          sorted(TIME_COLS, key=lambda c: -exc[c]) if c != "wall" and abs(exc[c]) >= 1)))
        lines.append("")
    if stats:
        # mean counters per frame over the window (steady work vs the worst frames below)
        acc = {}
        for x in fr:
            _, s0, th0 = frame_row(x, times, stats, tnames)
            for c, v in s0.items():
                acc[c] = acc.get(c, 0.0) + v
            for k, v in th0.items():
                acc["thr " + k] = acc.get("thr " + k, 0.0) + v
        lines.append("mean per frame: " + fmt_stats({c: v / len(fr) for c, v in acc.items()}) + "; threads ms: " +
                     ", ".join("%s %.1f" % (k[4:], v / len(fr)) for k, v in sorted(acc.items(), key=lambda kv: -kv[1])
                               if k.startswith("thr ") and v / len(fr) >= 0.5))
        lines.append("")
    worst = sorted(range(len(fr)), key=lambda i: -iv[i])[:top]
    lines.append("| first field | fields | interval | step | gs_wait (in step) | sync | present (in sync/post) | pace | out | pump+audio+post | other | counters | threads ms |")
    lines.append("| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |")
    for i in sorted(worst):
        t, s, thr = frame_row(fr[i], times, stats, tnames)
        # present / read happen inside sync (overlap: the previous frame) or post (copy path)
        # ... and $RG_FIELD_STATS's own sampling (fstats_ms) sits between the columns
        other = t["wall"] - (t["step"] + t["sync"] + t["pace"] + t["out"] + t["pump"] + t["audio"] + t["post"]
                             + s.get("fstats_ms", 0.0))
        th = ", ".join("%s %.0f" % (k, v) for k, v in sorted(thr.items(), key=lambda kv: -kv[1])[:4])
        lines.append("| %d | %d | %.1f | %.1f | %.1f | %.1f | %.1f | %.1f | %.1f | %.1f | %.1f | %s | %s |" % (
            fr[i][0], len(fr[i]), t["wall"], t["step"], t["gs_wait"], t["sync"], t["present"], t["pace"],
            t["out"], t["pump"] + t["audio"] + t["post"], other, fmt_stats(s) if s else "-", th or "-"))
    lines.append("")
    return dict(name=name, frames=len(fr), med=med, p99=p99, max=max(iv), over=len(over), over2=len(over2), img=img)


def report(d: Path, wins, top, thr_ms, out=True):
    times = load_times(d / "times.tsv")
    stats, _, _ = load_stats(d / "stats.tsv")
    st = load_status(d / "run.log")
    tnames = thread_names(stats)
    lo, hi = min(times), max(times)
    ws = []
    for w in wins or []:
        n, r = w.split(":")
        a, b = r.split("-")
        ws.append((n, int(a), int(b)))
    if not wins:
        ws = [(n, max(a, lo + 3), min(b, hi)) for n, a, b in transitions(st)]
    ws.append(("whole run (from +3)", lo + 3, hi))
    lines = ["# stutter report: %s" % d, ""]
    if st:
        seg = []
        prev = None
        for f in sorted(st):
            if st[f][:2] != prev:
                seg.append("%d: ovl %d mode %d" % (f, st[f][0], st[f][1]))
                prev = st[f][:2]
        lines.append("game modes: " + "; ".join(seg))
        lines.append("")
    summ = []
    for n, a, b in ws:
        r = window_report(n, a, b, times, stats, tnames, thr_ms, top, lines)
        if r:
            summ.append(r)
    lines.append("| window | presents | median | p99 | max | > %.0f ms | > 2x median | new images | median | p99 | max | > 40 ms | > %.0f ms |"
                 % (thr_ms, thr_ms))
    lines.append("| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |")
    for r in summ:
        im = r["img"] or dict(n=0, med=0, p99=0, max=0, over40=0, over=0)
        lines.append("| %s | %d | %.1f | %.1f | %.1f | %d | %d | %d | %.1f | %.1f | %.1f | %d | %d |" % (
            r["name"], r["frames"], r["med"], r["p99"], r["max"], r["over"], r["over2"],
            im["n"], im["med"], im["p99"], im["max"], im["over40"], im["over"]))
    txt = "\n".join(lines) + "\n"
    if out:
        (d / "report.md").write_text(txt)
        print(txt)
    return summ


def run(a, extra):
    d = Path(a.dir).resolve()
    d.mkdir(parents=True, exist_ok=True)
    a.exe = str(Path(a.exe).resolve())
    if a.state:
        a.state = str(Path(a.state).resolve())
    if a.input:
        a.input = str(Path(a.input).resolve())
    saves = d / "saves"
    saves.mkdir(exist_ok=True)
    env = dict(os.environ)
    env.setdefault("RG_GPU", "hw")
    env.setdefault("RG_DATA", str(ROOT / "data"))
    env["RG_FIELD_TIMES"] = str(d / "times.tsv")
    env["RG_FIELD_STATS"] = str(d / "stats.tsv")
    env["RG_STATUS_EVERY"] = "1"
    for kv in a.env or []:
        k, v = kv.split("=", 1)
        env[k] = v
    cmd = [a.exe] + (["--headless"] if a.headless else []) + ["--fields", str(a.fields), "--saves", str(saves)]
    if a.state:
        inp = a.input or str(ROOT / "tools/trace/goldens/newgame_save2.input.txt")
        cmd += ["--input", inp, "--load-state", a.state]
    elif a.boot_save:
        import shutil
        card = ROOT / "out/fixtures/cards" / a.boot_save
        for f in card.iterdir():
            if f.is_file():
                shutil.copy(f, saves / f.name)
            else:
                shutil.copytree(f, saves / f.name, dirs_exist_ok=True)
        inp = a.input or str(ROOT / ("tools/trace/goldens/boot_%s.input.txt" % a.boot_save))
        cmd += ["--input", inp]
    cmd += extra
    with open(d / "cmd.txt", "w") as f:
        f.write(" ".join(cmd) + "\n" + "\n".join("%s=%s" % (k, v) for k, v in env.items() if k.startswith("RG_")) + "\n")
    with open(d / "run.log", "w") as log:
        rc = subprocess.call(cmd, env=env, stdout=log, stderr=subprocess.STDOUT)
    print("rg-game exit %d" % rc)
    report(d, a.win, a.top, a.thr)
    return rc


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    extra = []
    if "--" in argv:
        i = argv.index("--")
        argv, extra = argv[:i], argv[i + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for n in ("report", "run", "compare"):
        p = sub.add_parser(n)
        p.add_argument("dir")
        if n == "compare":
            p.add_argument("dir2")
        p.add_argument("--win", action="append")
        p.add_argument("--top", type=int, default=12)
        p.add_argument("--thr", type=float, default=50.0)
        if n == "run":
            p.add_argument("--exe", required=True)
            p.add_argument("--state")
            p.add_argument("--boot-save")
            p.add_argument("--fields", type=int, required=True)
            p.add_argument("--input")
            p.add_argument("--headless", action="store_true")
            p.add_argument("--env", action="append")
    a = ap.parse_args(argv)
    if a.cmd == "report":
        report(Path(a.dir), a.win, a.top, a.thr)
    elif a.cmd == "run":
        return run(a, extra)
    else:
        ra = report(Path(a.dir), a.win, a.top, a.thr, out=False)
        rb = report(Path(a.dir2), a.win, a.top, a.thr, out=False)
        print("| window | A images: median / p99 / max / > 40 / > thr | B images: median / p99 / max / > 40 / > thr |")
        print("| --- | --- | --- |")
        z = dict(med=0, p99=0, max=0, over40=0, over=0)
        for x, y in zip(ra, rb):
            xi, yi = x["img"] or z, y["img"] or z
            print("| %s | %.1f / %.1f / %.1f / %d / %d | %.1f / %.1f / %.1f / %d / %d |" % (
                x["name"], xi["med"], xi["p99"], xi["max"], xi["over40"], xi["over"],
                yi["med"], yi["p99"], yi["max"], yi["over40"], yi["over"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())

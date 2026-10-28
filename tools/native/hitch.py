#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Hitch measurement: what stops video and audio on a windowed, real-time run, and why
(docs/NATIVE-THREADS.md "Hitches").

    python tools/native/hitch.py run TAG [--route poweron|battle2|shop|all] [--exe EXE]
                                 [--load none|cpu:N|game:N|gamewin:N] [--fields N] [--env K=V ...]
                                 [-- extra rg-game args]
    python tools/native/hitch.py report DIR [--thr-periods 3]
    python tools/native/hitch.py compare DIR_A DIR_B ...
    python tools/native/hitch.py window F0 F1 DIR_A DIR_B ...   (one field range only, e.g. the
                                 mode-11 scenes 12148 22432: read-back waits, wall p99, hitches)

`run` starts EXE (default the latest play-test exe) windowed with the play-test setup
(RG_GPU=hw, RG_SLOTS_PRIORITY=normal, out/playtest/settings.ini copied into the run dir and
passed with --settings, so the run never writes the play-test's own file) over a scripted
route, with every per-field log the runtime has:
  RG_FIELD_TIMES  wall / step / pace / gs_wait / sync / present / pump / audio / post / out ms
  RG_FIELD_STATS  main-thread and process CPU, page faults, file reads (count, ms), GPU work
  RG_AUDIO_LOG    device queue before / after the push, starves (+ silent frames), pads, drops
  RG_PRESENT_LOG  wall time of every present
  RG_STATUS_EVERY game mode / overlay per field (to name the scene of a hitch)
plus a 1 s machine sample (typeperf: total CPU %, GPU 3D engine %, the rg-game processes
running) so a hitch can be set against what else the machine did.  Output: out/hitch/TAG/ROUTE/.

Routes (all from real inputs, no save states, so any exe works):
  poweron  power-on to the first save: title, opening FMV, field, first battle, town (map
           transitions), save point, transporter menu, card save (tools/trace/goldens/
           newgame_save2.input.txt, 31,700 fields, ~9 min)
  battle2  card boot (save2) -> load screen -> walk -> random encounter -> second battle ->
           field (boot_save2_battle2.input.txt, 7,800 fields, ~2.2 min)
  shop     card zshop2 -> Zerard shop open / browse / close (tools/native/hitch_shop.input.txt,
           4,450 fields, ~75 s)

--load starts contention this tool owns (stopped by PID when the run ends): cpu:N = N busy
processes at normal priority; game:N = N headless rg-game power-on runs of the same exe
(unthrottled, below-normal priority like the other lanes' test runs, RG_SLOTS=0);
gamewin:N = N windowed unthrottled rg-game (GPU load at normal priority).

`report` (also run at the end of `run`) writes DIR/hitches.tsv and DIR/hitch.md:
  * a VIDEO hitch = a present interval > --thr-periods display periods (default 3 = 50 ms:
    at least two refreshes without a new present); an AUDIO hitch = a field whose push found
    the device queue starved (the player hears silence);
  * each hitch's fields are attributed: pace (pacer sleep: oversleep = timer), game CPU (EE
    step on-CPU), file I/O, GPU / GS-worker waits (gs_wait + sync), present, download
    (read-back) waits, event pump, audio push, and OFF-CPU = wall - pace - main-thread CPU -
    the timed waits: the main thread was neither running nor in a timed wait (preempted by
    other processes, or an untimed wait);
  * cause = the category with the largest excess over the route's median field; a hitch
    whose off-CPU share dominates while the machine was loaded is "load"; one dominated by
    game CPU / file I/O / GPU waits in a scene change is "port" (the work is ours).
"""
from __future__ import annotations

import argparse
import csv
import os
import shutil
import statistics
import subprocess
import sys
import threading
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/perf3d"))
import stutter  # noqa: E402  (loaders for RG_FIELD_TIMES / RG_FIELD_STATS / STATUS lines)

PERIOD = 1000.0 / 59.94
DEF_EXE = ROOT / "out/playtest/rg-game-1025c.exe"
SETTINGS = ROOT / "out/playtest/settings.ini"
CARDS = ROOT / "out/fixtures/cards"
GOLD = ROOT / "tools/trace/goldens"
ROUTES = {
    "poweron": dict(card=None, input=GOLD / "newgame_save2.input.txt", fields=31700),
    "battle2": dict(card="save2", input=GOLD / "boot_save2_battle2.input.txt", fields=7800),
    "shop": dict(card="zshop2", input=ROOT / "tools/native/hitch_shop.input.txt", fields=4450),
}
BUSY = "import time\nwhile True:\n    pass\n"


# ------------------------------------------------------------------ run
def copy_card(name, saves):
    saves.mkdir(parents=True, exist_ok=True)
    if not name:
        return
    for f in (CARDS / name).iterdir():
        if f.is_file():
            shutil.copy(f, saves / f.name)
        else:
            shutil.copytree(f, saves / f.name, dirs_exist_ok=True)


def start_load(spec, exe, d):
    procs = []
    if not spec or spec == "none":
        return procs
    kind, n = spec.split(":")
    n = int(n)
    env = dict(os.environ)
    env["RG_SLOTS"] = "0"
    env.pop("RG_SLOTS_PRIORITY", None)
    for i in range(n):
        if kind == "cpu":
            procs.append(subprocess.Popen([sys.executable, "-c", BUSY]))
        elif kind in ("game", "gamewin"):
            ld = d / ("load%d" % i)
            (ld / "saves").mkdir(parents=True, exist_ok=True)
            cmd = [str(exe), "--data", str(ROOT / "data"), "--saves", str(ld / "saves"), "--fields", "40000",
                   "--input", str(GOLD / "newgame_save2.input.txt")]
            if kind == "game":
                cmd.insert(1, "--headless")
            else:
                env["RG_GPU"] = "hw"
                cmd += ["--unthrottled", "--settings", str(ld / "settings.ini"), "--set", "display.frame_rate=uncapped"]
                shutil.copy(SETTINGS, ld / "settings.ini")
            procs.append(subprocess.Popen(cmd, env=env, stdout=open(ld / "log.txt", "w"), stderr=subprocess.STDOUT))
        else:
            raise SystemExit("hitch: unknown load " + spec)
    return procs


def rg_processes():
    try:
        t = subprocess.run(["tasklist", "/fo", "csv", "/nh"], capture_output=True, text=True, timeout=20).stdout
    except Exception:
        return []
    out = []
    for r in csv.reader(t.splitlines()):
        if r and r[0].lower().startswith("rg-game"):
            out.append("%s:%s:%s" % (r[0], r[1], r[4].replace(",", "").replace(" K", "K")))
    return out


def run_route(a, extra, tag, route):
    rt = ROUTES[route]
    d = (ROOT / "out/hitch" / tag / route).resolve()
    if d.exists():
        shutil.rmtree(d)
    d.mkdir(parents=True)
    exe = Path(a.exe).resolve()
    copy_card(rt["card"], d / "saves")
    shutil.copy(SETTINGS, d / "settings.ini")
    env = dict(os.environ)
    env.update(RG_GPU="hw", RG_SLOTS_PRIORITY="normal", RG_SLOTS="0",
               RG_FIELD_TIMES=str(d / "times.tsv"), RG_FIELD_STATS=str(d / "stats.tsv"),
               RG_AUDIO_LOG=str(d / "audio.tsv"), RG_PRESENT_LOG=str(d / "present.tsv"), RG_STATUS_EVERY="1")
    for kv in a.env or []:
        k, v = kv.split("=", 1)
        env[k] = v
    fields = a.fields or rt["fields"]
    cmd = [str(exe), "--data", str(ROOT / "data"), "--saves", str(d / "saves"), "--settings", str(d / "settings.ini"),
           "--fields", str(fields), "--input", str(rt["input"])] + extra
    with open(d / "cmd.txt", "w") as f:
        f.write(" ".join(cmd) + "\n" + "\n".join("%s=%s" % (k, v) for k, v in env.items() if k.startswith("RG_")) + "\n")
        f.write("load=%s\nbefore: %s\n" % (a.load, " ".join(rg_processes())))
    load = start_load(a.load, exe, d)
    if load:
        time.sleep(5)  # let the load reach its steady state
    tp = subprocess.Popen(["typeperf", "-si", "1", "-o", str(d / "machine.csv"), "-f", "CSV", "-y",
                           r"\Processor(_Total)\% Processor Time",
                           r"\GPU Engine(*engtype_3D)\Utilization Percentage"],
                          stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    t0 = time.time()
    try:
        # the game's stdout / stderr (a STATUS line every field) go through a pipe drained into
        # memory: written straight to a file, a write that blocks on a busy disk stalled the game
        # thread for up to ~1 s (the "between fields" stalls); the log is written at the end
        proc = subprocess.Popen(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        chunks = []
        rd = threading.Thread(target=lambda: chunks.extend(iter(lambda: proc.stdout.read1(65536), b"")), daemon=True)
        rd.start()
        rc = proc.wait()
        rd.join()
        with open(d / "run.log", "wb") as log:
            log.write(b"".join(chunks).replace(b"\r\n", b"\n"))
    finally:
        for p in load + [tp]:
            p.kill()  # by PID: only processes this tool started
        for p in load + [tp]:
            p.wait()
    with open(d / "cmd.txt", "a") as f:
        f.write("t0=%.3f\nexit=%d\nafter: %s\n" % (t0, rc, " ".join(rg_processes())))
    print("%s/%s: rg-game exit %d, %.0f s" % (tag, route, rc, time.time() - t0))
    report(d, a.thr_periods)
    return rc


# ------------------------------------------------------------------ report
def load_tsv(p):
    rows = {}
    if not p.exists():
        return rows
    cols = None
    for ln in open(p):
        f = ln.rstrip("\n").split("\t")
        if cols is None:
            cols = [c.lstrip("#") for c in f]
            continue
        if not f[0].isdigit():
            continue
        rows[int(f[0])] = {c: float(x) for c, x in zip(cols[1:], f[1:])}
    return rows


def load_present(p):
    out = []
    if not p.exists():
        return out
    for ln in open(p):
        if ln.startswith("#") or not ln.strip():
            continue
        t, k, f = ln.split("\t")
        out.append((float(t), int(k), int(f)))
    return out


def load_machine(p):
    """[(epoch, cpu %, gpu3d %)] from typeperf CSV (GPU: sum over the 3D engine instances)"""
    out = []
    if not p.exists():
        return out
    import datetime
    rows = list(csv.reader(open(p, errors="replace")))
    if len(rows) < 2:
        return out
    for r in rows[1:]:
        try:
            ts = datetime.datetime.strptime(r[0], "%m/%d/%Y %H:%M:%S.%f").timestamp()
        except Exception:
            continue
        vals = []
        for x in r[1:]:
            try:
                vals.append(float(x))
            except ValueError:
                vals.append(0.0)
        out.append((ts, vals[0] if vals else 0.0, sum(vals[1:])))
    return out


CATS = ["pace", "cpu", "fileio", "gpuwait", "present", "download", "pump", "audio", "out", "offcpu"]
CAT_TEXT = {"pace": "pacer sleep", "cpu": "game CPU", "fileio": "file I/O", "gpuwait": "GPU/GS-worker wait",
            "present": "present", "download": "read-back wait", "pump": "event pump", "audio": "audio push",
            "out": "between fields (the caller: STATUS / log writes of the measurement itself)",
            "offcpu": "off-CPU (preempted / untimed wait)"}


def field_cats(t, s):
    """per-field ms by category (see the module doc).  The present path's own time = read
    (compose / zero-copy hand-over or read-back) + present (the window present call); it runs in
    post (presented this field) or inside sync (overlap: composed on the worker)."""
    main = s.get("main_cpu_ms", 0.0) if s else 0.0
    fio = s.get("fs_ms", 0.0) if s else 0.0
    dl = s.get("download_ms", 0.0) if s else 0.0
    pres = t["read"] + t["present"]
    sync = t["sync"]
    if t["post"] + 0.05 < pres:  # presented inside sync
        sync = max(0.0, sync - pres)
    gw = t["gs_wait"] + sync
    c = dict(pace=t["pace"], fileio=fio, gpuwait=gw, present=pres, download=dl, pump=t["pump"], audio=t["audio"],
             out=t["out"])
    # game CPU: the EE step's time on the CPU (step minus its waits for the worker and file reads)
    c["cpu"] = max(0.0, min(main, t["step"] - t["gs_wait"] - fio))
    waited = t["pace"] + fio + gw + dl + pres + t["pump"] + t["audio"]
    c["offcpu"] = max(0.0, t["wall"] - waited - c["cpu"] - (s.get("fstats_ms", 0.0) if s else 0.0)
                      - max(0.0, t["post"] - pres) - t["out"])
    return c


def report(d: Path, thr_periods=3.0, quiet=False):
    d = Path(d)
    times = stutter.load_times(d / "times.tsv")
    stats, _, _ = stutter.load_stats(d / "stats.tsv")
    st = stutter.load_status(d / "run.log")
    au = load_tsv(d / "audio.tsv")
    pres = load_present(d / "present.tsv")
    mach = load_machine(d / "machine.csv")
    t0 = None
    for ln in open(d / "cmd.txt") if (d / "cmd.txt").exists() else []:
        if ln.startswith("t0="):
            t0 = float(ln[3:])
    if not times:
        print("hitch: no times.tsv in", d)
        return None
    fl = sorted(times)
    cats = {f: field_cats(times[f], stats.get(f)) for f in fl}
    med = {c: statistics.median([cats[f][c] for f in fl]) for c in CATS}
    # wall-clock of each field's end (for the machine samples), ms since the first field
    acc, wend = 0.0, {}
    for f in fl:
        acc += times[f]["wall"]
        wend[f] = acc
    # the machine sample nearest a field (t0 = process launch; the first field ends ~load time later)
    lead = (mach[0][0] - t0) if (mach and t0) else 0.0

    def machine_at(f):
        if not mach or t0 is None:
            return (-1.0, -1.0)
        # field times start at the first field; the launch-to-first-field gap is the boot (a few s)
        ts = t0 + boot_s + wend[f] / 1000.0
        best = min(mach, key=lambda m: abs(m[0] - ts))
        return best[1], best[2]

    boot_s = 0.0
    if pres and t0 is not None:
        boot_s = 0.0  # present log t0 ~ host init; small next to the 1 s machine samples

    def scene(f):
        k = max((x for x in st if x <= f), default=None)
        if k is None:
            return "-"
        o, g, sub = st[k]
        return "ovl%d/m%d.%d" % (o, g, sub)

    if not pres and stats:
        # exes without $RG_PRESENT_LOG: present times = end of the fields that presented
        pres = [(wend[f], 1, f) for f in fl if (stats.get(f) or {}).get("presents", 0) > 0]
    events = []
    # video: present intervals
    thr = thr_periods * PERIOD
    prev = None
    for (t, k, f) in pres:
        if prev is not None:
            iv = t - prev[0]
            if iv > thr:
                events.append(dict(kind="video", f0=prev[2] + 1, f1=f, ms=iv))
        prev = (t, k, f)
    # audio: starved pushes
    for f in sorted(au):
        r = au[f]
        if r.get("starves", 0) > 0:
            events.append(dict(kind="audio", f0=f, f1=f, ms=r.get("starve_frames", 0) / 48.0))
    # attribute: fields of the event plus the 4 fields before an audio starve (the queue's cushion)
    rows = []
    for e in events:
        lo = e["f0"] - (4 if e["kind"] == "audio" else 0)
        fs = [f for f in range(lo, e["f1"] + 1) if f in cats]
        if not fs:
            continue
        tot = {c: sum(cats[f][c] for f in fs) for c in CATS}
        exc = {c: tot[c] - med[c] * len(fs) for c in CATS}
        wall = sum(times[f]["wall"] for f in fs)
        cause = max((c for c in CATS if c != "pace"), key=lambda c: exc[c])
        if exc["pace"] > exc[cause]:
            cause = "pace"
        cpu, gpu = machine_at(fs[-1])
        fsr = sum((stats.get(f) or {}).get("fs_reads", 0) for f in fs)
        pf = sum((stats.get(f) or {}).get("page_faults", 0) for f in fs)
        resy = au.get(fs[-1], {}).get("resyncs", 0) - au.get(fs[0] - 1, au.get(fs[0], {})).get("resyncs", 0)
        rows.append(dict(kind=e["kind"], f0=e["f0"], f1=e["f1"], ms=e["ms"], fields=len(fs), wall=wall,
                         scene=scene(e["f0"]), cause=cause, cpu=cpu, gpu=gpu, fs_reads=fsr, page_faults=pf,
                         resyncs=resy, **{"x_" + c: exc[c] for c in CATS}, **{"t_" + c: tot[c] for c in CATS}))
    rows.sort(key=lambda r: (r["f0"], r["kind"]))
    cols = ["kind", "f0", "f1", "ms", "fields", "wall", "scene", "cause", "cpu", "gpu", "fs_reads", "page_faults",
            "resyncs"] + ["t_" + c for c in CATS] + ["x_" + c for c in CATS]
    with open(d / "hitches.tsv", "w") as f:
        f.write("\t".join(cols) + "\n")
        for r in rows:
            f.write("\t".join(("%.1f" % r[c]) if isinstance(r[c], float) else str(r[c]) for c in cols) + "\n")
    # summary
    span_s = wend[fl[-1]] / 1000.0
    vid = [r for r in rows if r["kind"] == "video"]
    aud = [r for r in rows if r["kind"] == "audio"]
    # the measurement's own stalls (cause "out": the caller's STATUS / log writes blocking on a busy
    # disk; a play-test run writes nothing per field) are reported but not counted as the game's
    vid_x = [r for r in vid if r["cause"] == "out"]
    aud_x = [r for r in aud if r["cause"] == "out"]
    vid_g = [r for r in vid if r["cause"] != "out"]
    aud_g = [r for r in aud if r["cause"] != "out"]
    ivs = [pres[i][0] - pres[i - 1][0] for i in range(1, len(pres))]
    L = ["# hitch report: %s" % d, ""]
    if (d / "cmd.txt").exists():
        for ln in open(d / "cmd.txt"):
            if ln.startswith(("load=", "before:", "after:")):
                L.append("- " + ln.strip())
    cpu_all = [m[1] for m in mach]
    gpu_all = [m[2] for m in mach]
    if mach:
        L.append("- machine over the run: CPU total mean %.0f %% (max %.0f), GPU 3D mean %.0f %% (max %.0f)"
                 % (statistics.mean(cpu_all), max(cpu_all), statistics.mean(gpu_all), max(gpu_all)))
    L.append("- fields %d-%d, %.0f s; presents %d, interval median %.1f ms, p99 %.1f, max %.1f"
             % (fl[0], fl[-1], span_s, len(pres), statistics.median(ivs) if ivs else 0,
                sorted(ivs)[int(len(ivs) * 0.99)] if ivs else 0, max(ivs) if ivs else 0))
    L.append("- median field ms by category: " + ", ".join("%s %.2f" % (c, med[c]) for c in CATS))
    L.append("- VIDEO hitches (present gap > %.0f ms): %d (%.1f / min), %.0f ms lost beyond one period"
             % (thr, len(vid_g), len(vid_g) / span_s * 60, sum(r["ms"] - PERIOD for r in vid_g)))
    L.append("- AUDIO hitches (starved pushes): %d, %.0f ms of silence; with a video hitch in the same fields: %d"
             % (len(aud_g), sum(r["ms"] for r in aud_g),
                sum(1 for r in aud_g if any(v["f0"] - 4 <= r["f0"] <= v["f1"] + 1 for v in vid_g))))
    L.append("- not counted above: the measurement's own stalls (between fields: STATUS / log writes): "
             "%d video (%.0f ms), %d audio (%.0f ms silence)"
             % (len(vid_x), sum(r["ms"] for r in vid_x), len(aud_x), sum(r["ms"] for r in aud_x)))
    L.append("")
    for kind, rs in (("video", vid), ("audio", aud)):
        if not rs:
            continue
        L.append("## %s hitches by cause" % kind)
        L.append("")
        L.append("| cause | hitches | ms (gap / silence) | excess ms in the cause |")
        L.append("| --- | --- | --- | --- |")
        by = {}
        for r in rs:
            b = by.setdefault(r["cause"], [0, 0.0, 0.0])
            b[0] += 1
            b[1] += r["ms"]
            b[2] += r["x_" + r["cause"]]
        for c, b in sorted(by.items(), key=lambda kv: -kv[1][1]):
            L.append("| %s | %d | %.0f | %.0f |" % (CAT_TEXT[c], b[0], b[1], b[2]))
        L.append("")
        L.append("| kind | fields | gap/silence ms | scene | cause | machine CPU %% / GPU %% | fs reads | pf | "
                 + " | ".join(CATS) + " |")
        L.append("| --- " * (8 + len(CATS)) + "|")
        for r in sorted(rs, key=lambda r: -r["ms"])[:40]:
            L.append("| %s | %d-%d | %.0f | %s | %s | %.0f / %.0f | %d | %d | %s |" % (
                r["kind"], r["f0"], r["f1"], r["ms"], r["scene"], CAT_TEXT[r["cause"]], r["cpu"], r["gpu"],
                r["fs_reads"], r["page_faults"], " | ".join("%.0f" % r["t_" + c] for c in CATS)))
        L.append("")
    txt = "\n".join(L) + "\n"
    (d / "hitch.md").write_text(txt)
    if not quiet:
        print(txt)
    return dict(dir=str(d), span=span_s, video=len(vid_g), video_ms=sum(r["ms"] - PERIOD for r in vid_g),
                audio=len(aud_g), audio_ms=sum(r["ms"] for r in aud_g), meas=len(vid_x) + len(aud_x),
                cpu=statistics.mean(cpu_all) if mach else -1, gpu=statistics.mean(gpu_all) if mach else -1,
                p99=sorted(ivs)[int(len(ivs) * 0.99)] if ivs else 0, by=rows)


def window(dirs, f0, f1, thr):
    """one row per run: fields f0..f1 only (e.g. the mode-11 scripted scenes 12148-22432):
    read-back waits (download_ms: mean, p99, max, fields > 16 / 50 ms), field wall p99 / max,
    video hitches (present gap > thr periods) and audio starves / silence inside the window."""
    print("| run | fields | read-back ms mean / p99 / max | fields read-back > 16 / > 50 ms | wall p99 / max ms | "
          "video hitches | audio starves | silence ms | measurement stalls (not counted) |")
    print("| --- | --- | --- | --- | --- | --- | --- | --- | --- |")
    for x in dirs:
        d = Path(x)
        times = stutter.load_times(d / "times.tsv")
        stats, _, _ = stutter.load_stats(d / "stats.tsv")
        au = load_tsv(d / "audio.tsv")
        fl = [f for f in sorted(times) if f0 <= f <= f1]
        if not fl:
            print("| %s | - |" % x)
            continue
        dl = sorted((stats.get(f) or {}).get("download_ms", 0.0) for f in fl)
        wl = sorted(times[f]["wall"] for f in fl)
        rr = report(d, thr, quiet=True) or {"by": []}
        rows = [r for r in rr["by"] if f0 <= r["f0"] <= f1 and r["cause"] != "out"]
        nv = sum(1 for r in rows if r["kind"] == "video")
        st = [r for r in rows if r["kind"] == "audio"]
        meas = sum(1 for r in rr["by"] if f0 <= r["f0"] <= f1 and r["cause"] == "out")
        print("| %s | %d | %.1f / %.1f / %.1f | %d / %d | %.1f / %.1f | %d | %d | %.0f | %d |" % (
            x, len(fl), statistics.mean(dl), dl[int(len(dl) * 0.99)], dl[-1], sum(1 for v in dl if v > 16),
            sum(1 for v in dl if v > 50), wl[int(len(wl) * 0.99)], wl[-1], nv, len(st),
            sum(r["ms"] for r in st), meas))


def compare(dirs, thr):
    print("| run | s | machine CPU / GPU % | video hitches | /min | ms lost | audio starves | silence ms | present p99 ms "
          "| measurement stalls (not counted) |")
    print("| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |")
    for x in dirs:
        r = report(Path(x), thr, quiet=True)
        if r:
            print("| %s | %.0f | %.0f / %.0f | %d | %.1f | %.0f | %d | %.0f | %.1f | %d |" % (
                x, r["span"], r["cpu"], r["gpu"], r["video"], r["video"] / r["span"] * 60, r["video_ms"],
                r["audio"], r["audio_ms"], r["p99"], r["meas"]))


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    extra = []
    if "--" in argv:
        i = argv.index("--")
        argv, extra = argv[:i], argv[i + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("run")
    p.add_argument("tag")
    p.add_argument("--route", default="all")
    p.add_argument("--exe", default=str(DEF_EXE))
    p.add_argument("--load", default="none")
    p.add_argument("--fields", type=int)
    p.add_argument("--env", action="append")
    p.add_argument("--thr-periods", type=float, default=3.0)
    p = sub.add_parser("report")
    p.add_argument("dir")
    p.add_argument("--thr-periods", type=float, default=3.0)
    p = sub.add_parser("compare")
    p.add_argument("dirs", nargs="+")
    p.add_argument("--thr-periods", type=float, default=3.0)
    p = sub.add_parser("window")
    p.add_argument("f0", type=int)
    p.add_argument("f1", type=int)
    p.add_argument("dirs", nargs="+")
    p.add_argument("--thr-periods", type=float, default=3.0)
    a = ap.parse_args(argv)
    if a.cmd == "window":
        window(a.dirs, a.f0, a.f1, a.thr_periods)
        return 0
    if a.cmd == "run":
        rc = 0
        for r in (ROUTES if a.route == "all" else a.route.split(",")):
            rc |= run_route(a, extra, a.tag, r)
        return rc
    if a.cmd == "report":
        report(Path(a.dir), a.thr_periods)
        return 0
    compare(a.dirs, a.thr_periods)
    return 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Options-matrix gate (PLAN.md "P6 - PC features" Gate; docs/P6-STATUS.md "Gates and the
Original preset"): every live non-gameplay setting must leave the run hash and the audio hash
of the Original preset unchanged.

    python tools/p6/optgate.py run    --exe EXE [--mode quick|full] [--out DIR] [-j N] [--max-hours H]
    python tools/p6/optgate.py plan   [--mode quick|full]          # the job list, runs nothing
    python tools/p6/optgate.py report [--out DIR]                  # report from finished jobs

What it does:
  1. Re-runs tools/settings_census.py into OUT/settings.tsv (static, no build), so settings a
     lane registered since the last checked-in census are picked up automatically; the diff
     against census/settings.tsv is listed in the report.  (--census FILE uses a given TSV.)
  2. Classifies every setting: GAMEPLAY -> excluded (listed); PLACEHOLDER or no reader -> not
     live (listed); live ones -> "headless" (a reader is reached in a headless scripted run:
     swept) or "not testable headless" (the reader is a window, an audio device, a host clock
     or live input, none of which a headless scripted run has; see CLASS below).  Settings
     the table does not know are classified from their reader sites.
  3. Jobs (each = one rg-game run, `--headless --preset original [--set id=v]...`, with
     $RG_HASH_LOG):
       baseline   Original preset: golden route (full) + the boot fixtures (fxlib.BOOT_FIXTURES)
       sweep      each headless setting, each value (bool flip, every enum value, numeric min /
                  max, curated strings / bindings): route PREFIX + the save2 boot fixture
       nth group  all not-testable-headless settings of one group at once (host / input): a
                  leak check only, never counted as a pass
       combined   every live non-gameplay setting at its "on" value, and the default preset
                  (`--preset default`, what a player gets): full route + all boot fixtures
     A job compares its hash log against the baseline of the same scenario: final run hash,
     final audio part, last field, exit code; on a difference the first differing field and
     the hash-log columns that differ there (pad / audio / ktrace / ktrace_n / now).
  4. OUT/report.tsv + OUT/report.md; exit 0 = every job equal, 1 = a difference or an error,
     75 = incomplete (time budget reached or jobs claimed by another runner: run again).

Parallel-safe and resumable: every job has its own dir OUT/jobs/<id>/ (fresh saves dir with a
copy of the fixture's card; out/fixtures/cards is only read) and is claimed atomically
(claim file with the PID; a dead claimer's claim is taken over); result.json marks it done and
is reused while the exe id, the scenario and the settings are the same.  Several runners may
share one OUT.  --max-hours stops starting jobs after H hours (default 1.8, so a background
run stays under 2 h; run again to continue).  The exe is copied to OUT/exe/<exe-id>/ first, so
a relink of the build dir does not change it mid-run.

Modes: quick (ctest fixtures.optgate_quick: 4 settings, save2 boot + route to 2,000, a few
minutes) and full.  --only ID[,ID] restricts the sweep; --prefix N sets the sweep's route length.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fxlib  # noqa: E402

REFERENCE_31700 = "b0632cdfa80153de"   # power-on to 31,700, Original (BRINGUP-HISTORY 2026-10-26)
FULL_ROUTE = 31700
SWEEP_PREFIX = 13000                    # title, NEW GAME, opening FMV, first field, first lens flare (12,151)
QUICK_PREFIX = 2000
BOOTS_ALL = ["save2", "factory", "insectron", "save2_battle2"]
BOOTS_SWEEP = ["save2"]
COLS = ["pad", "audio", "ktrace", "ktrace_n", "now"]

# ---- classification -------------------------------------------------------------------
# id -> (class, reason).  class: "headless" (swept), "host" / "input" (not testable headless;
# leak-checked as a group).  Unknown ids: reader-site heuristic (classify()).
CLASS = {
    "display.window_mode": ("host", "window only (a headless host has no window)"),
    "display.monitor": ("host", "window only"),
    "display.scale": ("host", "window fit only; headless frames are never scaled to a window"),
    "display.vsync": ("host", "presents / host clock only (headless: retail cadence, no presents)"),
    "display.pacing": ("host", "headless forces the retail cadence (runtime.c pace_update)"),
    "display.frame_rate": ("host", "present cap + host pacing only; no presents headless "
                                   "(the frame-rate gate belongs to the interpolation lane)"),
    "display.fps_counter": ("host", "window overlay only"),
    "audio.master_volume": ("host", "host stream gain after the mix (no audio device headless)"),
    "audio.latency_ms": ("host", "host stream buffer (no audio device headless)"),
    "audio.background": ("host", "focus events of a window (none headless)"),
    "audio.device": ("host", "host audio device (none headless)"),
    "system.throttle": ("host", "headless forces unthrottled (runtime.c rg_runtime_init)"),
    "system.screenshot_dir": ("host", "window screenshot key only"),
    "prompts.style": ("host", "scripted / headless runs always use PlayStation prompts (host_sdl.c)"),
    "input.overlay_chord": ("input", "live gamepad input only"),
    "input.overlay_chord_hold": ("input", "live gamepad input only"),
    "input.min_press_fields": ("input", "press latch of live input; scripts bypass it (INPUT.md)"),
    # headless with a note
    "display.width": ("headless", "aspect_apply reads it headless (graphics.aspect=auto); window size otherwise"),
    "display.height": ("headless", "as display.width"),
    "graphics.anisotropic": ("headless", "read, but no effect in the native-only exe (P6-STATUS)"),
    "display.interpolation": ("headless", "inert headless without $RG_INTERP_SIM; swept with RG_INTERP_SIM=120"),
}

# Curated sweep values (else derived from the type).  A value may be (value, {env}).
VALUES = {
    "display.interpolation": [("true", {"RG_INTERP_SIM": "120"}), ("true", {})],
    "audio.device": ["optgate-no-such-device"],
    "system.screenshot_dir": ["out/optgate-shots"],
    "input.overlay_chord": ["", "pad:leftshoulder, pad:rightshoulder"],
}
# "on" value for the combined run (else the last sweep value).  Kept moderate where the
# headless cost would explode (8x x SSAA4).
COMBINED = {
    "graphics.internal_res": "4x", "graphics.antialiasing": "ssaa2", "graphics.aspect": "16:9",
    "display.width": "1920", "display.height": "1080", "display.backend": "d3d11",
    "audio.enabled": "true", "display.interpolation": "true",
    "audio.music_volume": "30", "audio.effects_volume": "55", "audio.voice_volume": "0", "audio.movie_volume": "70",
    "display.window_mode": "fullscreen", "display.monitor": "1",
}
# No $RG_INTERP_SIM in the combined run: the harness reads back and hashes the display after
# every simulated present, which costs ~ the internal resolution's pixel count (2026-10-26:
# route to 1,500 at 3 s Original, 19 s at 2x + sim, 108 s at 8x + sim, 111 s with
# RG_INTERP_SIM_SNAP=1 = no passes at all; the full combined run (4x x SSAA2 = 8x + sim) made
# ~1 field/s).  The interpolation passes are exercised instead by "combined_interp": the
# combined set at 2x without SSAA, with the sim (and by the per-setting sweep at native).
COMBINED_ENV = {}
COMBINED_INTERP = {"graphics.internal_res": "2x", "graphics.antialiasing": "off"}
BINDING_SWEEP = ["", "key:F9"]
QUICK_SET = {"graphics.internal_res": ["2x"], "graphics.aspect": ["16:9"], "audio.music_volume": ["0"],
             "graphics.output_filter": ["crt"]}


def census_rows(path: Path) -> list[dict]:
    lines = path.read_text(encoding="utf-8").splitlines()
    cols = lines[0].split("\t")
    return [dict(zip(cols, ln.split("\t"))) for ln in lines[1:] if ln.strip()]


def src_range(row: dict):
    """min / max of a numeric setting from its initialiser (census src = file:line)."""
    try:
        f, ln = row["src"].rsplit(":", 1)
        text = (PORT / f).read_text(encoding="utf-8").split("\n")
    except (OSError, ValueError):
        return None, None
    body = "\n".join(text[int(ln) - 1:int(ln) + 8])
    body = body[:body.find("}") + 1] if "}" in body else body
    suf = "f" if row["type"] == "FLOAT" else "i"
    lo = re.search(r"\.min_%s\s*=\s*([-0-9.]+)" % suf, body)
    hi = re.search(r"\.max_%s\s*=\s*([-0-9.]+)" % suf, body)
    return (lo.group(1) if lo else None), (hi.group(1) if hi else None)


def base_value(row: dict) -> str:
    return row["original"] if "ORIG" in row["flags"].split(",") else row["default"]


def _num_eq(a, b):
    try:
        return float(a) == float(b)
    except (TypeError, ValueError):
        return a == b


def sweep_values(row: dict) -> list:
    sid, typ, base = row["id"], row["type"], base_value(row)
    if sid in VALUES:
        return list(VALUES[sid])
    if typ == "BOOL":
        return ["false" if base == "true" else "true"]
    if typ == "ENUM":
        vals = [v for v in row["values"].split("|") if v]
        # census can print an enum's macro name (prompts.style); compare names when it is one
        return [v for v in vals if v != base]
    if typ in ("INT", "FLOAT"):
        lo, hi = src_range(row)
        return [v for v in (lo, hi) if v is not None and not _num_eq(v, base)]
    if typ == "BINDING":
        return list(BINDING_SWEEP)
    if typ == "STRING":
        return ["optgate"]
    return []


def classify(row: dict):
    sid = row["id"]
    if sid in CLASS:
        return CLASS[sid]
    sites = [s for s in row["reader_sites"].split() if s != "..."]
    if sid.startswith("input.") or sid.startswith("prompts."):
        return "input", "live input mapping (scripts bypass it); classified from its id"
    files = {s.split(":")[0] for s in sites}
    if files and files <= {"src/host/host_sdl.c", "src/host/host_audio.c"}:
        return "host", "readers only in the SDL host (none headless); classified from reader sites"
    return "headless", "a reader outside the SDL host; classified from reader sites"


def plan_settings(rows: list[dict]):
    excluded, notlive, live = [], [], []
    for r in rows:
        fl = r["flags"].split(",")
        if "GAMEPLAY" in fl:
            excluded.append(r)
        elif "PLACEHOLDER" in fl or r["readers"] == "0":
            notlive.append(r)
        else:
            cls, why = classify(r)
            live.append(dict(r, cls=cls, why=why, sweep=sweep_values(r)))
    return excluded, notlive, live


# ---- jobs ------------------------------------------------------------------------------
def _val(v):
    return (v[0], dict(v[1])) if isinstance(v, tuple) else (v, {})


def scen_route(fields):
    return {"kind": "route", "fields": fields, "name": f"route{fields}"}


def scen_boot(name):
    ms = fxlib.BOOT_FIXTURES[name]
    end = max((m[1][1] if isinstance(m[1], tuple) else m[1]) for m in ms) + 50
    return {"kind": "boot", "boot": name, "fields": end, "name": f"boot_{name}"}


def make_jobs(live, mode, prefix, only):
    jobs = []
    if mode == "quick":
        rscen = [scen_route(prefix or QUICK_PREFIX), scen_boot("save2")]
        full = rscen
    else:
        rscen = [scen_route(prefix or SWEEP_PREFIX)] + [scen_boot(b) for b in BOOTS_SWEEP]
        full = [scen_route(FULL_ROUTE)] + [scen_boot(b) for b in BOOTS_ALL]
    base_scen = {s["name"]: s for s in rscen + full}

    def add(cfg, label, sets, env, scens, preset="original", setting=None, value=None, args=()):
        for s in scens:
            jobs.append({"cfg": cfg, "label": label, "sets": sets, "env": env, "scen": s,
                         "preset": preset, "setting": setting, "value": value, "args": list(args),
                         "id": f"{cfg}__{s['name']}"})

    # the control (probe-arming proof): a setting on a path the scripted run DOES reach, with
    # input that uses it -- the mouse camera turned by scripted mouse motion right after field
    # control (save2 boot: control from ~3,725).  It must be reported DIFF, or the gate is blind.
    add("control", "CONTROL: input.mouse_look=true + --mouse-motion 3730-3790:40:0 (must differ)",
        ["input.mouse_look=true"], {}, [scen_boot("save2")], args=["--mouse-motion", "3730-3790:40:0"])

    add("original", "Original preset", [], {}, list(base_scen.values()))
    if mode == "quick":
        for sid, vals in QUICK_SET.items():
            for i, v in enumerate(vals):
                add(f"q_{sid}_{i}", f"{sid}={v}", [f"{sid}={v}"], {}, rscen, setting=sid, value=v)
        return jobs, base_scen
    groups = {"host": [], "input": []}
    on = []
    for r in live:
        if only and r["id"] not in only:
            continue
        if r["cls"] == "headless":
            for i, v in enumerate(r["sweep"]):
                val, env = _val(v)
                tag = val + (" +" + ",".join(f"{k}={x}" for k, x in env.items()) if env else "")
                add(f"s_{r['id']}_{i}", f"{r['id']}={tag}", [f"{r['id']}={val}"], env, rscen,
                    setting=r["id"], value=tag)
        elif r["sweep"]:
            groups[r["cls"]].append(f"{r['id']}={_val(r['sweep'][-1])[0]}")
        if r["sweep"]:
            on.append(f"{r['id']}={COMBINED.get(r['id'], _val(r['sweep'][-1])[0])}")
    if not only:
        for g, sets in groups.items():
            if sets:
                add(f"nth_{g}", f"not-testable-headless group '{g}' ({len(sets)} settings)", sets, {}, rscen)
        add("combined", f"everything on ({len(on)} settings)", on, dict(COMBINED_ENV), full)
        on_ip = [x for x in on if x.split("=")[0] not in COMBINED_INTERP] + [f"{k}={v}" for k, v in COMBINED_INTERP.items()]
        add("combined_interp", "everything on, 2x / no SSAA, with RG_INTERP_SIM=120", on_ip,
            {"RG_INTERP_SIM": "120"}, rscen)
        add("preset_default", "default preset (--preset default)", [], {}, full, preset="default")
    return jobs, base_scen


# ---- running ---------------------------------------------------------------------------
def snapshot_exe(exe: Path, out: Path) -> Path:
    eid = fxlib.exe_id(exe)
    d = out / "exe" / eid
    dst = d / exe.name
    if not dst.exists():
        d.mkdir(parents=True, exist_ok=True)
        for f in [exe, exe.with_suffix(".map")] + sorted(exe.parent.glob("*.dll")):
            if f.exists():
                tmp = d / f"{f.name}.{os.getpid()}.tmp"
                shutil.copy2(f, tmp)
                tmp.replace(d / f.name)
    return dst


def job_key(job, eid):
    return json.dumps([eid, job["preset"], job["sets"], sorted(job["env"].items()), job["scen"], job["args"]],
                      sort_keys=True)


def pid_alive(pid: int) -> bool:
    if pid <= 0:
        return False
    if os.name == "nt":
        import ctypes
        h = ctypes.windll.kernel32.OpenProcess(0x1000, False, pid)   # PROCESS_QUERY_LIMITED_INFORMATION
        if not h:
            return False
        code = ctypes.c_ulong()
        ctypes.windll.kernel32.GetExitCodeProcess(h, ctypes.byref(code))
        ctypes.windll.kernel32.CloseHandle(h)
        return code.value == 259   # STILL_ACTIVE
    try:
        os.kill(pid, 0)
        return True
    except OSError:
        return False


def claim(d: Path) -> bool:
    d.mkdir(parents=True, exist_ok=True)
    c = d / "claim"
    for _ in range(2):
        try:
            fd = os.open(str(c), os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            os.write(fd, str(os.getpid()).encode())
            os.close(fd)
            return True
        except FileExistsError:
            try:
                pid = int(c.read_text().strip() or 0)
            except (OSError, ValueError):
                pid = 0
            if pid == os.getpid() or pid_alive(pid):
                return False
            try:
                c.unlink()   # dead claimer
            except OSError:
                return False
    return False


def read_hashlog(p: Path) -> dict:
    rows = {}
    if not p.exists():
        return rows
    with open(p, encoding="utf-8", errors="replace") as f:
        hdr = f.readline().rstrip("\n").split("\t")
        for line in f:
            if line[:1].isdigit():
                v = line.rstrip("\n").split("\t")
                rows[int(v[0])] = dict(zip(hdr, v))
    return rows


def run_job(job, exe: Path, eid: str, out: Path, timeout_s: float | None = None) -> dict | None:
    d = out / "jobs" / job["id"]
    res_p = d / "result.json"
    key = job_key(job, eid)
    if res_p.exists():
        r = json.loads(res_p.read_text(encoding="utf-8"))
        if r.get("key") == key and not (r.get("timeout") and timeout_s and timeout_s > r.get("timeout_s", 0)):
            return r
    if not claim(d):
        return None
    try:
        if res_p.exists():   # finished by another runner meanwhile
            r = json.loads(res_p.read_text(encoding="utf-8"))
            if r.get("key") == key:
                return r
        saves = d / "saves"
        shutil.rmtree(saves, ignore_errors=True)
        s = job["scen"]
        if s["kind"] == "boot":
            card = fxlib.BOOT_CARD.get(s["boot"], s["boot"])
            shutil.copytree(fxlib.CARDS / card, saves)
            inp = fxlib.PORT / "tools" / "trace" / "goldens" / f"boot_{s['boot']}.input.txt"
        else:
            saves.mkdir(parents=True)
            inp = fxlib.GOLDEN
        hl = d / "hash.tsv"
        cmd = [str(exe), "--headless", "--fields", str(s["fields"]), "--saves", str(saves), "--input", str(inp),
               "--preset", job["preset"]]
        for x in job["sets"]:
            cmd += ["--set", x]
        cmd += job["args"]
        env = fxlib.game_env(dict(job["env"], RG_HASH_LOG=str(hl), RG_QUIET="1"))
        t0 = time.time()
        with open(d / "port.log", "w", encoding="utf-8", errors="replace") as log:
            log.write(" ".join(cmd) + "\n" + json.dumps(job["env"]) + "\n")
            log.flush()
            p = subprocess.Popen(cmd, env=env, stdout=log, stderr=subprocess.STDOUT, cwd=str(d))
            timed_out = False
            try:
                rc = p.wait(timeout=timeout_s)
            except subprocess.TimeoutExpired:
                p.kill()          # our own child, by handle
                rc = p.wait()
                timed_out = True
        text = (d / "port.log").read_text(encoding="utf-8", errors="replace")
        m = re.findall(r"run_hash=([0-9a-f]{16})", text)
        rows = read_hashlog(hl)
        last = rows[max(rows)] if rows else {}
        r = {"key": key, "id": job["id"], "rc": rc, "run_hash": m[-1] if m else None,
             "field": max(rows) if rows else None, "audio": last.get("audio"), "last": last,
             "wall_s": round(time.time() - t0, 1), "timeout": timed_out, "timeout_s": timeout_s, "settings_errors": [ln for ln in text.splitlines()[2:] if "ignored" in ln or "bad settings" in ln][:5]}
        shutil.rmtree(saves, ignore_errors=True)
        tmp = d / "result.json.tmp"
        tmp.write_text(json.dumps(r, indent=1), encoding="utf-8")
        tmp.replace(res_p)
        return r
    finally:
        try:
            (d / "claim").unlink()
        except OSError:
            pass


def compare(job, r, base, out: Path) -> dict:
    """Verdict of one finished job against its scenario's baseline."""
    if r is None or base is None:
        return {"verdict": "PENDING"}
    if job["cfg"] == "original":
        ok = r["rc"] == 0 and r["run_hash"] and r["field"] == job["scen"]["fields"]
        return {"verdict": "BASE" if ok else "ERROR", "detail": "" if ok else f"rc {r['rc']} field {r['field']}"}
    if r.get("timeout"):
        a = read_hashlog(out / "jobs" / job["id"] / "hash.tsv")
        b = read_hashlog(out / "jobs" / base["id"] / "hash.tsv")
        firstd = next((f for f in sorted(a) if f in b and any(a[f].get(c) != b[f].get(c) for c in COLS)), None)
        return {"verdict": "SLOW", "detail": f"killed after {r['wall_s']:.0f} s (limit {r.get('timeout_s', 0):.0f} s, "
                f"baseline {base.get('wall_s')} s) at field {r['field']}; hash log "
                + (f"differs from field {firstd}" if firstd is not None else f"equal to the baseline up to field {r['field']}")}
    if r["rc"] != 0 and r["field"] is None:
        return {"verdict": "ERROR", "detail": f"rc {r['rc']} (no field ran: bad --set? see port.log)"}
    same = (r["run_hash"] == base["run_hash"] and r["audio"] == base["audio"] and r["field"] == base["field"]
            and r["rc"] == base["rc"])
    if job["cfg"] == "control" and same:
        return {"verdict": "ERROR", "detail": "CONTROL NOT DETECTED: the gate is blind"}
    if same:
        if job["cfg"] != "original":
            hl = out / "jobs" / job["id"] / "hash.tsv"
            try:
                hl.unlink()   # equal: the result.json keeps the last row
            except OSError:
                pass
        return {"verdict": "EQUAL", "detail": ""}
    a = read_hashlog(out / "jobs" / job["id"] / "hash.tsv")
    b = read_hashlog(out / "jobs" / base["id"] / "hash.tsv")
    first, cols = None, []
    for f in sorted(set(a) | set(b)):
        ra, rb = a.get(f), b.get(f)
        if ra is None or rb is None:
            first, cols = f, ["(run ended)" if ra is None else "(baseline ended)"]
            break
        diff = [c for c in COLS if ra.get(c) != rb.get(c)]
        if diff:
            first, cols = f, diff
            break
    det = f"rc {r['rc']} vs {base['rc']}; " if r["rc"] != base["rc"] else ""
    det += f"first differing field {first}: {','.join(cols)}" if first is not None else "hash logs equal (exit / final line differs)"
    if job["cfg"] == "control":
        return {"verdict": "CONTROL_OK", "detail": "detected, as it must be: " + det}
    return {"verdict": "DIFF", "detail": det, "first_field": first, "first_cols": cols,
            "run_eq": r["run_hash"] == base["run_hash"], "audio_eq": r["audio"] == base["audio"]}


def census_for(a, out: Path) -> Path:
    if a.census:
        return Path(a.census)
    out.mkdir(parents=True, exist_ok=True)
    p = out / "settings.tsv"
    subprocess.run([sys.executable, str(PORT / "tools" / "settings_census.py"), "-o", str(p)], check=True,
                   stderr=subprocess.DEVNULL)
    return p


def write_report(out: Path, jobs, results, verdicts, rows, excluded, notlive, live, mode, eid, wall) -> int:
    ck = PORT / "census" / "settings.tsv"
    old = {r["id"] for r in census_rows(ck)} if ck.exists() else set()
    new_ids = [r["id"] for r in rows if r["id"] not in old]
    gone = sorted(old - {r["id"] for r in rows})
    tsv = ["job\tsetting\tvalue\tscenario\tverdict\trun_hash\taudio\tfield\trc\twall_s\tdetail"]
    for j in jobs:
        r, v = results.get(j["id"]), verdicts[j["id"]]
        tsv.append("\t".join(str(x) for x in [j["cfg"], j["setting"] or j["label"], j["value"] or "", j["scen"]["name"],
                                              v["verdict"], (r or {}).get("run_hash"), (r or {}).get("audio"),
                                              (r or {}).get("field"), (r or {}).get("rc"), (r or {}).get("wall_s"),
                                              v.get("detail", "")]))
    (out / "report.tsv").write_text("\n".join(tsv) + "\n", encoding="utf-8")
    cnt = {}
    for v in verdicts.values():
        cnt[v["verdict"]] = cnt.get(v["verdict"], 0) + 1
    md = [f"# Options-matrix gate ({mode})", "",
          f"exe id `{eid}`; {len(jobs)} jobs; " + ", ".join(f"{k} {n}" for k, n in sorted(cnt.items()))
          + f"; wall {wall / 60:.1f} min this invocation", ""]
    base = {j["scen"]["name"]: results.get(j["id"]) for j in jobs if j["cfg"] == "original"}
    md += ["## Original baselines", "", "| scenario | run hash | audio part | field | rc |", "| --- | --- | --- | --- | --- |"]
    for n, r in base.items():
        md.append(f"| {n} | `{(r or {}).get('run_hash')}` | `{(r or {}).get('audio')}` | {(r or {}).get('field')} | {(r or {}).get('rc')} |")
    r31 = base.get(f"route{FULL_ROUTE}")
    if r31:
        md += ["", f"Reference power-on to {FULL_ROUTE}: `{REFERENCE_31700}` -> "
               + ("**equal**" if r31.get("run_hash") == REFERENCE_31700 else f"**differs** (`{r31.get('run_hash')}`)")]
    md += ["", "## Swept settings (headless)", "", "| setting | values tried | equal | first difference |", "| --- | --- | --- | --- |"]
    by_set = {}
    for j in jobs:
        if j["setting"]:
            by_set.setdefault(j["setting"], []).append(j)
    for sid, js in by_set.items():
        vals = sorted({j["value"] for j in js}, key=str)
        vs = [verdicts[j["id"]] for j in js]
        eq = "yes" if all(v["verdict"] == "EQUAL" for v in vs) else (
            "pending" if any(v["verdict"] == "PENDING" for v in vs) else "**no**")
        firsts = [f"{j['value']} / {j['scen']['name']}: {verdicts[j['id']].get('detail')}" for j in js
                  if verdicts[j["id"]]["verdict"] not in ("EQUAL", "PENDING")]
        md.append(f"| `{sid}` | {', '.join(f'`{v}`' for v in vals)} | {eq} | {'; '.join(firsts)} |")
    grp = [j for j in jobs if not j["setting"] and j["cfg"] != "original"]
    md += ["", "## Group and combined runs", "", "| run | scenario | verdict | detail |", "| --- | --- | --- | --- |"]
    for j in grp:
        md.append(f"| {j['label']} | {j['scen']['name']} | {verdicts[j['id']]['verdict']} | {verdicts[j['id']].get('detail', '')} |")
    for j in grp:
        if j["cfg"] == "combined":
            md += ["", "Combined settings: " + " ".join(f"`{s}`" for s in j["sets"]) + " (+ env "
                   + ",".join(f"{k}={v}" for k, v in j["env"].items()) + ")"]
            break
    nth = [r for r in live if r["cls"] != "headless"]
    md += ["", "## Not testable headless (never counted as a pass; leak-checked in the group / combined runs)", "",
           "| setting | group | why |", "| --- | --- | --- |"]
    md += [f"| `{r['id']}` | {r['cls']} | {r['why']} |" for r in nth if not r["id"].startswith("input.bind.")]
    nb = [r["id"] for r in nth if r["id"].startswith("input.bind.")]
    if nb:
        md.append(f"| `input.bind.*` ({len(nb)}) | input | live input mapping; scripts bypass it |")
    notes = [r for r in live if r["cls"] == "headless" and r["id"] in CLASS]
    if notes:
        md += ["", "Notes on swept settings: " + "; ".join(f"`{r['id']}`: {r['why']}" for r in notes)]
    md += ["", "## Excluded (gameplay)", ""] + [f"- `{r['id']}`" for r in excluded]
    md += ["", "## Not live (placeholder or no reader)", ""] + [f"- `{r['id']}` ({r['flags']})" for r in notlive]
    md += ["", "## Census", "", f"{len(rows)} settings in the fresh census; new since census/settings.tsv: "
           + (", ".join(f"`{i}`" for i in new_ids) or "none") + "; gone: " + (", ".join(gone) or "none")]
    (out / "report.md").write_text("\n".join(md) + "\n", encoding="utf-8")
    if any(v["verdict"] in ("DIFF", "ERROR", "SLOW") for v in verdicts.values()):
        return 1
    if any(v["verdict"] == "PENDING" for v in verdicts.values()):
        return 75
    return 0


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["run", "plan", "report"])
    ap.add_argument("--exe")
    ap.add_argument("--mode", choices=["quick", "full"], default="full")
    ap.add_argument("--out")
    ap.add_argument("--census", help="settings TSV to use (default: a fresh settings_census.py run)")
    ap.add_argument("-j", "--jobs", type=int, default=2)
    ap.add_argument("--max-hours", type=float, default=1.8,
                    help="no job starts after H hours and a running one is killed at H (default 1.8)")
    ap.add_argument("--timeout-factor", type=float, default=10.0,
                    help="kill a job after F x its scenario's Original wall time (verdict SLOW, a finding)")
    ap.add_argument("--timeout-min", type=float, default=600.0, help="... but never before this many seconds")
    ap.add_argument("--prefix", type=int, help="route fields of the sweep scenario")
    ap.add_argument("--only", help="comma list of setting ids to sweep (no group / combined runs)")
    ap.add_argument("--skip-missing", action="store_true", help="exit 77 when the exe, data or cards are missing")
    a = ap.parse_args(argv)
    out = Path(a.out or PORT / "out" / "optgate" / a.mode).resolve()
    rows = census_rows(census_for(a, out))
    excluded, notlive, live = plan_settings(rows)
    only = set(a.only.split(",")) if a.only else None
    jobs, _ = make_jobs(live, a.mode, a.prefix, only)
    if a.cmd == "plan":
        for j in jobs:
            print(f"{j['id']:60s} {j['scen']['fields']:6d}  {' '.join(j['sets'])[:140]}  {j['env'] or ''}")
        print(f"{len(jobs)} jobs; live {len(live)} (headless {sum(r['cls'] == 'headless' for r in live)}), "
              f"excluded {len(excluded)}, not live {len(notlive)}", file=sys.stderr)
        return 0
    exe = Path(a.exe or fxlib.exe_path()).resolve()
    need = [exe, fxlib.PORT / "data", fxlib.CARDS / "save2"]
    if any(not p.exists() for p in need):
        print("optgate: missing " + ", ".join(str(p) for p in need if not p.exists()))
        return 77 if a.skip_missing else 2
    eid = fxlib.exe_id(exe)
    t0 = time.time()
    if a.cmd == "run":
        exe_run = snapshot_exe(exe, out)
        base_first = [j for j in jobs if j["cfg"] == "original"]
        rest = [j for j in jobs if j["cfg"] != "original"]
        deadline = t0 + a.max_hours * 3600
        done = 0

        def go(j):
            left = deadline - time.time()
            if left <= 60:
                return j, None
            lim = left
            if j["cfg"] != "original":
                bp = out / "jobs" / f"original__{j['scen']['name']}" / "result.json"
                bw = json.loads(bp.read_text(encoding="utf-8")).get("wall_s", 0) if bp.exists() else 0
                lim = min(left, max(a.timeout_min, a.timeout_factor * bw))
            return j, run_job(j, exe_run, eid, out, lim)

        for batch in (base_first, rest):
            with ThreadPoolExecutor(max_workers=max(1, a.jobs)) as ex:
                futs = [ex.submit(go, j) for j in batch]
                for f in as_completed(futs):
                    j, r = f.result()
                    done += 1
                    st = "skipped (budget / claimed)" if r is None else \
                        f"rc {r['rc']} field {r['field']} run {r['run_hash']} audio {r['audio']} {r['wall_s']} s"
                    print(f"[{done}/{len(jobs)}] {j['id']}: {st}", flush=True)
    results = {}
    for j in jobs:
        p = out / "jobs" / j["id"] / "result.json"
        if p.exists():
            r = json.loads(p.read_text(encoding="utf-8"))
            if r.get("key") == job_key(j, eid):
                results[j["id"]] = r
    bases = {j["scen"]["name"]: dict(results[j["id"]], id=j["id"]) for j in jobs
             if j["cfg"] == "original" and j["id"] in results}
    verdicts = {j["id"]: compare(j, results.get(j["id"]), bases.get(j["scen"]["name"]), out) for j in jobs}
    rc = write_report(out, jobs, results, verdicts, rows, excluded, notlive, live, a.mode, eid, time.time() - t0)
    bad = [(j["id"], verdicts[j["id"]]) for j in jobs if verdicts[j["id"]]["verdict"] in ("DIFF", "ERROR", "SLOW")]
    for i, v in bad:
        print(f"  {v['verdict']}: {i}: {v.get('detail', '')}")
    print(f"optgate: {out / 'report.md'}; " + {0: "PASS", 1: "FAIL", 75: "INCOMPLETE (run again to resume)"}[rc])
    return rc


if __name__ == "__main__":
    sys.exit(main())

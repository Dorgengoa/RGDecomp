#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Frame-rate gate (PLAN.md "Unlocked frame rate" Gate; docs/P6-STATUS.md "Frame-rate gate";
docs/TEST-FIXTURES.md "Frame-rate gate"): the regression corpus must give the same logic at every
presentation rate, with interpolation on / off, retail and host pacing, and jittered presents:
per field the run hash, the audio part, pad reads, the kernel trace and the clock all equal the
Original run of the same scenario (and the run hash + audio part at every milestone).

    python tools/p6/fpsgate.py run    --exe EXE --tier quick|rates|full|lib|drivers|window [--out DIR]
                                      [-j N] [--max-hours H]
    python tools/p6/fpsgate.py plan   --tier T          # the job list, runs nothing
    python tools/p6/fpsgate.py report --tier T [--out DIR]

Headless, the presentation is simulated (runtime.c ip_sim_field): with display.interpolation on,
$RG_INTERP_SIM=hz makes after every field the presents a host at hz would make before the next
phase (each an interpolation pass + the display read back, then the restore);
$RG_INTERP_SIM_SNAP=1 the same presents without passes (interpolation off: the newest frame shown
again); $RG_INTERP_SIM_JITTER=seed random presents (0..8 per phase at random sorted times, repeats:
frames with zero ticks and frames with several); $RG_INTERP_CHECK=1 an exact re-render of the
newest frame per field.  Headless forces retail pacing, so display.frame_rate / display.pacing are
leak-checked there and exercised for real by the window tier (no --headless, real time, host or
retail pacing, $RG_PACE_JITTER=ms: a noisy host clock + random host stalls).

Every job proves its hook ran (probe arming): sim jobs need "sim N presents" with N > 0 (and
passes > 0 with interpolation), window jobs the pacing mode of $RG_PACE_LOG's summary, between-
phase presents with interpolation, stalls with jitter.  The CONTROL job (input.mouse_look + mouse
motion on the save2 boot, as optgate.py) must be reported different, or the gate is blind.

Tiers (each < 2 h at -j 2 on a quiet machine; resumable, --max-hours stops starting jobs):
  quick    route to 2,000 + save2 boot: Original, 144 Hz interpolated, 60 Hz snapshots, jitter
           (+ exact check), host / 240 / no-interp leak, control              (ctest fixtures.fpsgate_quick)
  rates    route to 13,000 + save2_battle2 (battle 2 won): every display.frame_rate value
           interpolated (30/60/120/144/165/240/display=60/uncapped=300 Hz), snapshots at 30/144/300
  full     route to 31,700 (milestones title .. saved) + boots save2/factory/insectron/
           save2_battle2: jitter + exact check, 144 Hz interpolated, control
  lib      the 25 card-library cards (boot, recap, control; bootcheck.py pass-1 script to 4,700):
           jitter
  drivers  the closed-loop drivers' open-loop replays (insectrun, factory, insectstory;
           tools/trace/goldens/fpsgate_drv_*.input.txt): jitter
  window   windowed (real time; no rg_slots): route to 13,000 + save2_battle2 at retail pacing,
           host 60, host 144 / uncapped / display interpolated, host jitter 40 ms with and
           without interpolation; the reference is the headless Original of the same exe
Exit 0 = every job equal and armed, 1 = a difference / unarmed / error, 75 = incomplete.
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
sys.path.insert(0, str(PORT / "tools" / "p6"))
import fxlib  # noqa: E402
import optgate  # noqa: E402  (snapshot_exe, claim, read_hashlog)

COLS = ["run_hash", "audio", "pad", "ktrace", "ktrace_n", "now"]
GOLD = PORT / "tools" / "trace" / "goldens"
# display.frame_rate -> the simulated present rate headless (rg_frame_cap_fps: "display" with no
# display = 60; uncapped = 300, five presents per phase)
SIM_HZ = {"30": 30, "60": 60, "120": 120, "144": 144, "165": 165, "240": 240, "display": 60, "uncapped": 300}
DRIVERS = {   # name: (card, last field)   (soak.py DRIVERS, recorded by the optgate lane 10-31)
    "insectrun": ("insectron_play", 21100),
    "factory": ("factory_prod", 32458),
    "insectstory": ("insect_final_s", 18520),
}
LIB_FIELDS = 4700


# ---- scenarios -------------------------------------------------------------------------
def scen_route(n):
    ms = [(nm, f) for nm, f, _ in fxlib.MILESTONES if f <= n]
    return {"kind": "route", "name": f"route{n}", "fields": n, "card": None, "input": str(fxlib.GOLDEN),
            "ms": ms + [("end", n)]}


def scen_boot(name):
    ms = []
    for m in fxlib.BOOT_FIXTURES[name]:
        f = m[1][1] if isinstance(m[1], tuple) else m[1]
        ms.append((m[0], f))
    end = max(f for _, f in ms) + 50
    return {"kind": "boot", "name": f"boot_{name}", "fields": end, "card": fxlib.BOOT_CARD.get(name, name),
            "input": str(GOLD / f"boot_{name}.input.txt"), "ms": ms + [("end", end)]}


def lib_input() -> Path:
    import bootcheck
    p = PORT / "out" / "fpsgate" / "inputs" / "lib_pass1.input.txt"
    txt = bootcheck.lib_script(None)
    if not p.exists() or p.read_text(encoding="utf-8") != txt:
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(txt, encoding="utf-8")
    return p


def scen_lib(card):
    return {"kind": "lib", "name": f"lib_{card}", "fields": LIB_FIELDS, "card": card, "input": str(lib_input()),
            "ms": [("load", 2700), ("recap", 3700), ("control?", 4000), ("end", LIB_FIELDS)]}


def scen_drv(name):
    card, last = DRIVERS[name]
    end = last + 50
    step = max(2000, end // 8)
    return {"kind": "drv", "name": f"drv_{name}", "fields": end, "card": card,
            "input": str(GOLD / f"fpsgate_drv_{name}.input.txt"),
            "ms": [(f"f{f}", f) for f in range(step, end, step)] + [("end", end)]}


# ---- configurations --------------------------------------------------------------------
IP = ["display.interpolation=true", "display.pacing=host"]


def cfg(name, label, sets=(), env=None, arm=None, window=False, preset="original", args=()):
    return {"cfg": name, "label": label, "sets": list(sets), "env": dict(env or {}), "arm": arm,
            "window": window, "preset": preset, "args": list(args)}


BASE = cfg("original", "Original preset (the reference)")
CONTROL = cfg("control", "CONTROL: input.mouse_look=true + --mouse-motion 3730-3790:40:0 (must differ)",
              ["input.mouse_look=true"], args=["--mouse-motion", "3730-3790:40:0"])


def ip_rate(r):
    return cfg(f"ip_{r}", f"frame_rate {r}, interpolation on, host pacing; sim {SIM_HZ[r]} Hz",
               [f"display.frame_rate={r}"] + IP, {"RG_INTERP_SIM": str(SIM_HZ[r])}, arm="pass")


def snap_rate(r):
    return cfg(f"snap_{r}", f"frame_rate {r}, presents of the newest frame (no passes); sim {SIM_HZ[r]} Hz snapshots",
               [f"display.frame_rate={r}"] + IP, {"RG_INTERP_SIM": str(SIM_HZ[r]), "RG_INTERP_SIM_SNAP": "1"},
               arm="present")


JIT = cfg("jit", "frame_rate uncapped, interpolation on; jittered presents (0..8 per phase) + exact re-render per field",
          ["display.frame_rate=uncapped"] + IP, {"RG_INTERP_SIM_JITTER": "1", "RG_INTERP_CHECK": "1"}, arm="pass")
JIT_LITE = cfg("jit", "frame_rate uncapped, interpolation on; jittered presents (0..8 per phase)",
               ["display.frame_rate=uncapped"] + IP, {"RG_INTERP_SIM_JITTER": "2"}, arm="pass")
JIT_SNAP = cfg("jitsnap", "jittered presents of the newest frame (no passes)",
               ["display.frame_rate=uncapped"] + IP,
               {"RG_INTERP_SIM_JITTER": "3", "RG_INTERP_SIM_SNAP": "1"}, arm="present")
LEAK = cfg("leak", "frame_rate 240, host pacing, vsync off, interpolation off (settings leak check)",
           ["display.frame_rate=240", "display.pacing=host", "display.vsync=false", "display.interpolation=false"])


def wcfg(name, label, sets, env=None, arm="host"):
    e = {"RG_GPU": "hw"}
    e.update(env or {})
    return cfg(name, label, sets, e, arm=arm, window=True)


WINDOW = [
    wcfg("w_retail", "window, retail pacing, frame_rate original", ["display.pacing=retail"], arm="retail"),
    wcfg("w_host60", "window, host pacing, 60, interpolation off", ["display.pacing=host", "display.frame_rate=60"]),
    wcfg("w_ip144", "window, host pacing, 144, interpolation on", ["display.frame_rate=144"] + IP, arm="host_ip"),
    wcfg("w_ipunc", "window, host pacing, uncapped, interpolation on", ["display.frame_rate=uncapped"] + IP,
         arm="host_ip"),
    wcfg("w_ipdisp", "window, host pacing, display rate, interpolation on", ["display.frame_rate=display"] + IP,
         arm="host_ip"),
    wcfg("w_jit_ip", "window, host pacing, uncapped, interpolation on, host jitter 40 ms",
         ["display.frame_rate=uncapped"] + IP, {"RG_PACE_JITTER": "40:1"}, arm="host_ip_jit"),
    wcfg("w_jit_off", "window, host pacing, 144, interpolation off, host jitter 40 ms",
         ["display.pacing=host", "display.frame_rate=144"], {"RG_PACE_JITTER": "40:2"}, arm="host_jit"),
]


def tier_jobs(tier):
    """[(cfg, scenario)] of a tier; the Original of each scenario first."""
    if tier == "quick":
        sc = [scen_route(2000), scen_boot("save2")]
        cf = [BASE, ip_rate("144"), snap_rate("60"), JIT, LEAK]
        extra = [(CONTROL, scen_boot("save2"))]
    elif tier == "rates":
        sc = [scen_route(13000), scen_boot("save2_battle2")]
        cf = [BASE] + [ip_rate(r) for r in SIM_HZ] + [snap_rate(r) for r in ("30", "144", "uncapped")] + [LEAK]
        extra = []
    elif tier == "full":
        sc = [scen_route(31700)] + [scen_boot(b) for b in ("save2", "factory", "insectron", "save2_battle2")]
        cf = [BASE, JIT, ip_rate("144")]
        extra = [(CONTROL, scen_boot("save2"))]
    elif tier == "lib":
        import cardlib
        sc = [scen_lib(c) for c in cardlib.LIBRARY if (fxlib.CARDS / c).exists()]
        cf = [BASE, JIT_LITE]
        extra = []
    elif tier == "drivers":
        sc = [scen_drv(d) for d in DRIVERS if (fxlib.CARDS / DRIVERS[d][0]).exists()]
        cf = [BASE, JIT_LITE, JIT_SNAP]
        extra = []
    elif tier == "window":
        sc = [scen_route(13000), scen_boot("save2_battle2")]
        cf = [BASE] + WINDOW
        extra = []
    else:
        raise SystemExit(f"unknown tier {tier}")
    pairs = [(c, s) for c in cf for s in sc] + extra
    jobs = []
    for c, s in pairs:
        j = dict(c, scen=s, id=f"{c['cfg']}__{s['name']}")
        jobs.append(j)
    return jobs


# ---- running ---------------------------------------------------------------------------
def job_key(job, eid):
    return json.dumps([eid, job["preset"], job["sets"], sorted(job["env"].items()), job["scen"]["name"],
                       job["scen"]["fields"], job["scen"]["input"], job["args"], job["window"]], sort_keys=True)


def parse_arming(text):
    a = {}
    m = re.search(r"sim (\d+) presents at [0-9.]+ Hz \((\d+) from a pass\)", text)
    if m:
        a["sim_presents"], a["sim_passes"] = int(m.group(1)), int(m.group(2))
    m = re.search(r"exact check (\d+) same, (\d+) differ", text)
    if m:
        a["check_same"], a["check_differ"] = int(m.group(1)), int(m.group(2))
    m = re.search(r"interpolated presents (\d+) \(between phases (\d+)\)", text)
    if m:
        a["ip_presents"], a["ip_between"] = int(m.group(1)), int(m.group(2))
    m = re.search(r"rg_pace: mode=(\w+) cap=(\d+).*?presents=(\d+).*?between=(\d+)", text)
    if m:
        a["pace_mode"], a["pace_cap"], a["presents"], a["between"] = m.group(1), int(m.group(2)), int(m.group(3)), int(m.group(4))
    m = re.search(r"interp: passes (\d+)", text)
    if m:
        a["ip_passes"] = int(m.group(1))   # (windowed: the GS worker's interpolated presents)
    m = re.search(r"rg_pace: .*?dropped=(\d+)", text)
    if m:
        a["dropped"] = int(m.group(1))
    m = re.search(r"jitter=(\d+)ms stalls=(\d+)", text)
    if m:
        a["jit_stalls"] = int(m.group(2))
    m = re.search(r"phases/present:([ 0-9+:]*)", text)
    if m:
        a["hist"] = m.group(1).strip()
    return a


def armed(job, a):
    """'' when the job's hook demonstrably ran, else why not"""
    k = job.get("arm")
    if not k:
        return ""
    if k == "pass":
        if not a.get("sim_presents") or not a.get("sim_passes"):
            return f"interpolation sim not armed ({a.get('sim_presents')} presents, {a.get('sim_passes')} passes)"
        if job["env"].get("RG_INTERP_CHECK") and not (a.get("check_same", 0) + a.get("check_differ", 0)):
            return "exact check not armed"
        return ""
    if k == "present":
        return "" if a.get("sim_presents") else "sim presents not armed"
    want = "retail" if k == "retail" else "host"
    if a.get("pace_mode") != want:
        return f"pacing {a.get('pace_mode')} (wanted {want})"
    if "ip" in k and not (a.get("ip_between") or a.get("between") or a.get("ip_passes")):
        return f"no interpolated presents ({a.get('ip_between')}/{a.get('between')}/{a.get('ip_passes')})"
    if "jit" in k and not a.get("jit_stalls"):
        return "no jitter stalls"
    return ""


def run_job(job, exe: Path, eid: str, out: Path, timeout_s=None):
    d = out / "jobs" / job["id"]
    res_p = d / "result.json"
    key = job_key(job, eid)
    if res_p.exists():
        r = json.loads(res_p.read_text(encoding="utf-8"))
        if r.get("key") == key and not (r.get("timeout") and timeout_s and timeout_s > r.get("timeout_s", 0)):
            return r
    if not optgate.claim(d):
        return None
    try:
        s = job["scen"]
        saves = d / "saves"
        shutil.rmtree(saves, ignore_errors=True)
        if s["card"]:
            shutil.copytree(fxlib.CARDS / s["card"], saves)
        else:
            saves.mkdir(parents=True)
        hl = d / "hash.tsv"
        cmd = [str(exe)] + ([] if job["window"] else ["--headless"]) + [
            "--fields", str(s["fields"]), "--saves", str(saves), "--input", s["input"], "--preset", job["preset"]]
        for x in job["sets"]:
            cmd += ["--set", x]
        cmd += job["args"]
        env = dict(job["env"], RG_HASH_LOG=str(hl))
        if job["window"]:
            env["RG_PACE_LOG"] = str(d / "pace.tsv")
        env = fxlib.game_env(env)
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
        rows = optgate.read_hashlog(hl)
        last = rows[max(rows)] if rows else {}
        r = {"key": key, "id": job["id"], "rc": rc, "run_hash": m[-1] if m else None,
             "field": max(rows) if rows else None, "audio": last.get("audio"), "last": last,
             "ms": {nm: [rows[f].get("run_hash"), rows[f].get("audio")] if f in rows else None for nm, f in s["ms"]},
             "arming": parse_arming(text), "wall_s": round(time.time() - t0, 1), "timeout": timed_out,
             "timeout_s": timeout_s,
             "settings_errors": [ln for ln in text.splitlines()[2:] if "ignored" in ln or "bad settings" in ln][:5]}
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


def base_id(job):
    return f"original__{job['scen']['name']}"


def compare(job, r, base, out: Path) -> dict:
    if r is None or base is None:
        return {"verdict": "PENDING"}
    s = job["scen"]
    if job["cfg"] == "original":
        ok = r["rc"] == 0 and r["run_hash"] and r["field"] == s["fields"]
        return {"verdict": "BASE" if ok else "ERROR", "detail": "" if ok else f"rc {r['rc']} field {r['field']}"}
    if r.get("timeout"):
        return {"verdict": "SLOW", "detail": f"killed after {r['wall_s']:.0f} s at field {r['field']}"}
    if r["settings_errors"]:
        return {"verdict": "ERROR", "detail": "; ".join(r["settings_errors"])}
    hl = out / "jobs" / job["id"] / "hash.tsv"
    a = optgate.read_hashlog(hl)
    b = optgate.read_hashlog(out / "jobs" / base["id"] / "hash.tsv")
    first, cols = None, []
    if not hl.exists() and (r.get("fields_equal") == base.get("run_hash") or (
            "fields_equal" not in r and r["run_hash"] == base["run_hash"] and r["audio"] == base["audio"])):
        # compared field by field by an earlier report (which drops an equal job's hash log;
        # fields_equal records it since 11-01 evening, before that only an EQUAL verdict dropped it)
        a = b
    for f in sorted(set(a) | set(b)):
        ra, rb = a.get(f), b.get(f)
        if ra is None or rb is None:
            first, cols = f, ["(run ended)" if ra is None else "(reference ended)"]
            break
        diff = [c for c in COLS if ra.get(c) != rb.get(c)]
        if diff:
            first, cols = f, diff
            break
    msd = [nm for nm, _ in s["ms"] if r["ms"].get(nm) != base["ms"].get(nm)]
    same = first is None and not msd and r["run_hash"] == base["run_hash"] and r["rc"] == base["rc"]
    if job["cfg"] == "control":
        return ({"verdict": "ERROR", "detail": "CONTROL NOT DETECTED: the gate is blind"} if same else
                {"verdict": "CONTROL_OK", "detail": f"detected, as it must be: first differing field {first} ({','.join(cols)})"})
    why = armed(job, r.get("arming", {}))
    if same and why:
        return {"verdict": "UNARMED", "detail": why}
    if same:
        if hl.exists():
            # equal field by field: result.json keeps the milestones and the fact (fields_equal =
            # the reference run hash it was compared with), the hash log goes
            rp = out / "jobs" / job["id"] / "result.json"
            rr = json.loads(rp.read_text(encoding="utf-8"))
            rr["fields_equal"] = base["run_hash"]
            tmp = rp.with_suffix(".json.tmp")
            tmp.write_text(json.dumps(rr, indent=1), encoding="utf-8")
            tmp.replace(rp)
            try:
                hl.unlink()
            except OSError:
                pass
        return {"verdict": "EQUAL", "detail": ""}
    det = f"first differing field {first}: {','.join(cols)}" if first is not None else "hash logs equal (exit / final line differs)"
    if msd:
        det += "; milestones differing: " + ", ".join(msd)
    return {"verdict": "DIFF", "detail": det, "first_field": first, "first_cols": cols}


def arm_text(a):
    if not a:
        return ""
    bits = []
    if "sim_presents" in a:
        bits.append(f"sim {a['sim_presents']} presents / {a['sim_passes']} passes")
    if "check_same" in a and a["check_same"] + a["check_differ"]:
        bits.append(f"exact check {a['check_same']} same / {a['check_differ']} differ")
    if "pace_mode" in a:
        bits.append(f"pacing {a['pace_mode']} cap {a['pace_cap']}, {a['presents']} presents, {a['between']} between")
    if a.get("ip_between"):
        bits.append(f"interp between {a['ip_between']}")
    if a.get("ip_passes"):
        bits.append(f"interp passes {a['ip_passes']}")
    if a.get("dropped"):
        bits.append(f"{a['dropped']} phases dropped (host behind)")
    if "jit_stalls" in a:
        bits.append(f"{a['jit_stalls']} stalls")
    if a.get("hist"):
        bits.append(f"phases/present {a['hist']}")
    return "; ".join(bits)


def write_report(out: Path, tier, jobs, results, verdicts, eid, wall) -> int:
    cnt = {}
    for v in verdicts.values():
        cnt[v["verdict"]] = cnt.get(v["verdict"], 0) + 1
    tsv = ["job\tconfig\tscenario\tverdict\trun_hash\taudio\tfield\trc\twall_s\tarming\tdetail"]
    md = [f"# Frame-rate gate ({tier})", "",
          f"exe id `{eid}`; {len(jobs)} jobs; " + ", ".join(f"{k} {n}" for k, n in sorted(cnt.items()))
          + f"; wall {wall / 60:.1f} min this invocation", "",
          "| config | scenario | verdict | run hash | audio | wall s | armed by | detail |",
          "| --- | --- | --- | --- | --- | --- | --- | --- |"]
    for j in jobs:
        r, v = results.get(j["id"]) or {}, verdicts[j["id"]]
        at = arm_text(r.get("arming"))
        tsv.append("\t".join(str(x) for x in [j["id"], j["cfg"], j["scen"]["name"], v["verdict"], r.get("run_hash"),
                                              r.get("audio"), r.get("field"), r.get("rc"), r.get("wall_s"), at,
                                              v.get("detail", "")]))
        md.append(f"| {j['cfg']} | {j['scen']['name']} | {v['verdict']} | `{r.get('run_hash')}` | `{r.get('audio')}` | "
                  f"{r.get('wall_s')} | {at} | {v.get('detail', '')} |")
    md += ["", "## Configurations", ""]
    seen = set()
    for j in jobs:
        if j["cfg"] in seen:
            continue
        seen.add(j["cfg"])
        md.append(f"- `{j['cfg']}`: {j['label']}; " + " ".join(f"`--set {x}`" for x in j["sets"])
                  + (" env " + ",".join(f"{k}={v}" for k, v in j["env"].items()) if j["env"] else "")
                  + (" (windowed)" if j["window"] else ""))
    md += ["", "## Milestones (run hash / audio part per scenario; every job's must equal the Original's)", ""]
    for j in jobs:
        if j["cfg"] == "original" and results.get(j["id"]):
            ms = results[j["id"]]["ms"]
            md.append(f"- {j['scen']['name']}: " + ", ".join(f"{nm}@{f} `{(ms.get(nm) or ['-'])[0]}`" for nm, f in j["scen"]["ms"]))
    (out / "report.tsv").write_text("\n".join(tsv) + "\n", encoding="utf-8")
    (out / "report.md").write_text("\n".join(md) + "\n", encoding="utf-8")
    if any(v["verdict"] in ("DIFF", "ERROR", "SLOW", "UNARMED") for v in verdicts.values()):
        return 1
    if any(v["verdict"] == "PENDING" for v in verdicts.values()):
        return 75
    return 0


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["run", "plan", "report"])
    ap.add_argument("--exe")
    ap.add_argument("--tier", default="quick", choices=["quick", "rates", "full", "lib", "drivers", "window"])
    ap.add_argument("--out")
    ap.add_argument("-j", "--jobs", type=int, default=2)
    ap.add_argument("--max-hours", type=float, default=1.8)
    ap.add_argument("--timeout-factor", type=float, default=25.0, help="kill a job after F x its Original wall time")
    ap.add_argument("--timeout-min", type=float, default=900.0)
    ap.add_argument("--only", help="comma list of config names (the Originals always run)")
    ap.add_argument("--skip-missing", action="store_true", help="exit 77 when the exe, data or cards are missing")
    a = ap.parse_args(argv)
    out = Path(a.out or PORT / "out" / "fpsgate" / a.tier).resolve()
    jobs = tier_jobs(a.tier)
    if a.only:
        keep = set(a.only.split(",")) | {"original"}
        jobs = [j for j in jobs if j["cfg"] in keep]
    if a.cmd == "plan":
        for j in jobs:
            print(f"{j['id']:48s} {j['scen']['fields']:6d}  {' '.join(j['sets'])[:110]}  {j['env'] or ''}")
        print(f"{len(jobs)} jobs", file=sys.stderr)
        return 0
    exe = Path(a.exe or fxlib.exe_path()).resolve()
    need = [exe, PORT / "data", fxlib.CARDS / "save2"] + [Path(j["scen"]["input"]) for j in jobs]
    if any(not p.exists() for p in need):
        print("fpsgate: missing " + ", ".join(sorted({str(p) for p in need if not p.exists()})))
        return 77 if a.skip_missing else 2
    eid = fxlib.exe_id(exe)
    out.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    if a.cmd == "run":
        exe_run = optgate.snapshot_exe(exe, out)
        deadline = t0 + a.max_hours * 3600
        done = 0

        def go(j):
            left = deadline - time.time()
            if left <= 60:
                return j, None
            lim = left
            if j["cfg"] != "original":
                bp = out / "jobs" / base_id(j) / "result.json"
                bw = json.loads(bp.read_text(encoding="utf-8")).get("wall_s", 0) if bp.exists() else 0
                lim = min(left, max(a.timeout_min, a.timeout_factor * bw))
            return j, run_job(j, exe_run, eid, out, lim)

        win = [j for j in jobs if j["window"]]
        head = [j for j in jobs if not j["window"]]
        base_first = [j for j in head if j["cfg"] == "original"]
        rest = [j for j in head if j["cfg"] != "original"]
        # window jobs one at a time (real time, one GPU); headless ones -j N (rg_slots also limits)
        for batch, nj in ((base_first, a.jobs), (rest, a.jobs), (win, 1)):
            with ThreadPoolExecutor(max_workers=max(1, nj)) as ex:
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
                lp = p.parent / "port.log"   # (arming re-read: the parser may know more lines now)
                if lp.exists():
                    r["arming"] = parse_arming(lp.read_text(encoding="utf-8", errors="replace"))
                results[j["id"]] = r
    bases = {j["scen"]["name"]: dict(results[j["id"]], id=j["id"]) for j in jobs
             if j["cfg"] == "original" and j["id"] in results}
    verdicts = {j["id"]: compare(j, results.get(j["id"]), bases.get(j["scen"]["name"]), out) for j in jobs}
    rc = write_report(out, a.tier, jobs, results, verdicts, eid, time.time() - t0)
    for j in jobs:
        v = verdicts[j["id"]]
        if v["verdict"] in ("DIFF", "ERROR", "SLOW", "UNARMED"):
            print(f"  {v['verdict']}: {j['id']}: {v.get('detail', '')}")
    print(f"fpsgate {a.tier}: {out / 'report.md'}; " + {0: "PASS", 1: "FAIL", 75: "INCOMPLETE (run again to resume)"}[rc])
    return rc


if __name__ == "__main__":
    sys.exit(main())

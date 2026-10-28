# SPDX-License-Identifier: CC0-1.0
"""Reference timing contract: probe JSONL (probe.py --hooks timing) -> TSVs.

PLAN.md "Unlocked frame rate", work-order step 1; docs/TIMING-REFERENCE.md.

    python tools/trace/probe.py --hooks timing --out out/timing/RUN.jsonl [--input ...] --stop-vbl V
    python tools/trace/timing.py build out/timing/RUN.jsonl      # -> RUN.ticks.tsv, RUN.events.tsv,
                                                                #    RUN.milestones.tsv, RUN.summary.json
    python tools/trace/timing.py summary out/timing/RUN.summary.json
    python tools/trace/timing.py align A.milestones.tsv B.milestones.tsv   # docs/TIMING-LOCKSTEP.md
    python tools/trace/timing.py build out/timing/port/RUN.jsonl --map build/.../rg-game.map   # a port run
    python tools/trace/timing.py align --nowrap GOLDEN.milestones.tsv PORT.milestones.tsv

One `ticks` row per GfxEndFrame_141c20 return (= one frame of whichever loop
called it: MainLoop_1c2c10, LoadingScreenThread_343510 or
MoviePlayModal_267c60). Everything logged since the previous row (task-table
runs, scene time-scale update, pad updates, sound-sequence advances, VBlank
interrupts, frame-worker wakes) is folded into it. `events` holds the rare
records (interval/lock changes, game-mode push/pop, overlay loads, state
machines, pause requests, movie open/close, task-list changes, CD reads).
`milestones` is the subset meant for port/PCSX2 alignment (TIMING-LOCKSTEP.md
"Milestone-aligned comparison"). Port records (same schema) may carry `ra_name`
instead of a PS2 `ra` and a `pair` id for entry/return pairing.

Port records (src/trace/timing.c, RG_TIMING=path) also carry, until the
probe_wrap stage wraps the game functions: `MemState` (game memory read at
each VBlank: interval, game mode, overlay, scene lock; folded into the tick
state and into the `mem_*` events), GfxEndFrame pairs synthesised from the
frame context's flip counter ("src":"mem", loop named by "ra_name"), and
`ra_rva` (a wrapper's host return address, named with --map rg-game.map).
The `mem_*` events (interval, game mode, scene lock and sysmode as seen at
each VBlank) are derived on either side: from MemState on the port, from the
hook records on PCSX2, so `align --nowrap` can compare a port run without
function wrapping against a PCSX2 capture.

Function names for return addresses come from the decomp's asm (read-only,
--asm, default ../RGDecomp/asm). Original CC0 code.
"""
import argparse
import bisect
import collections
import json
import os
import re
import struct
import sys

EE_HZ = 294912000          # EE clock; COP0 Count runs at it (README "Probe runs")
OVL_DIR = {2: "title", 3: "normal"}   # overlay id -> asm/overlays/<dir> (README golden timeline)
PAD0, PAD1 = 0x004B2570, 0x004B27E0
LOOPS = {"MainLoop_1c2c10": "main", "LoadingScreenThread_343510": "loadscreen",
         "MoviePlayModal_267c60": "moviemodal"}
SEQ_OWNERS = {"MainLoop_1c2c10": "main", "SysTickThreadMain_1c33f0": "thread"}
ARENA = (0x004E9E80, 0x00528200)


def f32(u):
    return struct.unpack("<f", struct.pack("<I", u & 0xFFFFFFFF))[0]


def s32(u):
    u &= 0xFFFFFFFF
    return u - (1 << 32) if u & 0x80000000 else u


def fmt(x):
    if isinstance(x, float):
        return ("%.4f" % x).rstrip("0").rstrip(".") if x == x else "nan"
    return str(x)


# ------------------------------------------------------------ symbols
class Syms:
    LINE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s")

    def __init__(self, asm_dir):
        self.main = []
        self.ovl = collections.defaultdict(list)
        cache = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "out", "timing", "asm_syms.json")
        if os.path.exists(cache):
            d = json.load(open(cache))
            self.main = [tuple(x) for x in d["main"]]
            self.ovl = collections.defaultdict(list, {k: [tuple(x) for x in v] for k, v in d["ovl"].items()})
        elif os.path.isdir(asm_dir):
            self.main = self._scan(os.path.join(asm_dir, "main.s"))
            od = os.path.join(asm_dir, "overlays")
            for name in sorted(os.listdir(od)) if os.path.isdir(od) else []:
                for f in sorted(os.listdir(os.path.join(od, name))):
                    if f.endswith(".s"):
                        self.ovl[name] += self._scan(os.path.join(od, name, f))
                self.ovl[name].sort()
            os.makedirs(os.path.dirname(cache), exist_ok=True)
            json.dump({"main": self.main, "ovl": self.ovl}, open(cache, "w"))
        self.mkeys = [a for a, _ in self.main]
        self.okeys = {k: [a for a, _ in v] for k, v in self.ovl.items()}

    def _scan(self, path):
        out = []
        pend = None
        for line in open(path, encoding="utf-8", errors="replace"):
            if line.startswith("glabel "):
                pend = line.split()[1]
                continue
            if pend:
                m = self.LINE.search(line)
                if m:
                    out.append((int(m.group(1), 16), pend))
                    pend = None
        out.sort()
        return out

    @staticmethod
    def _find(keys, table, a):
        i = bisect.bisect_right(keys, a) - 1
        return table[i][1] if i >= 0 else None

    def caller(self, r, ovl_id=None):
        """Name of a record's return address; port records carry it as
        ra_name, or as a host RVA (ra_rva) named with the link map."""
        if r.get("ra_name"):
            return r["ra_name"]
        if "ra_rva" in r:
            return self.host_name(r["ra_rva"])
        if "ra" not in r:
            return "?"
        return self.name(r["ra"], ovl_id)

    hmap = None

    def load_map(self, path):
        """lld-link / link.exe /MAP rows `0001:off  name  rva+base  object`."""
        rx = re.compile(r"^\s*0001:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8,16})\s")
        base = 0x400000
        out = []
        for line in open(path, encoding="utf-8", errors="replace"):
            m = re.search(r"Preferred load address is ([0-9a-fA-F]+)", line)
            if m:
                base = int(m.group(1), 16)
                continue
            m = rx.match(line)
            if m:
                n = m.group(1)
                out.append((int(m.group(2), 16) - base, n[1:] if n.startswith("_") and "@" not in n else n))
        out.sort()
        self.hmap = out
        self.hkeys = [a for a, _ in out]

    def host_name(self, rva):
        if not self.hmap:
            return "rva_%x" % rva
        i = bisect.bisect_right(self.hkeys, rva) - 1
        return self.hmap[i][1] if i >= 0 else "rva_%x" % rva

    def name(self, a, ovl_id=None):
        if ARENA[0] <= a < ARENA[1]:
            d = OVL_DIR.get(ovl_id)
            if d in self.ovl:
                return self._find(self.okeys[d], self.ovl[d], a) or "%08x" % a
            c = sorted({self._find(self.okeys[k], v, a) for k, v in self.ovl.items()} - {None})
            return "|".join(c) if c else "%08x" % a
        if 0x00098000 <= a < 0x000A0000:
            return "probe"
        return (self._find(self.mkeys, self.main, a) or "%08x" % a) if self.main else "%08x" % a


# ------------------------------------------------------------ build
TICK_COLS = ["tick", "loop", "vbl", "dvbl", "cyc", "dcyc", "interval", "sync", "waited", "late",
             "t0", "vutime", "div", "fb", "fb_over", "sysmode", "overlay", "gamemode", "phase",
             "pause", "taskdepth", "ts_calls", "ts_count", "ts_scale", "ts_mult", "ts_step",
             "ts_countdown", "ts_locked", "ts_susp", "ts_dbl", "task_runs", "task_restarts",
             "pad0", "pad0_edges", "pad1_edges", "seq_main_n", "seq_main_step", "seq_thr_n",
             "seq_thr_step", "vblanks", "wakes", "coalesced", "movie_frames", "cd_reads",
             "depth_on", "depth_z", "events"]


def build(path, syms, out_prefix=None):
    out_prefix = out_prefix or re.sub(r"\.jsonl$", "", path)
    recs = []
    meta = {}
    lost = bad = 0
    lost_windows = []           # (last sampled vbl before, sampled vbl after, records lost)
    last_s = 0
    for line in open(path, encoding="utf-8"):
        o = json.loads(line)
        t = o.get("t")
        if t == "r":
            recs.append(o)
        elif t == "meta":
            meta = o
        elif t == "lost":
            lost += o["n"]
            lost_windows.append([last_s, None, o["n"]])
        elif t == "s":
            if lost_windows and lost_windows[-1][1] is None:
                lost_windows[-1][1] = o["vbl"]
            last_s = o["vbl"]
        elif t == "bad":
            bad += 1
    recs.sort(key=lambda r: r["seq"])

    ticks, events = [], []
    open_entries = {}                 # (fn, sp) -> entry record
    state = {"overlay": None, "sysmode": None, "gamemode": None, "phase": None, "pause": None,
             "taskdepth": None, "interval": None}
    cur = None

    def new_acc():
        return {"ts": None, "ts_calls": 0, "task_runs": 0, "task_restarts": 0, "pad0": None,
                "pad0_edges": 0, "pad1_edges": 0, "seq_main_n": 0, "seq_main_step": 0.0,
                "seq_thr_n": 0, "seq_thr_step": 0.0, "vblanks": 0, "wakes": 0, "coalesced": 0,
                "movie_frames": 0, "cd_reads": 0, "events": [], "wait": None, "gfx_entry": None}
    cur = new_acc()
    prev = {"vbl": None, "cyc": None}
    vbl_cnt = []                      # (vbl, count) per VblankStart
    first_vbl = None

    def ev(r, kind, detail):
        e = {"vbl": r["vbl"], "cyc": r["cnt"], "tick": len(ticks), "kind": kind, "detail": detail}
        events.append(e)
        cur["events"].append("%s:%s" % (kind, detail))

    # the memory view (`mem_*` events): what game memory holds at each VBlank,
    # tracked from the hook records (PCSX2) or read (port MemState)
    mv = {k: None for k in MEM_KINDS}
    mv_prev = dict(mv)

    def mem_events(r):
        for k in MEM_KINDS:
            v, p = mv[k], mv_prev[k]
            if v is not None and v != p and (p is not None or v != MEM_DEFAULT.get(k))                     and v not in MEM_UNSEEN.get(k, ()):
                ev(r, "mem_" + k, "%d (was %s)" % (v, p))
            mv_prev[k] = v

    for r in recs:
        fn, k, d, a = r["fn"], r["k"], r["d"], r["a"]
        if first_vbl is None:
            first_vbl = r["vbl"]
        # entry/return pairing: PCSX2 return records carry the trampoline's
        # sp (entry sp - 16); a port record may carry an explicit "pair" id
        if "pair" in r:
            key_in = key_out = (fn, r["pair"])
        else:
            key_in, key_out = (fn, r["sp"]), (fn, r["sp"] - 16)
        if k == "entry" and fn in ("GfxEndFrame", "WaitVsync", "SceneTimeScale", "TaskTableRun", "OverlayLoad"):
            open_entries[key_out] = r
        ent = open_entries.pop(key_in, None) if k == "ret" else None

        if fn == "MemState":
            # port: game memory at this VBlank (src/trace/timing.c)
            x = r.get("x", {})
            if x.get("db", 1):
                mv["interval"] = s32(d[0])
                state["interval"] = s32(d[0])
            mv["gamemode"] = s32(d[2])
            if x.get("scene", 1):
                mv["locked"] = d[5] & 0xFF
            state.update(gamemode=s32(d[2]), phase=s32(d[3]), sysmode=s32(a[0]), pause=s32(a[1]),
                         taskdepth=s32(a[2]))
            if s32(d[4]) >= 0:
                state["overlay"] = s32(d[4])
        elif fn == "VblankStart":
            mv["sysmode"] = s32(d[5])
            mem_events(r)
            cur["vblanks"] += 1
            vbl_cnt.append((r["vbl"], r["cnt"]))
            if d[1] == 0:
                cur["coalesced"] += 1
        elif fn == "TickWake":
            cur["wakes"] += 1
        elif fn == "SoundSeqUpdate":
            owner = SEQ_OWNERS.get(syms.caller(r), "other")
            step = f32(d[0])
            if owner == "thread":
                cur["seq_thr_n"] += 1
                cur["seq_thr_step"] += step
            else:
                cur["seq_main_n"] += 1
                cur["seq_main_step"] += step
                if owner == "other":
                    ev(r, "seq_other_owner", syms.caller(r))
        elif fn == "GfxEndFrame" and k == "entry":
            cur["gfx_entry"] = r
        elif fn == "WaitVsync" and k == "ret" and ent:
            cur["wait"] = (ent["a"][0], ent["a"][1], ent["vbl"], r["vbl"])
        elif fn == "SceneTimeScale" and k == "ret":
            cur["ts_calls"] += 1
            cur["ts"] = d
            mv["locked"] = d[5] & 0xFF
        elif fn == "TaskTableRun":
            if k == "entry":
                cur["task_runs"] += 1
                state.update(gamemode=s32(d[0]), phase=s32(d[1]), pause=s32(d[2]), taskdepth=s32(d[3]),
                             sysmode=s32(d[4]))
                mv["gamemode"] = s32(d[0])
            elif r["v0"] & 0xFF:
                cur["task_restarts"] += 1
        elif fn == "TaskListChanged":
            ev(r, "task_list_changed", syms.caller(r, state["overlay"]))
        elif fn == "PadUpdate":
            edges = d[1] & ~d[2] & 0xFFFF
            if d[0] == PAD0:
                cur["pad0"] = d[1] & 0xFFFF
                cur["pad0_edges"] |= edges
            elif d[0] == PAD1:
                cur["pad1_edges"] |= edges
        elif fn == "SetVsyncInterval":
            ev(r, "set_interval", "%d sync=%d by %s" % (s32(a[1]), s32(a[2]), syms.caller(r, state["overlay"])))
            state["interval"] = s32(a[1])
            mv["interval"] = s32(a[1])
        elif fn == "SetTimeScaleLocked":
            ev(r, "scale_locked", "%d by %s" % (a[1] & 0xFF, syms.caller(r, state["overlay"])))
            mv["locked"] = a[1] & 0xFF
        elif fn == "SetTimeScaleSuspended":
            ev(r, "scale_suspended", "%d by %s" % (a[1] & 0xFF, syms.caller(r, state["overlay"])))
        elif fn in ("GameModePush", "GameModePop"):
            if fn == "GameModePush":
                ev(r, "gamemode_push", "%d phase=%d (was %d) by %s" % (s32(a[0]), s32(a[1]), s32(d[0]),
                                                                      syms.caller(r, state["overlay"])))
                mv["gamemode"] = s32(a[0])
            else:
                ev(r, "gamemode_pop", "%d -> %d by %s" % (s32(d[0]), s32(d[1]), syms.caller(r, state["overlay"])))
                mv["gamemode"] = s32(d[1])
        elif fn == "OverlayLoad":
            # the id is the argument (the stored D_0047E254 reads 0 at return)
            if k == "entry":
                ev(r, "overlay_load", "%d (sysmode %d)" % (s32(a[0]), s32(d[1])))
            elif ent:
                state["overlay"] = s32(ent["a"][0])
                ev(r, "overlay_loaded", "%d in %d vbl" % (s32(ent["a"][0]), r["vbl"] - ent["vbl"]))
        elif fn == "StateMachineSetState":
            ev(r, "sm_state", "sm=%08x state=%d by %s" % (a[0], s32(a[1]), syms.caller(r, state["overlay"])))
        elif fn == "PauseRequest":
            ev(r, "pause_request", "%d by %s" % (s32(a[0]), syms.caller(r, state["overlay"])))
        elif fn == "MovieOpen":
            ev(r, "movie_open", "player=%08x by %s%s" % (a[0], syms.caller(r, state["overlay"]),
                                                       " path=%s" % r["path"] if "path" in r else ""))
        elif fn == "MovieShutdown":
            ev(r, "movie_shutdown", "player=%08x by %s" % (a[0], syms.caller(r, state["overlay"])))
        elif fn == "MovieDrawFrame":
            cur["movie_frames"] += 1
        elif fn == "sceCdRead":
            cur["cd_reads"] += 1
            events.append({"vbl": r["vbl"], "cyc": r["cnt"], "tick": len(ticks), "kind": "cd_read",
                           "detail": "lsn=%d n=%d" % (a[0], a[1])})
        elif fn == "FsRead":
            # native file service (docs/NATIVE-FS.md): counted with the CD reads
            cur["cd_reads"] += 1
            events.append({"vbl": r["vbl"], "cyc": r["cnt"], "tick": len(ticks), "kind": "cd_read",
                           "detail": "file=%s off=%d n=%d" % (r.get("file", "?"), d[0] | (d[1] << 32), d[2])})
        elif fn == "GfxEndFrame" and k == "ret":
            ge = ent or cur["gfx_entry"] or {"d": [0] * 6, "ra": 0}
            gname = syms.caller(ge) if "fn" in ge else "?"
            loop = LOOPS.get(gname, gname)
            fb = f32(d[0])
            interval = s32(d[3])
            ts = cur["ts"]
            row = {"tick": len(ticks), "loop": loop, "vbl": r["vbl"],
                   "dvbl": r["vbl"] - prev["vbl"] if prev["vbl"] is not None else "",
                   "cyc": r["cnt"], "dcyc": (r["cnt"] - prev["cyc"]) & 0xFFFFFFFF if prev["cyc"] is not None else "",
                   "interval": interval, "sync": s32(ge["d"][3]),
                   "waited": (cur["wait"][3] - cur["wait"][2]) if cur["wait"] else "",
                   "late": s32(d[2]), "t0": ge["d"][0], "vutime": ge["d"][1], "div": s32(ge["d"][2]),
                   "fb": fb, "fb_over": int(fb > interval), "sysmode": state["sysmode"],
                   "overlay": state["overlay"], "gamemode": state["gamemode"], "phase": state["phase"],
                   "pause": state["pause"], "taskdepth": state["taskdepth"], "ts_calls": cur["ts_calls"],
                   "ts_count": s32(ts[1]) if ts else "", "ts_scale": f32(ts[2]) if ts else "",
                   "ts_mult": f32(ts[3]) if ts else "", "ts_step": f32(ts[2]) * f32(ts[3]) if ts else "",
                   "ts_countdown": s32(ts[4]) if ts else "", "ts_locked": (ts[5] & 0xFF) if ts else "",
                   "ts_susp": ((ts[5] >> 8) & 0xFF) if ts else "", "ts_dbl": (ts[0] & 0xFF) if ts else "",
                   "task_runs": cur["task_runs"], "task_restarts": cur["task_restarts"],
                   "pad0": "%04x" % cur["pad0"] if cur["pad0"] is not None else "",
                   "pad0_edges": "%04x" % cur["pad0_edges"], "pad1_edges": "%04x" % cur["pad1_edges"],
                   "seq_main_n": cur["seq_main_n"], "seq_main_step": cur["seq_main_step"],
                   "seq_thr_n": cur["seq_thr_n"], "seq_thr_step": cur["seq_thr_step"],
                   "vblanks": cur["vblanks"], "wakes": cur["wakes"], "coalesced": cur["coalesced"],
                   "movie_frames": cur["movie_frames"], "cd_reads": cur["cd_reads"],
                   "depth_on": s32(d[4]), "depth_z": s32(d[5]), "events": ";".join(cur["events"])}
            ticks.append(row)
            prev = {"vbl": r["vbl"], "cyc": r["cnt"]}
            cur = new_acc()

    with open(out_prefix + ".ticks.tsv", "w", encoding="utf-8", newline="\n") as f:
        f.write("# timing ticks from %s (hooks %s, input %s)\n" % (os.path.basename(path), meta.get("hooks"), meta.get("input")))
        f.write("\t".join(TICK_COLS) + "\n")
        for row in ticks:
            f.write("\t".join(fmt(row[c]) if row[c] is not None else "" for c in TICK_COLS) + "\n")
    with open(out_prefix + ".events.tsv", "w", encoding="utf-8", newline="\n") as f:
        f.write("vbl\tcyc\ttick\tkind\tdetail\n")
        for e in events:
            f.write("%d\t%d\t%d\t%s\t%s\n" % (e["vbl"], e["cyc"], e["tick"], e["kind"], e["detail"]))
    ms = milestones(events, ticks)
    with open(out_prefix + ".milestones.tsv", "w", encoding="utf-8", newline="\n") as f:
        f.write("vbl\tmain_tick\tkind\tkey\n")
        for m in ms:
            f.write("%d\t%d\t%s\t%s\n" % m)
    summ = summarize(ticks, events, vbl_cnt, lost, bad, meta)
    summ["milestones"] = len(ms)
    summ["lost_windows"] = lost_windows
    json.dump(summ, open(out_prefix + ".summary.json", "w"), indent=1)
    print("%d ticks, %d events, %d milestones, %d lost, %d bad -> %s.*" % (len(ticks), len(events), len(ms), lost, bad, out_prefix))
    return summ


# ------------------------------------------------------------ milestones
MEM_KINDS = ("interval", "gamemode", "locked", "sysmode")
# a first known value equal to the boot default is not a change (PCSX2 knows
# nothing until the first hook record; the port reads memory from boot)
MEM_DEFAULT = {"gamemode": -1, "locked": 0, "sysmode": 0}
# values PCSX2's hooks cannot see being stored: GameModeStack is 0 from boot and
# reset to -1 by plain stores at NORMAL boot, not by GameModePush/Pop
MEM_UNSEEN = {"gamemode": (0, -1)}
MILESTONE_KINDS = ("overlay_load", "gamemode_push", "gamemode_pop", "set_interval", "scale_locked",
                   "movie_open", "movie_shutdown", "sm_state", "loop") + tuple("mem_" + k for k in MEM_KINDS)
# what a port run yields without wrapping game functions (align --nowrap)
NOWRAP_KINDS = ("overlay_load", "movie_open", "movie_shutdown", "loop") + tuple("mem_" + k for k in MEM_KINDS)


def milestone_key(kind, det):
    """The part of an event both sides reproduce exactly: game-visible values
    and caller names, no timing. Movie players are heap objects: keyed by the
    caller instead. State machines keep their (PS2) address: the port maps
    host pointers back (TRACE-PORT.md), and heap parity holds at the title
    (BRINGUP.md: 0x00948D90 on both sides)."""
    if kind in ("movie_open", "movie_shutdown"):
        return det.split(" by ")[-1].split(" path=")[0]
    if kind.startswith("mem_"):
        return det.split(" (")[0]
    if kind == "gamemode_push":
        return det.split(" (was")[0]
    if kind in ("set_interval", "scale_locked"):
        return det
    return det.split(" by ")[0].split(" (")[0]


def milestones(events, ticks):
    """Game events both sides can detect, as (vbl, main ticks before it, kind,
    key). `loop` marks a change of frame loop (main / loadscreen /
    moviemodal), taken from the ticks."""
    main_before = [0]
    n = 0
    for t in ticks:
        if t["loop"] == "main":
            n += 1
        main_before.append(n)
    out = []
    for j, e in enumerate(events):
        if e["kind"] in MILESTONE_KINDS:
            out.append(((e["tick"], 1, j), (e["vbl"], main_before[min(e["tick"], len(ticks))], e["kind"],
                                             milestone_key(e["kind"], e["detail"]))))
    last = None
    for i, t in enumerate(ticks):
        if t["loop"] != last:
            out.append(((i, 2, 0), (t["vbl"], main_before[i], "loop", t["loop"])))
            last = t["loop"]
    # logic order (frame index, then record order), never vbl order: the
    # port's vbls differ
    out.sort(key=lambda m: m[0])
    return [m[1] for m in out]


# ------------------------------------------------------------ summary
def hist(vals):
    c = collections.Counter(vals)
    return {str(k): v for k, v in sorted(c.items(), key=lambda kv: (str(type(kv[0])), kv[0]))}


def summarize(ticks, events, vbl_cnt, lost, bad, meta):
    s = {"meta": {"hooks": meta.get("hooks"), "input": meta.get("input"), "speed": meta.get("speed")},
         "lost_records": lost, "bad_records": bad, "ticks": len(ticks)}
    # vblank period from consecutive VblankStart records
    per = [(c2 - c1) & 0xFFFFFFFF for (v1, c1), (v2, c2) in zip(vbl_cnt, vbl_cnt[1:]) if v2 == v1 + 1]
    if per and sorted(per)[len(per) // 2]:   # (a clockless unit-test record has none)
        per_sorted = sorted(per)
        med = per_sorted[len(per) // 2]
        s["vblank"] = {"n": len(vbl_cnt), "pairs": len(per), "median_cycles": med,
                       "min_cycles": per_sorted[0], "max_cycles": per_sorted[-1],
                       "mean_cycles": sum(per) / len(per), "hz_median": EE_HZ / med,
                       "hz_mean": EE_HZ * len(per) / sum(per),
                       "top": collections.Counter(per).most_common(5),
                       "first_vbl": vbl_cnt[0][0], "last_vbl": vbl_cnt[-1][0],
                       "gaps": sum(1 for (v1, _), (v2, _) in zip(vbl_cnt, vbl_cnt[1:]) if v2 != v1 + 1)}
    # interval changes
    s["interval_changes"] = [(e["vbl"], e["detail"]) for e in events if e["kind"] == "set_interval"]
    s["lock_changes"] = [(e["vbl"], e["detail"]) for e in events if e["kind"] in ("scale_locked", "scale_suspended")]
    # per loop and interval
    by = collections.defaultdict(list)
    for t in ticks:
        by["%s/i%s" % (t["loop"], t["interval"])].append(t)
    groups = {}
    for key, ts in sorted(by.items()):
        iv = ts[0]["interval"]
        g = {"ticks": len(ts), "vbl_span": sum(t["dvbl"] for t in ts if t["dvbl"] != ""),
             "dvbl": hist(t["dvbl"] for t in ts),
             "waited": hist(t["waited"] for t in ts),
             "fb_over_interval": sum(t["fb_over"] for t in ts),
             "fb_at_2x_clamp": sum(1 for t in ts if iv and abs(t["fb"] - 2 * iv) < 1e-6),
             "fb_hist": hist(round(t["fb"], 2) for t in ts),
             "late": sum(1 for t in ts if t["late"]),
             "task_runs": hist(t["task_runs"] for t in ts),
             "task_restarts": sum(t["task_restarts"] for t in ts),
             "ts_count": hist(t["ts_count"] for t in ts),
             "ts_mult": hist(round(t["ts_mult"], 3) if t["ts_mult"] != "" else "" for t in ts),
             "ts_scale": hist(round(t["ts_scale"], 3) if t["ts_scale"] != "" else "" for t in ts),
             "ts_locked": hist(t["ts_locked"] for t in ts), "ts_susp": hist(t["ts_susp"] for t in ts),
             "seq_main_n": hist(t["seq_main_n"] for t in ts), "seq_thr_n": hist(t["seq_thr_n"] for t in ts),
             "vblanks": hist(t["vblanks"] for t in ts), "wakes": hist(t["wakes"] for t in ts),
             "coalesced": sum(t["coalesced"] for t in ts),
             "gamemodes": hist(t["gamemode"] for t in ts)}
        groups[key] = g
    s["groups"] = groups
    # slow-frame response: main-loop tick N's scene update sees tick N-1's feedback
    resp = collections.Counter()
    for t0, t1 in zip(ticks, ticks[1:]):
        if t1["loop"] != "main" or t1["ts_mult"] == "":
            continue
        over = t0["fb"] > t0["interval"]
        resp[(t0["interval"], over, t1["ts_locked"], t1["ts_susp"], round(t1["ts_mult"], 2) > 1.0, t1["ts_count"])] += 1
    s["slow_frame_response"] = [{"prev_interval": k[0], "prev_fb_over": k[1], "locked": k[2], "susp": k[3],
                                 "mult_gt_1": k[4], "count": k[5], "ticks": v} for k, v in sorted(resp.items(), key=str)]
    s["mult_vs_prev_fb"] = []
    pairs = collections.Counter()
    for t0, t1 in zip(ticks, ticks[1:]):
        if t1["loop"] == "main" and t1["ts_mult"] != "" and t1["ts_mult"] > 1.0:
            pairs[(round(t0["fb"], 3), round(t1["ts_mult"], 3))] += 1
    s["mult_vs_prev_fb"] = [[k[0], k[1], v] for k, v in sorted(pairs.items())[:40]]
    # sound sequence ownership
    s["seq"] = {"main_updates": sum(t["seq_main_n"] for t in ticks),
                "thread_updates": sum(t["seq_thr_n"] for t in ticks),
                "ticks_with_both": sum(1 for t in ticks if t["seq_main_n"] and t["seq_thr_n"]),
                "main_step_hist": hist(round(t["seq_main_step"], 2) for t in ticks if t["seq_main_n"]),
                "owner_changes": owner_changes(ticks)}
    s["service"] = {"vblanks": sum(t["vblanks"] for t in ticks), "wakes": sum(t["wakes"] for t in ticks),
                    "coalesced": sum(t["coalesced"] for t in ticks)}
    s["depth_slot0"] = {"ticks_on": sum(1 for t in ticks if t["depth_on"]),
                        "z_hist_top": collections.Counter(t["depth_z"] for t in ticks if t["depth_on"]).most_common(5)}
    s["pad_edge_ticks"] = sum(1 for t in ticks if t["pad0_edges"] != "0000")
    s["restart_sources"] = collections.Counter(e["detail"] for e in events if e["kind"] == "task_list_changed").most_common(20)
    s["events"] = dict(collections.Counter(e["kind"] for e in events))
    s["segments"] = segments(ticks)
    return s


def segments(ticks):
    """Contiguous runs of (loop, interval, game mode, scale lock)."""
    out = []
    for t in ticks:
        key = (t["loop"], t["interval"], t["gamemode"], t["ts_locked"])
        if out and out[-1]["key"] == key:
            o = out[-1]
            o["last_vbl"] = t["vbl"]
            o["ticks"] += 1
            o["slow"] += int(t["dvbl"] != "" and t["dvbl"] > t["interval"])
            o["fb_over"] += t["fb_over"]
        else:
            out.append({"key": key, "loop": t["loop"], "interval": t["interval"], "gamemode": t["gamemode"],
                        "locked": t["ts_locked"], "first_vbl": t["vbl"], "last_vbl": t["vbl"], "ticks": 1,
                        "slow": 0, "fb_over": t["fb_over"]})
    for o in out:
        del o["key"]
    return out


def owner_changes(ticks):
    out = []
    last = None
    for t in ticks:
        o = "thread" if t["seq_thr_n"] else ("main" if t["seq_main_n"] else None)
        if o and o != last:
            out.append((t["vbl"], o))
            last = o
    return out[:50]


# ------------------------------------------------------------ align
def read_milestones(path):
    out = []
    for line in open(path, encoding="utf-8"):
        if line.startswith("vbl\t") or line.startswith("#") or not line.strip():
            continue
        vbl, tick, kind, key = line.rstrip("\n").split("\t")
        out.append((int(vbl), int(tick), kind, key))
    return out


def align(a_path, b_path, kinds=None, show=40, nowrap=False):
    """Milestone-aligned comparison (TIMING-REFERENCE.md): match the two
    milestone sequences on (kind, key) and compare, for each matched pair of
    consecutive milestones, the number of main-loop ticks between them (must be
    equal when the game logic between them does not depend on time) and the
    VBlanks between them (free to differ: loads, lag, cost model)."""
    import difflib
    A, B = read_milestones(a_path), read_milestones(b_path)
    if nowrap:
        # a port run without wrapped game functions: only the milestones it
        # can produce, movies keyed by kind alone (no caller names)
        kinds = set(kinds or NOWRAP_KINDS) & set(NOWRAP_KINDS)
        A = [(m[0], m[1], m[2], "" if m[2].startswith("movie_") else m[3]) for m in A]
        B = [(m[0], m[1], m[2], "" if m[2].startswith("movie_") else m[3]) for m in B]
    if kinds:
        A = [m for m in A if m[2] in kinds]
        B = [m for m in B if m[2] in kinds]
    ka = [(m[2], m[3]) for m in A]
    kb = [(m[2], m[3]) for m in B]
    sm = difflib.SequenceMatcher(a=ka, b=kb, autojunk=False)
    pairs = []
    for blk in sm.get_matching_blocks():
        for k in range(blk.size):
            pairs.append((blk.a + k, blk.b + k))
    first_gap = None
    for op in sm.get_opcodes():
        if op[0] != "equal":
            first_gap = op
            break
    print("A: %d milestones, B: %d, matched %d" % (len(A), len(B), len(pairs)))
    if first_gap:
        tag, i1, i2, j1, j2 = first_gap
        print("first sequence difference (%s): A[%d:%d] %s  vs  B[%d:%d] %s" % (
            tag, i1, i2, ka[i1:i2][:3], j1, j2, kb[j1:j2][:3]))
    else:
        print("milestone sequences IDENTICAL")
    print("%-5s %-16s %-28s %9s %9s %7s %7s %7s %7s" % ("i", "kind", "key", "A.vbl", "B.vbl", "dA.tk", "dB.tk", "dA.vbl", "dB.vbl"))
    drift = 0
    prev = None
    n = 0
    for ia, ib in pairs:
        ma, mb = A[ia], B[ib]
        if prev:
            pa, pb = A[prev[0]], B[prev[1]]
            dta, dtb = ma[1] - pa[1], mb[1] - pb[1]
            dva, dvb = ma[0] - pa[0], mb[0] - pb[0]
            flag = "" if dta == dtb else "  <- tick count differs"
            if flag:
                drift += 1
            if n < show or flag:
                print("%-5d %-16s %-28s %9d %9d %7d %7d %7d %7d%s" % (ia, ma[2], ma[3][:28], ma[0], mb[0], dta, dtb, dva, dvb, flag))
                n += 1
        prev = (ia, ib)
    print("segments with a different main-tick count: %d of %d" % (drift, max(0, len(pairs) - 1)))
    return 0 if not first_gap and not drift else 1


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    al = sub.add_parser("align", help="milestone-aligned comparison of two *.milestones.tsv")
    al.add_argument("a")
    al.add_argument("b")
    al.add_argument("--kinds", default=None, help="comma list of milestone kinds to use")
    al.add_argument("--show", type=int, default=40)
    al.add_argument("--nowrap", action="store_true",
                    help="only milestones a port run yields without wrapping game functions (overlay loads, "
                         "frame loops, movie open/close by kind, mem_* views)")
    b = sub.add_parser("build")
    b.add_argument("jsonl")
    b.add_argument("--out", default=None, help="output prefix (default: the jsonl path without .jsonl)")
    b.add_argument("--asm", default=r"../RGDecomp/asm")
    b.add_argument("--map", default=None, help="rg-game.map: names for port records' ra_rva")
    sm = sub.add_parser("summary")
    sm.add_argument("json")
    args = ap.parse_args()
    if args.cmd == "build":
        syms = Syms(args.asm)
        if args.map:
            syms.load_map(args.map)
        build(args.jsonl, syms, args.out)
    elif args.cmd == "align":
        sys.exit(align(args.a, args.b, set(args.kinds.split(",")) if args.kinds else None, args.show,
                       args.nowrap))
    else:
        json.dump(json.load(open(args.json)), sys.stdout, indent=1)


if __name__ == "__main__":
    main()

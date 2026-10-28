#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Retail-parity harness: the same input on the port and on retail PCSX2, game state
sampled once per game frame on both, aligned on game frames and events, first divergence
per field.  (docs/TEST-FIXTURES.md "Retail parity", docs/BRINGUP.md "Retail parity".)

    python tools/parity/parity.py list                                  # scenarios + fields
    python tools/parity/parity.py port SCEN --exe EXE [--out D] [--env K=V ..] [--groups G]
    python tools/parity/parity.py retail SCEN [--out D] [--speed 1.0] [--ee-rate 3]
    python tools/parity/parity.py compare D [--groups G] [--context 4] [--limit N]
    python tools/parity/parity.py run SCEN --exe EXE [--out D]          # port + retail + compare

Sampling, the same code point on both sides: the entry of GfxEndFrame_141c20, once per
game frame, after the frame's logic.  Port: RG_BREAK there + RG_BREAK_SPEC (the fields'
pointer chains; src/game/rg_game_main.c rg_dump_spec) -> BRK/SDUMP lines.  Retail: a
probe.py-style trampoline at the same address that bumps a frame counter (FRAMECTR) and
appends ceil(words/6) 64-byte records (probe.emit_log with W_ptr / W_abs items) to the
ring at 0xA0000, drained live from PCSX2's memory (live.LiveSampler; record tags carry
the sequence).  Field table: tools/parity/fields.py.

Input keyed by GAME FRAMES (the number of GfxEndFrame entries since power-on), not by
VBlank: retail drops a frame now and then (a load, the menu opening: frametime > 1), the
port never does, so a VBlank-keyed press lands one frame later on retail after each drop.
Port: RG_INPUT_KEY=frames (rg-game keys its script by the hits of the first RG_BREAK
site = GfxEndFrame).  Retail: input.py's guest table indexed by FRAMECTR instead of the
VBlank counter (the trampoline is built with that address).  A press at frame K is seen by
the pad reads that follow the K-th GfxEndFrame on both sides.

A card scenario is a plan of steps anchored on events seen in the frame stream (game
mode / phase / overlay); offsets and durations are game frames:

    ("wait", COND, max_frames[, (BUTTON, period, first)])
                                      next anchor = the first frame (after the previous
                                      anchor) where COND holds; the optional mash presses
                                      BUTTON every `period` frames from anchor + first
                                      until COND (both sides stop pressing at the anchor)
    ("press", OFF, BUTTON, DUR)       BUTTON from anchor + OFF for DUR frames
    ("stick", OFF, DUR, LX, LY)       left stick bytes (0..255, 128 = centre)
    ("compare",)                      the compare anchor: frame 0 of the report
    ("end", OFF)                      stop at anchor + OFF frames

The port runs a plan in passes (one boot-save run per wait, core fields only, to find the
anchor's frame; then the next actions become script lines), the last pass samples every
field.  Retail runs it live (presses written >= LEAD frames ahead of the current frame).
`route` scenarios instead replay a golden input (VBlank keys) from power-on on retail and
from a fixture milestone on the port (port field = vbl + 33), plus extra lines.

Compare: frames paired by index from the compare anchor; per field the first frame where
the values differ (floats bit-exact; ptr NULL-ness), grouped per object, with context.
`rng` (the newlib rand state) is reported, and later divergences are tagged "after rng".

PCSX2 runs with an overclocked EE (EECycleRate 3, --ee-rate) so retail drops fewer
frames.  One PCSX2 at a time (cardboot.busy()); one rg-game at a time (machine mutex).
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(PORT / "tools" / "trace"))
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fields as FL  # noqa: E402

SAMPLE_ADDR = 0x141C20          # GfxEndFrame_141c20
SAMPLE_SYM = "GfxEndFrame_141c20"
FRAMECTR = 0x000E1000           # retail: GfxEndFrame entries since power-on (probe.py DATA area)
LEAD = 6                        # retail: presses written at least this many frames ahead
MASH_FROM = 300                 # first mash press of a plan's first wait (frame; boot logos)
ROUTE_FIELD_OFF = 33            # route: port field = game vbl + 33 (TEST-FIXTURES.md "Route")
CORE = "core"

# ------------------------------------------------------------------ scenarios
LIB_CTRL = "o==3 and m=='6/100'"
FIGHT = "o==3 and m=='7/201'"


def _gun_pattern(at: int) -> list[str]:
    """guncadence.py's SQUARE patterns, as route lines at game vbl AT."""
    out = [f"{at + k} {at + k + 2} SQUARE" for k in range(0, 250, 10)]
    out.append(f"{at + 340} {at + 540} SQUARE")
    out += [f"{at + 640 + k} {at + 642 + k} SQUARE" for k in range(0, 200, 6)]
    return out


def _box_walk(start: int, n: int, seg: int = 75) -> list[tuple]:
    dirs = [(0, 128), (128, 255), (255, 128), (128, 0)]
    return [("stick", start + seg * k, seg, *dirs[k % 4]) for k in range(n)]


def _taps(btn: str, start: int, n: int, period: int, dur: int = 2) -> list[tuple]:
    return [("press", start + period * k, btn, dur) for k in range(n)]


SCENARIOS = {
    # the route's first battle: golden from power-on, gun cadence pattern at vbl 24,760
    # (guncadence.py's retail run); port from the `battle` milestone
    "gun_route": dict(kind="route", golden="newgame_battle.input.txt", milestone="battle",
                      extra=_gun_pattern(24760), start_vbl=24600, end_vbl=25700,
                      compare=FIGHT, desc="first battle, gun cadence pattern (vbl keys)"),
    # card library: field control, menu, a short walk (bootcheck pass 2's smoke actions,
    # in frames: the field runs at 30 frames/s, the menu at 60)
    **{f"walk_{c}": dict(kind="card", card=c, plan=[
        ("wait", LIB_CTRL, 4000, ("CROSS", 30, 0)),
        ("compare",),
        ("press", 30, "TRIANGLE", 2),
        ("press", 200, "CIRCLE", 2),
        ("stick", 260, 100, 128, 0),
        *_box_walk(400, 4),
        ("end", 760)], desc=f"{c}: control, menu, walk forward, a box walk")
       for c in ("save2", "ch01_salgin", "ch02_juraika", "ch03_burkaqua", "ch04_prison",
                 "ch05_factory", "ch06_mines", "ch06_vedan", "ch07_rosa", "ch10_kuje")},
    # save2's scripted second battle (boot_save2_battle2.input.txt's walk + skips), then a
    # fight with gun taps and sword presses anchored on the fight phase
    # battle2's walk and event skip, compared from field control (where battle2 diverges)
    "battle2_walk": dict(kind="card", card="save2", plan=[
        ("wait", LIB_CTRL, 4000, ("CROSS", 30, 0)),
        ("compare",),
        ("stick", 31, 20, 74, 1), ("stick", 51, 20, 1, 74), ("stick", 71, 20, 24, 1),
        ("stick", 91, 20, 85, 1), ("stick", 111, 20, 90, 1), ("stick", 131, 20, 202, 1),
        ("end", 400)], desc="save2 -> the walk into the second battle's event"),
    "battle2": dict(kind="card", card="save2", plan=[
        ("wait", LIB_CTRL, 4000, ("CROSS", 30, 0)),
        # (first action >= 30 frames after the anchor: retail detects the anchor from the
        # drained ring, a few frames late)
        ("stick", 31, 20, 74, 1), ("stick", 51, 20, 1, 74), ("stick", 71, 20, 24, 1),
        ("stick", 91, 20, 85, 1), ("stick", 111, 20, 90, 1), ("stick", 131, 20, 202, 1),
        ("wait", FIGHT, 3000, ("START", 60, 300)),
        ("compare",),
        *_taps("SQUARE", 10, 30, 5),
        ("press", 170, "SQUARE", 100),
        *_taps("CROSS", 300, 20, 8),
        *_taps("SQUARE", 470, 40, 3),
        ("end", 700)], desc="save2 -> scripted second battle, gun/sword patterns"),
}


def scenario(name: str) -> dict:
    if name not in SCENARIOS:
        raise SystemExit(f"unknown scenario {name}; `parity.py list`")
    return SCENARIOS[name]


def cond_fn(expr: str):
    code = compile(expr, "<cond>", "eval")
    return lambda fr: bool(eval(code, {}, {"m": f"{fr.get('mode')}/{fr.get('phase')}",
                                          "o": fr.get("ovl"), "f": fr}))


# ------------------------------------------------------------------ decoding
def decode(typ: str, raw: bytes | None):
    if raw is None:
        return None
    if typ == "ptr":
        return int.from_bytes(raw, "little") != 0
    fmt = {"u8": "<B", "s8": "<b", "u16": "<H", "s16": "<h", "u32": "<I", "s32": "<i",
           "f32": "<f", "u64": "<Q"}[typ]
    v = struct.unpack(fmt, raw)[0]
    if typ == "f32":
        return ("f", raw.hex(), v)       # bits + value: compared on bits
    return v


def show(v) -> str:
    if isinstance(v, (tuple, list)) and v and v[0] == "f":
        return f"{v[2]:.9g}"
    if isinstance(v, int) and abs(v) > 0xFFFF:
        return f"0x{v:X}"
    return str(v)


# ------------------------------------------------------------------ port side
class PortMap:
    """RVAs of the port's data symbols D_00xxxxxx (retail names) and host symbols."""

    def __init__(self, exe: Path):
        self.data = []      # (retail addr, rva)
        self.syms = {}
        for line in open(Path(exe).with_suffix(".map"), encoding="latin-1"):
            m = re.match(r"\s*000\d:[0-9a-f]+\s+_?(\S+)\s+([0-9a-f]{16})\s", line)
            if not m:
                continue
            name, rva = m.group(1), int(m.group(2), 16) - 0x400000
            self.syms[name] = rva
            d = re.fullmatch(r"D_00([0-9A-F]{6})", name)
            if d:
                self.data.append((int(d.group(1), 16), rva))
        self.data.sort()

    def rva_of(self, addr: int) -> int:
        import bisect
        i = bisect.bisect_right(self.data, (addr, 1 << 40)) - 1
        if i < 0:
            raise KeyError(hex(addr))
        a, r = self.data[i]
        if addr - a > 0x10000:
            raise KeyError(f"{addr:#x}: nearest data symbol D_{a:08X} is {addr - a:#x} below")
        return r + (addr - a)


def port_groups(flds, pm: PortMap):
    """RG_BREAK_SPEC items (one per chain, covering its fields) and {field: (item, off, size)}."""
    chains = {}
    for f in flds:
        ch, off = f.port if f.port else (f.chain, f.off)
        sz = FL.TYPES[f.typ]
        lo, hi = chains.get(ch, (off, off + sz))
        chains[ch] = (min(lo, off), max(hi, off + sz))
    items, idx = [], {}
    for k, (ch, (lo, hi)) in enumerate(chains.items()):
        kind, addr, hops = FL.parse_chain(ch)
        if kind == "&":
            items.append(f"r0x{pm.syms[ch[1:]] + lo:X}:{hi - lo}")
        elif kind == "=":
            items.append(f"r0x{pm.rva_of(addr + lo):X}:{hi - lo}")
        else:
            items.append(f"p0x{pm.rva_of(addr):X}" + "".join(f"/0x{h:X}" for h in hops) + f"+0x{lo:X}:{hi - lo}")
        idx[ch] = (k, lo)
    where = {}
    for f in flds:
        ch, off = f.port if f.port else (f.chain, f.off)
        k, lo = idx[ch]
        where[f.name] = (k, off - lo, FL.TYPES[f.typ])
    return items, where


def parse_port_log(log: str, flds, where, nitems: int) -> list[dict]:
    """BRK + SDUMP lines -> frames [{_vbl, _field, frame, field values...}]."""
    frames = []
    cur = None
    for ln in log.splitlines():
        if ln.startswith("BRK rva="):
            if cur is not None and len(cur["_raw"]) == nitems:
                frames.append(cur)
            m = re.search(r"vbl=(\d+).* hit=(\d+)", ln)
            cur = {"_raw": [], "_vbl": int(m.group(1)), "frame": int(m.group(2))}
            continue
        if ln.startswith("SDUMP ") and cur is not None:
            m = re.match(r"SDUMP field=(\d+) vbl=(\d+) (\S+?):(.*)$", ln)
            if not m:
                continue
            cur["_field"] = int(m.group(1))
            if ln.endswith(": NULL"):
                cur["_raw"].append(b"")      # retail's W_ptr reads a NULL chain as 0
                continue
            cur["_raw"].append(bytes.fromhex(m.group(4).strip().replace(" ", "")))
    if cur is not None and len(cur["_raw"]) == nitems:
        frames.append(cur)
    out = []
    for fr in frames:
        d = {"_field": fr.get("_field"), "_vbl": fr["_vbl"], "frame": fr["frame"]}
        for f in flds:
            k, o, sz = where[f.name]
            b = fr["_raw"][k]
            d[f.name] = decode(f.typ, bytes(sz) if not b else None if len(b) < o + sz else b[o:o + sz])
        out.append(d)
    return out


def _run_port(exe: Path, args: list[str], env: dict, log_path: Path, timeout=1800) -> str:
    import fxlib
    cmd = [sys.executable, str(PORT / "tools" / "fixtures" / "run_from.py")] + args + ["--exe", str(exe)]
    p = subprocess.run(cmd, env=fxlib.game_env(env), capture_output=True, text=True, errors="replace",
                       timeout=timeout)
    log = p.stdout + p.stderr
    log_path.write_text(" ".join(cmd) + "\n" + json.dumps(env) + "\n" + log, encoding="utf-8")
    if "EXCEPTION" in log:
        print(f"  port: EXCEPTION in {log_path}", flush=True)
    return log


def port_env(exe: Path, flds, from_vbl: int, extra_env: dict, frame_keys: bool):
    pm = PortMap(exe)
    items, where = port_groups(flds, pm)
    spec = ",".join(items)
    if len(spec) > 4000:
        raise SystemExit(f"field spec too long for rg_dump_spec ({len(spec)} chars); use --groups")
    sym = pm.syms.get("_" + SAMPLE_SYM, pm.syms.get(SAMPLE_SYM))
    env = {"RG_BREAK": f"0x{sym:X}", "RG_BREAK_SPEC": spec, "RG_BREAK_MAX": "100000000",
           "RG_BREAK_FROM_VBL": str(from_vbl), "RG_SS": "1"}
    if frame_keys:
        env["RG_INPUT_KEY"] = "frames"
    env.update(extra_env)
    return env, where, len(items)


def script_lines(events: list[tuple]) -> list[str]:
    """plan events (frame-keyed) -> rg-game script lines (RG_INPUT_KEY=frames)."""
    L, S = [], []
    for e in sorted(events, key=lambda e: e[1]):
        if e[0] == "press":
            _, v, btn, dur = e
            L.append(f"{v} {v + dur - 1} {btn}")
        elif e[0] == "stick":
            _, v, dur, lx, ly = e
            S.append(f"#!stick {v} {v + dur - 1} {lx} {ly}")
    return L + (["#!stick 1 0"] + S if S else [])


def _shift_line(line: str, off: int) -> str:
    p = line.split(None, 2)
    if len(p) >= 3 and p[0].isdigit() and p[1].isdigit():
        return f"{int(p[0]) + off} {int(p[1]) + off} {p[2]}"
    return line


def _write_frames(path: Path, frames, anchors, meta) -> Path:
    with open(path, "w", encoding="utf-8") as f:
        f.write(json.dumps({"meta": meta, "anchors": anchors}) + "\n")
        for i, fr in enumerate(frames):
            f.write(json.dumps({"i": i, **{k: v for k, v in fr.items() if k != "_raw"}}) + "\n")
    print(f"  {path}: {len(frames)} frames, anchors {anchors}", flush=True)
    return path


def plan_segments(plan):
    """[(wait step or None, [actions after it])]."""
    segs, cur = [], (None, [])
    for st in plan:
        if st[0] == "wait":
            segs.append(cur)
            cur = (st, [])
        else:
            cur[1].append(st)
    segs.append(cur)
    return [s for s in segs if s[0] is not None or s[1]]


def run_port_scenario(name: str, exe: Path, out: Path, groups=None, extra_env=None) -> Path:
    sc = scenario(name)
    out.mkdir(parents=True, exist_ok=True)
    flds = FL.select(groups)
    extra_env = extra_env or {}
    if sc["kind"] == "route":
        golden = PORT / "tools" / "trace" / "goldens" / sc["golden"]
        inp = out / "port.input.txt"
        L = golden.read_text().splitlines() + [_shift_line(x, ROUTE_FIELD_OFF) for x in sc.get("extra", [])]
        inp.write_text("\n".join(L) + "\n")
        env, where, n = port_env(exe, flds, sc["start_vbl"], extra_env, frame_keys=False)
        log = _run_port(exe, [sc["milestone"], "--input", str(inp), "--fields",
                              str(sc["end_vbl"] + ROUTE_FIELD_OFF)], env, out / "port.log")
        frames = parse_port_log(log, flds, where, n)
        cmp = cond_fn(sc["compare"])
        idx = next((i for i, fr in enumerate(frames) if cmp(fr)), None)
        return _write_frames(out / "port.jsonl", frames, {"compare": idx}, {"scenario": name, "exe": str(exe)})
    core = FL.select(CORE)
    events: list[tuple] = []          # frame-keyed presses / sticks
    anchor = None                     # (frame, vbl) of the current anchor
    compare_at = end_at = None
    passno = 0
    for wait, actions in plan_segments(sc["plan"]):
        if wait is not None:
            _, cond, max_frames, *mash = wait
            base = anchor[0] if anchor else 0
            horizon = base + max_frames
            trial = list(events)
            mash = mash[0] if mash else None
            if mash:
                btn, period, first = mash
                start = base + first if anchor else max(first, MASH_FROM)
                trial += [("press", f, btn, 2) for f in range(start, horizon, period)]
            passno += 1
            frames = _port_pass(exe, sc, out, core, trial, horizon, f"pass{passno}", extra_env, 0)
            c = cond_fn(cond)
            hit = next((fr for fr in frames if fr["frame"] > base and c(fr)), None)
            if hit is None:
                raise SystemExit(f"port pass {passno}: `{cond}` not met by frame {horizon}")
            anchor = (hit["frame"], hit["_vbl"])
            if mash:   # the mash presses that began before the anchor frame (as on retail)
                events = [e for e in trial if e in events or e[1] < anchor[0]]
            print(f"  port pass {passno}: `{cond}` at frame {anchor[0]} (vbl {anchor[1]}, field "
                  f"{hit['_field']})", flush=True)
        for st in actions:
            if st[0] == "press":
                events.append(("press", anchor[0] + st[1], st[2], st[3]))
            elif st[0] == "stick":
                events.append(("stick", anchor[0] + st[1], st[2], st[3], st[4]))
            elif st[0] == "compare":
                compare_at = anchor
            elif st[0] == "end":
                end_at = anchor[0] + st[1]
    frames = _port_pass(exe, sc, out, flds, events, end_at, "final", extra_env, max(0, compare_at[1] - 120))
    idx = next((i for i, fr in enumerate(frames) if fr["frame"] >= compare_at[0]), None)
    (out / "port_events.json").write_text(json.dumps({"events": events, "compare": compare_at, "end": end_at}))
    return _write_frames(out / "port.jsonl", frames, {"compare": idx},
                         {"scenario": name, "exe": str(exe), "compare_frame": compare_at[0]})


def _port_pass(exe, sc, out, flds, events, horizon_frames, tag, extra_env, from_vbl):
    """One boot-save run of a card scenario, frame-keyed input, frames up to horizon."""
    sp = out / f"{tag}.input.txt"
    sp.write_text("# parity.py generated (RG_INPUT_KEY=frames: keys are game frames)\n"
                  + "\n".join(script_lines(events)) + "\n")
    env, where, n = port_env(exe, flds, from_vbl, extra_env, frame_keys=True)
    # fields to run: frames run at 1-2 VBlanks (+ loads); stop is checked on the frames
    fields = 2 * horizon_frames + 1200
    log = _run_port(exe, ["--boot-save", sc["card"], "--input", str(sp), "--fields", str(fields)],
                    env, out / f"{tag}.log")
    return [fr for fr in parse_port_log(log, flds, where, n) if fr["frame"] <= horizon_frames]


# ------------------------------------------------------------------ retail side
def retail_items(flds):
    """Unique (chain, word offset) words in record order, and their probe W_* items."""
    import probe
    words, seen = [("=E1000", 0)], {("=E1000", 0): 0}     # word 0: FRAMECTR
    for f in flds:
        sz = FL.TYPES[f.typ]
        for w in range(f.off & ~3, f.off + sz, 4):
            key = (f.chain, w)
            if key not in seen:
                seen[key] = len(words)
                words.append(key)
    specs = []
    for ch, w in words:
        kind, addr, hops = FL.parse_chain(ch)
        specs.append(probe.W_abs(addr + w) if kind == "=" else probe.W_ptr(addr, *hops, w))
    return words, seen, specs


def retail_decode(rec_words: list[int], flds, seen) -> dict:
    d = {"frame": rec_words[0]}
    for f in flds:
        sz = FL.TYPES[f.typ]
        w0 = f.off & ~3
        raw = b"".join(struct.pack("<I", rec_words[seen[(f.chain, w)]]) for w in range(w0, f.off + sz, 4))
        o = f.off - w0
        d[f.name] = decode(f.typ, raw[o:o + sz])
    return d


class RetailRun:
    """One PCSX2 run with the frame sampler and the guest input table."""

    def __init__(self, flds, speed: float, memcard_name: str | None, input_words=None,
                 sticks=False, tag="parity", ee_rate: int = 0, frame_keys=True, extra_hooks=None):
        import emu
        import input as inp
        import probe
        from mips import T4, T5
        self.flds = flds
        self.words, self.seen, specs = retail_items(flds)
        self.nrec = (len(specs) + 5) // 6
        h = probe.Hooks()
        w0, w1 = h._orig(SAMPLE_ADDR)
        a = h.a
        t = a.pc
        # FRAMECTR += 1 (t4/t5 are free at a function entry, as emit_log assumes)
        a.lui(T4, FRAMECTR >> 16)
        a.lw(T5, FRAMECTR & 0xFFFF, T4)
        a.addiu(T5, T5, 1)
        a.sw(T5, FRAMECTR & 0xFFFF, T4)
        self.sites = []
        for r in range(self.nrec):
            chunk = specs[6 * r:6 * r + 6]
            while len(chunk) < 6:
                chunk.append(probe.W_reg(probe.ZERO))
            s = h._site(f"S{r}")
            self.sites.append(s)
            probe.emit_log(a, 1, s, ("words", chunk))
        a.w(w0)
        a.w(w1)
        a.j(SAMPLE_ADDR + 8)
        h._patch(SAMPLE_ADDR, t, (w0, w1))
        if extra_hooks:     # more probe hooks; their records go to self.events (raw)
            extra_hooks(h)
        self.hooks = h
        self.events = []
        # EE overclock (PCSX2 EECycleRate 1..3): fewer dropped frames on retail
        # + fast CDVD: the port's loads take no game time; retail's emulated drive makes the
        # game drop frames (frametime > 1) while a battle or a menu loads
        # (route scenarios replay a VBlank-keyed golden recorded on a stock PCSX2: --ee-rate 0
        # keeps both off there)
        ov = [f"EmuCore/Speedhacks/EECycleRate={ee_rate}",
              f"EmuCore/Speedhacks/fastCDVD={'true' if ee_rate else 'false'}"]
        if memcard_name:
            ov += ["MemoryCards/Slot1_Enable=true", f"MemoryCards/Slot1_Filename={memcard_name}"]
        self.e = emu.Emu(speed=speed, renderer=11, tag=tag, overrides=ov, memcard=memcard_name is None)
        self.inp, self.probe = inp, probe
        self.input_words = input_words if input_words is not None else [0] * inp.MAX_ENTRIES
        self.sticks, self.frame_keys = sticks, frame_keys
        self.last = 0
        self.frames = []
        self.pending = []
        self.lost = 0
        self.stick_events = []

    def start(self):
        import live
        pine = self.e.connect()
        self.pine = pine
        self.sampler = live.LiveSampler(self.e.proc.pid, self.e.log)
        self.base = self.sampler.addr["ee"]
        blobs = self.hooks.blobs()
        probe, inp = self.probe, self.inp

        def sites_loaded():
            return all((pine.read32(p[0]), pine.read32(p[0] + 4)) == tuple(p[2]) for p in self.hooks.patches)

        t_end = time.time() + 120
        while not sites_loaded():
            if time.time() > t_end:
                raise RuntimeError("hook site never showed the retail code")
            time.sleep(0.002)

        def check_free():
            z = pine.read_block(probe.CODE, 0x400) + pine.read_block(probe.LOG, 0x400)
            return not any(z) and sites_loaded() and pine.read32(FRAMECTR) == 0
        st = [0, 0] if self.sticks else None
        keep = inp.VBL
        if self.frame_keys:
            inp.VBL = FRAMECTR          # the trampoline indexes the table by the frame counter
        try:
            k = inp.install(pine, self.input_words, sampler=None, extra=blobs, precheck=check_free, sticks=st)
        finally:
            inp.VBL = keep
        print(f"  retail: hooks installed at key {k}, {self.nrec} records/frame", flush=True)

    def mem(self, addr, n):
        return self.sampler.p.read(self.base + addr, n)

    def u32(self, addr):
        return struct.unpack("<I", self.mem(addr, 4))[0]

    def frame(self):
        return self.u32(FRAMECTR)

    def vbl(self):
        return self.u32(self.inp.VBL)

    def drain(self) -> list[dict]:
        """New complete frames from the ring."""
        probe = self.probe
        count = self.u32(probe.LOG)
        safe = count - 1
        if safe <= self.last:
            return []
        first = self.last
        if safe - first > probe.NREC:
            self.lost += safe - first - probe.NREC
            first = safe - probe.NREC
            self.pending = []
        ring = self.mem(probe.RING, probe.NREC * probe.REC)
        new = []
        for seq in range(first, safe):
            o = (seq % probe.NREC) * probe.REC
            w = struct.unpack_from("<16I", ring, o)
            if (w[0] >> 16) != (seq & 0xFFFF):
                self.pending = []
                continue
            site = w[0] & 0xFF
            if site not in self.sites:
                self.events.append({"seq": seq, "site": self.hooks.sites.get(site, site), "kind": (w[0] >> 8) & 0xFF,
                                    "vbl": w[1], "a": list(w[3:7]), "v0": w[7], "ra": w[8], "d": list(w[10:16])})
                continue
            if site == self.sites[0]:
                self.pending = [(w[1], list(w[10:16]))]
                self.pending_seq = seq
            elif self.pending and len(self.pending) < self.nrec and site == self.sites[len(self.pending)]:
                self.pending.append((w[1], list(w[10:16])))
            else:
                self.pending = []
                continue
            if len(self.pending) == self.nrec:
                fr = retail_decode([x for _, r in self.pending for x in r], self.flds, self.seen)
                fr["_vbl"] = self.pending[0][0]
                fr["_seq"] = self.pending_seq
                new.append(fr)
                self.pending = []
        self.last = safe
        self.frames += new
        return new

    def press(self, k, btn, dur):
        bits = self.inp.BUTTONS[btn]
        cur = self.frame() if self.frame_keys else self.vbl()
        if k <= cur:
            print(f"  retail: press {btn} at {k} too late (now {cur})", flush=True)
        for j in range(k, k + dur):
            if j < self.inp.MAX_ENTRIES:
                self.input_words[j] |= bits
                self.pine.write16(self.inp.TABLE + 4 + 2 * j, self.input_words[j])

    def add_sticks(self, events):
        """events [(first, last, word)] -> the stick window (base, count, words): words first,
        then base|count in one 64-bit write."""
        self.stick_events += events
        tab = self.inp.build_stick_table(self.stick_events)
        base, cnt, words = tab[0], tab[1], tab[2:]
        blob = struct.pack(f"<{len(words)}I", *words)
        blob += bytes(-len(blob) % 8)
        self.pine.write_block(self.inp.STICK_TABLE + 8, blob)
        self.pine.write64(self.inp.STICK_TABLE, base | (cnt << 32))

    def stop(self):
        self.e.stop()


def run_retail_scenario(name: str, out: Path, speed: float, groups=None, ee_rate: int = 3,
                        extra_hooks=None) -> Path:
    import cardboot
    import input as inp
    sc = scenario(name)
    out.mkdir(parents=True, exist_ok=True)
    b = cardboot.busy()
    if b:
        raise SystemExit("a portable PCSX2 is running (" + ", ".join(b) + "); one instance at a time")
    flds = FL.select(groups)
    logf = open(out / "retail.log", "w", encoding="utf-8")

    def log(msg):
        logf.write(msg + "\n")
        logf.flush()
        print("  retail: " + msg, flush=True)

    t0 = time.time()
    if sc["kind"] == "route":
        golden = PORT / "tools" / "trace" / "goldens" / sc["golden"]
        tmp = out / "retail.input.txt"
        tmp.write_text(golden.read_text().rstrip("\n") + "\n" + "\n".join(sc.get("extra", [])) + "\n")
        words = inp.build_table(inp.parse_script(str(tmp)))
        sticks = inp.parse_sticks(str(tmp))
        rr = RetailRun(flds, speed, None, input_words=words, sticks=bool(sticks), tag="parity_route",
                       ee_rate=0, frame_keys=False)
        try:
            rr.start()
            if sticks:
                rr.add_sticks(sticks)
            keep, nxt = [], time.time()
            while True:
                keep += [fr for fr in rr.drain() if fr["_vbl"] >= sc["start_vbl"]]
                v = rr.vbl()
                if time.time() > nxt:
                    log(f"vbl {v} frames {len(keep)} lost {rr.lost} ({time.time() - t0:.0f} s)")
                    nxt = time.time() + 60
                if v >= sc["end_vbl"]:
                    time.sleep(0.3)
                    keep += [fr for fr in rr.drain() if fr["_vbl"] >= sc["start_vbl"]]
                    break
                if time.time() - t0 > 3600:
                    raise TimeoutError("route run over an hour")
                time.sleep(0.05)
        finally:
            rr.stop()
        cmp = cond_fn(sc["compare"])
        idx = next((i for i, fr in enumerate(keep) if cmp(fr)), None)
        return _write_frames(out / "retail.jsonl", keep, {"compare": idx}, {"scenario": name, "lost": rr.lost})
    # card scenario: live, frame keyed
    src = cardboot.CARDS / sc["card"]
    mc_dir = Path(cardboot.emu.EMU_DIR) / "memcards"
    mc_dir.mkdir(parents=True, exist_ok=True)
    mc = mc_dir / f"parity_{sc['card']}.ps2"
    cardboot.export_card(src, mc)
    rr = RetailRun(flds, speed, mc.name, sticks=True, tag=f"parity_{sc['card']}", ee_rate=ee_rate,
                   extra_hooks=extra_hooks)
    events = []
    compare_at = end_at = None
    try:
        rr.start()
        anchor = None
        for wait, actions in plan_segments(sc["plan"]):
            if wait is not None:
                _, cond, max_frames, *mash = wait
                mash = mash[0] if mash else None
                c = cond_fn(cond)
                base = anchor[0] if anchor else 0
                nextp = (base + mash[2] if anchor else max(mash[2], MASH_FROM)) if mash else None
                hit, tw = None, time.time()
                while hit is None:
                    for fr in rr.drain():
                        if fr["frame"] > base and c(fr):
                            hit = fr
                            break
                    if hit:
                        break
                    cur = rr.frame()
                    if mash and cur + LEAD >= nextp:
                        at = max(nextp, cur + LEAD)
                        rr.press(at, mash[0], 2)
                        events.append(("press", at, mash[0], 2))
                        nextp = at + mash[1]
                    if cur > base + max_frames or time.time() - tw > 900:
                        raise TimeoutError(f"`{cond}` not met by frame {cur}")
                    time.sleep(0.005)
                anchor = (hit["frame"], hit["_vbl"])
                # mash presses at or after the anchor frame are taken back where still possible
                for e in [e for e in events if e[1] >= anchor[0] and mash and e[2] == mash[0]]:
                    for j in range(e[1], e[1] + e[3]):
                        rr.input_words[j] &= ~inp.BUTTONS[e[2]]
                        rr.pine.write16(inp.TABLE + 4 + 2 * j, rr.input_words[j])
                    events.remove(e)
                log(f"wait `{cond}`: anchor frame {anchor[0]} vbl {anchor[1]} (now frame {rr.frame()})")
            sticks = []
            for st in actions:
                if st[0] == "press":
                    rr.press(anchor[0] + st[1], st[2], st[3])
                    events.append(("press", anchor[0] + st[1], st[2], st[3]))
                elif st[0] == "stick":
                    a0 = anchor[0] + st[1]
                    sticks.append((a0, a0 + st[2] - 1, 0x80 | 0x80 << 8 | st[3] << 16 | st[4] << 24))
                    events.append(("stick", a0, st[2], st[3], st[4]))
                elif st[0] == "compare":
                    compare_at = anchor
                elif st[0] == "end":
                    end_at = anchor[0] + st[1]
            if sticks:
                if sticks[0][0] <= rr.frame() + 1:
                    log(f"WARNING: stick from frame {sticks[0][0]} written at frame {rr.frame()} (late)")
                rr.add_sticks(sticks)
        while rr.frame() < end_at:
            rr.drain()
            time.sleep(0.05)
        time.sleep(0.3)
        rr.drain()
    finally:
        rr.stop()
        mc.unlink(missing_ok=True)
    frames = [fr for fr in rr.frames if compare_at[0] - 60 <= fr["frame"] <= end_at]
    idx = next((i for i, fr in enumerate(frames) if fr["frame"] >= compare_at[0]), None)
    (out / "retail_events.json").write_text(json.dumps({"events": events, "compare": compare_at, "end": end_at}))
    if extra_hooks:
        (out / "retail_hooks.json").write_text(json.dumps(rr.events))
    log(f"done: {len(frames)} frames, lost {rr.lost}, {time.time() - t0:.0f} s")
    return _write_frames(out / "retail.jsonl", frames, {"compare": idx},
                         {"scenario": name, "lost": rr.lost, "compare_frame": compare_at[0]})


# ------------------------------------------------------------------ compare
def load_frames(path: Path):
    with open(path, encoding="utf-8") as f:
        head = json.loads(f.readline())
        frames = [json.loads(ln) for ln in f]
    for fr in frames:
        for k, v in fr.items():
            if isinstance(v, list) and v and v[0] == "f":
                fr[k] = tuple(v)
    return head, frames


def same(a, b) -> bool:
    if isinstance(a, tuple) and isinstance(b, tuple):
        return a[1] == b[1]
    return a == b


def compare(port_path: Path, retail_path: Path, groups=None, context=4, limit=None,
            context_groups=12, shift=0) -> str:
    ph, pf = load_frames(port_path)
    rh, rf = load_frames(retail_path)
    pa, ra = ph["anchors"].get("compare"), rh["anchors"].get("compare")
    if pa is None or ra is None:
        return f"no compare anchor (port {pa}, retail {ra})"
    shift = min(shift, pa, ra)        # start SHIFT frames before the anchor
    P, R = pf[pa - shift:], rf[ra - shift:]
    n = min(len(P), len(R))
    if limit:
        n = min(n, limit)
    flds = [f for f in FL.select(groups) if f.name not in FL.NOT_COMPARED]
    names = [f.name for f in flds if f.name in P[0] and f.name in R[0]]
    first = {}
    for k in range(n):
        for nm in names:
            if nm not in first and not same(P[k].get(nm), R[k].get(nm)):
                first[nm] = k
    out = [f"== parity {ph['meta'].get('scenario')}: {n} frames compared from the anchor "
           f"(port frame {P[0].get('frame')} vbl {P[0]['_vbl']}, retail frame {R[0].get('frame')} vbl {R[0]['_vbl']})"]
    gap = next((k for k in range(1, n) if (P[k].get("frame", 0) - P[0].get("frame", 0)) !=
                (R[k].get("frame", 0) - R[0].get("frame", 0))), None)
    pv = [P[k]["_vbl"] - P[0]["_vbl"] for k in range(n)]
    rv = [R[k]["_vbl"] - R[0]["_vbl"] for k in range(n)]
    pace = next((k for k in range(n) if pv[k] != rv[k]), None)
    drops = sum(1 for k in range(1, n) if (rv[k] - rv[k - 1]) > (pv[k] - pv[k - 1]))
    out.append(f"  frame index gaps (missing samples): {'none' if gap is None else 'first at ' + str(gap)}; "
               f"VBlank pacing first differs at frame {pace}, retail longer frames: {drops}")
    rng_k = first.get("rng")
    out.append(f"  identical fields: {len(names) - len(first)}/{len(names)}; rng first differs at "
               f"{'never' if rng_k is None else rng_k}")
    groups_ = {}
    for nm, k in first.items():
        obj = nm.rsplit(".", 1)[0] if "." in nm else nm
        groups_.setdefault((k, obj), []).append(nm)
    shown = 0
    for (k, obj), nms in sorted(groups_.items()):
        nms.sort()
        tag = " (after rng)" if rng_k is not None and k > rng_k else ""
        vals = ", ".join(f"{nm.split('.')[-1]} {show(P[k].get(nm))}/{show(R[k].get(nm))}" for nm in nms[:6])
        more = f" (+{len(nms) - 6} more)" if len(nms) > 6 else ""
        out.append(f"  frame {k:5d} (vbl port {P[k]['_vbl']} retail {R[k]['_vbl']}) {obj}: {vals}{more}{tag}")
        if shown < context_groups:
            shown += 1
            nm = nms[0]
            for j in range(max(0, k - context), min(n, k + 3)):
                out.append(f"      f{j:5d}  {nm:12s} port {show(P[j].get(nm)):>16s}  retail "
                           f"{show(R[j].get(nm)):>16s}  {'' if same(P[j].get(nm), R[j].get(nm)) else '<--'}")
    return "\n".join(out)


# ------------------------------------------------------------------ cli
def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("list")
    for c in ("port", "retail", "run"):
        p = sub.add_parser(c)
        p.add_argument("scenario")
        p.add_argument("--out")
        p.add_argument("--groups")
        if c in ("port", "run"):
            p.add_argument("--exe", required=True)
            p.add_argument("--env", action="append", default=[], metavar="K=V")
        if c in ("retail", "run"):
            p.add_argument("--speed", type=float, default=1.0)
            p.add_argument("--ee-rate", type=int, default=3, help="PCSX2 EECycleRate (0 = stock EE)")
    p = sub.add_parser("compare")
    p.add_argument("dir")
    p.add_argument("--port")
    p.add_argument("--retail")
    p.add_argument("--groups")
    p.add_argument("--context", type=int, default=4)
    p.add_argument("--limit", type=int)
    p.add_argument("--shift", type=int, default=0, help="start N frames before the compare anchor")
    a = ap.parse_args(argv)
    if a.cmd == "list":
        for k, v in SCENARIOS.items():
            print(f"{k:20s} {v['kind']:6s} {v.get('desc', '')}")
        print(f"{len(FL.all_fields())} fields; groups: " + ",".join(sorted({f.group for f in FL.all_fields()})))
        return 0
    if a.cmd == "compare":
        d = Path(a.dir)
        rep = compare(Path(a.port or d / "port.jsonl"), Path(a.retail or d / "retail.jsonl"), a.groups,
                      a.context, a.limit, shift=a.shift)
        (d / "compare.txt").write_text(rep + "\n", encoding="utf-8")
        print(rep.encode("ascii", "replace").decode())
        return 0
    out = Path(a.out or PORT / "out" / "parity" / a.scenario)
    if a.cmd in ("port", "run"):
        env = dict(kv.split("=", 1) for kv in a.env)
        run_port_scenario(a.scenario, Path(a.exe).resolve(), out, a.groups, env)
    if a.cmd in ("retail", "run"):
        run_retail_scenario(a.scenario, out, a.speed, a.groups, a.ee_rate)
    if a.cmd == "run":
        rep = compare(out / "port.jsonl", out / "retail.jsonl", a.groups)
        (out / "compare.txt").write_text(rep + "\n", encoding="utf-8")
        print(rep.encode("ascii", "replace").decode())
    return 0


if __name__ == "__main__":
    sys.exit(main())

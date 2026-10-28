#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Long soak: play every library card for thousands of fields with scripted input and
collect what a play-tester would hit (docs/TEST-FIXTURES.md "Long soak").

    python tools/fixtures/soak.py run --exe EXE --out DIR [CARD ...] [--all] [--fields 5000]
                                  [--seed 1] [--shots] [--max-battles 3] [--tag NAME]
    python tools/fixtures/soak.py report DIR [DIR ...]        # findings table (markdown)
    python tools/fixtures/soak.py heap STATE [STATE ...]      # dlmalloc walk of a state's game heap
    python tools/fixtures/soak.py repro DIR/findings/NN       # re-run one finding's segment
    python tools/fixtures/soak.py run ... --wide --maps --fast-boot [--map-fields N]  # widened (soak2)
    python tools/fixtures/soak.py fights --exe EXE --out DIR [CARD ...]   # one --wide fight per w_ card
    python tools/fixtures/soak.py coverage DIR [DIR ...]      # zones per planet, battle tactic totals
    python tools/fixtures/soak.py drivers --exe EXE --out DIR [NAME ...]  # closed-loop drivers (DRIVERS):
                                  # insectstory (story Insectron final + rank reward), insectrun, factory production

--wide / --maps / fights / coverage: docs/TEST-FIXTURES.md "Widened soak".

Per card one session (default cards: cardlib.LIBRARY + save2 + factory + insectron):
  boot     the bootcheck.py library script (CONTINUE, recap; pass 1 finds field control C),
           then a run to C+40 that writes the session's first save state (RG_SS=1).  The
           session keeps ONE saves dir (the card copy): card writes persist across segments.
  loop     one rg-game segment at a time from the last state (--load-state, --save-state at
           the segment end, a memory probe = autobattle.dump_spec + the map id at the end):
           - field control (6/*): explore (camera-free random stick headings, 120-240
             fields, the heading changes when the leader stops moving), every 4th activity a
             menu pass (main menu, a seeded random walk of DOWN/UP/LEFT/RIGHT/CROSS/L1/R1
             presses = Items/Equip/Revelation/Allies/Strategy/... sub-screens, item use,
             equipment changes; then CIRCLE x8: the game must be back in the field), once per
             session a transporter save on cards that spawn at one (save2, alistia) and a
             reload check of the written card (a fresh boot must reach field control);
           - battle (7/*): autobattle.fight from that state (closed loop: run, sword, potions,
             leader switch), then CROSS through the results until field control;
           - a lost battle / title / game over: the session restarts from its boot state;
           - anything else (event, talk, loading): CROSS every 30 fields.
  checks   per segment: rg-game exit code and EXCEPTION (crash), the wall-clock timeout
           (hang), the field reached (no progress), log lines outside the known set
           (anomaly), UBSan rows ($RG_UBSAN_LOG, a -DRG_UBSAN=ON exe), stack-guard rows
           ($RG_SBGUARD_LOG, a -DRG_SBGUARD=ON exe), a dlmalloc walk of the game heap in the
           segment's end state every --heap-every segments (corrupt chain = finding; in-use
           bytes are tracked per card: a steady climb = leak candidate), a menu pass that does
           not return to the field (soft lock candidate), N segments with nothing changing.
  output   DIR/<card>/: session.tsv (one row per segment), route.txt (boot script + every
           segment's input with absolute fields: replays the session from power-on as long as
           it never restarted), states of the last segments, ubsan.tsv / sbguard.tsv;
           DIR/findings/NN/: finding.json, the segment's start state, input and log, and a
           repro command (soak.py repro); DIR/summary.tsv (one row per card), DIR/findings.tsv.

Exit 0 always (the report is the result).  One rg-game at a time (machine limits).
Factory: the boot_factory golden (FACTORY overlay and back) then the normal loop;
insectron: the boot_insectron golden (INSMENU -> INSECT CPU vs CPU) extended with CROSS every
300 fields (crash / hang checks only).
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
import random
import re
import shutil
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "trace"))
import fxlib  # noqa: E402
import bootcheck  # noqa: E402
import autobattle  # noqa: E402
import cardlib  # noqa: E402

GOLD = fxlib.PORT / "tools" / "trace" / "goldens"
SAVE_CARDS = {"save2", "alistia"}      # spawn at a transporter: the save activity works there
SCRIPT_MAX = 32636                     # RG_SCRIPT_MAX_ENTRIES: input keys are absolute fields

# log lines every run prints (prefixes); anything else is collected as an anomaly
KNOWN = re.compile(r"^(rg-game: (fields|run_hash|data|saves|settings|exe)|rg_audio|rg_fs|rg_runtime|rg_iop|"
                   r"LOADSTATE|SAVESTATE|SHOT|STATUS|DUMP|native render|rg_slots|rg_gpu: adapter|"
                   r"rg_movie|rg_settings|rg_host|rg_pace|native |rg-game: \d+ runs? already active|  )")


def now():
    return time.strftime("%H:%M:%S")


# ---------------------------------------------------------------- state file / heap walk
def state_sections(path: Path, want=("ram",)) -> dict:
    """{name: (addr, bytes)} of the wanted sections of an .rgstate (src/savestate/ss_core.c:
    560-byte header (nsect at +112), then per section a 56-byte ss_shdr, a page bitmap and
    the non-zero 4 KiB pages)."""
    out = {}
    with open(path, "rb") as f:
        hdr = f.read(fxlib.HDR_BYTES)
        nsect = struct.unpack_from("<I", hdr, 112)[0]
        for _ in range(nsect):
            sh = f.read(56)
            if len(sh) < 56:
                break
            name = sh[:32].split(b"\0")[0].decode("latin-1")
            addr, size, enc, stored = struct.unpack_from("<4I", sh, 32)
            if name not in want:
                f.seek(stored, 1)
                continue
            npages = (size + 4095) // 4096
            bm = f.read((npages + 7) // 8)
            buf = bytearray(size)
            for i in range(npages):
                if bm[i // 8] >> (i % 8) & 1:
                    o = i * 4096
                    n = min(4096, size - o)
                    buf[o:o + n] = f.read(n)
            out[name] = (addr, bytes(buf))
    return out


_HEAPSYM = {}


def _heap_syms(exe: Path) -> dict:
    """RVAs of the retail malloc state the game link binds (rg_game_main.c rg_crt_heap_bind):
    D_00449868 = av_ (bins; top = av_[2]), D_00449C70 = params ([4] sbrk_base, [10] sbrked_mem)."""
    k = str(exe)
    if k not in _HEAPSYM:
        r = {}
        for line in open(Path(exe).with_suffix(".map"), encoding="latin-1"):
            m = re.match(r"\s*000\d:[0-9a-f]+\s+_?(D_00449868|D_00449C70)\s+([0-9a-f]{16})\s", line)
            if m:
                r[m.group(1)] = int(m.group(2), 16) - 0x400000
        _HEAPSYM[k] = r
    return _HEAPSYM[k]


def heapwalk(path: Path, exe: Path) -> dict:
    """Walk the game heap's dlmalloc chunk chain (src/crt/crt_heap.c: retail newlib dlmalloc,
    8-byte headers prev_size / size|PREV_INUSE; the port's bins / top / sbrk_base are HOST
    pointers) from the first chunk after sbrk_base to the top chunk read from av_.  Checks:
    sizes 8-aligned and >= 16, every free chunk's footer (next.prev_size == size), no two
    adjacent free chunks (dlmalloc always coalesces), the walk lands exactly on top, top
    ends at sbrk_base + sbrked_mem.  {ok, why, chunks, used, used_bytes, free, free_bytes,
    top_bytes, sbrked}."""
    try:
        hdr = Path(path).open("rb").read(fxlib.HDR_BYTES)
        image_base = struct.unpack_from("<I", hdr, 64)[0]
        secs = state_sections(path, ("ram", "statics.map", "statics"))
    except OSError as e:
        return {"ok": False, "why": f"unreadable: {e}"}
    if "ram" not in secs or "statics" not in secs:
        return {"ok": False, "why": "no ram / statics section"}
    ram_host, ram = secs["ram"]
    tab = secs["statics.map"][1]
    nr = struct.unpack_from("<I", tab, 0)[0]
    flat = secs["statics"][1]
    ranges, o = [], 0
    for i in range(nr):
        lo, hi = struct.unpack_from("<II", tab, 4 + 8 * i)
        ranges.append((lo, hi, o))
        o += hi - lo

    def sread(addr, n):
        for lo, hi, off in ranges:
            if lo <= addr and addr + n <= hi:
                return flat[off + addr - lo:off + addr - lo + n]
        return None
    sy = _heap_syms(exe)
    if len(sy) < 2:
        return {"ok": False, "why": "no D_00449868 / D_00449C70 in the map"}
    av = sread(image_base + sy["D_00449868"], 16)
    pm = sread(image_base + sy["D_00449C70"], 48)
    if av is None or pm is None:
        return {"ok": False, "why": "malloc state not in the statics"}
    top = struct.unpack_from("<I", av, 8)[0]
    sbrk_base, sbrked = struct.unpack_from("<I", pm, 16)[0], struct.unpack_from("<I", pm, 40)[0]
    to = lambda h: h - ram_host
    p = to(sbrk_base)
    p += (8 - (p + ram_host) % 16) % 16          # first chunk: chunk2mem 16-aligned
    end, t = to(sbrk_base + sbrked), to(top)
    n = len(ram)
    if not (0 <= p < n and 0 <= t < n and 0 < end <= n):
        return {"ok": False, "why": f"heap pointers outside the ram section: sbrk_base {sbrk_base:#x} "
                f"top {top:#x} sbrked {sbrked:#x} ram {ram_host:#x}+{n:#x}"}
    chunks = used = used_b = free = free_b = 0
    prev_free = False
    while p != t:
        if p > t or p + 8 > n:
            return {"ok": False, "why": f"chain passes top (+{t:#x}) at +{p:#x} after {chunks} chunks",
                    "chunks": chunks}
        size_f = struct.unpack_from("<I", ram, p + 4)[0]
        sz = size_f & ~7
        if sz < 16:
            return {"ok": False, "why": f"bad size {size_f:#x} at +{p:#x} after {chunks} chunks",
                    "chunks": chunks}
        nxt = p + sz
        if nxt > t:
            return {"ok": False, "why": f"chunk +{p:#x} size {sz:#x} overlaps top +{t:#x}", "chunks": chunks}
        in_use = bool(struct.unpack_from("<I", ram, nxt + 4)[0] & 1)
        if not in_use:
            if struct.unpack_from("<I", ram, nxt)[0] != sz:
                return {"ok": False, "why": f"free chunk +{p:#x} size {sz:#x}: footer "
                        f"{struct.unpack_from('<I', ram, nxt)[0]:#x}", "chunks": chunks}
            if prev_free:
                return {"ok": False, "why": f"two adjacent free chunks at +{p:#x}", "chunks": chunks}
            free += 1
            free_b += sz
        else:
            used += 1
            used_b += sz
        prev_free = not in_use
        chunks += 1
        p = nxt
    tsz = struct.unpack_from("<I", ram, t + 4)[0] & ~7
    r = {"ok": True, "why": "", "chunks": chunks, "used": used, "used_bytes": used_b, "free": free,
         "free_bytes": free_b, "top_bytes": tsz, "sbrked": sbrked}
    if t + tsz != end:
        r.update(ok=False, why=f"top +{t:#x} size {tsz:#x} ends at +{t + tsz:#x}, sbrk end +{end:#x}")
    return r


# ---------------------------------------------------------------- one rg-game segment
class Seg:
    pass


def factory_menu_row(png) -> int | None:
    """FACTORY menu cursor row from a 512x448 shot (0 Blueprints .. 6 Go Back, 7 Run): the
    highlighted row's blue bar (mean B - R over x 70..150 at the row's y) stands >= 8 above
    the others; None when the menu is hidden (floor view, Place / Move / Remove modes)."""
    if not png or not Path(png).exists():
        return None
    from PIL import Image
    im = Image.open(png).convert("RGB")
    if im.size != (512, 448):
        im = im.resize((512, 448))
    px = im.load()
    sc = []
    for y in (63, 102, 141, 179, 217, 255, 293, 365):
        v = [px[x, yy][2] - px[x, yy][0] for x in range(70, 150, 4) for yy in (y - 4, y, y + 4)]
        sc.append(sum(v) / len(v))
    order = sorted(range(8), key=lambda k: -sc[k])
    if sc[order[0]] - sc[order[1]] < 8 or sorted(sc)[3] < 0:
        return None
    return order[0]


def map_rva(exe: Path) -> int | None:
    mp = Path(exe).with_suffix(".map")
    for line in open(mp, encoding="latin-1"):
        m = re.match(r"\s*0003:[0-9a-f]+\s+_?D_004838C0\s+([0-9a-f]{16})\s", line)
        if m:
            return int(m.group(1), 16) - 0x400000
    return None


_SPEC = {}


def dump_spec(exe: Path) -> str:
    """autobattle's probe (party, records, cameras, the first action-manager charas) + the
    map id (D_004838C0 -> +0x18 -> +4, navprobe.py)."""
    k = str(exe)
    if k not in _SPEC:
        s = autobattle.dump_spec(exe)
        items = s.split(",")
        r = map_rva(exe)
        cs = autobattle._sym_rvas(exe)["D_004837C0"]
        zone = f"p0x{cs:X}/0x18+0x4:0xC"     # party +4 planet, +6 area, +8 sky, +A slot, +C zone
        if r is not None:
            while len(",".join(items + [f"p0x{r:X}/0x18+0x4:0x4", zone])) >= 511:
                items.pop()
            items.append(f"p0x{r:X}/0x18+0x4:0x4")
            items.append(zone)
        _SPEC[k] = ",".join(items)
    return _SPEC[k]


def parse_map(log: str, field: int):
    for ln in log.splitlines():
        m = re.match(rf"DUMP field={field} vbl=\d+ 00000004: ([0-9a-f]{{8}})\s*$", ln)
        if m:
            return struct.unpack("<i", bytes.fromhex(m.group(1)))[0]
    return None


def parse_zone(log: str, field: int):
    """(planet, area, zone) from the party +4..+0xF dump (dump_spec), or None."""
    for ln in log.splitlines():
        m = re.match(rf"DUMP field={field} vbl=\d+ 00000004: ([0-9a-f]{{8}}) ([0-9a-f]{{8}}) ([0-9a-f]{{8}})\s*$", ln)
        if m:
            b = bytes.fromhex(m.group(1) + m.group(2) + m.group(3))
            pl, area, sky, slot, zone = struct.unpack_from("<5h", b, 0)
            return pl, area, zone
    return None


def run_game(exe, args, env_extra, timeout):
    cmd = [str(exe), "--headless"] + [str(a) for a in args]
    t0 = time.time()
    try:
        p = subprocess.run(cmd, env=fxlib.game_env(env_extra), capture_output=True, text=True,
                           errors="replace", timeout=timeout)
        rc, log, hang = p.returncode, p.stdout + p.stderr, False
    except subprocess.TimeoutExpired as e:
        out = e.stdout or ""
        err = e.stderr or ""
        if isinstance(out, bytes):
            out = out.decode("utf-8", "replace")
        if isinstance(err, bytes):
            err = err.decode("utf-8", "replace")
        rc, log, hang = -9, out + err + "\nsoak: TIMEOUT (hang?)\n", True
    return rc, log, hang, time.time() - t0, cmd


# ---------------------------------------------------------------- the session
ANOMS = {}   # log-line anomaly keys seen in this soak run (one finding per key)

class Session:
    def __init__(self, card, exe, out, cfg, findings):
        self.card, self.exe, self.cfg, self.findings = card, exe, cfg, findings
        self.dir = out / card
        if self.dir.exists():
            shutil.rmtree(self.dir, ignore_errors=True)
        self.dir.mkdir(parents=True, exist_ok=True)
        self.rng = random.Random(f"{cfg.seed}:{card}")
        self.saves = self.dir / "saves"
        self.route = []              # absolute-field input lines since the last (re)boot
        self.k = 0                   # segment counter
        self.fields = 0              # soak fields played (after boot)
        self.stats = {"segments": 0, "battles": 0, "won": 0, "lost": 0, "menus": 0, "menu_ok": 0,
                      "walk": 0, "other": 0, "restarts": 0, "saves": 0, "save_ok": 0,
                      "reload_ok": 0, "heap_walks": 0, "maps": set(), "modes": set(),
                      "findings": 0, "heap_used": [], "zones": set(), "ability_tries": 0, "cutins": 0,
                      "items": 0, "lead_switch": 0, "switch": 0, "gun": 0, "battle_modes": {}, "transitions": 0}
        self.tsv = open(self.dir / "session.tsv", "w", encoding="utf-8")
        self.tsv.write("seg\tfrom\tto\tkind\trc\tmode\tmap\tleader\tnote\twall_s\n")
        self.same = 0
        self.last_sig = None
        self.heading = self.rng.randrange(8)
        self.visits = {}
        self.stuck_seen = set()
        self.in_mode = 0
        self.last_mode = None
        self.banned = set()
        self.env = {"RG_SS": "1", "RG_UBSAN_LOG": str(self.dir / "ubsan.tsv"),
                    "RG_SBGUARD_LOG": str(self.dir / "sbguard.tsv")}
        self.anoms = ANOMS

    # -------------------------------------------------- bookkeeping
    def finding(self, kind, note, state=None, inp=None, log=None, cmd=None, extra=None):
        n = len(list(self.findings.glob("[0-9]*"))) + 1
        d = self.findings / f"{n:03d}"
        d.mkdir(parents=True, exist_ok=True)
        info = {"n": n, "card": self.card, "kind": kind, "note": note, "segment": self.k,
                "exe": str(self.exe), "exe_id": fxlib.exe_id(self.exe), "soak_fields": self.fields}
        if state and Path(state).exists():
            shutil.copyfile(state, d / "start.rgstate")
            info["state"] = str(d / "start.rgstate")
            info["state_field"] = fxlib.peek(Path(state))["field"]
        if inp is not None:
            (d / "input.txt").write_text(inp, encoding="utf-8")
        if log is not None:
            (d / "log.txt").write_text(log, encoding="utf-8")
        if cmd:
            info["cmd"] = " ".join(map(str, cmd))
        if extra:
            info.update(extra)
        # the session's input since its last (re)boot + this segment's lines: replays the
        # finding from power-on with the card (run_from.py --boot-save CARD --input route.txt)
        seg_lines = [ln for ln in (inp or "").splitlines()
                     if ln.strip() and (not ln.startswith("#") or
                                        (ln.startswith("#!stick ") and ln.strip() != "#!stick 1 0"))]
        (d / "route.txt").write_text("\n".join(self.route + seg_lines) + "\n", encoding="utf-8")
        if kind in ("stuck", "menu-stuck", "save", "battle-stuck", "crash", "hang") and info.get("state"):
            info["shots"] = self.triage_shots(d, Path(info["state"]), inp, 16 if kind in ("crash", "hang") else 4)
        (d / "finding.json").write_text(json.dumps(info, indent=1), encoding="utf-8")
        with open(self.findings.parent / "findings.tsv", "a", encoding="utf-8") as f:
            f.write("\t".join([f"{n:03d}", self.card, kind, note.replace("\t", " "), str(self.k),
                               fxlib.exe_id(self.exe)]) + "\n")
        self.stats["findings"] += 1
        fxlib.say(f"  [{now()}] {self.card}: FINDING {n:03d} {kind}: {note}")

    def triage_shots(self, d, state, inp, nshots=4):
        """Replay a finding's segment from its start state with screenshots (5 shots over the
        segment, or over 600 fields of CROSS-every-30 when there is no input) and STATUS every
        20 fields: d/shots/sNNNNN.png + d/shots/log.txt."""
        f0 = fxlib.peek(state)["field"]
        if not inp:
            inp = "#!stick 1 0\n" + "\n".join(f"{f0 + 10 + 30 * i} {f0 + 13 + 30 * i} CROSS" for i in range(20)) + "\n"
        keys = [int(m.group(1)) for m in re.finditer(r"^(?:#!stick )?(\d+) (\d+)", inp, re.M)]
        end = max([k for k in keys if k > f0] + [f0 + 600]) + 60
        sd = d / "shots"
        sd.mkdir(exist_ok=True)
        (sd / "input.txt").write_text(inp, encoding="utf-8")
        (sd / "saves").mkdir(exist_ok=True)
        fs = sorted({f0 + 5 + (end - f0 - 5) * i // nshots for i in range(nshots + 1)})
        args = ["--fields", end, "--saves", sd / "saves", "--input", sd / "input.txt", "--load-state", state]
        for f in fs:
            args += ["--shot", f"{f}:{sd / f's{f:05d}.png'}"]
        rc, log, hang, wall, cmd = run_game(self.exe, args, dict(self.env, RG_STATUS_EVERY="10"),
                                            self.cfg.timeout + (end - f0) / 20)
        (sd / "log.txt").write_text(" ".join(map(str, cmd)) + "\n" + log, encoding="utf-8")
        return [str(sd / f"s{f:05d}.png") for f in fs]

    def anomalies(self, log, state, inp, cmd):
        for ln in log.splitlines():
            s = ln.rstrip()
            if not s or KNOWN.match(s) or s.startswith(str(self.exe)) or re.match(r"[A-Za-z]:\\", s):
                continue
            key = re.sub(r"0x[0-9A-Fa-f]+|\b[0-9a-f]{8,}\b|\d+", "#", s)[:160]
            if key not in self.anoms:
                self.anoms[key] = 0
                self.finding("log", s[:300], state, inp, log, cmd)
            self.anoms[key] += 1

    # -------------------------------------------------- segments
    def seg(self, state, lines, n, kind, note="", shots=False, extra_shots=()):
        """One segment of n fields from `state` with input `lines` (absolute fields > the
        state's field).  Returns (ok, new_state, probe) and records findings."""
        f0 = fxlib.peek(Path(state))["field"]
        to = f0 + n
        self.k += 1
        sd = self.dir / f"seg{self.k:04d}"
        sd.mkdir(exist_ok=True)
        inp = "\n".join(["# soak.py " + kind, "#!stick 1 0"] + lines) + "\n"
        (sd / "input.txt").write_text(inp, encoding="utf-8")
        st = sd / f"f{to}.rgstate"
        every = to                       # STATUS + probe only at the segment end
        args = ["--fields", to, "--saves", self.saves, "--input", sd / "input.txt",
                "--load-state", Path(state).resolve(), "--save-state", f"{to}:{st}"]
        if shots or self.cfg.shots:
            args += ["--shot", f"{to}:{sd / f's{to:05d}.png'}"]
        for fs in extra_shots:
            args += ["--shot", f"{fs}:{sd / f's{fs:05d}.png'}"]
        env = dict(self.env, RG_STATUS_EVERY=str(every), RG_STATUS_DUMP=dump_spec(self.exe))
        for attempt in range(3):
            rc, log, hang, wall, cmd = run_game(self.exe, args, env, self.cfg.timeout + n / 20)
            if not (hang and "waiting for a free slot" in log):
                break
            fxlib.say(f"  [{now()}] {self.card}: segment timed out while waiting for an rg_slots slot; retry")
        (sd / "log.txt").write_text(" ".join(map(str, cmd)) + "\n" + log, encoding="utf-8")
        crash = fxlib.crash_report(log, self.exe)
        pr = autobattle.parse_probe(log, to)
        mp = parse_map(log, to)
        pr["map"] = mp
        zn = parse_zone(log, to)
        pr["zone"] = zn
        if zn and zn[0] > 0 and (pr["mode"] or "").startswith("6/"):
            if self.stats["zones"] and zn not in self.stats["zones"]:
                self.stats["transitions"] += 1
            self.stats["zones"].add(zn)
        m = re.search(rf"^SHOT field={to} \S+ hash=([0-9a-f]+)", log, re.M)
        pr["shot"] = m.group(1) if m else None
        self.stats["segments"] += 1
        lead = pr.get("leader") or {}
        lp = lead.get("pos")
        self.tsv.write(f"{self.k}\t{f0}\t{to}\t{kind}\t{rc}\t{pr['mode']}\t{mp if not zn else '%d/%d/%d' % zn}\t"
                       f"{'' if not lp else '%.0f,%.0f' % (lp[0], lp[2])}\t{note}\t{wall:.1f}\n")
        self.tsv.flush()
        if pr["mode"]:
            self.stats["modes"].add(pr["mode"].split("/")[0])
        if mp is not None:
            self.stats["maps"].add(mp)
        if hang:
            self.finding("hang", f"no exit after {wall:.0f} s ({kind}, fields {f0}-{to})", state, inp, log, cmd)
            return False, None, pr
        if crash or rc != 0:
            self.finding("crash", (crash[0] if crash else f"exit {rc}") + f" ({kind}, fields {f0}-{to})",
                         state, inp, log, cmd, {"crash": crash, "rc": rc})
            return False, None, pr
        if not st.exists() or pr["field"] != to:
            self.finding("noprogress", f"state/probe at {to} missing (last probe {pr['field']}, {kind})",
                         state, inp, log, cmd)
            return False, None, pr
        self.anomalies(log, state, inp, cmd)
        self.route += lines
        self.fields += n
        if self.cfg.heap_every and self.k % self.cfg.heap_every == 0:
            self.check_heap(st, state, inp, cmd)
        self.prune()
        return True, st, pr

    def check_heap(self, st, state, inp, cmd):
        h = heapwalk(st, self.exe)
        self.stats["heap_walks"] += 1
        if not h.get("ok"):
            self.finding("heap", f"game heap walk failed: {h.get('why')}", state, inp, None, cmd,
                         {"heap": h, "end_state": str(st)})
            keep = self.findings / f"{len(list(self.findings.glob('[0-9]*'))):03d}" / "end.rgstate"
            shutil.copyfile(st, keep)
        else:
            self.stats["heap_used"].append((self.fields, h["used"], h["used_bytes"], h["free_bytes"]))

    def prune(self):
        """Keep the last 3 segment dirs' states (repro), drop saves-less clutter."""
        old = self.k - 3
        if old > 0:
            od = self.dir / f"seg{old:04d}"
            for f in od.glob("*.rgstate"):
                f.unlink(missing_ok=True)

    # -------------------------------------------------- activities
    def walk(self, state, f0, pr):
        """Explore: one WORLD heading per segment (camera-compensated, navprobe.stick_for, full
        deflection = run band), chosen by novelty: the 8 headings are scored by how often the
        cell CELL units ahead was visited on this map (+ jitter); a heading that just failed
        to move the leader is banned for the next pick.  Without a leader / camera reading
        the stick is raw (camera-relative)."""
        import navprobe as nav
        n = self.rng.choice([160, 200, 240])
        lp = (pr.get("leader") or {}).get("pos")
        cam = pr.get("cam")
        mp = pr.get("map")
        CELL = 250.0
        cell = lambda x, z: (mp, int(math.floor(x / CELL)), int(math.floor(z / CELL)))
        if lp:
            c = cell(lp[0], lp[2])
            self.visits[c] = self.visits.get(c, 0) + 1
        blocked = bool(self.last_pos and lp and math.dist(self.last_pos, lp) < 40)
        if blocked:
            self.banned = {self.heading, (self.heading + 1) % 8, (self.heading + 7) % 8}
        else:
            self.banned = set()
        if lp:
            best = None
            for k in range(8):
                if k in self.banned:
                    continue
                h = k * math.pi / 4
                sc = -self.visits.get(cell(lp[0] + 2 * CELL * math.sin(h), lp[2] + 2 * CELL * math.cos(h)), 0)
                sc -= 0.5 * self.visits.get(cell(lp[0] + CELL * math.sin(h), lp[2] + CELL * math.cos(h)), 0)
                sc += self.rng.random() * 1.5 + (0.8 if k == self.heading else 0.0)
                if best is None or sc > best[0]:
                    best = (sc, k)
            self.heading = best[1]
        elif blocked or self.rng.random() < 0.3:
            self.heading = (self.heading + self.rng.choice([2, 3, 4, 5, 6])) % 8
        self.last_pos = lp
        h = self.heading * math.pi / 4
        if lp and cam:
            lx, ly = nav.stick_for(h, cam)
        else:
            lx, ly = int(round(128 + 127 * math.sin(h))), int(round(128 - 127 * math.cos(h)))
        lines = [f"#!stick {f0 + 1} {f0 + n - 10} {lx} {ly}  # explore world heading {self.heading}"
                 f"{'' if (lp and cam) else ' (raw stick)'}"]
        if self.cfg.wide:
            # doors, shops, transporters, signboards, NPCs: CROSS through the walk (the stick
            # keeps pushing; a dialogue / shop / door is handled by the next segments)
            for ff in range(f0 + 40, f0 + n - 10, 60):
                if self.rng.random() < 0.5:
                    lines.append(f"{ff} {ff + 3} CROSS  # examine / enter / talk")
        elif self.rng.random() < 0.25:
            lines.append(f"{f0 + n - 6} {f0 + n - 3} CROSS  # examine / talk")
        self.stats["walk"] += 1
        return self.seg(state, lines, n, "walk", f"heading {self.heading}")

    def menu(self, state, f0):
        """Main menu + a seeded random walk over its sub-screens, then back out."""
        f = f0 + 2
        lines = [f"{f} {f + 3} TRIANGLE  # main menu"]
        f += 120
        presses = ["DOWN", "DOWN", "UP", "CROSS", "CROSS", "CROSS", "LEFT", "RIGHT", "CIRCLE", "R1", "L1"]
        # row first: DOWN x r then CROSS (r spans every main-menu row), then the random walk
        r = self.rng.randrange(9)
        for _ in range(r):
            lines.append(f"{f} {f + 3} DOWN")
            f += 15
        lines.append(f"{f} {f + 3} CROSS  # row {r} (from the remembered cursor)")
        sub = f + 80
        f += 90
        for _ in range(self.rng.randrange(8, 20)):
            b = self.rng.choice(presses)
            lines.append(f"{f} {f + 3} {b}")
            f += self.rng.choice([20, 30, 45])
        mid = f - 5
        for i in range(8):
            lines.append(f"{f} {f + 3} CIRCLE  # back out {i + 1}")
            f += 30
        n = f - f0 + 60
        self.stats["menus"] += 1
        ok, st, pr = self.seg(state, lines, n, "menu", f"row {r}", extra_shots=(sub, mid))
        if not ok:
            return ok, st, pr
        if pr["mode"] and pr["mode"].startswith("6/"):
            self.stats["menu_ok"] += 1
            return ok, st, pr
        if pr["mode"] and pr["mode"].split("/")[0] in ("17", "12", "14", "16", "20"):
            # still in a menu: more CIRCLEs, then TRIANGLE / START, then judge
            g = to = fxlib.peek(st)["field"]
            more = [f"{g + 10 + 30 * i} {g + 13 + 30 * i} CIRCLE  # back out (extra)" for i in range(10)]
            ok2, st2, pr2 = self.seg(st, more, 360, "menu-exit")
            if not ok2:
                return ok2, st2, pr2
            if pr2["mode"] and pr2["mode"].startswith("6/"):
                self.stats["menu_ok"] += 1
                return ok2, st2, pr2
            if pr2["mode"] and pr2["mode"].startswith("16/"):
                # the FACTORY (main menu row "Factory"): CIRCLE never leaves it; the way out is
                # Go Back + "Halt factory operations?" Yes (boot_factory golden), then CIRCLE
                # closes the main menu.  The cursor row is unknown (and may wrap), so attempt
                # a moves UP x10 then DOWN x (6 + a) % 8: one attempt lands on Go Back.
                # closed loop (soak2: the open-loop UP x10 / DOWN n attempts failed when the menu
                # wraps (8 rows) and CIRCLE on the menu hides it): a 30-field look segment with a
                # shot; menu hidden or in a sub-mode -> CIRCLE; else move from the detected row
                # (factory_menu_row) to Go Back (row 6), CROSS, 'Halt factory operations?' Yes,
                # then CIRCLE x2 closes the main menu
                for att in range(10):
                    g = fxlib.peek(st2)["field"]
                    okl, stl, prl = self.seg(st2, [], 30, "factory-look", f"attempt {att}", shots=True)
                    if not okl:
                        return okl, stl, prl
                    st2, pr2 = stl, prl
                    if not (pr2["mode"] or "").startswith("16/"):
                        break
                    g = fxlib.peek(st2)["field"]
                    shot = self.dir / f"seg{self.k:04d}" / f"s{g:05d}.png"
                    row = factory_menu_row(shot)
                    if row is None:
                        fl = [f"{g + 10} {g + 13} CIRCLE  # factory: back to the menu (attempt {att})"]
                        okx, stx, prx = self.seg(st2, fl, 80, "factory-exit", f"attempt {att}: CIRCLE")
                    else:
                        fl, f = [], g + 10
                        step = "DOWN" if (6 - row) % 8 <= 4 else "UP"
                        for _ in range((6 - row) % 8 if step == "DOWN" else (row - 6) % 8):
                            fl.append(f"{f} {f + 3} {step}")
                            f += 25
                        fl += [f"{f + 20} {f + 23} CROSS  # factory: Go Back (row {row} -> 6)",
                               f"{f + 120} {f + 123} CROSS  # 'Halt factory operations?' Yes",
                               f"{f + 1300} {f + 1303} CIRCLE  # close the main menu",
                               f"{f + 1400} {f + 1403} CIRCLE"]
                        okx, stx, prx = self.seg(st2, fl, f + 1500 - g, "factory-exit", f"attempt {att}: row {row}")
                    if not okx:
                        return okx, stx, prx
                    st2, pr2 = stx, prx
                    if pr2["mode"] and not pr2["mode"].startswith("16/"):
                        break
                if pr2["mode"] and pr2["mode"].startswith("6/"):
                    self.stats["menu_ok"] += 1
                    return ok2, st2, pr2
            self.finding("menu-stuck", f"menu pass did not return to the field: mode {pr2['mode']} after "
                         f"18 CIRCLEs (row {r}, start field {f0})", state, "\n".join(lines + more), None, None,
                         {"end_state": str(st2)})
            return ok2, st2, pr2
        return ok, st, pr

    def save(self, state, f0):
        """Transporter -> Save -> slot 1 -> FILE 01 -> overwrite Yes -> dismiss -> back out."""
        h0 = self.card_hash()
        f = f0
        seq = [(10, "CROSS", "transporter menu"), (80, "CROSS", "Save"), (150, "CROSS", "MEMORY CARD slot 1"),
               (150, "CROSS", "FILE 01"), (50, "LEFT", "overwrite? -> Yes"), (30, "CROSS", "save"),
               (340, "CROSS", "dismiss 'File 1 saved.'"), (80, "CIRCLE", "close the slot list"),
               (60, "CIRCLE", "close the transporter menu"), (60, "CIRCLE", "")]
        lines = []
        for d, b, c in seq:
            f += d
            lines.append(f"{f} {f + 3} {b}  # save: {c}")
        self.stats["saves"] += 1
        ok, st, pr = self.seg(state, lines, f - f0 + 80, "save")
        if not ok:
            return ok, st, pr
        h1 = self.card_hash()
        if h1 and h1 != h0:
            self.stats["save_ok"] += 1
            self.reload_check()
        else:
            self.finding("save", f"transporter save wrote nothing (mode {pr['mode']})", state,
                         "\n".join(lines), None, None, {"end_state": str(st)})
        return ok, st, pr

    def card_hash(self):
        """Hash of the memory-card files (card1/** + card1.card; backups/ left out)."""
        h = hashlib.sha256()
        for f in sorted(self.saves.rglob("*")):
            if f.is_file() and "backups" not in f.parts and f.suffix != ".txt":
                h.update(str(f.relative_to(self.saves)).encode())
                h.update(f.read_bytes())
        return h.hexdigest()

    def reload_check(self):
        """A fresh boot from the card the session just wrote must reach field control."""
        d = self.dir / "reload"
        shutil.rmtree(d, ignore_errors=True)
        d.mkdir()
        shutil.copytree(self.saves, d / "saves")
        (d / "input.txt").write_text(bootcheck.lib_script(None), encoding="utf-8")
        rc, log, hang, wall, cmd = run_game(self.exe, ["--fields", 4700, "--saves", d / "saves",
                                                       "--input", d / "input.txt"],
                                            dict(self.env, RG_STATUS_EVERY="10"), self.cfg.timeout + 300)
        (d / "log.txt").write_text(log, encoding="utf-8")
        st = bootcheck.parse_status(log)
        ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v[1] == "6/100"), None)
        if ctl and not hang and rc == 0:
            self.stats["reload_ok"] += 1
        else:
            self.finding("reload", f"boot from the saved card: control {ctl}, exit {rc}, hang {hang}",
                         None, bootcheck.lib_script(None), log, cmd)

    def battle(self, state):
        self.stats["battles"] += 1
        bd = self.dir / f"battle{self.stats['battles']:02d}"
        cfg = autobattle.options().parse_args([])
        cfg.max_fields = self.cfg.battle_fields
        cfg.wide = bool(self.cfg.wide)
        cfg.seed = self.cfg.seed + self.stats["battles"]
        f0 = fxlib.peek(Path(state))["field"]
        cfg.max_fields = min(cfg.max_fields, SCRIPT_MAX - 400 - f0)
        # autobattle builds its env from os.environ: hand it the session's UBSan / guard logs
        saved_env = {k: os.environ.get(k) for k in ("RG_UBSAN_LOG", "RG_SBGUARD_LOG")}
        os.environ.update({k: self.env[k] for k in saved_env})
        try:
            res = autobattle.fight(Path(state), self.exe, bd, cfg)
        finally:
            for k, val in saved_env.items():
                if val is None:
                    os.environ.pop(k, None)
                else:
                    os.environ[k] = val
        v = res["verdict"]
        for key in ("ability_tries", "cutins", "items", "lead_switch", "switch", "gun"):
            self.stats[key] += res.get(key, 0) or 0
        for md, c in (res.get("other_modes") or {}).items():
            self.stats["battle_modes"][md] = self.stats["battle_modes"].get(md, 0) + c
        self.fields += res.get("fields", 0)
        self.route += res.get("route_lines", [])
        self.tsv.write(f"{self.k}\t{f0}\t{res.get('to_field')}\tbattle\t-\t{res.get('mode_end')}\t\t\t"
                       f"{v} killed {res.get('killed')}/{res.get('enemies_start')} heals {res.get('heals')} "
                       f"abil {res.get('ability_tries')} cutins {res.get('cutins')} items {res.get('items')} "
                       f"lead {res.get('lead_switch')} gun {res.get('gun')}\t"
                       f"{res.get('wall_s')}\n")
        self.tsv.flush()
        fxlib.say(f"  [{now()}] {self.card}: battle {self.stats['battles']}: {v} ({res.get('fields')} fields)")
        end = Path(res["state_end"]) if res.get("state_end") else None
        if v in ("crash", "hang") or v.startswith("no state"):
            segs = sorted(bd.glob("seg*"))
            last = segs[-1] if segs else None
            self.finding(v.split()[0] if v != "crash" else "crash",
                         f"battle: {v}: {' '.join(res.get('crash') or [])}", end,
                         (last / "input.txt").read_text() if last and (last / "input.txt").exists() else None,
                         (last / "log.txt").read_text(errors="replace") if last and (last / "log.txt").exists() else None,
                         None, {"battle_dir": str(bd)})
            return False, None, None, v
        if v.startswith("stuck"):
            self.finding("battle-stuck", f"autobattle: {v} (see {bd}/fight.tsv; often the leader-switch "
                         "loop, a tool limit)", end, None, None, None, {"battle_dir": str(bd)})
        if v == "won":
            self.stats["won"] += 1
        if v == "lost":
            self.stats["lost"] += 1
        # clean the battle dir's states but the end one
        for s in bd.glob("seg*/*.rgstate"):
            if end and s.resolve() != end.resolve():
                s.unlink(missing_ok=True)
        return True, end, res, v

    def gameover(self, state):
        """--wide: a lost battle is played on through the game over to the title (game session
        shutdown, GameSessionShutdown_1f5bf0: the path the Insectron Return-to-title hang shared)
        with CROSS every 40 fields; a hang / crash is a finding (seg), not reaching the title
        in 12 segments is a 'gameover' finding."""
        self.stats["gameover"] = self.stats.get("gameover", 0) + 1
        st, modes = state, []
        for i in range(12):
            f0 = fxlib.peek(Path(st))["field"]
            lines = [f"{f0 + 10 + 40 * j} {f0 + 13 + 40 * j} CROSS  # game over: advance" for j in range(7)]
            ok, st2, pr = self.seg(st, lines, 300, "gameover", f"step {i}", shots=True)
            if not ok:
                return
            st = st2
            modes.append(pr["mode"])
            if pr["mode"] and (pr["mode"].split("/")[0] in ("0", "1", "2")
                               or "-1/-1" in modes[:-1] and pr["mode"] != "-1/-1"):
                self.stats["gameover_title"] = self.stats.get("gameover_title", 0) + 1
                fxlib.say(f"  [{now()}] {self.card}: game over -> title ({pr['mode']}) after {i + 1} segments")
                return
        self.finding("gameover", f"lost battle did not reach the title in 12 segments: modes {modes}", state,
                     None, None, None, {"end_state": str(st)})

    def advance(self, state, f0, why):
        """Non-control modes (results, event, talk, loading): CROSS every 30 fields."""
        btn = "CROSS"
        if self.cfg.wide and self.in_mode >= 2 and self.in_mode % 2 == 1:
            btn = "CIRCLE"   # a shop / menu-like mode that CROSS keeps open: back out
        lines = [f"{f0 + 10 + 30 * i} {f0 + 13 + 30 * i} {btn}  # advance ({why})" for i in range(6)]
        self.stats["other"] += 1
        return self.seg(state, lines, 200, "advance", why, shots=True)

    # -------------------------------------------------- boot
    def boot(self):
        """(state, probe) at field control + 40, or None."""
        shutil.rmtree(self.saves, ignore_errors=True)
        src = fxlib.CARDS / fxlib.BOOT_CARD.get(self.card, self.card)
        shutil.copytree(src, self.saves)
        bd = self.dir / "boot"
        bd.mkdir(exist_ok=True)
        if self.card == "factory":
            script = (GOLD / "boot_factory.input.txt").read_text()
            ctl, at = 6400, 6450
        elif self.cfg.fast_boot:
            # one run: the pass-1 script with a state just before each recap CROSS (3790,
            # 3890, ..); the session starts at the first one >= control + 20 (a recap CROSS
            # between control and that state stays in the route: an examine press)
            script = bootcheck.lib_script(None)
            (bd / "boot.input.txt").write_text(script, encoding="utf-8")
            cands = list(range(3790, 4700, 100))
            args = ["--fields", 4700, "--saves", self.saves, "--input", bd / "boot.input.txt"]
            for c in cands:
                args += ["--save-state", f"{c}:{bd / f'b{c}.rgstate'}"]
            rc, log, hang, wall, cmd = run_game(self.exe, args, dict(self.env, RG_STATUS_EVERY="10"),
                                                self.cfg.timeout + 400)
            (bd / "boot.log").write_text(log, encoding="utf-8")
            st = bootcheck.parse_status(log)
            ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v == (3, "6/100")), None)
            crash = fxlib.crash_report(log, self.exe)
            at = next((c for c in cands if ctl is not None and c >= ctl + 20), None)
            if hang or crash or rc != 0 or ctl is None or at is None:
                self.finding("boot", f"no field control by 4,700 (exit {rc}, hang {hang}) "
                             f"{' '.join(crash)}", None, script, log, cmd)
                return None
            st0 = bd / f"control{at}.rgstate"
            (bd / f"b{at}.rgstate").replace(st0)
            for c in cands:
                (bd / f"b{c}.rgstate").unlink(missing_ok=True)
            self.anomalies(log, None, script, cmd)
            self.boot_state = st0
            self.boot_script = [ln for ln in script.splitlines()
                                if ln and not ln.startswith("#") and int(ln.split()[0]) < at]
            self.route = list(self.boot_script) + ["#!stick 1 0"]
            fxlib.say(f"  [{now()}] {self.card}: control at {ctl}, session state {st0.name} (fast boot)")
            return st0
        else:
            script = bootcheck.lib_script(None)
            (bd / "pass1.input.txt").write_text(script, encoding="utf-8")
            rc, log, hang, wall, cmd = run_game(self.exe, ["--fields", 4700, "--saves", self.saves,
                                                           "--input", bd / "pass1.input.txt"],
                                                dict(self.env, RG_STATUS_EVERY="10"), self.cfg.timeout + 400)
            (bd / "pass1.log").write_text(log, encoding="utf-8")
            st = bootcheck.parse_status(log)
            ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v == (3, "6/100")), None)
            crash = fxlib.crash_report(log, self.exe)
            if hang or crash or rc != 0 or ctl is None:
                self.finding("boot", f"no field control by 4,700 (exit {rc}, hang {hang}) "
                             f"{' '.join(crash)}", None, script, log, cmd)
                return None
            script = bootcheck.lib_script(ctl).split("#!stick 1 0")[0]
            script = "\n".join(ln for ln in script.splitlines()
                               if not re.match(r"\s*(\d+)", ln) or int(re.match(r"\s*(\d+)", ln).group(1)) < ctl) + "\n"
            at = ctl + 40
        (bd / "boot.input.txt").write_text(script, encoding="utf-8")
        st0 = bd / f"control{at}.rgstate"
        shutil.rmtree(self.saves, ignore_errors=True)
        shutil.copytree(src, self.saves)
        rc, log, hang, wall, cmd = run_game(self.exe, ["--fields", at + 2, "--saves", self.saves, "--input",
                                                       bd / "boot.input.txt", "--save-state", f"{at}:{st0}"],
                                            dict(self.env, RG_STATUS_EVERY="10", RG_STATUS_DUMP=dump_spec(self.exe)),
                                            self.cfg.timeout + 400)
        (bd / "boot.log").write_text(log, encoding="utf-8")
        crash = fxlib.crash_report(log, self.exe)
        if hang or crash or rc != 0 or not st0.exists():
            self.finding("boot", f"boot run to {at}: exit {rc}, hang {hang} {' '.join(crash)}", None,
                         script, log, cmd)
            return None
        self.anomalies(log, None, script, cmd)
        self.boot_state = st0
        self.boot_script = [ln for ln in script.splitlines() if ln and not ln.startswith("#")]
        self.route = list(self.boot_script) + ["#!stick 1 0"]
        fxlib.say(f"  [{now()}] {self.card}: control at {ctl}, session state {st0.name}")
        return st0

    def restart(self, why):
        self.stats["restarts"] += 1
        fxlib.say(f"  [{now()}] {self.card}: restart from the boot state ({why})")
        self.route = list(self.boot_script) + ["#!stick 1 0", f"# restart: {why}"]
        self.last_pos = None
        return self.boot_state

    # -------------------------------------------------- main loop
    def run(self):
        t0 = time.time()
        self.last_pos = None
        if self.card == "insectron":
            return self.run_insectron(t0)
        state = self.boot()
        if state is None:
            return self.summary(t0, "boot failed")
        pr = {"mode": "6/100", "leader": None}
        act = 0
        saved = False
        fails = 0
        budget = self.cfg.map_fields if (self.card.startswith("m_") and self.cfg.map_fields) else self.cfg.fields
        while self.fields < budget:
            f0 = fxlib.peek(Path(state))["field"]
            if f0 > SCRIPT_MAX - 1200:
                state = self.restart("input script limit")
                continue
            mode = pr.get("mode") or "?"
            # nothing changed: mode, map, leader position and (advance segments) the frame
            sig = (mode, pr.get("map"), str((pr.get("leader") or {}).get("pos")), pr.get("shot"))
            self.same = self.same + 1 if sig == self.last_sig else 0
            self.last_sig = sig
            self.in_mode = self.in_mode + 1 if mode == self.last_mode and not mode.startswith(("6/", "7/")) else 0
            self.last_mode = mode
            if self.in_mode >= self.cfg.long_event:
                # one non-field mode for very long while the frame keeps changing (a long story
                # event the CROSS presses do advance): not a soft lock; end the session there
                fxlib.say(f"  [{now()}] {self.card}: {self.in_mode} advance segments in mode {mode} "
                          f"(frames changing): long event, session ends")
                self.long_event = f"long event {mode} map {pr.get('map')}"
                break
            if self.same >= self.cfg.stuck:
                key = (mode, pr.get("map"))
                if key in self.stuck_seen:
                    fxlib.say(f"  [{now()}] {self.card}: stuck again in {key}: session ends")
                    break
                self.stuck_seen.add(key)
                self.finding("stuck", f"nothing changed for {self.same} segments (mode {mode}, map "
                             f"{pr.get('map')})", state, None, None, None)
                state = self.restart("stuck")
                self.same = 0
                pr = {"mode": "6/100"}
                continue
            ph = int(mode.split("/")[1]) if mode.startswith("7/") and mode.split("/")[1].isdigit() else -1
            if 700 <= ph < 800:
                if self.cfg.wide and self.stats.get("gameover", 0) < 1:
                    self.gameover(state)
                state = self.restart(f"battle lost ({mode})")
                pr = {"mode": "6/100"}
                continue
            if 0 <= ph < 500 or ph == 2000:
                ok, st, res, v = self.battle(state)
                if not ok:
                    state = self.restart(f"battle {v}")
                    fails += 1
                    pr = {"mode": "6/100"}
                    if fails > 3:
                        break
                    continue
                if v == "lost" or v.startswith("timeout"):
                    if v == "lost" and st and self.cfg.wide and self.stats.get("gameover", 0) < 1:
                        self.gameover(st)
                    state = self.restart(f"battle {v}")
                    pr = {"mode": "6/100"}
                    continue
                state = st
                ok, st2, pr = self.advance(state, fxlib.peek(state)["field"], "battle results")
                if not ok:
                    state = self.restart("crash after battle")
                    fails += 1
                    pr = {"mode": "6/100"}
                    continue
                state = st2
                continue
            m0 = mode.split("/")[0]
            if m0 == "6":
                act += 1
                if self.card in SAVE_CARDS and not saved and act == 1:
                    saved = True
                    ok, st, pr = self.save(state, f0)
                elif act % self.cfg.menu_every == 0:
                    ok, st, pr = self.menu(state, f0)
                else:
                    ok, st, pr = self.walk(state, f0, pr)
            elif m0 in ("2", "0", "1") or mode.startswith("?"):
                # title / boot modes = game over or quit to title: restart
                state = self.restart(f"mode {mode}")
                pr = {"mode": "6/100"}
                continue
            else:
                ok, st, pr = self.advance(state, f0, f"mode {mode}")
            if not ok:
                fails += 1
                if fails > 3:
                    break
                state = self.restart("after a failed segment")
                pr = {"mode": "6/100"}
                continue
            state = st
        return self.summary(t0, getattr(self, "long_event", ""))

    def run_insectron(self, t0):
        """boot_insectron golden + CROSS every 300 fields, in segments of 1500 fields."""
        shutil.rmtree(self.saves, ignore_errors=True)
        shutil.copytree(fxlib.CARDS / "insectron", self.saves)
        bd = self.dir / "boot"
        bd.mkdir(exist_ok=True)
        script = (GOLD / "boot_insectron.input.txt").read_text()
        at = 11500
        st0 = bd / f"insect{at}.rgstate"
        (bd / "boot.input.txt").write_text(script, encoding="utf-8")
        rc, log, hang, wall, cmd = run_game(self.exe, ["--fields", at + 2, "--saves", self.saves, "--input",
                                                       bd / "boot.input.txt", "--save-state", f"{at}:{st0}"],
                                            dict(self.env, RG_STATUS_EVERY="50"), self.cfg.timeout + 600)
        (bd / "boot.log").write_text(log, encoding="utf-8")
        if hang or rc != 0 or not st0.exists():
            self.finding("boot", f"insectron boot to {at}: exit {rc}, hang {hang} "
                         f"{' '.join(fxlib.crash_report(log, self.exe))}", None, script, log, cmd)
            return self.summary(t0, "boot failed")
        self.anomalies(log, None, script, cmd)
        self.route = [ln for ln in script.splitlines() if ln and not ln.startswith("#")]
        state = st0
        while self.fields < self.cfg.fields:
            f0 = fxlib.peek(state)["field"]
            if f0 > SCRIPT_MAX - 2000:
                break
            lines = [f"{f0 + 150 + 300 * i} {f0 + 153 + 300 * i} CROSS  # insectron: advance" for i in range(5)]
            ok, st, pr = self.seg(state, lines, 1500, "insect")
            if not ok:
                break
            state = st
        return self.summary(t0, "")

    def summary(self, t0, why):
        self.tsv.close()
        s = self.stats
        hu = s["heap_used"]
        leak = ""
        if len(hu) >= 3:
            leak = f"{hu[0][2]}->{hu[-1][2]} B in use ({hu[0][1]}->{hu[-1][1]} chunks)"
        ub = _count_rows(self.dir / "ubsan.tsv")
        sg = _count_rows(self.dir / "sbguard.tsv", guard=True)
        row = {"card": self.card, "fields": self.fields, "segments": s["segments"], "battles": s["battles"],
               "won": s["won"], "lost": s["lost"], "menus": f"{s['menu_ok']}/{s['menus']}",
               "saves": f"{s['save_ok']}/{s['saves']} reload {s['reload_ok']}", "restarts": s["restarts"],
               "maps": len(s["maps"]), "modes": " ".join(sorted(s["modes"], key=lambda x: int(x) if x.isdigit() else 99)),
               "heap": f"{s['heap_walks']} walks {leak}", "ubsan_rows": ub, "sbguard_rows": sg,
               "findings": s["findings"], "wall_s": round(time.time() - t0), "note": why,
               "zones": " ".join(f"{p}/{a}/{z}" for p, a, z in sorted(s["zones"])),
               "transitions": s["transitions"], "abilities": s["ability_tries"], "cutins": s["cutins"],
               "items": s["items"], "lead_switch": s["lead_switch"], "gun": s["gun"],
               "gameover": f"{s.get('gameover_title', 0)}/{s.get('gameover', 0)}",
               "battle_modes": " ".join(f"{k}:{v}" for k, v in sorted(s["battle_modes"].items()))}
        (self.dir / "summary.json").write_text(json.dumps(row, indent=1), encoding="utf-8")
        return row


def _count_rows(p: Path, guard: bool = False) -> int:
    """UBSan census rows (NEW lines) or stack-guard rows (site<TAB>side<TAB>..)."""
    if not p.exists():
        return 0
    lines = p.read_text(errors="replace").splitlines()
    if guard:
        return sum(1 for ln in lines if ln.count("\t") >= 4)
    return sum(1 for ln in lines if ln.startswith("NEW"))


# ---------------------------------------------------------------- commands
def cmd_run(a):
    exe = bootcheck.snapshot_exe(fxlib.exe_path(a.exe))
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    findings = out / "findings"
    findings.mkdir(exist_ok=True)
    names = list(a.cards)
    if a.wide and not names:
        names = cardlib.wide_names() + ["save2", "factory", "insectron"]
    if a.maps:
        names += cardlib.map_names()
    names = names or (list(cardlib.LIBRARY) + ["save2", "factory", "insectron"])
    missing = [n for n in names if n.startswith(("w_", "m_")) and not (fxlib.CARDS / n).is_dir()]
    if missing:
        subprocess.run([sys.executable, str(HERE / "saveedit.py"), "make"] + missing, check=True,
                       stdout=subprocess.DEVNULL)
    if a.skip:
        names = [n for n in names if n not in a.skip.split(",")]
    (out / "run.json").write_text(json.dumps({"exe": str(exe), "exe_id": fxlib.exe_id(exe), "cards": names,
                                              "fields": a.fields, "seed": a.seed,
                                              "started": time.strftime("%Y-%m-%d %H:%M")}, indent=1))
    summ = out / "summary.tsv"
    cols = ["card", "fields", "segments", "battles", "won", "lost", "menus", "saves", "restarts", "maps",
            "modes", "heap", "ubsan_rows", "sbguard_rows", "findings", "wall_s", "note"]
    if a.wide or a.maps:
        cols += ["zones", "transitions", "abilities", "cutins", "items", "lead_switch", "gun", "gameover",
                 "battle_modes"]
    if not summ.exists():
        summ.write_text("\t".join(cols) + "\n", encoding="utf-8")
    for n in names:
        if a.resume and (out / n / "summary.json").exists():
            continue
        if not (fxlib.CARDS / fxlib.BOOT_CARD.get(n, n)).is_dir():
            fxlib.say(f"soak: {n}: no card (saveedit.py make)")
            continue
        fxlib.say(f"[{now()}] soak {n}: {a.fields} fields, exe {fxlib.exe_id(exe)}")
        s = Session(n, exe, out, a, findings)
        try:
            row = s.run()
        except Exception as e:   # a tool error must not end the whole soak
            import traceback
            traceback.print_exc()
            row = s.summary(time.time(), f"tool error: {e!r}")
        with open(summ, "a", encoding="utf-8") as f:
            f.write("\t".join(str(row[c]) for c in cols) + "\n")
        fxlib.say(f"[{now()}] soak {n}: " + " ".join(f"{c}={row[c]}" for c in cols[1:]))
    return 0


def _norm(f):
    return re.sub(r"^.*?port[\\/]", "", f).replace("\\", "/")


def ubsan_sites(d: Path) -> dict:
    """{(kind, sub, file, line, col): (first detail, {cards})} over DIR/*/ubsan.tsv."""
    ub = {}
    for p in d.glob("*/ubsan.tsv"):
        for ln in p.read_text(errors="replace").splitlines():
            w = ln.split("\t")
            if w[0] == "NEW" and len(w) >= 7:
                k = (w[1], w[2], _norm(w[3]), w[4], w[5])
                ub.setdefault(k, (w[6], set()))[1].add(p.parent.name)
    return ub


def route_census() -> set:
    """(kind, sub, file, line, col) of census/ub_ubsan_route.tsv (the triaged route sites)."""
    p = fxlib.PORT / "census" / "ub_ubsan_route.tsv"
    out = set()
    if p.exists():
        for ln in p.read_text(errors="replace").splitlines()[1:]:
            w = ln.split("\t")
            if len(w) >= 5:
                out.add(tuple(w[:5]))
    return out


def cmd_report(a):
    """Markdown tables of one or more soak dirs."""
    for d in map(Path, a.dirs):
        print(f"\n### {d}\n")
        run = json.loads((d / "run.json").read_text()) if (d / "run.json").exists() else {}
        print(f"exe {run.get('exe_id')} ({run.get('exe')}), {run.get('fields')} fields/card, "
              f"seed {run.get('seed')}\n")
        sp = d / "summary.tsv"
        rows = [ln.split("\t") for ln in sp.read_text().splitlines()] if sp.exists() else []
        if rows:
            print("| " + " | ".join(rows[0]) + " |")
            print("|" + "---|" * len(rows[0]))
            for r in rows[1:]:
                print("| " + " | ".join(r) + " |")
        fr = d / "findings.tsv"
        if fr.exists():
            print("\n| # | card | kind | note | seg |\n|---|---|---|---|---|")
            for ln in fr.read_text().splitlines():
                w = ln.split("\t")
                print(f"| {w[0]} | {w[1]} | {w[2]} | {w[3][:200]} | {w[4]} |")
        ub = ubsan_sites(d)
        if ub:
            known = route_census()
            for bd in (a.baseline or []):   # sites an earlier soak already reported (triaged there)
                known |= set(ubsan_sites(Path(bd)))
            nnew = sum(1 for k in ub if k not in known)
            print(f"\nUBSan sites: {len(ub)} ({len(ub) - nnew} also in census/ub_ubsan_route.tsv, "
                  f"{nnew} new)\n")
            print("| kind | sub | file:line:col | detail | cards | route |\n|---|---|---|---|---|---|")
            for k, (det, cards) in sorted(ub.items()):
                print(f"| {k[0]} | {k[1]} | {k[2]}:{k[3]}:{k[4]} | {det[:80]} | "
                      f"{', '.join(sorted(cards))[:60]} | {'yes' if k in known else '**new**'} |")
        sg = {}
        for p in d.glob("*/sbguard.tsv"):
            for ln in p.read_text(errors="replace").splitlines():
                if ln.strip() and not ln.startswith(("BEGIN", "END")):
                    sg.setdefault(ln, set()).add(p.parent.name)
        if sg:
            print(f"\nStack-guard rows: {len(sg)}\n")
            for k, v in sorted(sg.items()):
                print(f"- {k} ({', '.join(sorted(v))})")
    return 0


def gameover_run(state: Path, exe: Path, out: Path, segs: int = 12) -> str:
    """From a lost battle's end state: CROSS every 40 fields, 300-field segments, until a
    title / boot game mode (0/1/2: the game-session shutdown after the game over) or a crash /
    hang; returns 'title 2/..' / 'crash ..' / 'hang' / 'no title (modes)'."""
    modes = []
    for i in range(segs):
        f0 = fxlib.peek(state)["field"]
        txt = "#!stick 1 0\n" + "\n".join(f"{f0 + 10 + 40 * j} {f0 + 13 + 40 * j} CROSS" for j in range(7)) + "\n"
        rc, log, st = autobattle.run_seg(exe, state, txt, f0 + 300, out / f"seg{i:02d}", f0 + 300,
                                         shots=[f0 + 300], every=300)
        if "TIMEOUT" in log:
            return "hang"
        crash = fxlib.crash_report(log, exe)
        if crash or rc != 0:
            return f"crash {' '.join(crash)[:200]} (exit {rc})"
        m = re.findall(r"STATUS field=\d+ .*?gamemode=(\S+)", log)
        modes.append(m[-1] if m else "?")
        # the game over (11/0 'GAME OVER') ends the session: a loading gap (-1/-1) and then the
        # boot logos / story intro / opening movie (11/0 again, ovl 3; soak2 shots) = the
        # session shutdown went through (no hang in StreamChanClose / the effect teardown)
        if m and (m[-1].split("/")[0] in ("0", "1", "2") or "-1/-1" in modes[:-1] and m[-1] != "-1/-1"):
            return f"session restarted ({' '.join(modes)}) after {i + 1} segments"
        if st is None:
            return f"no state (exit {rc})"
        state = st
    return f"no title ({' '.join(modes)})"


def cmd_fights(a):
    """Battle pass (soak2): for each card, autobattle prep (the bootcheck box walk's first
    battle, cached per exe) and a --wide fight (abilities, items, leader switch, gun) to its
    end; DIR/fights.tsv + DIR/<card>/ (fight dirs; ubsan.tsv with a -DRG_UBSAN=ON exe)."""
    exe = bootcheck.snapshot_exe(fxlib.exe_path(a.exe))
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    names = a.cards or cardlib.wide_names()
    tsv = out / "fights.tsv"
    if not tsv.exists():
        tsv.write_text("card\tverdict\tfields\tkilled\tabilities\tcutins\titems\tlead_switch\tswitch\tgun\t"
                       "heals\tother_modes\tcrash\n", encoding="utf-8")
    done = {ln.split("\t")[0] for ln in tsv.read_text().splitlines()[1:]}
    for n in names:
        if n in done:
            continue
        os.environ["RG_UBSAN_LOG"] = str(out / n / "ubsan.tsv")
        (out / n).mkdir(exist_ok=True)
        fxlib.say(f"[{now()}] fights {n}")
        try:
            r = autobattle.fight_card(n, exe, out / n / "fight", wide=True, max_fields=a.battle_fields,
                                      seed=a.seed)
        except Exception as e:  # a tool error must not end the pass
            r = {"verdict": f"tool error {e!r}"}
        go = ""
        if r.get("verdict") == "lost" and r.get("state_end"):
            go = gameover_run(Path(r["state_end"]), exe, out / n / "gameover")
        row = [n, r.get("verdict") + (f" -> {go}" if go else ""), r.get("fields"),
               f"{r.get('killed')}/{r.get('enemies_start')}",
               r.get("ability_tries"), r.get("cutins"), r.get("items"), r.get("lead_switch"), r.get("switch"),
               r.get("gun"), r.get("heals"), " ".join(f"{k}:{v}" for k, v in (r.get("other_modes") or {}).items()),
               " ".join(r.get("crash") or [])]
        with open(tsv, "a", encoding="utf-8") as f:
            f.write("\t".join("" if x is None else str(x) for x in row) + "\n")
        fxlib.say(f"[{now()}] fights {n}: " + " ".join(map(str, row[1:])))
    return 0


# Overlay / story drivers (soak.py drivers): name -> (tool, args); each writes D/<name>/result.json
# with a "verdict" (cov3 lane, 2026-10-25: the story Insectron final and its rank reward, factory
# production of a Healing vial product)
DRIVERS = {
    "insectstory": ("insectstory.py", ["run", "--card", "insect_final_s"], "won"),
    "insectrun": ("insectrun.py", ["run", "--title"], "done"),
    "factory": ("factory.py", ["run", "--card", "factory_prod", "--plan", "healing_ath", "--cords", "--produce", "1000",
                               "--save"], "produced"),
}


def cmd_drivers(a):
    """Driver pass: the closed-loop overlay / story drivers (DRIVERS) on one exe, one after the
    other; D/drivers.tsv (name, verdict, pass, wall seconds, result.json) + D/<name>/."""
    exe = bootcheck.snapshot_exe(fxlib.exe_path(a.exe))
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    tsv = out / "drivers.tsv"
    if not tsv.exists():
        tsv.write_text("driver\tverdict\tpass\twall_s\tresult\n", encoding="utf-8")
    bad = 0
    for name in (a.names or list(DRIVERS)):
        tool, args, want = DRIVERS[name]
        d = out / name
        t0 = time.time()
        fxlib.say(f"[{now()}] driver {name}")
        p = subprocess.run([sys.executable, str(HERE / tool)] + args + ["--exe", str(exe), "--out", str(d)],
                           capture_output=True, text=True, errors="replace")
        (out / f"{name}.log").write_text(p.stdout + p.stderr, encoding="utf-8")
        try:
            verdict = json.loads((d / "result.json").read_text(encoding="utf-8")).get("verdict")
        except (OSError, ValueError):
            verdict = f"no result.json (exit {p.returncode})"
        ok = verdict == want
        bad += not ok
        with open(tsv, "a", encoding="utf-8") as f:
            f.write(f"{name}\t{verdict}\t{'PASS' if ok else 'FAIL'}\t{round(time.time() - t0)}\t{d / 'result.json'}\n")
        fxlib.say(f"[{now()}] driver {name}: {verdict} ({'PASS' if ok else 'FAIL'})")
    return 1 if bad else 0


def planet_zones() -> dict:
    """planet_zone_param_2_EN #401 / #403: {planet: {zone id: name}}."""
    import rgdata
    out, pl = {}, None
    for cid, ar in rgdata.table("planet_zone_param_2_EN.cfg.bin"):
        if cid == 401:
            pl = ar[0]
            out.setdefault(pl, {})
        elif cid == 403 and pl is not None:
            out[pl][ar[0]] = ar[3] if len(ar) > 3 else ar[1]
    return out


def cmd_coverage(a):
    """--wide / --maps soak dirs: zones reached per planet (party +0xC at field-mode segment
    ends) against planet_zone_param, and the battle tactic totals."""
    zones, tot = {}, {}
    keys = ("fields", "battles", "won", "lost", "abilities", "cutins", "items", "lead_switch", "gun",
            "findings", "transitions")
    gameover = [0, 0]
    cards = 0
    for d in map(Path, a.dirs):
        for sj in d.glob("*/summary.json"):
            r = json.loads(sj.read_text())
            cards += 1
            for k in keys:
                v = r.get(k, 0)
                tot[k] = tot.get(k, 0) + (v if isinstance(v, int) else 0)
            g = str(r.get("gameover", "0/0")).split("/")
            gameover[0] += int(g[0]); gameover[1] += int(g[1])
            for z in (r.get("zones") or "").split():
                pl, area, zone = map(int, z.split("/"))
                zones.setdefault(pl, {}).setdefault(zone, set()).add(r["card"])
    pz = planet_zones()
    print(f"cards {cards}; " + ", ".join(f"{k} {v}" for k, v in tot.items()) +
          f", game over -> title {gameover[0]}/{gameover[1]}")
    print("\n| planet | zones reached | of | names reached | not reached |\n|---|---|---|---|---|")
    allr = allt = 0
    for pl in sorted(set(pz) | set(zones)):
        names = pz.get(pl, {})
        got = zones.get(pl, {})
        known = [z for z in got if z in names]
        allr += len(known)
        allt += len(names)
        print(f"| {pl} | {len(known)} (+{len(got) - len(known)} other ids) | {len(names)} | "
              f"{', '.join(str(names.get(z, z)) for z in sorted(got))[:200]} | "
              f"{', '.join(str(names[z]) for z in sorted(names) if z not in got)[:200]} |")
    print(f"\nzones reached {allr} of {allt} listed")
    return 0


def cmd_heap(a):
    exe = fxlib.exe_path(a.exe)
    for s in a.states:
        print(s, json.dumps(heapwalk(Path(s), exe)))
    return 0


def cmd_repro(a):
    d = Path(a.finding)
    info = json.loads((d / "finding.json").read_text())
    exe = Path(info["exe"])
    if not (d / "start.rgstate").exists():
        print("soak repro: no start state (boot finding): rerun the card's boot:", info.get("cmd"))
        return 1
    f0 = info["state_field"]
    n = a.fields or 600
    out = d / "repro"
    out.mkdir(exist_ok=True)
    (out / "saves").mkdir(exist_ok=True)
    args = ["--fields", f0 + n, "--saves", out / "saves", "--input", d / "input.txt", "--load-state",
            d / "start.rgstate"]
    rc, log, hang, wall, cmd = run_game(exe, args, {"RG_SS": "1", "RG_STATUS_EVERY": "50"}, 600)
    (out / "log.txt").write_text(log, encoding="utf-8")
    print(" ".join(map(str, cmd)))
    print(f"exit {rc} hang {hang} {wall:.0f} s")
    for c in fxlib.crash_report(log, exe):
        print(" ", c)
    return 0


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run")
    r.add_argument("cards", nargs="*")
    r.add_argument("--exe")
    r.add_argument("--out", required=True)
    r.add_argument("--fields", type=int, default=12000, help="soak fields per card (after boot)")
    r.add_argument("--seed", type=int, default=1)
    r.add_argument("--shots", action="store_true", help="a screenshot at every segment end")
    r.add_argument("--menu-every", type=int, default=6, help="every Nth field activity is a menu pass")
    r.add_argument("--battle-fields", type=int, default=4000, help="autobattle --max-fields per fight")
    r.add_argument("--stuck", type=int, default=8, help="segments without any change = finding")
    r.add_argument("--heap-every", type=int, default=4, help="walk the game heap every N segments (0 = off)")
    r.add_argument("--timeout", type=float, default=240.0, help="seconds per segment (+ fields/20)")
    r.add_argument("--skip", help="comma list of cards to leave out")
    r.add_argument("--long-event", type=int, default=40,
                   help="advance segments (200 fields) in one non-field mode before it counts as stuck")
    r.add_argument("--resume", action="store_true", help="skip cards that already have DIR/CARD/summary.json")
    r.add_argument("--wide", action="store_true",
                   help="widened soak: the w_ cards (abilities + Burning Strike learned), autobattle --wide "
                        "(abilities, items, leader switch, gun), CROSS through walks (doors / shops / signs), "
                        "CIRCLE in persistent non-field modes, zone coverage columns")
    r.add_argument("--maps", action="store_true",
                   help="+ the map-sweep cards m_<jump> (cardlib.map_points: per-planet spread of jump points)")
    r.add_argument("--map-fields", type=int, default=0, help="soak fields per m_ card (default --fields)")
    r.add_argument("--fast-boot", action="store_true",
                   help="one boot run per card (states every 100 fields, the first one after control + 20)")
    p = sub.add_parser("report")
    p.add_argument("dirs", nargs="+")
    p.add_argument("--baseline", action="append", help="earlier soak dir: its UBSan sites count as known")
    fg = sub.add_parser("fights")
    fg.add_argument("cards", nargs="*")
    fg.add_argument("--exe")
    fg.add_argument("--out", required=True)
    fg.add_argument("--battle-fields", type=int, default=5000)
    fg.add_argument("--seed", type=int, default=1)
    dv = sub.add_parser("drivers", help="the closed-loop drivers (DRIVERS: insectstory, insectrun, ..)")
    dv.add_argument("names", nargs="*")
    dv.add_argument("--exe")
    dv.add_argument("--out", required=True)
    c = sub.add_parser("coverage")
    c.add_argument("dirs", nargs="+")
    h = sub.add_parser("heap")
    h.add_argument("states", nargs="+")
    h.add_argument("--exe", help="the exe that wrote the states (its .map)")
    q = sub.add_parser("repro")
    q.add_argument("finding")
    q.add_argument("--fields", type=int)
    a = ap.parse_args(argv)
    return {"run": cmd_run, "report": cmd_report, "heap": cmd_heap, "repro": cmd_repro,
            "coverage": cmd_coverage, "fights": cmd_fights, "drivers": cmd_drivers}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())

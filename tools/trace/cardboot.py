#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Boot a manufactured game-save card on retail (PCSX2) through CONTINUE and take
screenshots at the same milestones as the port (docs/TEST-FIXTURES.md "Retail comparison").

    python tools/trace/cardboot.py CARD [CARD ...] [--plan lib|factory|battle] [--out D]
                                  [--speed 1.0] [--timeout 600] [--keep-card]
    python tools/trace/cardboot.py --list-plans

CARD = a card folder of out/fixtures/cards/ (a port saves dir: card1/BASCUS-...) or a .ps2
image.  A folder is exported first with tools/saves/ps2card.py (`export --format`, ECC on; retail
reads its ECC as is since the 2026-10-18 column-parity fix)
into .tools/pcsx2/memcards/cardboot_<name>.ps2 (removed after the run unless --keep-card).

Retail runs slower than the port in places (title data sort, loads), so the port's fixed-time
boot scripts do not line up.  The driver here is event driven: PINE polls the game VBlank
(0x004810C4), the overlay index (D_0047E254) and the game mode / phase (D_004B51A0 /
D_004B51E0); presses are written into input.py's guest input table a few VBlanks ahead of the
current VBlank (the hook is installed frozen at boot with an empty table, as trace.py does), and
the milestones are taken relative to events:

  lib      CROSS every 60 VBlanks until field control (mode 6/100 after the load; CONTINUE ->
           slot 1 -> FILE 01 -> Yes -> loaded -> recap), then as bootcheck.py's card-library
           pass 2: shot `control` at C+40, TRIANGLE C+60, shot `menu` C+160, CIRCLE C+260, shot
           `field` C+340.
  factory  as lib to control, then boot_factory.input.txt's menu walk anchored on events: shot
           `menu_before` (main menu open), Factory row, FACTORY overlay (ovl 4), factory menu
           (16/100), Go Back, "Halt factory operations?" Yes, back in the NORMAL main menu (17)
           -> shot `menu_after` (rows 4 / 5: "? ? ?" or "Battle Recorder" / "Frog Log").

Shots: D/<card>_<milestone>.png (PrintWindow of the PCSX2 window, software renderer 13), a
log D/<card>.log (VBlank, mode, events, presses), D/<card>.json (milestone VBlanks).  Compare
with the port's shots side by side: tools/fixtures/montage.py --pairs.

One PCSX2 instance (refuses to start when a portable instance's PID file is live); PCSX2 is
stopped by PID (emu.Emu).  The user's own PCSX2 config and cards are never touched.
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import emu  # noqa: E402
import input as inp  # noqa: E402

PORT = HERE.parents[1]
CARDS = PORT / "out" / "fixtures" / "cards"
VBL = inp.VBL
OVL = 0x0047E254
MODE = 0x004B51A0
PHASE = 0x004B51E0
MENUOPEN = 0x0048416C   # title menu open (s16)
MENUSEL = 0x004803AC    # title menu row (s16)


def _s32(v):
    return v - (1 << 32) if v & 0x80000000 else v


class Driver:
    """Event-driven presses and shots over PINE (one PCSX2 run)."""

    def __init__(self, e: emu.Emu, pine, log, shots_dir: Path, name: str):
        self.e, self.pine, self.logf, self.dir, self.name = e, pine, log, shots_dir, name
        self.ms = {}
        self.last = None

    def state(self):
        p = self.pine
        v = p.read32(VBL)
        return v, _s32(p.read32(OVL)), f"{_s32(p.read32(MODE))}/{_s32(p.read32(PHASE))}"

    def log(self, msg):
        v, o, m = self.state()
        line = f"vbl={v} ovl={o} mode={m}  {msg}"
        self.logf.write(line + "\n")
        self.logf.flush()
        print(f"  [{self.name}] {line}", flush=True)

    def press(self, btn, at=None, n=4):
        """Write BUTTON into table[at .. at+n-1] (at default: now + 6)."""
        v = self.pine.read32(VBL)
        at = max(at or 0, v + 4) if at else v + 6
        bits = inp.BUTTONS[btn]
        for k in range(at, at + n):
            if k < inp.MAX_ENTRIES:
                self.pine.write16(inp.TABLE + 4 + 2 * k, bits)
        self.logf.write(f"press {btn} at vbl {at}..{at + n - 1} (now {v})\n")
        return at

    def wait_vbl(self, target, timeout=120):
        t0 = time.time()
        while True:
            v = self.pine.read32(VBL)
            if v >= target:
                return v
            if time.time() - t0 > timeout:
                raise TimeoutError(f"vbl {target} not reached (at {v})")
            time.sleep(0.005)

    def wait(self, cond, timeout=300, what="", every=None):
        """Poll until cond(vbl, ovl, mode) holds; optional every = (btn, period) mashing."""
        t0 = time.time()
        nextp = 0
        while True:
            st = self.state()
            if cond(*st):
                self.log(f"event: {what}")
                return st
            if every and st[0] >= nextp:
                self.press(every[0])
                nextp = st[0] + every[1]
            if time.time() - t0 > timeout:
                self.log(f"TIMEOUT waiting for {what}")
                raise TimeoutError(what)
            time.sleep(0.01)

    def shot(self, ms, at=None):
        if at is not None:
            self.wait_vbl(at)
        v, o, m = self.state()
        p = self.dir / f"{self.name}_{ms}.png"
        import live
        ok = live.window_shot(self.e.proc.pid, str(p))
        cams = []
        for k in range(6):   # Camera0..5 (navprobe.CAMS): +0x50 look-at, +0x60 eye
            b = self.pine.read_block(0x4B5660 + k * 0x2F0 + 0x50, 0x20)
            f = struct.unpack("<8f", b)
            cams.append([round(x, 1) for x in f[0:3] + f[4:7]])
        self.ms[ms] = {"vbl": v, "ovl": o, "mode": m, "shot": str(p) if ok else None, "cams": cams}
        self.log(f"shot {ms} -> {p.name}{'' if ok else ' (FAILED)'}")


def boot_to_control(d: Driver):
    """CONTINUE -> slot 1 -> FILE 01 -> Yes -> loaded -> recap, CROSS every 60 VBlanks until
    field control (game mode 6/100 with the NORMAL overlay)."""
    d.wait(lambda v, o, m: v > 300, what="game running", timeout=180)
    # the title menu (TITLE overlay, menu open flag D_0048416C): shot of the menu as the card
    # scan left it (CONTINUE is the default row when the card holds a valid save)
    d.wait(lambda v, o, m: o == 2 and d.pine.read32(MENUOPEN) & 0xFFFF and v > 600, what="title menu",
           timeout=300)
    d.shot("title", d.pine.read32(VBL) + 90)
    st = d.wait(lambda v, o, m: o == 3 and m == "6/100", what="field control", timeout=600,
                every=("CROSS", 60))
    d.ms["control_vbl"] = st[0]
    return st[0]


def plan_lib(d: Driver):
    c = boot_to_control(d)
    d.shot("control", c + 40)
    d.press("TRIANGLE", c + 60)
    d.shot("menu", c + 160)
    d.press("CIRCLE", c + 260)
    d.shot("field", c + 340)


def plan_factory(d: Driver):
    """boot_factory.input.txt, anchored on events (port offsets in comments)."""
    c = boot_to_control(d)
    d.press("TRIANGLE", c + 40)
    st = d.wait(lambda v, o, m: m.startswith("17/"), what="main menu", timeout=60)
    d.shot("menu_before", st[0] + 60)
    v = st[0] + 160                         # port: TRIANGLE 3770, DOWN x6 3850..3950, CROSS 3990
    for k in range(6):                      # (retail lost presses 20 VBlanks apart right after
        d.press("DOWN", v + 30 * k)         # the menu opened: wait longer, space them wider)
    d.shot("menu_factory_row", v + 200)
    d.press("CROSS", v + 220)
    st = d.wait(lambda v, o, m: o == 4, what="FACTORY overlay", timeout=120, every=("CROSS", 100))
    st = d.wait(lambda v, o, m: m == "16/100", what="factory menu", timeout=120)
    d.shot("factory", st[0] + 60)
    v = st[0] + 200                         # port: 4400 menu, CROSS 4600 Blueprints, CIRCLE 4800
    d.press("CROSS", v)
    d.press("CIRCLE", v + 200)
    for k in range(6):                      # DOWN x6 4900..5000, CROSS 5050 Go Back, CROSS 5150 Yes
        d.press("DOWN", v + 300 + 30 * k)
    d.shot("factory_goback", v + 490)
    d.press("CROSS", v + 500)
    d.press("CROSS", v + 620)
    st = d.wait(lambda v, o, m: o == 3 and m.startswith("17/"), what="NORMAL main menu again", timeout=300)
    d.shot("menu_after", st[0] + 200)
    d.press("CIRCLE", st[0] + 260)
    d.shot("field_after", st[0] + 400)


def plan_loadmenu(d: Driver):
    """The boot card check and the Load menu's file list (renderer lane, text brightness): shots
    `boot350` / `boot450` / `boot550` (memory card check), `title`, then CONTINUE, slot 1 and
    `load` / `load2` (the file list, FILE 01 selected) without loading."""
    for v in (350, 450, 550):
        d.shot(f"boot{v}", v)
    # (the menu flag is already set under the company logos: wait past them, as the port's
    # boot scripts press at 1,900 / 2,150)
    d.wait(lambda v, o, m: o == 2 and d.pine.read32(MENUOPEN) & 0xFFFF and v > 1850, what="title menu",
           timeout=300)
    t = d.pine.read32(VBL)
    d.shot("title", t + 30)
    d.press("CROSS", t + 50)             # CONTINUE
    d.wait(lambda v, o, m: v > t + 600, what="slot dialog", timeout=120)
    t = d.pine.read32(VBL)
    for k in range(4):                   # MEMORY CARD slot 1 (retail takes the press late): a shot
        d.press("CROSS", t + 200 * k)    # before each further press (the file list shows in one)
        d.shot(f"load{k}", t + 200 * k + 190)


def plan_revel(d: Driver):
    """revelation.input.txt (BRINGUP item 6, late_game card) to the Revelation board, anchored
    on events: main menu, DOWN x3 (row 4 Revelation), CROSS x3 (Jaster's flow), shots `board0`..
    `board4` 20 VBlanks apart (the empty slot flashes), then CROSS on the flashing slot ->
    `place` (port: 3790 menu, DOWN 3960..3990, CROSS 4010/4100/4200, board 4250, place 4400)."""
    c = boot_to_control(d)
    d.press("TRIANGLE", c + 40)
    st = d.wait(lambda v, o, m: m.startswith("17/"), what="main menu", timeout=60)
    v = st[0] + 160
    for k in range(3):
        d.press("DOWN", v + 30 * k)
    d.shot("menu_revel_row", v + 120)
    d.press("CROSS", v + 140)
    d.press("CROSS", v + 260)
    d.press("CROSS", v + 380)
    for k in range(5):
        d.shot(f"board{k}", v + 480 + 20 * k)
    d.press("CROSS", v + 600)
    d.shot("place", v + 720)


PLANS = {"lib": plan_lib, "factory": plan_factory, "loadmenu": plan_loadmenu, "revel": plan_revel}


def _par(v):
    v ^= v >> 4
    v ^= v >> 2
    v ^= v >> 1
    return v & 1


# Column-parity bit order of the card ECC: bit 0..2 = parity of the bits selected by 0x55, 0x33,
# 0x0F, bit 3 unused, bits 4..6 = 0xAA, 0xCC, 0xF0 (the order mcman checks; see
# docs/TEST-FIXTURES.md "Retail comparison" for the evidence: ps2card.py's old order 0x55, 0xAA,
# 0x33, -, 0xCC, 0x0F, 0xF0 left retail unable to read the save).  ps2card.py writes this order
# since 2026-10-18 (tests/padmc/test_ps2card.py compares the two), so the rewrite is optional
# (`--ecc mcman`; it also fills erased pages' spare areas, which ps2card leaves 0xFF).
_CP = [_par(b & 0x55) | _par(b & 0x33) << 1 | _par(b & 0x0F) << 2 | _par(b & 0xAA) << 4 |
       _par(b & 0xCC) << 5 | _par(b & 0xF0) << 6 for b in range(256)]
_PB = [_par(b) for b in range(256)]


def ecc128(chunk: bytes) -> bytes:
    cp, lp0, lp1 = 0x77, 0x7F, 0x7F
    for i, c in enumerate(chunk):
        cp ^= _CP[c]
        if _PB[c]:
            lp0 ^= ~i & 0x7F
            lp1 ^= i
    return bytes((cp, lp0 & 0x7F, lp1 & 0x7F))


def reecc(path: Path) -> int:
    """Rewrite every page's spare area (16 bytes after each 512-byte page) with ecc128;
    returns the number of pages changed."""
    b = bytearray(path.read_bytes())
    if len(b) != 16384 * 528:
        return 0
    n = 0
    for p in range(16384):
        o = p * 528
        page = bytes(b[o:o + 512])
        sp = b"".join(ecc128(page[i:i + 128]) for i in range(0, 512, 128)) + bytes(4)
        if b[o + 512:o + 528] != sp:
            b[o + 512:o + 528] = sp
            n += 1
    path.write_bytes(bytes(b))
    return n


def export_card(src: Path, dst: Path, ecc: str = "ps2card"):
    if src.suffix == ".ps2":
        shutil.copyfile(src, dst)
    else:
        if dst.exists():
            dst.unlink()
        subprocess.run([sys.executable, str(PORT / "tools" / "saves" / "ps2card.py"), "export", str(dst),
                        "--format", "--saves", str(src)], check=True, capture_output=True, text=True)
    if ecc == "mcman":
        reecc(dst)


def busy() -> list[str]:
    """Live portable PCSX2 PID files (another harness run)."""
    out = []
    rd = Path(emu.RUN_DIR)
    for p in rd.glob("*.pid") if rd.is_dir() else []:
        try:
            pid = int(p.read_text().strip())
        except ValueError:
            continue
        r = subprocess.run(["tasklist", "/FI", f"PID eq {pid}", "/NH"], capture_output=True, text=True)
        if "pcsx2" in r.stdout.lower():
            out.append(f"{p.name} (PID {pid})")
    return out


def run_card(card: str, plan: str, out: Path, speed: float, timeout: float, keep: bool,
             ecc: str = "ps2card") -> dict:
    src = Path(card)
    if not src.exists():
        src = CARDS / card
    name = src.stem if src.suffix == ".ps2" else src.name
    mc_dir = Path(emu.EMU_DIR) / "memcards"
    mc_dir.mkdir(parents=True, exist_ok=True)
    mc = mc_dir / f"cardboot_{name}.ps2"
    export_card(src, mc, ecc)
    out.mkdir(parents=True, exist_ok=True)
    logf = open(out / f"{name}.log", "w", encoding="utf-8")
    res = {"card": name, "plan": plan, "ok": False}
    e = emu.Emu(speed=speed, renderer=13, tag=f"cardboot_{name}",
                overrides=["MemoryCards/Slot1_Enable=true", f"MemoryCards/Slot1_Filename={mc.name}"])
    t0 = time.time()
    try:
        pine = e.connect()
        # The hook goes in unfrozen (trace.py freezes the EE for cycle determinism, which a
        # screenshot comparison does not need; at speed 1 the frozen install often finds no
        # idle vsync on the shared PC).
        vbl = inp.install(pine, [0] * inp.MAX_ENTRIES, sampler=None)
        logf.write(f"input hook installed at game vbl {vbl}\n")
        d = Driver(e, pine, logf, out, name)
        PLANS[plan](d)
        res.update(ok=True, milestones=d.ms)
    except Exception as ex:   # noqa: BLE001 -- report and keep going with the next card
        res["error"] = f"{type(ex).__name__}: {ex}"
        logf.write(f"ERROR {res['error']}\n")
        try:
            import live
            live.window_shot(e.proc.pid, str(out / f"{name}_error.png"))
        except Exception:  # noqa: BLE001
            pass
        print(f"  [{name}] ERROR {res['error']}", flush=True)
    finally:
        e.stop()
        logf.close()
        if not keep:
            mc.unlink(missing_ok=True)
    res["wall_s"] = round(time.time() - t0)
    (out / f"{name}.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    return res


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cards", nargs="*")
    ap.add_argument("--plan", default="lib", choices=sorted(PLANS))
    ap.add_argument("--out", default=str(PORT / "out" / "retail" / "cardboot"))
    ap.add_argument("--speed", type=float, default=1.0)
    ap.add_argument("--timeout", type=float, default=600)
    ap.add_argument("--keep-card", action="store_true")
    ap.add_argument("--ecc", default="ps2card", choices=["mcman", "ps2card"],
                    help="spare-area ECC of the exported image: ps2card's own (default; same order as "
                         "mcman's since 2026-10-18) or rewrite every page incl. erased ones (mcman)")
    ap.add_argument("--list-plans", action="store_true")
    a = ap.parse_args(argv)
    if a.list_plans:
        for k, f in PLANS.items():
            print(f"{k}: {(f.__doc__ or '').strip()}")
        return 0
    b = busy()
    if b:
        print("cardboot: a portable PCSX2 is running (" + ", ".join(b) + "); one instance at a time")
        return 2
    ok = True
    for c in a.cards:
        r = run_card(c, a.plan, Path(a.out), a.speed, a.timeout, a.keep_card, a.ecc)
        ok &= r["ok"]
        print(f"cardboot {r['card']}: {'OK' if r['ok'] else 'FAIL ' + r.get('error', '')} ({r['wall_s']} s)", flush=True)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())

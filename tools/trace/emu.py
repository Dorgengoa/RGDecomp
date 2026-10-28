# SPDX-License-Identifier: CC0-1.0
"""Isolated portable PCSX2 for reference traces: setup, launch, snapshots.

PCSX2 is GPL. It is used here only as an external program; nothing from its
source is copied (PLAN.md D7). Everything below talks to it through its
command line, its ini file, PINE and its savestate files.
"""
import hashlib
import os
import shutil
import struct
import subprocess
import sys
import time
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
TOOLS = os.path.join(PORT, ".tools")
EMU_DIR = os.path.join(TOOLS, "pcsx2")
EXE = os.path.join(EMU_DIR, "pcsx2-qt.exe")
RUN_DIR = os.path.join(TOOLS, "run")

INSTALL_DIR = r"C:\Program Files\PCSX2"
USER_INI = os.path.join(os.path.expanduser("~"), "Documents", "PCSX2", "inis", "PCSX2.ini")
DEFAULT_ISO = r"../ROMS\Rogue Galaxy (USA).iso"
DEFAULT_SLOT = 28012          # user's own PCSX2 uses 28011; never collide
STATE_SLOT = 1

# EE cycles per vsync. The BIOS starts at exactly 60 Hz (4,915,200); once the
# game sets NTSC mode PCSX2 uses 59.94 Hz (4,920,120). Both observed.
VSYNC_PERIODS = (4920120, 4915200)
EE_CYCLES_PER_VSYNC = VSYNC_PERIODS[0]
VSYNC_TOL = 2000      # vsync samples land within ~50 cycles (block granularity)


def _delta(a, b):
    """a - b for EE cycle values: plain difference for the 64-bit unwrapped
    counts live.py provides, mod 2^32 for raw u32 savestate values."""
    return a - b if a >= b else (a - b) & 0xFFFFFFFF


# Power-on vsync grid (SCUS-97490 + BIOS 0230a, fast boot): vsync k is at
# cycle k*4,915,200 (60 Hz) up to frame 109 (0x1FEF0008); the game then sets
# NTSC: frame 110 is at 0x203A3A1F (one odd 4,930,071-cycle frame) and later
# frames follow every 4,920,120. Measured from every-frame live traces.
NTSC_SWITCH_FRAME = 110
NTSC_SWITCH_CYCLE = 0x203A3A1F


def first_frame(cyc):
    """Absolute VBlank index of the first sample (cycle within the first 2^32,
    i.e. 14.5 s of EE time, or already unwrapped by live.py)."""
    if cyc < NTSC_SWITCH_CYCLE - VSYNC_PERIODS[1] // 2:
        return int(round(cyc / VSYNC_PERIODS[1]))
    return NTSC_SWITCH_FRAME + int(round((cyc - NTSC_SWITCH_CYCLE) / VSYNC_PERIODS[0]))


class FrameClock:
    """Turns the u32 EE cycle counter of successive snapshots into an absolute
    VBlank index since power-on, and rejects snapshots not on a vsync.

    frame0 comes from first_frame(): the power-on vsync grid, so a run whose
    first sample is late (high speed, no idle early on) numbers frames the
    same as one sampled from the BIOS on.

    A sample is accepted at once when its distance from the last accepted one
    is a clean sum of vsync periods (within VSYNC_TOL). Video-mode switches
    make one odd-length frame (the BIOS->NTSC switch is 4,930,071 cycles), so a
    sample that is only roughly on the grid (within a quarter frame) is held
    as pending and accepted when the next sample is a clean multiple of
    periods from it. A mid-frame idle (e.g. a CD wait) is never followed by a
    clean interval, so it is dropped."""

    def __init__(self):
        self.last = None
        self.frame = None
        self.pending = None      # (cycle, frames after last, payload, vbl)
        self.last_vbl = 0
        self.dropped = 0

    @staticmethod
    def _clean(d):
        # d = a*P60 + (n-a)*PNTSC for some 0 <= a <= n: a gap may straddle
        # the 60 Hz -> 59.94 Hz switch.
        if d == 0:
            return None
        p_ntsc, p_60 = VSYNC_PERIODS
        step = p_ntsc - p_60
        for n in {int(d // p_ntsc), int(d // p_ntsc) + 1, int(round(d / p_60))}:
            if n < 1:
                continue
            r = n * p_ntsc - d
            a = int(round(r / step))
            if 0 <= a <= n and abs(r - a * step) <= VSYNC_TOL:
                return n
        return None

    @staticmethod
    def _loose(d):
        n = int(round(d / VSYNC_PERIODS[0]))
        if n >= 1 and abs(d - n * VSYNC_PERIODS[0]) <= VSYNC_PERIODS[0] // 4:
            return n
        return None

    def wanted(self, cyc):
        """Is a snapshot at this cycle worth reading?"""
        if self.last is None:
            return True
        if self.pending and cyc == self.pending[0]:
            return False
        d = _delta(cyc, self.last)
        return bool(self._clean(d) or self._loose(d))

    @staticmethod
    def _span(cyc, ref, vbl, ref_vbl):
        """EE cycles from ref to cyc. The cycle counter is u32 (wraps every
        873 frames); if the host stalled long enough for live.py to miss a wrap
        (a slow disk flush can block for tens of seconds), the game's own
        VBlank counter says how many frames really passed, which pins the
        number of 2^32 wraps (873 frames apart, far beyond its +-1 jitter)."""
        d = _delta(cyc, ref)
        if vbl and ref_vbl and vbl > ref_vbl:
            d32 = d & 0xFFFFFFFF
            k = int(round(((vbl - ref_vbl) * VSYNC_PERIODS[0] - d32) / 2.0 ** 32))
            if k >= 0:
                d = d32 + (k << 32)
        return d

    def offer(self, cyc, payload, vbl=0):
        """Returns the list of (frame, payload) that became final. vbl = the
        game's VBlank counter in this snapshot (0 if unknown)."""
        if self.last is None:
            self.last, self.frame, self.last_vbl = cyc, first_frame(cyc), vbl
            return [(self.frame, payload)]
        d = self._span(cyc, self.last, vbl, self.last_vbl)
        n = self._clean(d)
        if n:
            if self.pending:
                self.dropped += 1
            self.pending = None
            self.last, self.frame, self.last_vbl = cyc, self.frame + n, vbl
            return [(self.frame, payload)]
        if self.pending:
            pc, pn, pp, pv = self.pending
            m = self._clean(self._span(cyc, pc, vbl, pv))
            if m:
                self.pending = None
                f1 = self.frame + pn
                self.last, self.frame, self.last_vbl = cyc, f1 + m, vbl
                return [(f1, pp), (f1 + m, payload)]
        nl = self._loose(d)
        if nl:
            if self.pending:
                self.dropped += 1
            self.pending = (cyc, nl, payload, vbl)
        else:
            self.dropped += 1
        return []


# ---------------------------------------------------------------- setup
def _ini_value(path, section, key):
    sec = None
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            s = line.strip()
            if s.startswith("["):
                sec = s.strip("[]")
            elif sec == section and "=" in s:
                k, v = s.split("=", 1)
                if k.strip() == key:
                    return v.strip()
    return None


def user_bios():
    """BIOS dir+file from the user's own PCSX2 config (read only)."""
    folder = _ini_value(USER_INI, "Folders", "Bios")
    name = _ini_value(USER_INI, "Filenames", "BIOS")
    if not folder or not name:
        raise SystemExit("no BIOS configured in %s" % USER_INI)
    if not os.path.isabs(folder):
        folder = os.path.join(os.path.dirname(os.path.dirname(USER_INI)), folder)
    return os.path.normpath(folder), name


def _apply_override(text, spec):
    """spec = 'Section/Sub/Key=Value' (section path may contain '/')."""
    path, value = spec.split("=", 1)
    section, key = path.rsplit("/", 1)
    lines = text.split(chr(10))
    sec, last_in_sec = None, None
    for i, line in enumerate(lines):
        st = line.strip()
        if st.startswith("["):
            sec = st.strip("[]")
            continue
        if sec == section:
            last_in_sec = i
            if "=" in st and st.split("=", 1)[0].strip() == key:
                lines[i] = "%s = %s" % (key, value)
                return chr(10).join(lines)
    if last_in_sec is None:
        lines += ["", "[%s]" % section, "%s = %s" % (key, value)]
    else:
        lines.insert(last_in_sec + 1, "%s = %s" % (key, value))
    return chr(10).join(lines)


def write_ini(speed=1.0, slot=DEFAULT_SLOT, renderer=11, overrides=()):
    bios_dir, bios_file = user_bios()
    with open(os.path.join(HERE, "pcsx2_portable.ini"), encoding="utf-8") as f:
        text = f.read()
    text = (text.replace("@BIOS_DIR@", bios_dir).replace("@BIOS_FILE@", bios_file)
            .replace("@PINE_SLOT@", str(slot)).replace("@SPEED@", repr(float(speed)))
            .replace("@RENDERER@", str(renderer)))
    for spec in overrides:
        text = _apply_override(text, spec)
    os.makedirs(os.path.join(EMU_DIR, "inis"), exist_ok=True)
    with open(os.path.join(EMU_DIR, "inis", "PCSX2.ini"), "w", encoding="utf-8") as f:
        f.write(text)
    return text


def setup(force=False):
    """Copy the installed PCSX2 to .tools/pcsx2 and make it portable."""
    if force and os.path.isdir(EMU_DIR):
        shutil.rmtree(EMU_DIR)
    if not os.path.exists(EXE):
        shutil.copytree(INSTALL_DIR, EMU_DIR,
                        ignore=shutil.ignore_patterns("unins000.*", "updater.exe"))
    # PCSX2 2.x: portable.txt (or portable.ini) next to the exe = data under the exe dir.
    open(os.path.join(EMU_DIR, "portable.txt"), "a").close()
    os.makedirs(RUN_DIR, exist_ok=True)
    write_ini()
    print("portable PCSX2 ready at", EMU_DIR)


def bios_sidecar_hashes():
    """Hashes of the .nvm/.mec files PCSX2 keeps next to the BIOS. The portable
    copy reads the BIOS from the user's folder (no admin -> no symlink, and
    BIOS files must not be copied), so a run could in principle write the
    user's NVM. Runs check these before/after and warn if they changed."""
    d, name = user_bios()
    base = os.path.splitext(name)[0]
    out = {}
    for ext in (".nvm", ".mec"):
        p = os.path.join(d, base + ext)
        if os.path.exists(p):
            with open(p, "rb") as f:
                out[ext] = hashlib.sha256(f.read()).hexdigest()
    return out


# --------------------------------------------------------------- launch
class Emu:
    """One portable PCSX2 process. Stopped by PID only."""

    def __init__(self, iso=DEFAULT_ISO, speed=1.0, slot=DEFAULT_SLOT, renderer=11,
                 tag="run", statefile=None, state_slot=STATE_SLOT, overrides=(), memcard=False):
        if not os.path.exists(EXE):
            raise SystemExit("run `python tools/trace/emu.py setup` first")
        os.makedirs(RUN_DIR, exist_ok=True)
        overrides = list(overrides)
        self.memcard = None
        if memcard:
            # A fresh card per run: PCSX2 creates a new formatted 8 MB card when
            # the slot's file is missing. Parallel runs need distinct tags.
            mc_dir = os.path.join(EMU_DIR, "memcards")
            os.makedirs(mc_dir, exist_ok=True)
            name = "trace_%s.ps2" % tag
            self.memcard = os.path.join(mc_dir, name)
            if os.path.exists(self.memcard):
                os.remove(self.memcard)
            overrides += ["MemoryCards/Slot1_Enable=true", "MemoryCards/Slot1_Filename=" + name]
        write_ini(speed=speed, slot=slot, renderer=renderer, overrides=overrides)
        self.slot = slot
        self.state_slot = state_slot
        self.sstates = os.path.join(EMU_DIR, "sstates")
        os.makedirs(self.sstates, exist_ok=True)
        for f in os.listdir(self.sstates):
            if f.endswith(".%02d.p2s" % state_slot):
                os.remove(os.path.join(self.sstates, f))
        self.log = os.path.join(RUN_DIR, tag + ".emulog.txt")
        args = [EXE, "-batch", "-nogui", "-fastboot", "-logfile", self.log]
        if statefile:
            args += ["-statefile", statefile]
        args += ["--", iso]
        self.nvm_before = bios_sidecar_hashes()
        self.proc = subprocess.Popen(args)
        self.pidfile = os.path.join(RUN_DIR, tag + ".pid")
        with open(self.pidfile, "w") as f:
            f.write(str(self.proc.pid))
        self.pine = None

    def connect(self, timeout=300):
        from pine import Pine
        t0 = time.time()
        while time.time() - t0 < timeout:
            if self.proc.poll() is not None:
                raise RuntimeError("PCSX2 exited early (code %s)" % self.proc.returncode)
            try:
                self.pine = Pine(self.slot)
                break
            except OSError:
                time.sleep(0.25)
        if self.pine is None:
            raise RuntimeError("PINE did not come up")
        while time.time() - t0 < timeout:  # status 0 = running (a VM exists)
            try:
                if self.pine.status() == 0:
                    return self.pine
            except Exception:
                pass
            time.sleep(0.1)
        raise RuntimeError("VM did not start")

    def stop(self):
        if self.pine:
            self.pine.close()
        if self.proc.poll() is None:
            self.proc.kill()          # TerminateProcess on our own PID only
            self.proc.wait(timeout=30)
        for f in (self.pidfile, self.memcard):
            try:
                if f:
                    os.remove(f)     # the per-run card is recreated next time anyway
            except OSError:
                pass
        after = bios_sidecar_hashes()
        if after != self.nvm_before:
            print("WARNING: user BIOS .nvm/.mec changed during the run", file=sys.stderr)

    # ------------------------------------------------------------ snapshots
    def _state_path(self):
        for f in os.listdir(self.sstates):
            if f.endswith(".%02d.p2s" % self.state_slot):
                return os.path.join(self.sstates, f)
        return None

    def snapshot(self, timeout=30):
        """Ask PCSX2 for a savestate and return a Snapshot of it.

        The save request is queued to PCSX2's CPU thread, which services it
        while handling a vsync. The memory copy is taken there, with the EE and
        IOP stopped, so the snapshot is internally consistent and sits on a
        vsync boundary. (PINE memory reads, by contrast, run on PINE's own
        thread while the EE keeps running.)"""
        old = self._state_path()
        if old:
            os.remove(old)
        self.pine.save_state(self.state_slot)
        t0 = time.time()
        while time.time() - t0 < timeout:
            p = self._state_path()
            if p:
                try:
                    return Snapshot(p)
                except (zipfile.BadZipFile, KeyError, OSError, EOFError):
                    pass      # still being written
            time.sleep(0.01)
        raise RuntimeError("savestate did not appear")


class Snapshot:
    def __init__(self, path):
        with zipfile.ZipFile(path) as z:
            self.ee = z.read("eeMemory.bin")
            self.iop = z.read("iopMemory.bin")
            self.spr = z.read("Scratchpad.bin")
            self.internal = z.read("PCSX2 Internal Structures.dat")
        if len(self.ee) < 0x2000000:
            raise zipfile.BadZipFile("short eeMemory")
        # cpuRegs.cycle = 'cpuRegs' freeze tag (32-byte name) + 960. Offset
        # observed in PCSX2 v2.6.3 savestates (version 0x9a550000); re-check
        # if the savestate version changes. Same field live.py reads.
        i = self.internal.find(b"cpuRegs\0")
        if i < 0:
            raise KeyError("no cpuRegs tag")
        self.ee_cycle32 = struct.unpack_from("<I", self.internal, i + 32 + 960)[0]

    def space(self, name):
        return {"ee": self.ee, "iop": self.iop, "spr": self.spr}[name]


class LiveSnapshot:
    """Same interface as Snapshot, filled from a frozen live process."""

    def __init__(self, cycle, ee, iop, spr):
        self.ee_cycle32, self.ee, self.iop, self.spr = cycle, ee, iop, spr

    def space(self, name):
        return {"ee": self.ee, "iop": self.iop, "spr": self.spr}[name]


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "setup":
        setup(force="--force" in sys.argv)
    else:
        print("usage: emu.py setup [--force]")

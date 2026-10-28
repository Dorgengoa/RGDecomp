# SPDX-License-Identifier: CC0-1.0
"""Probe runs: guest-side call logging and in-guest experiments in PCSX2.

The trace harness (trace.py) only sees memory at vsyncs. Some questions need
more: the arguments of every sceCdRead, the id every CreateSema returns, the
order in which INTC handlers run. probe.py patches small trampolines into the
game's EE code (the same way input.py installs the pad hook: written over PINE
while PCSX2's CPU thread is frozen at a vsync, before the game runs), and the
trampolines append fixed-size records to a ring buffer in EE RAM that is
unused after boot. The harness drains the ring at each sampled vsync (frozen,
like live.py snapshots), together with any watched memory ranges.

Guest memory map (all in 0x98000..0xF0000, zero after boot, see input.py):
    CODE  0x098000..0x0A0000   trampolines, experiment code
    LOG   0x0A0000             u32 count, u32 exp_state, u32 exp_arg, u32 pad
          0x0A0010..0x0E0010   4096 records x 64 bytes (ring)
    DATA  0x0E1000..0x0E8000   experiment variables and results
    STACK 0x0E8000..0x0F0000   stacks of experiment threads (4 x 8 KB)
(input.py owns 0x0F0000..0x100000.)

Record (16 u32): 0 tag = seq<<16 | kind<<8 | site, 1 game vbl [0x4810C4],
2 COP0 Count, 3..6 a0..a3, 7 v0, 8 ra, 9 sp, 10..15 six dump words.
kind 1 = entry, 2 = function return (via a stack frame the trampoline pushes),
3 = syscall return, 4 = custom (experiment).

Logging clobbers only $12-$15 and $24 (t4-t7, t8), which are dead at a
function entry and right after a call. The ring reservation (lw/sw of the
count) is not interrupt-atomic; an interrupt-context record landing in that
3-instruction window would overwrite one record (seq duplicates are reported).

Nothing here comes from PCSX2's source. The hooks change EE timing, so probe
runs are not comparable to the goldens; they answer questions, they are not
lockstep references.
"""
import argparse
import json
import os
import struct
import sys
import time
import zipfile
import shutil

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import emu      # noqa: E402
import input as inp  # noqa: E402
from mips import (Asm, is_control, ZERO, AT, V0, V1, A0, A1, A2, A3, T0, T1, T2, T3, T4, T5,  # noqa: E402
                  T6, T7, S0, S1, S2, S3, S4, S5, S6, S7, T8, T9, GP, SP, FP, RA, hi, lo)

CODE = 0x00098000
CODE_END = 0x000A0000
LOG = 0x000A0000
NREC = 4096
REC = 64
RING = LOG + 0x10
DATA = 0x000E1000
STACKS = 0x000E8000
VBL = 0x004810C4
ELF = os.environ.get("RG_ELF", r"../work/SCUS_974.90")

KIND = {1: "entry", 2: "ret", 3: "sysret", 4: "exp"}


# ------------------------------------------------------------ retail ELF
_elf = None


def elf_word(a):
    """A word of the retail main ELF image (to check hook sites)."""
    global _elf
    if _elf is None:
        d = open(ELF, "rb").read()
        phoff, = struct.unpack_from("<I", d, 0x1C)
        phnum, = struct.unpack_from("<H", d, 0x2C)
        _elf = (d, [struct.unpack_from("<6I", d, phoff + 32 * i)[1:5] for i in range(phnum)])
    d, segs = _elf
    for off, va, pa, fsz in segs:
        if va <= a < va + fsz:
            return struct.unpack_from("<I", d, off + a - va)[0]
    raise KeyError(hex(a))


# ------------------------------------------------------------ log emitter
_wl = [0]


def W_abs(addr):
    """words-dump item: the u32 at a fixed address (also hardware registers)."""
    return ("m", ("abs", addr), 0)


def W_ptr(addr, *offs):
    """words-dump item: follow the pointer stored at addr through offs
    (each intermediate pointer null-checked; null gives 0)."""
    return ("m", ("abs", addr), 0, *offs)


def W_reg(r, *offs):
    """words-dump item: register r itself (no offs) or *(r + off ...)."""
    return ("m", ("reg", r), *offs)


def W_stk(slot, *offs):
    """words-dump item (return hooks): the saved arg at sp + 4*slot, or
    memory through it."""
    return ("m", ("stk", slot), *offs)


def W_fpr(n):
    """words-dump item: the bits of FPR $f<n> (float arguments)."""
    return ("fpr", n)


def _emit_word(a, spec):
    """Load one words-dump item into T7 (uses T7, T8 only)."""
    if spec[0] == "fpr":
        a.w(0x44000000 | (T7 << 16) | (spec[1] << 11))      # mfc1 t7, $fN
        return
    _, base, *offs = spec
    if base[0] == "abs":
        a.li(T8, base[1])
    elif base[0] == "reg":
        if not offs:
            a.addu(T7, base[1], ZERO)
            return
        a.addu(T8, base[1], ZERO)
    elif base[0] == "stk":
        a.lw(T8, 4 * base[1], SP)
        if not offs:
            a.addu(T7, T8, ZERO)
            return
    _wl[0] += 1
    skip = "wnull_%d" % _wl[0]
    for off in offs[:-1]:
        a.lw(T8, off, T8)
        a.beq(T8, ZERO, skip, delay=False)
        a.addu(T7, ZERO, ZERO)                                # delay slot: null -> 0
    a.lw(T7, offs[-1], T8)
    a.label(skip)


def emit_log(a, kind, site, dump=None):
    """Append one record. dump: None | ('reg', r, off) | ('abs', addr) |
    ('ptr', addr, off) [*(u32*)addr + off] | ('stk', slot, off)
    [*(u32*)(sp + 4*slot) + off, for return hooks] | ('words', [item...])
    [up to six independent words, items from W_abs/W_ptr/W_reg/W_stk/W_fpr]."""
    a.lui(T4, LOG >> 16)
    a.lw(T5, 0, T4)
    a.addiu(T7, T5, 1)
    a.sw(T7, 0, T4)
    a.andi(T6, T5, NREC - 1)
    a.sll(T6, T6, 6)
    a.addu(T6, T6, T4)
    a.sll(T5, T5, 16)
    a.ori(T5, T5, (kind << 8) | site)
    a.sw(T5, 0x10, T6)
    a.lui(T7, hi(VBL))
    a.lw(T7, lo(VBL), T7)
    a.sw(T7, 0x14, T6)
    a.mfc0(T7, 9)
    a.sw(T7, 0x18, T6)
    for i, r in enumerate((A0, A1, A2, A3, V0, RA, SP)):
        a.sw(r, 0x1C + 4 * i, T6)
    if dump and dump[0] == "words":
        assert len(dump[1]) <= 6
        for i, spec in enumerate(dump[1]):
            _emit_word(a, spec)
            a.sw(T7, 0x38 + 4 * i, T6)
    elif dump:
        base, off = None, 0
        if dump[0] == "reg":
            base, off = dump[1], dump[2]
        elif dump[0] == "abs":
            a.li(T8, dump[1])
            base = T8
        elif dump[0] == "ptr":
            a.lui(T8, hi(dump[1]))
            a.lw(T8, lo(dump[1]), T8)
            base, off = T8, dump[2]
        elif dump[0] == "stk":
            a.lw(T8, 4 * dump[1], SP)
            base, off = T8, dump[2]
        for i in range(6):
            a.lw(T7, off + 4 * i, base)
            a.sw(T7, 0x38 + 4 * i, T6)


# ------------------------------------------------------------ hooks
class Hooks:
    """Collects trampolines (in CODE) and the patches over game code."""

    def __init__(self):
        self.a = Asm(CODE)
        self.patches = []          # (addr, (w0, w1)) original pair -> j tramp; nop
        self.sites = {}            # site id -> name
        self.extra = []            # (addr, bytes) data writes
        self._next_site = 1

    def _site(self, name):
        s = self._next_site
        self._next_site += 1
        self.sites[s] = name
        return s

    def _orig(self, addr):
        w0, w1 = elf_word(addr), elf_word(addr + 4)
        if is_control(w0) or is_control(w1):
            raise SystemExit("hook site %08x: a control-transfer word in the first two" % addr)
        return w0, w1

    def _patch(self, addr, tramp, orig):
        self.patches.append((addr, tramp, orig))

    def entry(self, addr, name, dump=None, pre=None):
        """Log every call of the function at addr (args, ra, sp)."""
        w0, w1 = self._orig(addr)
        s = self._site(name)
        a = self.a
        t = a.pc
        if pre:
            pre(a)
        emit_log(a, 1, s, dump)
        a.w(w0)
        a.w(w1)
        a.j(addr + 8)
        self._patch(addr, t, (w0, w1))
        return s

    def leaf(self, addr, name, dump=None, skip_zero=None):
        """Log every call of a two-word leaf `jr ra; <insn>` (an accessor):
        the trampoline logs, then returns with <insn> in the delay slot.
        skip_zero=reg: log only when that register is non-zero."""
        w0, w1 = elf_word(addr), elf_word(addr + 4)
        if w0 != 0x03E00008 or is_control(w1):
            raise SystemExit("%08x is not a `jr ra; insn` leaf" % addr)
        s = self._site(name)
        a = self.a
        t = a.pc
        skip = "leafskip_%x" % addr
        if skip_zero is not None:
            a.beq(skip_zero, ZERO, skip)
        emit_log(a, 1, s, dump)
        a.label(skip)
        a.jr(RA)
        a.w(w1)
        self._patch(addr, t, (w0, w1))
        return s

    def entry_ret(self, addr, name, dump=None, dump_ret=None, log_entry=True):
        """Log entry and return (v0) of a function with <= 8 args (the
        trampoline pushes a 16-byte frame: ra, a0, a1, a2).
        log_entry=False logs the return only (rate)."""
        w0, w1 = self._orig(addr)
        s = self._site(name)
        a = self.a
        t = a.pc
        if log_entry:
            emit_log(a, 1, s, dump)
        a.addiu(SP, SP, -16)
        a.sw(RA, 0, SP)
        a.sw(A0, 4, SP)
        a.sw(A1, 8, SP)
        a.sw(A2, 12, SP)
        body = "body_%x" % addr
        a.jal(body)
        emit_log(a, 2, s, dump_ret)
        a.lw(RA, 0, SP)
        a.jr(RA)
        a.addiu(SP, SP, 16)          # delay slot
        a.label(body)
        a.w(w0)
        a.w(w1)
        a.j(addr + 8)
        self._patch(addr, t, (w0, w1))
        return s

    def syscall_stub(self, addr, name, dump=None):
        """libkernl stub `addiu v1,zero,N; syscall; jr ra; nop`: log entry and
        the kernel's return value."""
        w0, w1 = elf_word(addr), elf_word(addr + 4)
        if (w0 >> 16) != 0x2403 or w1 != 0x0000000C:
            raise SystemExit("%08x is not a syscall stub" % addr)
        s = self._site(name)
        a = self.a
        t = a.pc
        emit_log(a, 1, s, dump)
        a.w(w0)
        a.syscall()
        emit_log(a, 3, s)
        a.jr(RA)
        a.nop()
        self._patch(addr, t, (w0, w1))
        return s

    def blobs(self):
        code = self.a.blob()
        if CODE + len(code) > CODE_END:
            raise SystemExit("trampolines overflow CODE")
        out = [(CODE, code + bytes(-len(code) % 8))]
        out += self.extra
        for addr, tramp, orig in self.patches:
            out.append((addr, struct.pack("<II", (2 << 26) | ((tramp >> 2) & 0x03FFFFFF), 0)))
        return out


# ------------------------------------------------------------ hook sets
# libkernl syscall stubs (census/platform_ee_syscalls.tsv)
SYSCALLS = {
    "CreateThread": (0x1163A0, ("reg", A0, 0)),
    "DeleteThread": (0x1163B0, None),
    "StartThread": (0x1163C0, None),
    "ExitThread": (0x1163D0, None),
    "ExitDeleteThread": (0x1163E0, None),
    "TerminateThread": (0x1163F0, None),
    "ChangeThreadPriority": (0x116430, None),
    "GetThreadId": (0x116490, None),
    "SleepThread": (0x1164C0, None),
    "WakeupThread": (0x1164D0, None),
    "iWakeupThread": (0x1164E0, None),
    "SuspendThread": (0x116510, None),
    "ResumeThread": (0x116530, None),
    "CreateSema": (0x1165A0, ("reg", A0, 0)),
    "DeleteSema": (0x1165B0, None),
    "SignalSema": (0x1165C0, None),
    "iSignalSema": (0x1165D0, None),
    "WaitSema": (0x1165E0, None),
    "PollSema": (0x1165F0, None),
    "iPollSema": (0x116600, None),
    "ReferSemaStatus": (0x116610, None),
    "AddIntcHandler": (0x116280, None),
    "AddIntcHandler2": (0x116290, None),
    "RemoveIntcHandler": (0x1162A0, None),
    "AddDmacHandler": (0x1162B0, None),
    "AddDmacHandler2": (0x1162C0, None),
    "RemoveDmacHandler": (0x1162D0, None),
    "_EnableIntc": (0x1162E0, None),
    "_DisableIntc": (0x1162F0, None),
    "SetAlarm": (0x116320, None),
    "iSetAlarm": (0x116380, None),
}

# high-rate sema operations: separate set "sema" (sync SIF RPCs alone make
# ~30 CreateSema/DeleteSema pairs per VBlank; RotateThreadReadyQueue, the
# game's ThreadYield, is never hooked: it spins thousands of times per frame)
SEMA_OPS = {"SignalSema", "iSignalSema", "WaitSema", "PollSema", "iPollSema", "ReferSemaStatus"}

PAD_DMA = (0x004B2A80, 0x004B2B80)


# ------------------------------------------------------------ timing contract
# The reference timing contract (PLAN.md "Unlocked frame rate" step 1,
# docs/TIMING-REFERENCE.md). Addresses are retail SCUS_974.90; the field
# offsets come from the matching sources named in each comment.
T_DRAWCTX = 0x004810A4     # GetDrawCtx_15de80
T_SCENE = 0x00481998       # GetCurrentScene_1f5be0
T_SEQ_OWNER = 0x00481554   # MainLoop_1c2c10 / SysTickThreadMain_1c33f0: 0 = main loop advances sequences
T_TICK_READY = 0x0047E250  # SysTickThreadSignalIsr_1c34f0 readiness handshake
T_DISKWATCH = 0x00481558   # SysVblankCallback_1c33a0 1-in-30 counter
T_WAITFLAG = 0x004810C0    # WaitVsyncCount_15de90
T_PAUSESTEP = 0x0048276C   # GetPauseStep_2f6660
T_GAMEMODE = 0x004B51A0    # GameModeStack[0] (symbols.spec)
T_PHASE = 0x004B51E0       # GameModePhaseStack[0]
T_TASKDEPTH = 0x00482278   # TaskStatePushAll_27c220 depth
T_SYSMODE = 0x0047E224     # MainLoop_1c2c10 mode
T_OVERLAY = 0x0047E254     # OverlayLoad_1c3210
T_VUTIME = 0x004810B4      # GfxEndFrame_141c20 second time sample
T_T0COUNT = 0x10000000     # EE timer 0 count (GfxEndFrame_141c20 T0_COUNT)


def build_timing_hooks(h):
    W = lambda *items: ("words", list(items))          # noqa: E731
    # per VBlank (interrupt context): the game counter is the record's vbl
    # (before this handler increments it)
    h.entry(0x15DF20, "VblankStart",
            W(W_abs(T_WAITFLAG), W_abs(T_TICK_READY), W_abs(T_DISKWATCH),
              W_abs(T_SEQ_OWNER), W_abs(T_PAUSESTEP), W_abs(T_SYSMODE)))
    # one frame-worker wake (SysTickThreadMain_1c33f0 is the only caller)
    h.entry(0x1837A0, "TickWake")
    # sequence advance: ra tells MainLoop vs SysTickThreadMain; d0 = step (f32)
    h.entry(0x1BB110, "SoundSeqUpdate", W(W_fpr(12), W_abs(T_SEQ_OWNER)))
    # GfxEndFrame_141c20(ctx, flag): entry = raw time samples, return =
    # stored feedback (+0xF10), flip bookkeeping, depth slot 0
    h.entry_ret(0x141C20, "GfxEndFrame",
                W(W_abs(T_T0COUNT), W_abs(T_VUTIME), W_reg(A0, 0x270, 0x2C),
                  W_reg(A0, 0x270, 0x28), W_reg(A0, 0xF18), W_reg(A0, 0x3D2C)),
                W(W_stk(1, 0xF10), W_stk(1, 0xF00), W_stk(1, 0xF04),
                  W_stk(1, 0x270, 0x24), W_stk(1, 0x3CD0), W_stk(1, 0x3CDC)))
    # GfxFlipBuffersMaybe_143650 -> WaitVsyncCount_15de90(base, n)
    h.entry_ret(0x15DE90, "WaitVsync")
    # scene time scale: d = +0x5E00 dbl-step byte, +0x5E04 count, +0x5E08
    # scale, +0x5E0C mult, +0x5E10 countdown, +0x5E14 locked|susp<<8
    h.entry_ret(0x1CEBE0, "SceneTimeScale", ("reg", A0, 0x5E00), ("stk", 1, 0x5E00))
    h.entry_ret(0x1F5340, "TaskTableRun",
                W(W_abs(T_GAMEMODE), W_abs(T_PHASE), W_abs(T_PAUSESTEP),
                  W_abs(T_TASKDEPTH), W_abs(T_SYSMODE), W_abs(T_OVERLAY)))
    h.leaf(0x1F56B0, "TaskListChanged", skip_zero=A0)
    h.entry(0x144140, "SetVsyncInterval")
    h.leaf(0x1CEB90, "SetTimeScaleLocked")
    h.leaf(0x1CEB60, "SetTimeScaleSuspended")
    mode = W(W_abs(T_GAMEMODE), W_abs(T_GAMEMODE + 4), W_abs(T_PHASE))
    h.entry(0x1F58F0, "GameModePush", mode)
    h.entry(0x1F58A0, "GameModePop", mode)
    h.entry_ret(0x1C3210, "OverlayLoad", W(W_abs(T_OVERLAY), W_abs(T_SYSMODE)))
    # pad: return only; d = pad object, +4 current word, +0x5C previous, +0x24C lock
    h.entry_ret(0x1843A0, "PadUpdate", None,
                W(W_stk(1), W_stk(1, 4), W_stk(1, 0x5C), W_stk(1, 0x24C)), log_entry=False)
    h.entry(0x2F65E0, "PauseRequest")
    h.entry(0x28EDE0, "StateMachineSetState")
    h.entry(0x12A728, "sceCdRead")
    h.entry(0x1D5CF0, "MovieOpen")
    h.entry(0x1D56C0, "MovieShutdown")
    h.entry(0x1D5870, "MovieDrawFrame")


def build_hooks(sets):
    h = Hooks()
    if "kernel" in sets or "sema" in sets:
        for name, (addr, dump) in SYSCALLS.items():
            if name in SEMA_OPS and "sema" not in sets:
                continue
            if name not in SEMA_OPS and "kernel" not in sets:
                continue
            h.syscall_stub(addr, name, dump)
    if "cd" in sets:
        # sceCdRead(lsn, nsec, buf, mode); sceCdLayerSearchFile(fp, name, layer)
        h.entry(0x12A728, "sceCdRead", ("reg", A3, 0))
        h.entry_ret(0x1297E0, "sceCdLayerSearchFile", ("reg", A1, 0), ("stk", 1, 0))
        h.entry_ret(0x12ACD0, "sceCdReadDvdDualInfo", None, ("stk", 1, 0))
    if "sif" in sets:
        h.entry(0x11A4E8, "sceSifCallRpc", ("reg", A0, 0))
    if "pad" in sets:
        # scePadRead(port, slot, buf): v0 = bytes copied; dump the caller's buffer
        h.entry_ret(0x12B800, "scePadRead", None, ("stk", 3, 0))
        h.entry_ret(0x12BCA0, "scePadInfoMode", None, ("abs", PAD_DMA[0] + 0x58))
        h.entry_ret(0x12BA70, "scePadInfoAct", None, ("abs", PAD_DMA[0] + 0x58))
    if "movie" in sets:
        h.entry(0x1D4C90, "MovieVblankHandler", ("abs", 0x004B3218))
        h.entry(0x1D4B20, "MovieFrameQueueSendNext", ("abs", 0x004B32D0 + 0x34))
    if "vif1" in sets:
        h.entry(0x15E070, "Vif1DmaStart", ("reg", A0, 0))
    if "sm" in sets:
        # StateMachineSetState_28ede0(sm, state, run_enter): every UI/title
        # state machine transition (bring-up: title flow timing)
        h.entry(0x28EDE0, "StateMachineSetState")
    if "timing" in sets:
        build_timing_hooks(h)
    if "heap" in sets:
        # newlib malloc family + sbrk (docs/BRINGUP.md "Heap"): v0 on return.
        # Malloc/Memalign log the game caller (ra); the _r entries show the
        # inner calls (memalign_r -> malloc_r, malloc_r -> sbrk).
        h.entry_ret(0x130DD8, "malloc")
        h.entry(0x130E30, "free")
        h.entry_ret(0x130BA8, "memalign")
        h.entry_ret(0x1310D0, "_malloc_r")
        h.entry(0x12F9F8, "_free_r")
        h.entry_ret(0x1337D8, "_realloc_r")
        h.entry_ret(0x116CA0, "sbrk")
    return h


# ------------------------------------------------------------ record parsing
def parse_records(ring, count, last, sites):
    out = []
    lost = 0
    first = last
    if count - last > NREC:
        lost = count - last - NREC
        first = count - NREC
    for seq in range(first, count):
        o = (seq % NREC) * REC
        w = struct.unpack_from("<16I", ring, o)
        tag = w[0]
        if (tag >> 16) != (seq & 0xFFFF):
            out.append({"t": "bad", "seq": seq, "tag": tag})
            continue
        site = tag & 0xFF
        out.append({"t": "r", "seq": seq, "k": KIND.get((tag >> 8) & 0xFF, "?"),
                    "fn": sites.get(site, str(site)), "vbl": w[1], "cnt": w[2],
                    "a": list(w[3:7]), "v0": w[7], "ra": w[8], "sp": w[9], "d": list(w[10:16])})
    return out, lost


# ------------------------------------------------------------ run
def parse_watch(spec):
    name, addr, size = spec.split(":")
    return name, int(addr, 0), int(size, 0)


def run(args, experiment=None):
    sets = set(args.hooks.split(",")) if args.hooks else set()
    hooks = build_hooks(sets)
    for spec in args.fn:
        # --fn NAME:ADDR[:ret][:w=ITEMS] -- log any function's entry (and return).
        # ITEMS (up to six, comma-separated) fill the record's `d` words at entry:
        # `aN` (argument register), `aN+OFF[+OFF..]` (memory through it, each
        # pointer null-checked), `@ADDR[+OFF..]` (pointer chain from a fixed address).
        # `fN` = the bits of FPR $fN (float arguments).  `r=ITEMS` (with :ret):
        # the same items at the return (`f0` = a float result).
        f = spec.split(":")
        dump = dump_ret = None
        for x in f[2:]:
            if x.startswith(("w=", "r=")):
                items = []
                for it in x[2:].split(","):
                    parts = it.split("+")
                    offs = [int(o, 0) for o in parts[1:]]
                    if parts[0].startswith("@"):
                        items.append(W_ptr(int(parts[0][1:], 0), *offs) if offs
                                     else W_abs(int(parts[0][1:], 0)))
                    elif parts[0].startswith("f"):
                        items.append(W_fpr(int(parts[0][1:])))
                    else:
                        items.append(W_reg(4 + int(parts[0][1:]), *offs))
                while len(items) < 6:
                    items.append(W_reg(ZERO))
                if x.startswith("w="):
                    dump = ("words", items[:6])
                else:
                    dump_ret = ("words", items[:6])
        if "ret" in f[2:]:
            hooks.entry_ret(int(f[1], 0), f[0], dump=dump, dump_ret=dump_ret)
        else:
            hooks.entry(int(f[1], 0), f[0], dump=dump)
    exp = experiment(hooks) if experiment else None
    watches = [parse_watch(w) for w in args.watch]
    words = inp.build_table(inp.parse_script(args.input) if args.input else [])
    sticks = inp.build_stick_table(inp.parse_sticks(args.input)) if args.input else None
    tag = os.path.splitext(os.path.basename(args.out))[0]
    e = emu.Emu(speed=args.speed, slot=args.slot, renderer=args.renderer, tag=tag,
                state_slot=args.state_slot, overrides=args.set, memcard=args.memcard)
    out = open(args.out, "w", encoding="utf-8", newline="\n")

    def emit(obj):
        out.write(json.dumps(obj, separators=(",", ":")) + "\n")

    import live
    try:
        pine = e.connect()
        sampler = live.LiveSampler(e.proc.pid, e.log, idle_ms=args.idle_ms)
        if not sampler.find_cpuregs():
            raise RuntimeError("cpuRegs not found")
        sampler.find_cpu_thread()
        blobs = hooks.blobs()
        if exp:
            blobs += exp.blobs()
        emit({"t": "meta", "hooks": sorted(sets), "sites": hooks.sites, "speed": args.speed,
              "input": args.input, "exp": exp.name if exp else None,
              "patches": ["%08x" % p[0] for p in hooks.patches]})

        def sites_loaded():
            return all((pine.read32(p[0]), pine.read32(p[0] + 4)) == tuple(p[2]) for p in hooks.patches)

        # The ELF is loaded in pieces: input.install waits for its own hook
        # site only, so a hook site higher up could still be overwritten by
        # the rest of the load (seen at --speed 0.25: every site above
        # 0x1B0000 was lost). Wait until every site shows the retail code.
        t_end = time.time() + 120
        while hooks.patches and not sites_loaded():
            if time.time() > t_end:
                raise RuntimeError("hook sites never showed the retail code")
            time.sleep(0.002)

        def check_free():
            # the CODE/LOG/DATA area must be zero before we write it, and
            # every hook site must still hold the retail code
            z = pine.read_block(CODE, 0x400) + pine.read_block(LOG, 0x400) + pine.read_block(DATA, 0x400)
            return not any(z) and sites_loaded()
        vbl0 = inp.install(pine, words, sampler=sampler, extra=blobs, precheck=check_free, sticks=sticks)
        bad_sites = ["%08x" % p[0] for p in hooks.patches
                     if (pine.read32(p[0]), pine.read32(p[0] + 4)) != (0x08000000 | ((p[1] >> 2) & 0x03FFFFFF), 0)]
        if bad_sites:
            raise RuntimeError("hook patches not in place after install: %s" % bad_sites)
        emit({"t": "installed", "vbl": vbl0})
        print("hooks installed at game vbl", vbl0, "sites", len(hooks.sites), flush=True)
        base = sampler.addr["ee"]
        clock = emu.FrameClock()
        last = 0
        due = 0
        states = sorted(args.state_at)
        locs = sorted(args.locate_vu_at)
        vu_found = None
        t0 = time.time()
        exp_state = 0

        def wanted(c):
            if not clock.wanted(c):
                return False
            if clock.last is None or args.every <= 1:
                return True
            d = emu._delta(c, clock.last)
            return clock.frame + d / emu.EE_CYCLES_PER_VSYNC >= due - 0.5

        cap = {"queue": sorted(args.capture_at), "left": 0, "slots": [], "k": 0}
        from pine import Pine
        save_pine = Pine(args.slot)

        def cap_save():
            # Issued from a helper thread while the CPU thread is frozen at a
            # vsync: PCSX2 services the request when it runs again.
            slot = 1 + cap["k"] % 9
            cap["k"] += 1
            cap["slots"].append(slot)
            import threading
            threading.Thread(target=save_pine.save_state, args=(slot,), daemon=True).start()

        vc = {"queue": sorted(args.vucap_at), "left": 0, "frames": []}

        def vu_read():
            f = vu_found
            vu0c = f["vu0code"]
            regs = f["vu0regs"][0]
            hw = [pine.read32(0x10003C00 + 0x10 * k) for k in range(0x18)]
            d1 = [pine.read32(0x10009000 + 0x10 * k) for k in range(8)]
            return {"cycle": sampler.cycle64() & 0xFFFFFFFF,
                    "ee": sampler.p.read(base, 0x2000000),
                    "vublock": sampler.p.read(vu0c, 0xA000),     # vu0 code, vu0 mem, vu1 code, vu1 mem
                    "regs": sampler.p.read(regs, 0xC00),
                    "vif1": struct.pack("<24I", *hw), "d1": struct.pack("<8I", *d1)}

        def read():
            if vc["left"] > 0 and vu_found:
                vc["frames"].append(vu_read())
                vc["left"] -= 1
            if cap["left"] > 0:
                cap_save()
                cap["left"] -= 1
            hdr = sampler.p.read(base + LOG, 16)
            ring = sampler.p.read(base + RING, NREC * REC)
            vbl = struct.unpack("<I", sampler.p.read(base + VBL, 4))[0]
            w = {n: sampler.p.read(base + a, s).hex() for n, a, s in watches}
            ex = sampler.p.read(base + DATA, 0x1000) if exp else b""
            return hdr, ring, vbl, w, ex

        nsamp = 0
        cd_reads = []
        drained_at = time.time()
        while True:
            r = sampler.frozen_call(wanted, read, timeout=args.drain_s or args.idle_timeout)
            if r is None and args.drain_s:
                # no vsync idle for drain_s: drain the ring at an arbitrary
                # point so it cannot overflow (long FMV/event stretches). The
                # newest records may still be in flight; leave the last few.
                sampler.cpu.suspend()
                try:
                    hdr = sampler.p.read(base + LOG, 16)
                    ring = sampler.p.read(base + RING, NREC * REC)
                    vbl = struct.unpack("<I", sampler.p.read(base + VBL, 4))[0]
                finally:
                    sampler.cpu.resume()
                count = struct.unpack_from("<I", hdr)[0]
                safe = max(last, count - 4)
                recs, lost = parse_records(ring, safe, last, hooks.sites)
                if lost:
                    emit({"t": "lost", "n": lost, "frame": clock.frame, "vbl": vbl})
                for rec in recs:
                    emit(rec)
                emit({"t": "drain", "vbl": vbl, "count": count})
                if safe != last:
                    drained_at = time.time()
                last = safe
                if time.time() - drained_at > args.idle_timeout:
                    raise RuntimeError("no vsync idle and no new records")
                if args.stop_vbl and vbl >= args.stop_vbl:
                    break
                continue
            if r is None:
                raise RuntimeError("no vsync idle")
            drained_at = time.time()
            cyc, (hdr, ring, vbl, w, ex) = r
            for frame, _ in clock.offer(cyc, None, vbl):
                pass
            frame = clock.frame
            due = (frame // args.every + 1) * args.every
            if cap["left"] > 0 or vc["left"] > 0:
                due = frame + 1
            elif vc["frames"]:
                save_vu_frames(vc["frames"], args, emit)
                vc["frames"] = []
            if vc["queue"] and vbl >= vc["queue"][0] and vc["left"] == 0 and vu_found:
                vc["queue"].pop(0)
                vc["left"] = args.vucap_frames
                due = frame + 1
            if cap["left"] > 0:
                due = frame + 1
            elif cap["slots"]:
                collect_captures(e, cap["slots"], args, emit, vbl)
                cap["slots"] = []
            if cap["queue"] and vbl >= cap["queue"][0] and cap["left"] == 0:
                cap["queue"].pop(0)
                clear_slots(e)
                cap["left"] = args.capture_frames
                due = frame + 1
            count, est = struct.unpack_from("<II", hdr)
            recs, lost = parse_records(ring, count, last, hooks.sites)
            if lost:
                emit({"t": "lost", "n": lost, "frame": frame})
            for rec in recs:
                emit(rec)
                if rec.get("fn") == "sceCdRead" and exp_state >= 1:
                    cd_reads.append(rec)
            last = count
            emit({"t": "s", "frame": frame, "vbl": vbl, "cyc": cyc & 0xFFFFFFFF, "w": w})
            nsamp += 1
            if exp:
                if est != exp_state:
                    emit({"t": "exp_state", "frame": frame, "vbl": vbl, "state": est})
                    exp_state = est
                    if est == 3:
                        emit({"t": "exp_done", "frame": frame, "vbl": vbl, "data": ex.hex()})
                        print("experiment done at vbl", vbl, flush=True)
                        exp.report(ex)
                        if cd_reads:
                            dump_cd_buffers(sampler, base, cd_reads, args, emit)
                        if args.stop_after_exp:
                            break
                if est == 0 and vbl >= args.exp_at:
                    sampler.frozen_call(lambda c: True, lambda: pine.write32(LOG + 4, 1), timeout=30)
                    exp_state = 1
            if locs and vbl >= locs[0]:
                locs.pop(0)
                vu_found = locate_vu(sampler, e, pine, args, emit, vbl)
            if states and vbl >= states[0]:
                states.pop(0)
                take_states(e, pine, args, emit, vbl)
            if nsamp % 50 == 0:
                print("frame %d vbl %d recs %d %.0fs" % (frame, vbl, count, time.time() - t0), flush=True)
            if args.stop_vbl and vbl >= args.stop_vbl:
                break
        emit({"t": "end", "count": last})
    finally:
        out.close()
        e.stop()


def _slot_path(e, slot):
    for f in os.listdir(e.sstates):
        if f.endswith(".%02d.p2s" % slot):
            return os.path.join(e.sstates, f)
    return None


def clear_slots(e):
    for slot in range(1, 10):
        p = _slot_path(e, slot)
        if p:
            os.remove(p)


def collect_captures(e, slots, args, emit, vbl):
    """Wait for the capture window's savestates and keep them, named by the
    EE cycle they were taken at (consecutive vsyncs differ by ~4,920,120)."""
    os.makedirs(args.state_dir, exist_ok=True)
    t_end = time.time() + 300
    got = {}
    while time.time() < t_end and len(got) < len(set(slots)):
        for slot in set(slots) - set(got):
            p = _slot_path(e, slot)
            if not p:
                continue
            try:
                snap = emu.Snapshot(p)
            except (zipfile.BadZipFile, KeyError, OSError, EOFError):
                continue
            got[slot] = (p, snap)
        time.sleep(0.2)
    for slot, (p, snap) in sorted(got.items(), key=lambda kv: kv[1][1].ee_cycle32):
        gv = struct.unpack_from("<I", snap.ee, VBL)[0]
        dst = os.path.join(args.state_dir, "cap_v%05d_c%08x.p2s" % (gv, snap.ee_cycle32))
        shutil.copyfile(p, dst)
        emit({"t": "capture", "slot": slot, "cyc": snap.ee_cycle32, "game_vbl": gv, "file": dst})
        print("capture", dst, flush=True)
    if len(got) < len(set(slots)):
        emit({"t": "capture_missing", "slots": sorted(set(slots) - set(got))})


def dump_cd_buffers(sampler, base, reads, args, emit):
    """Save the EE buffers of the sceCdRead calls made during an experiment
    (read while frozen at a vsync after the experiment finished)."""
    d = os.path.join(emu.PORT, "out", "captures", "cd")
    os.makedirs(d, exist_ok=True)

    def grab():
        out = []
        for r in reads:
            lsn, n, buf = r["a"][0], r["a"][1], r["a"][2] & 0x1FFFFFFF
            size = min(n, 512) * 2048
            out.append((r, sampler.p.read(base + buf, size)))
        return out
    res = sampler.frozen_call(lambda c: True, grab, timeout=60)
    for r, data in (res[1] if res else []):
        f = os.path.join(d, "%s_lsn%d_n%d_seq%d.bin" % (os.path.splitext(os.path.basename(args.out))[0],
                                                         r["a"][0], r["a"][1], r["seq"]))
        open(f, "wb").write(data)
        emit({"t": "cdbuf", "seq": r["seq"], "lsn": r["a"][0], "n": r["a"][1], "file": f})


def save_vu_frames(frames, args, emit):
    """Raw per-vsync VU/VIF snapshots (consecutive vsyncs) -> out/captures/raw."""
    import zlib
    d = os.path.join(emu.PORT, "out", "captures", "raw")
    os.makedirs(d, exist_ok=True)
    for fr in frames:
        vbl = struct.unpack_from("<I", fr["ee"], VBL)[0]
        f = os.path.join(d, "%s_v%05d_c%08x.zip" % (os.path.splitext(os.path.basename(args.out))[0], vbl, fr["cycle"]))
        with zipfile.ZipFile(f, "w", zipfile.ZIP_DEFLATED, compresslevel=1) as z:
            for k, v in fr.items():
                if k != "cycle":
                    z.writestr(k + ".bin", v)
            z.writestr("cycle.txt", "%d" % fr["cycle"])
        emit({"t": "vuframe", "vbl": vbl, "cycle": fr["cycle"], "file": f})
    print("saved %d vu frames" % len(frames), flush=True)


def locate_vu(sampler, e, pine, args, emit, vbl):
    """Take one savestate (requested while running), freeze at the next
    vsync and find the state's VU1 memories, VU register files and EE
    hardware page in PCSX2's process memory. Returns host addresses."""
    import vucap
    import live
    args.state_count = 1
    take_states(e, pine, args, emit, vbl)
    path = sorted(os.listdir(args.state_dir), key=lambda f: os.path.getmtime(os.path.join(args.state_dir, f)))[-1]
    st = vucap.state_parts(os.path.join(args.state_dir, path))
    snap_cyc = emu.Snapshot(os.path.join(args.state_dir, path)).ee_cycle32
    found = {}

    def search():
        vu = sampler.addr["vu"]
        blk = sampler.p.read(vu, 0x100000)
        for name in ("vu1code", "vu1mem", "vu0code", "vu0mem"):
            i = blk.find(st[name]) if any(st[name]) else -1
            found[name] = (vu + i) if i >= 0 else None
        # EE hardware page: in the EE region, at a 64 KB boundary; match the
        # VIF1 and DMA channel 1 register blocks
        ee = sampler.addr["ee"]
        want = st["hw"][0x3C00:0x3D80]
        big = sampler.p.read(ee, 0x8F00000)
        hits = []
        i = big.find(want)
        while i >= 0 and len(hits) < 8:
            if (i - 0x3C00) % 0x1000 == 0:
                hits.append(ee + i - 0x3C00)
            i = big.find(want, i + 1)
        found["hw"] = hits
        # VU register files: writable image memory, like cpuRegs
        vf0 = st["vu0regs"][:0x200]
        hits = []
        for b, size, state_, prot, typ in sampler.p.regions():
            if state_ != live.MEM_COMMIT or typ != live.MEM_IMAGE or prot not in (live.PAGE_READWRITE, live.PAGE_WRITECOPY):
                continue
            try:
                blob = sampler.p.read(b, size)
            except OSError:
                continue
            j = blob.find(vf0)
            while j >= 0:
                hits.append(b + j)
                j = blob.find(vf0, j + 1)
        found["vu0regs"] = hits
        dd = os.path.join(args.state_dir, "locate_dump")
        os.makedirs(dd, exist_ok=True)
        if found["vu0code"]:
            open(os.path.join(dd, "vublock.bin"), "wb").write(sampler.p.read(found["vu0code"] - 0x10000, 0x40000))
        if hits:
            open(os.path.join(dd, "vuregs.bin"), "wb").write(sampler.p.read(hits[0] - 0x1000, 0x4000))
        hw = b"".join(struct.pack("<I", pine.read32(0x10003C00 + 0x10 * k)) for k in range(0x18))
        hw += b"".join(struct.pack("<I", pine.read32(0x10009000 + 0x10 * k)) for k in range(4))
        open(os.path.join(dd, "hw_pine.bin"), "wb").write(hw)
        return sampler.cycle64()
    r = sampler.frozen_call(lambda c: True, search, timeout=60)
    found["freeze_cycle"] = (r[1] & 0xFFFFFFFF) if r else None
    found["state_cycle"] = snap_cyc
    emit({"t": "vu_locate", "found": {k: (v if not isinstance(v, int) else v) for k, v in found.items()},
          "state": path})
    print("vu locate", found, flush=True)
    return found


def take_states(e, pine, args, emit, vbl):
    """Ask for --state-count savestates in a row and keep them."""
    os.makedirs(args.state_dir, exist_ok=True)
    for k in range(args.state_count):
        old = e._state_path()
        if old:
            os.remove(old)
        pine.save_state(e.state_slot)
        t_end = time.time() + 120
        while time.time() < t_end:
            p = e._state_path()
            if p:
                try:
                    with zipfile.ZipFile(p) as z:
                        z.testzip()
                    break
                except (zipfile.BadZipFile, OSError, EOFError):
                    pass
            time.sleep(0.005)
        else:
            raise RuntimeError("savestate did not appear")
        snap = emu.Snapshot(p)
        dst = os.path.join(args.state_dir, "v%05d_%d_c%08x.p2s" % (vbl, k, snap.ee_cycle32))
        shutil.copyfile(p, dst)
        emit({"t": "state", "vbl_req": vbl, "k": k, "cyc": snap.ee_cycle32,
              "game_vbl": struct.unpack_from("<I", snap.ee, VBL)[0], "file": dst})
        print("savestate", dst, flush=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True)
    ap.add_argument("--hooks", default="", help="comma list: kernel,sema,cd,sif,pad,movie,vif1,heap,sm,timing")
    ap.add_argument("--exp", default=None, help="experiment name (probe_exp.py)")
    ap.add_argument("--exp-at", type=int, default=1700, help="game vbl at which to trigger the experiment")
    ap.add_argument("--stop-after-exp", action="store_true")
    ap.add_argument("--watch", action="append", default=[], metavar="NAME:ADDR:SIZE")
    ap.add_argument("--fn", action="append", default=[], metavar="NAME:ADDR[:ret]",
                    help="hook any function entry (+ return with :ret)")
    ap.add_argument("--input", default=os.path.join(HERE, "goldens", "newgame_battle.input.txt"))
    ap.add_argument("--memcard", action="store_true", default=True)
    ap.add_argument("--speed", type=float, default=0.5)
    ap.add_argument("--every", type=int, default=10)
    ap.add_argument("--idle-ms", type=float, default=3.0)
    ap.add_argument("--idle-timeout", type=float, default=90.0)
    ap.add_argument("--drain-s", type=float, default=0.0,
                    help="if no vsync idle comes for this many seconds, drain the record ring "
                         "at any point (keeps high-rate hook sets such as timing from overflowing)")
    ap.add_argument("--stop-vbl", type=int, default=0)
    ap.add_argument("--state-at", type=int, action="append", default=[])
    ap.add_argument("--state-count", type=int, default=2)
    ap.add_argument("--capture-at", type=int, action="append", default=[],
                    help="game vbl: save a savestate at each of --capture-frames consecutive vsyncs")
    ap.add_argument("--capture-frames", type=int, default=4)
    ap.add_argument("--locate-vu-at", type=int, action="append", default=[])
    ap.add_argument("--vucap-at", type=int, action="append", default=[],
                    help="game vbl: snapshot EE RAM + VU1 + VIF1 at --vucap-frames consecutive vsyncs")
    ap.add_argument("--vucap-frames", type=int, default=8)
    ap.add_argument("--state-dir", default=os.path.join(emu.PORT, "out", "captures", "states"))
    ap.add_argument("--renderer", type=int, default=11)
    ap.add_argument("--slot", type=int, default=28020)
    ap.add_argument("--state-slot", type=int, default=5)
    ap.add_argument("--set", action="append", default=[])
    args = ap.parse_args()
    experiment = None
    if args.exp:
        import probe_exp
        experiment = probe_exp.EXPERIMENTS[args.exp]
    run(args, experiment)


if __name__ == "__main__":
    main()

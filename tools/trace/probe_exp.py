# SPDX-License-Identifier: CC0-1.0
"""In-guest kernel experiments for probe.py (docs/VALIDATION.md, item 2).

PCSX2 runs the real BIOS EE kernel, so a short program run inside the game
on PCSX2 measures the retail kernel's behaviour directly. The program is
called once, from the game's main thread, at the entry of PadReadData_184df0
when the harness sets LOG+4 = 1 (probe.py --exp kern --exp-at VBL). It saves
all GPRs (sq), runs, restores them, sets LOG+4 = 3 and returns into the game.

It uses the libkernl syscall numbers (census/platform_ee_syscalls.tsv) as
inline `addiu v1,N; syscall`, exactly like the game's stubs.

Results: RES words at DATA, an event log at EVT (code, COP0 Count, seq,
extra), printed by report().
"""
import struct

from mips import (ZERO, AT, V0, V1, A0, A1, A2, A3, T0, T1, T2, T3, T4, T5, T6, T7,
                  S0, S1, S2, S3, S4, S5, S6, S7, T8, T9, GP, SP, FP, RA, hi, lo)
import probe

DATA = probe.DATA
RES = DATA + 0x000          # 128 result words
SEQ = DATA + 0x200
VAR = DATA + 0x210          # named variables, 4 bytes each
EVT = DATA + 0x400          # 128 x 16-byte events
NEVT = 128
PARAM = DATA + 0xC00        # scratch structs
SAVE = DATA + 0x1000        # 32 x 16 bytes GPR save area
GAME_GP = 0x00485170        # gp the game gives its threads (MoviePlayerStart_1d5b50)
STK = probe.STACKS

SYS = {"CreateThread": 0x20, "StartThread": 0x22, "TerminateThread": 0x25, "DeleteThread": 0x21,
       "ChangeThreadPriority": 0x29, "GetThreadId": 0x2F, "ReferThreadStatus": 0x30,
       "SleepThread": 0x32, "CreateSema": 0x40, "DeleteSema": 0x41, "SignalSema": 0x42,
       "iSignalSema": -0x43, "WaitSema": 0x44, "PollSema": 0x45, "ReferSemaStatus": 0x47,
       "AddIntcHandler": 0x10, "RemoveIntcHandler": 0x11, "_EnableIntc": 0x14}

VARS = ["S2", "S3", "S4", "S5", "ARM", "R1", "CNT1", "CNT2", "CNT3", "TA1", "TA2", "TH", "TA3",
        "H1ID", "H2ID", "H3ID", "H4ID", "PM"]


def var(name):
    return VAR + 4 * VARS.index(name)


EV_NAMES = {
    0x10: "M: before StartThread(TA1, prio=M)", 0x11: "M: after StartThread(TA1)",
    0x12: "M: after ChangeThreadPriority(self, same prio)", 0x13: "M: before StartThread(TH, prio=M-1)",
    0x14: "M: after StartThread(TH)", 0x15: "M: after StartThread(TA2); spin starts (ARM=1)",
    0x16: "M: spin ended (3 frames of Count, no syscalls)", 0x17: "M: TA1+TA2 both signalled S4",
    0x20: "M: DI done, before StartThread(TA3) + WaitSema(S3)", 0x21: "M: woke from WaitSema(S3) (extra=Status)",
    0x30: "M: chain phase R1=0", 0x31: "M: chain phase R1=1", 0x32: "M: chain phase R1=-1", 0x33: "M: chain test done",
    0xA1: "TA1 runs", 0xA2: "TA2 runs", 0xA3: "TA3 runs (extra=Status)", 0xA4: "TA3 after SignalSema(S3)",
    0xB0: "TH woke (S2 from VBLANK handler H4)", 0xB4: "H4 VBLANK_START (ARM set -> iSignalSema S2)",
    0xC1: "H1 VBLANK_START head (extra=R1 returned)", 0xC2: "H2 VBLANK_START tail", 0xC3: "H3 VBLANK_END",
}


def ev(a, code, extra=None):
    """Event (code, COP0 Count, seq, extra reg). Clobbers t4-t7 only."""
    a.lui(T4, hi(SEQ))
    a.lw(T5, lo(SEQ), T4)
    a.addiu(T6, T5, 1)
    a.sw(T6, lo(SEQ), T4)
    a.andi(T6, T5, NEVT - 1)
    a.sll(T6, T6, 4)
    a.li(T7, EVT)
    a.addu(T6, T6, T7)
    a.sw(T5, 8, T6)
    a.mfc0(T7, 9)
    a.sw(T7, 4, T6)
    if extra is not None:
        a.sw(extra, 12, T6)
    a.addiu(T7, ZERO, code)
    a.sw(T7, 0, T6)


def sysc(a, name, *args):
    """Inline syscall; args are registers or ints. Result in v0."""
    for reg, v in zip((A0, A1, A2, A3), args):
        if isinstance(v, tuple):          # ('var', name) -> load variable
            a.lwa(reg, var(v[1]))
        elif isinstance(v, str):          # label address
            a.li(reg, 0)
            raise ValueError
        elif v is None:
            pass
        elif isinstance(v, int) and v >= 1 << 32:
            a.li(reg, v - (1 << 32))
        else:
            a.li(reg, v)
    a.sys(SYS[name])


def res(a, idx, reg=V0):
    a.swa(reg, RES + 4 * idx)


class Experiment:
    """Base: installs the trigger at PadReadData_184df0's entry; subclasses
    emit `exp_main` (called with jal, returns with jr ra)."""
    name = "?"
    hook_addr = 0x00184DF0          # PadReadData_184df0 (main thread, every frame)

    def install_trigger(self, hooks):
        a = hooks.a
        w0, w1 = hooks._orig(self.hook_addr)
        hooks.entry(0x0015DF20, "GfxVblankStartHandler")   # libgraph's vsync callback
        # --- trigger trampoline
        t = a.pc
        a.lui(T4, probe.LOG >> 16)
        a.lw(T5, 4, T4)
        a.addiu(T6, ZERO, 1)
        a.bne(T5, T6, "exp_skip")
        a.addiu(T6, ZERO, 2)
        a.sw(T6, 4, T4)
        a.li(T4, SAVE)
        for r in range(1, 32):
            if r not in (T4, 26, 27):
                a.sq(r, 16 * r, T4)
        a.jal("exp_main")
        a.li(T4, SAVE)
        for r in range(1, 32):
            if r not in (T4, 26, 27):
                a.lq(r, 16 * r, T4)
        a.lui(T4, probe.LOG >> 16)
        a.addiu(T6, ZERO, 3)
        a.sw(T6, 4, T4)
        a.label("exp_skip")
        a.w(w0)
        a.w(w1)
        a.j(self.hook_addr + 8)
        hooks._patch(self.hook_addr, t, (w0, w1))

    def blobs(self):
        return []

    def report(self, data):
        pass


class CdLayerExperiment(Experiment):
    """Call the game's own CdDiscSelect_1c3090(1): reopens the DATA1_* archives
    on layer 1 and relocates the overlays (sceCdLayerSearchFile(.., 1) +
    sceCdRead of the .HD6). Run with --hooks cd so every search/read is logged;
    the harness then dumps the read buffers (probe.py)."""
    name = "cdlayer"

    def __init__(self, hooks):
        self.h = hooks
        self.install_trigger(hooks)
        a = hooks.a
        a.label("exp_main")
        a.move(S7, RA)
        a.li(A0, 1)
        a.jal(0x001C3090)
        res(a, 0)
        a.move(RA, S7)
        a.jr(RA)
        a.nop()

    def report(self, data):
        print("CdDiscSelect(1) returned", struct.unpack_from("<i", data, 0)[0])


class KernExperiment(Experiment):
    name = "kern"

    def __init__(self, hooks):
        self.h = hooks
        a = hooks.a
        self.install_trigger(hooks)
        self._threads(a)
        self._handlers(a)
        self._main(a)

    # ---------------------------------------------------------- threads
    def _threads(self, a):
        def sleeper(label, code, signal_var=None):
            a.label(label)
            ev(a, code)
            if signal_var:
                sysc(a, "SignalSema", ("var", signal_var))
            a.label(label + "_z")
            sysc(a, "SleepThread")
            a.b(label + "_z")
        sleeper("th_a1", 0xA1, "S4")
        sleeper("th_a2", 0xA2, "S4")
        # TH: wait on S2 forever, log each wake
        a.label("th_h")
        sysc(a, "WaitSema", ("var", "S2"))
        ev(a, 0xB0)
        a.b("th_h")
        # TA3: report Status, signal S3
        a.label("th_a3")
        a.mfc0(S0, 12)
        ev(a, 0xA3, S0)
        sysc(a, "SignalSema", ("var", "S3"))
        ev(a, 0xA4)
        a.label("th_a3_z")
        sysc(a, "SleepThread")
        a.b("th_a3_z")

    # ---------------------------------------------------------- INTC handlers
    def _handlers(self, a):
        # H4: VBLANK_START at head; when ARM != 0 -> iSignalSema(S2)
        a.label("h4")
        a.lwa(T0, var("ARM"))
        a.beq(T0, ZERO, "h4_out")
        ev(a, 0xB4)
        a.lwa(A0, var("S2"))
        a.sys(SYS["iSignalSema"])
        a.label("h4_out")
        a.sync()
        a.ei()
        a.jr(RA)
        a.move(V0, ZERO)
        # H1: head handler, returns R1; counts; signals S5 every call
        a.label("h1")
        a.lwa(T0, var("R1"))
        ev(a, 0xC1, T0)
        a.lwa(T0, var("CNT1"))
        a.addiu(T0, T0, 1)
        a.swa(T0, var("CNT1"))
        a.lwa(A0, var("S5"))
        a.sys(SYS["iSignalSema"])
        a.lwa(V0, var("R1"))
        a.sync()
        a.ei()
        a.jr(RA)
        a.nop()
        # H2: tail handler
        a.label("h2")
        ev(a, 0xC2)
        a.lwa(T0, var("CNT2"))
        a.addiu(T0, T0, 1)
        a.swa(T0, var("CNT2"))
        a.sync()
        a.ei()
        a.jr(RA)
        a.move(V0, ZERO)
        # H3: VBLANK_END
        a.label("h3")
        ev(a, 0xC3)
        a.lwa(T0, var("CNT3"))
        a.addiu(T0, T0, 1)
        a.swa(T0, var("CNT3"))
        a.sync()
        a.ei()
        a.jr(RA)
        a.move(V0, ZERO)

    # ---------------------------------------------------------- main program
    def _sema(self, a, maxc, init, out_var=None, res_idx=None):
        p = PARAM
        a.li(T0, p)
        a.sw(ZERO, 0, T0)
        a.li(T1, maxc)
        a.sw(T1, 4, T0)
        a.li(T1, init)
        a.sw(T1, 8, T0)
        a.sw(ZERO, 12, T0)
        a.sw(ZERO, 16, T0)
        a.sw(ZERO, 20, T0)
        a.move(A0, T0)
        a.sys(SYS["CreateSema"])
        if out_var:
            a.swa(V0, var(out_var))
        if res_idx is not None:
            res(a, res_idx)

    def _thread(self, a, entry, prio_reg_delta, stack_k, out_var, res_idx):
        p = PARAM + 0x40
        a.li(T0, p)
        a.sw(ZERO, 0, T0)
        a.li(T1, 0)
        self._la(a, T1, entry)
        a.sw(T1, 4, T0)
        a.li(T1, STK + stack_k * 0x2000)
        a.sw(T1, 8, T0)
        a.li(T1, 0x2000)
        a.sw(T1, 12, T0)
        a.li(T1, GAME_GP)
        a.sw(T1, 16, T0)
        a.lwa(T1, var("PM"))
        a.addiu(T1, T1, prio_reg_delta)
        a.sw(T1, 20, T0)
        a.sw(T1, 24, T0)
        a.sw(ZERO, 28, T0)
        a.sw(ZERO, 32, T0)
        a.move(A0, T0)
        a.sys(SYS["CreateThread"])
        a.swa(V0, var(out_var))
        res(a, res_idx)

    def _la(self, a, reg, label):
        # address of a label, patched after assembly (labels resolve in assemble())
        a.fix.append((len(a.code), "hi", label))
        a.lui(reg, 0)
        a.fix.append((len(a.code), "lo", label))
        a.addiu(reg, reg, 0)

    def _main(self, a):
        a.label("exp_main")
        a.move(S7, RA)
        # ---- A. semaphores and ids
        a.sys(SYS["GetThreadId"])
        res(a, 18)
        a.move(A0, V0)
        a.li(A1, PARAM + 0x80)
        a.sys(SYS["ReferThreadStatus"])
        res(a, 19)
        a.lwa(T0, PARAM + 0x80 + 0x18)
        res(a, 20, T0)
        a.swa(T0, var("PM"))
        a.lwa(T0, PARAM + 0x80 + 0x14)
        res(a, 21, T0)
        # max 1, init 1, then signal at max
        self._sema(a, 1, 1, res_idx=0)
        a.move(S0, V0)
        a.move(A0, S0)
        a.sys(SYS["SignalSema"])
        res(a, 1)
        a.move(A0, S0)
        a.li(A1, PARAM + 0xC0)
        a.sys(SYS["ReferSemaStatus"])
        res(a, 2)
        a.lwa(T0, PARAM + 0xC0)
        res(a, 3, T0)
        a.lwa(T0, PARAM + 0xC4)
        res(a, 4, T0)
        a.move(A0, S0)
        a.sys(SYS["PollSema"])
        res(a, 5)
        a.move(A0, S0)
        a.sys(SYS["PollSema"])
        res(a, 6)
        a.move(A0, S0)
        a.sys(SYS["DeleteSema"])
        res(a, 7)
        # max 2, init 0, signal x3
        self._sema(a, 2, 0, res_idx=8)
        a.move(S0, V0)
        for k in range(3):
            a.move(A0, S0)
            a.sys(SYS["SignalSema"])
            res(a, 9 + k)
        a.move(A0, S0)
        a.li(A1, PARAM + 0xC0)
        a.sys(SYS["ReferSemaStatus"])
        a.lwa(T0, PARAM + 0xC0)
        res(a, 12, T0)
        a.move(A0, S0)
        a.sys(SYS["DeleteSema"])
        # id reuse: a, b, c; delete b; d
        self._sema(a, 1, 0, res_idx=13)
        a.move(S1, V0)
        self._sema(a, 1, 0, res_idx=14)
        a.move(S2, V0)
        self._sema(a, 1, 0, res_idx=15)
        a.move(S3, V0)
        a.move(A0, S2)
        a.sys(SYS["DeleteSema"])
        self._sema(a, 1, 0, res_idx=16)
        a.move(S2, V0)
        for r in (S1, S2, S3):
            a.move(A0, r)
            a.sys(SYS["DeleteSema"])
        # ---- B. scheduling
        self._sema(a, 64, 0, "S2", 22)
        self._sema(a, 1, 0, "S3", 23)
        self._sema(a, 8, 0, "S4", 24)
        self._sema(a, 64, 0, "S5", 25)
        self._thread(a, "th_a1", 0, 0, "TA1", 26)
        self._thread(a, "th_a2", 0, 1, "TA2", 27)
        self._thread(a, "th_h", -1, 2, "TH", 28)
        self._thread(a, "th_a3", 0, 3, "TA3", 29)
        a.li(A0, 2)
        self._la(a, A1, "h4")
        a.li(A2, 0)
        a.sys(SYS["AddIntcHandler"])
        a.swa(V0, var("H4ID"))
        res(a, 32)
        ev(a, 0x10)
        sysc(a, "StartThread", ("var", "TA1"), 0)
        ev(a, 0x11)
        a.sys(SYS["GetThreadId"])
        a.move(A0, V0)
        a.lwa(A1, var("PM"))
        a.sys(SYS["ChangeThreadPriority"])
        res(a, 33)
        ev(a, 0x12)
        ev(a, 0x13)
        sysc(a, "StartThread", ("var", "TH"), 0)
        ev(a, 0x14)
        sysc(a, "StartThread", ("var", "TA2"), 0)
        a.addiu(T0, ZERO, 1)
        a.swa(T0, var("ARM"))
        ev(a, 0x15)
        a.mfc0(S6, 9)
        a.li(S5, 3 * 4920120)
        a.label("spin")
        a.mfc0(T0, 9)
        a.subu(T0, T0, S6)
        a.sltu(T1, T0, S5)
        a.bne(T1, ZERO, "spin")
        ev(a, 0x16)
        a.swa(ZERO, var("ARM"))
        sysc(a, "WaitSema", ("var", "S4"))
        sysc(a, "WaitSema", ("var", "S4"))
        ev(a, 0x17)
        # ---- C. EIE across a blocking WaitSema
        a.mfc0(T0, 12)
        res(a, 34, T0)
        a.di()
        a.sync()
        a.mfc0(T0, 12)
        res(a, 35, T0)
        ev(a, 0x20, T0)
        sysc(a, "StartThread", ("var", "TA3"), 0)
        sysc(a, "WaitSema", ("var", "S3"))
        a.mfc0(T0, 12)
        res(a, 36, T0)
        ev(a, 0x21, T0)
        a.ei()
        # ---- D. INTC chain: H1 head (next=0), H2 tail (next=-1), H3 VBLANK_END
        a.swa(ZERO, var("R1"))
        a.li(A0, 2)
        self._la(a, A1, "h1")
        a.li(A2, 0)
        a.sys(SYS["AddIntcHandler"])
        a.swa(V0, var("H1ID"))
        res(a, 37)
        a.li(A0, 2)
        self._la(a, A1, "h2")
        a.li(A2, -1)
        a.sys(SYS["AddIntcHandler"])
        a.swa(V0, var("H2ID"))
        res(a, 38)
        a.li(A0, 3)
        self._la(a, A1, "h3")
        a.li(A2, -1)
        a.sys(SYS["AddIntcHandler"])
        a.swa(V0, var("H3ID"))
        res(a, 39)
        a.li(A0, 3)
        a.sys(SYS["_EnableIntc"])
        res(a, 40)
        for code, rv in ((0x30, 0), (0x31, 1), (0x32, -1), (0x30, 0)):
            a.li(T0, rv)
            a.swa(T0, var("R1"))
            ev(a, code)
            for _ in range(6):
                sysc(a, "WaitSema", ("var", "S5"))
        ev(a, 0x33)
        for v, cause in (("H1ID", 2), ("H2ID", 2), ("H3ID", 3), ("H4ID", 2)):
            a.li(A0, cause)
            a.lwa(A1, var(v))
            a.sys(SYS["RemoveIntcHandler"])
        # ---- cleanup threads/semas
        for v in ("TA1", "TA2", "TH", "TA3"):
            sysc(a, "TerminateThread", ("var", v))
            sysc(a, "DeleteThread", ("var", v))
        for v in ("S2", "S3", "S4", "S5"):
            sysc(a, "DeleteSema", ("var", v))
        a.move(RA, S7)
        a.jr(RA)
        a.nop()

    def blobs(self):
        return []

    def report(self, data):
        r = struct.unpack_from("<128i", data, 0)
        print("RES", " ".join("%d:%d" % (i, v) for i, v in enumerate(r[:48]) if v or i < 41))
        evs = []
        for k in range(NEVT):
            code, cnt, seq, extra = struct.unpack_from("<4I", data, 0x400 + 16 * k)
            if code:
                evs.append((seq, code, cnt, extra))
        evs.sort()
        t0 = evs[0][2] if evs else 0
        for seq, code, cnt, extra in evs:
            print("  ev %3d %02x  dCount=%11d extra=%08x  %s" % (seq, code, (cnt - t0) & 0xFFFFFFFF, extra,
                                                              EV_NAMES.get(code, "")))


EXPERIMENTS = {"kern": KernExperiment, "cdlayer": CdLayerExperiment}

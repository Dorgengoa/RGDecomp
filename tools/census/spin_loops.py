#!/usr/bin/env python3
"""Spin / busy-wait loop census (docs/SPIN.md) -> census/spin_loops.tsv.

The EE kernel HLE (docs/KERNEL.md) is non-preemptive and its virtual clock
moves only at kernel calls, ps2k_poll/ps2k_charge, or when every thread is
blocked.  A guest loop that waits for memory or a hardware register to change,
with nothing inside that blocks, therefore never sees the change.  This census
finds every such loop in the six retail images and says who would change the
value it waits on.

Ground truth is the RETAIL CODE (all of MAIN incl. the SDK band and the ~186
MAIN functions that the pinned snapshot still has only as asm, plus the five
overlays).  Per function:

  loops      every backward branch (b/beq/bne/bgez../bc0/bc1/bc2/j) whose
             target lies inside the function; back-edges to the same head
             are one loop, [head, last back-edge + delay slot].
  yields     a call graph from decoded jal/j edges (tools/census/platform
             common.cached()) plus the `syscall` number of every stub gives
             each function a yield level: BLOCK (reaches WaitSema 0x44 /
             SleepThread 0x32 / Exit*), ROTATE (RotateThreadReadyQueue),
             KCALL (any other syscall: a delivery point but NO time passes),
             NONE.  A loop yields if a call in its body reaches BLOCK; the
             call is `every` when no branch inside the body skips it.
  polled     register-taint over the loop body: each load gets a label by
             its address (constant -> hw register / GS / scratchpad /
             global; invariant base register -> `ptr`; a base written in the
             loop -> `walk`); calls taint $v0/$f0 with the callee's RETURN
             summary (labels its return value depends on, 3 levels deep);
             `bc0x` = CPCOND0 (DMA), `bc2x`/cfc2 = VU0 status.  An exit
             branch (the back-edge itself or a branch leaving the loop) whose
             condition carries a memory/hw/call label and no induction
             (`r = r + k`) or walk label is a POLL exit.
  setters    every constant-address store in every function, so a polled
             global's writers are known; each writer is placed in the
             interrupt handlers / threads that reach it.

Source lines: each retail loop is matched to a `while/for/do` in the
ingested game/ file of its function (the loop whose text mentions the polled
symbol, hw literal or callee; otherwise the n-th loop).  `src_match` says how.

Class:
  SAFE          a BLOCK-level call runs on every iteration
  HW            waits on a hardware status the port's models answer
                (DMA CHCR/D_STAT/CPCOND0, VIF/GIF/IPU status, GS CSR, SIF
                registers, INTC_STAT, VU0 status)
  TIMER         busy-waits on T0..T3 COUNT (needs virtual time per read)
  HANDLER-FLAG  waits on memory written by an interrupt handler, another
                thread, a callback, or the IOP (SIF DMA) -- needs the loop to
                let time pass and interrupts be delivered
  SDK-POLL      the exit depends on an SDK status function (sceCdSync(1),
                sceSifDmaStat, ...) called in the loop: the src/sce
                implementation of that function must let time pass
  PROGRESS      not a spin: the polled value is written by the loop's own
                (non-yielding) callees, or by this function
  REVIEW        a poll exit whose setter could not be determined

    python tools/census/spin_loops.py [--rebuild]
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE / "platform"))
import common as C  # noqa: E402

PORT = HERE.parents[1]
GAME = PORT / "game"
GP = C.GP

# --------------------------------------------------------------- registers
HW_NAMES = {
    0x10000000: "T0_COUNT", 0x10000010: "T0_MODE", 0x10000020: "T0_COMP", 0x10000030: "T0_HOLD",
    0x10000800: "T1_COUNT", 0x10000810: "T1_MODE", 0x10000820: "T1_COMP", 0x10000830: "T1_HOLD",
    0x10001000: "T2_COUNT", 0x10001010: "T2_MODE", 0x10001020: "T2_COMP",
    0x10001800: "T3_COUNT", 0x10001810: "T3_MODE", 0x10001820: "T3_COMP",
    0x10002000: "IPU_CMD", 0x10002010: "IPU_CTRL", 0x10002020: "IPU_BP", 0x10002030: "IPU_TOP",
    0x10003000: "GIF_CTRL", 0x10003010: "GIF_MODE", 0x10003020: "GIF_STAT",
    0x10003800: "VIF0_STAT", 0x10003810: "VIF0_FBRST", 0x10003C00: "VIF1_STAT",
    0x10003C10: "VIF1_FBRST", 0x10003C20: "VIF1_ERR", 0x10003C30: "VIF1_MARK",
    0x1000E000: "D_CTRL", 0x1000E010: "D_STAT", 0x1000E020: "D_PCR", 0x1000E030: "D_SQWC",
    0x1000E040: "D_RBSR", 0x1000E050: "D_RBOR", 0x1000E060: "D_STADR",
    0x1000F000: "INTC_STAT", 0x1000F010: "INTC_MASK",
    0x1000F200: "SIF_MSCOM", 0x1000F210: "SIF_SMCOM", 0x1000F220: "SIF_MSFLG",
    0x1000F230: "SIF_SMFLG", 0x1000F240: "SIF_CTRL", 0x1000F260: "SIF_BD6",
    0x1000F520: "D_ENABLER", 0x1000F590: "D_ENABLEW",
    0x12000000: "GS_PMODE", 0x12001000: "GS_CSR", 0x12001010: "GS_IMR",
    0x12001040: "GS_BUSDIR", 0x12001080: "GS_SIGLBLID",
}
DMA_CH = {0x10008000: "D0_VIF0", 0x10009000: "D1_VIF1", 0x1000A000: "D2_GIF",
          0x1000B000: "D3_fromIPU", 0x1000B400: "D4_toIPU", 0x1000C000: "D5_SIF0",
          0x1000C400: "D6_SIF1", 0x1000C800: "D7_SIF2", 0x1000D000: "D8_fromSPR",
          0x1000D400: "D9_toSPR"}
DMA_REG = {0x00: "CHCR", 0x10: "MADR", 0x20: "QWC", 0x30: "TADR", 0x40: "ASR0",
           0x50: "ASR1", 0x80: "SADR"}


def phys(a: int) -> int:
    a &= 0xFFFFFFFF
    if 0xA0000000 <= a < 0xC0000000 or 0x80000000 <= a < 0xA0000000:
        return a & 0x1FFFFFFF
    return a


def addr_kind(a: int):
    """(kind, name) for a constant load/store address."""
    p = phys(a)
    if 0x10000000 <= p < 0x10010000:
        if p in HW_NAMES:
            return "hw", HW_NAMES[p]
        for base, nm in DMA_CH.items():
            if base <= p < base + 0x100:
                return "hw", f"{nm}_{DMA_REG.get(p - base, hex(p - base))}"
        if 0x10004000 <= p < 0x10008000:
            return "hw", "FIFO_%X" % p
        return "hw", "HW_%08X" % p
    if 0x11000000 <= p < 0x11010000:
        return "vumem", "VU_%08X" % p
    if 0x12000000 <= p < 0x12002000:
        return "hw", HW_NAMES.get(p, "GS_%08X" % p)
    if 0x70000000 <= a < 0x70004000:
        return "spr", "SPR_%04X" % (a - 0x70000000)
    if 0x1FC00000 <= p < 0x20000000:
        return "bios", "BIOS_%08X" % p
    if 0x20000000 <= a < 0x40000000:
        return "glob", "D_%08X" % (a & 0x01FFFFFF)
    if p < 0x02000000:
        return "glob", "D_%08X" % p
    return "other", "A_%08X" % a


def hw_class(name: str) -> str:
    if re.match(r"T\d_COUNT", name):
        return "TIMER"
    return "HW"


# --------------------------------------------------------------- decoding
def sx(v):
    return v - 0x10000 if v & 0x8000 else v


LOADS = {0x20: 1, 0x21: 2, 0x23: 4, 0x24: 1, 0x25: 2, 0x27: 4, 0x37: 8, 0x1E: 16,
         0x22: 4, 0x26: 4, 0x1A: 8, 0x1B: 8}
FLOADS = {0x31: 4, 0x35: 8, 0x36: 16}          # lwc1 / ldc1 / lqc2
STORES = {0x28: 1, 0x29: 2, 0x2B: 4, 0x3F: 8, 0x1F: 16, 0x2A: 4, 0x2E: 4, 0x2C: 8,
          0x2D: 8, 0x39: 4, 0x3D: 8, 0x3E: 16}
FCC = 66
HILO = 64
COND_LIKELY = (0x14, 0x15, 0x16, 0x17)


def branch_info(pc, w):
    """(target, srcs, conditional) for a branch/jump, else None.  srcs are
    register ids (FCC for bc1, ('cp', n) for bc0/bc2)."""
    op = w >> 26
    rs, rt = (w >> 21) & 31, (w >> 16) & 31
    off = pc + 4 + (sx(w & 0xFFFF) << 2)
    if op in (4, 5, 0x14, 0x15):
        if op == 4 and rs == 0 and rt == 0:
            return off, (), False
        return off, (rs, rt), True
    if op in (6, 7, 0x16, 0x17):
        return off, (rs,), True
    if op == 1 and rt in (0, 1, 2, 3):
        if rt == 1 and rs == 0:
            return off, (), False      # bgez $0 = b
        return off, (rs,), True
    if op == 0x11 and rs == 8:
        return off, (FCC,), True
    if op in (0x10, 0x12) and rs == 8:
        return off, (("cp", op - 0x10),), True
    if op == 2:
        return ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2), (), False
    return None


def regs(w):
    """(dsts, srcs, kind) for one instruction (kind: load/store/call/other)."""
    op = w >> 26
    rs, rt, rd = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
    fn = w & 63
    if op == 0:
        if fn in (0, 2, 3):                       # sll srl sra
            return (rd,), (rt,), "alu"
        if fn == 8:                               # jr
            return (), (rs,), "jr"
        if fn == 9:                               # jalr
            return (rd,), (rs,), "jalr"
        if fn == 12:
            return (), (), "syscall"
        if fn in (0x10, 0x12):                    # mfhi mflo
            return (rd,), (HILO,), "alu"
        if fn in (0x11, 0x13):
            return (HILO,), (rs,), "alu"
        if fn in (0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F):
            return (HILO,), (rs, rt), "alu"
        if fn in (0x0A, 0x0B):                    # movz movn
            return (rd,), (rs, rt, rd), "alu"
        if fn in (0x0F, 0x0D, 0x34, 0x30, 0x31, 0x32, 0x33, 0x36):  # sync/break/trap
            return (), (), "other"
        return (rd,), (rs, rt), "alu"
    if op == 1:
        return (), (rs,), "branch"
    if op in (2,):
        return (), (), "j"
    if op == 3:
        return (31, 2, 3), (), "jal"
    if op in (4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17):
        return (), (rs, rt), "branch"
    if op == 0x0F:
        return (rt,), (), "lui"
    if op in (0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x18, 0x19):
        return (rt,), (rs,), "alui"
    if op in LOADS:
        return (rt,), (rs,), "load"
    if op in FLOADS:
        return (32 + rt,), (rs,), "load"
    if op in STORES:
        return (), (rs, rt), "store"
    if op == 0x11:                                # COP1
        fmt = rs
        ft, fs, fd = rt, rd, (w >> 6) & 31
        if fmt == 0:                              # mfc1
            return (rt,), (32 + fs,), "alu"
        if fmt == 4:                              # mtc1
            return (32 + fs,), (rt,), "alu"
        if fmt in (2, 6):                         # cfc1/ctc1
            return ((rt,), (), "alu") if fmt == 2 else ((), (rt,), "alu")
        if fmt == 8:
            return (), (FCC,), "branch"
        if fmt in (0x10, 0x14):
            if fn >= 0x30:                        # c.cond.s
                return (FCC,), (32 + fs, 32 + ft), "alu"
            if fn in (0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F):  # madd/msub(a)
                return (32 + fd,), (32 + fs, 32 + ft, 32 + fd), "alu"
            return (32 + fd,), (32 + fs, 32 + ft), "alu"
        return (), (), "other"
    if op == 0x12:                                # COP2
        if rs == 2 and rd == 29:                  # cfc2 rt, vi29 (VPU-STAT)
            return (rt,), (("cp", 2),), "alu"
        if rs in (1, 2):                          # qmfc2 / cfc2: data
            return (rt,), (), "alu"
        if rs == 8:
            return (), (("cp", 2),), "branch"
        return (), (), "other"
    if op == 0x10 and rs == 8:
        return (), (("cp", 0),), "branch"
    if op == 0x1C:                                # MMI
        return (rd,), (rs, rt), "alu"
    return (), (), "other"


def jal_target(pc, w):
    return ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)


# --------------------------------------------------------------- function model
class FnInfo:
    __slots__ = ("fn", "ins", "pre", "callees", "jalr", "sys", "stores", "ret", "ins_map")

    def __init__(self, fn, ins):
        self.fn = fn
        self.ins = ins
        self.pre = None
        self.callees = []        # (pc, Fn)
        self.jalr = []
        self.sys = []            # syscall numbers
        self.stores = []         # (addr, size)
        self.ret = None


CALLER_SAVED = set(range(1, 16)) | {24, 25, 31} | set(range(32, 52)) | {HILO, FCC}


def const_pass(ins, start_state=None, kill=frozenset()):
    """Linear constant tracking; returns {pc: state-before}."""
    st = dict(start_state or {})
    for r in kill:
        st.pop(r, None)
    st[28] = GP
    out = {}
    reset_at = None
    likely = None
    for pc, w in ins:
        if pc == reset_at:
            # reached only by a branch: keep address-like constants only
            st = {r: v for r, v in st.items() if v >= 0x10000}
        out[pc] = st.copy()
        op = w >> 26
        if (op == 4 and (w >> 16) & 0x3FF == 0) or op == 2 or (op == 0 and (w & 63) == 8):
            reset_at = pc + 8
        if op in COND_LIKELY or (op == 1 and ((w >> 16) & 31) in (2, 3)):
            likely = (pc + 4, st.copy())   # slot runs only when taken
        rs, rt, rd = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        if op == 0x0F:
            st[rt] = (w & 0xFFFF) << 16
        elif op == 0x09 or op == 0x19:
            if rs == 0:
                st[rt] = sx(w & 0xFFFF) & 0xFFFFFFFF
            elif rs in st:
                st[rt] = (st[rs] + sx(w & 0xFFFF)) & 0xFFFFFFFF
            else:
                st.pop(rt, None)
        elif op == 0x0D:
            if rs == 0:
                st[rt] = w & 0xFFFF
            elif rs in st:
                st[rt] = st[rs] | (w & 0xFFFF)
            else:
                st.pop(rt, None)
        elif op == 0 and (w & 63) in (0x21, 0x25, 0x2D) and (rt == 0 or rs == 0):
            src = rs if rt == 0 else rt
            if src == 0:
                st[rd] = 0
            elif src in st:
                st[rd] = st[src]
            else:
                st.pop(rd, None)
        else:
            d, _, k = regs(w)
            if k in ("jal", "jalr"):
                for r in CALLER_SAVED:
                    st.pop(r, None)
            for r in d:
                st.pop(r, None)
        st[28] = GP
        st[0] = 0
        if likely is not None and likely[0] == pc:
            st = likely[1]
            likely = None
    return out


def mem_addr(state, w):
    base = (w >> 21) & 31
    if base in state:
        return (state[base] + sx(w & 0xFFFF)) & 0xFFFFFFFF
    return None


# --------------------------------------------------------------- analysis
BLOCK_SYS = {0x32, 0x44, 0x23, 0x24, 0x04}
# SDK functions whose retail body BUSY-WAITS for an interrupt-driven event
# (so retail reach-analysis sees no blocking syscall) but which the port's
# src/sce implementation must turn into a blocking wait: seed them BLOCK.
PORT_LEVEL = {"sceGsSyncV": 3, "VSync_116a30": 3}
# status functions a caller polls (src/sce must let time pass inside them)
STATUS_FN = re.compile(r"^(sceSif(GetReg|GetSreg|DmaStat|CheckStatRpc|SetDma|SendCmd|"
                       r"GetNextRequest|RebootIop|SyncIop)|sceCdSync|sceCdDiskReady|sceCdGetError|"
                       r"sceCdSearchFile|sceCdLayerSearchFile|sceMcSync|scePadGetState|"
                       r"sceGsSyncPath|PollSema|iPollSema|ReferThreadStatus|ReferSemaStatus|"
                       r"MpegIsEnd|sceMpegIsEnd)")
ROTATE_SYS = {0x2B}
LV = {"NONE": 0, "KCALL": 1, "ROTATE": 2, "BLOCK": 3}


class Analysis:
    def __init__(self, imgs, edges):
        self.imgs = imgs
        self.info: dict = {}
        for name, im in imgs.items():
            for f in im.fns:
                if f.size <= 0:
                    continue
                fi_ = FnInfo(f, list(C.insns(im, f)))
                fi_.ins_map = dict(fi_.ins)
                self.info[f.key] = fi_
        self.store_map = defaultdict(set)    # aligned word -> {fn key}
        for k, fi in self.info.items():
            self._scan(fi)
        self._levels()
        self._arg_stores()
        self._roots()

    # ---- per function facts
    def _scan(self, fi: FnInfo):
        f = fi.fn
        fi.pre = const_pass(fi.ins)
        last_v1 = None
        for pc, w in fi.ins:
            op = w >> 26
            if op == 3:
                d = C.resolve(self.imgs, f.image, jal_target(pc, w))
                if d is not None:
                    fi.callees.append((pc, d))
            elif op == 2:
                t = jal_target(pc, w)
                if not (f.addr <= t < f.addr + f.size):
                    d = C.resolve(self.imgs, f.image, t)
                    if d is not None:
                        fi.callees.append((pc, d))
            elif op == 0 and (w & 63) == 9:
                fi.jalr.append(pc)
            elif op == 0 and (w & 63) == 12:
                n = fi.pre[pc].get(3)
                if n is not None:
                    n = n - (1 << 32) if n & 0x80000000 else n
                fi.sys.append(n)
            if op in STORES:
                a = mem_addr(fi.pre[pc], w)
                if a is not None:
                    fi.stores.append((a, STORES[op]))
                    self.store_map[phys(a) & ~3].add(f.key)

    def _arg_stores(self):
        """Stores through an argument pointer (`*(arg_i + off) = ..`), then
        every call site that passes a constant address for arg_i: the callee
        (and its caller) write that global.  One level, no transitivity."""
        argst = {}
        for k, fi in self.info.items():
            taint = {4: {("arg", 0)}, 5: {("arg", 1)}, 6: {("arg", 2)}, 7: {("arg", 3)}}
            out = set()
            for pc, w in fi.ins:
                op = w >> 26
                if op in STORES:
                    bt = taint.get((w >> 21) & 31, set())
                    if len(bt) == 1 and next(iter(bt))[0] == "arg":
                        out.add((next(iter(bt))[1], sx(w & 0xFFFF), STORES[op]))
                d, s_, kk = regs(w)
                if kk in ("jal", "jalr"):
                    for r in CALLER_SAVED:
                        taint.pop(r, None)
                    continue
                if kk == "alu" and op == 0 and (w & 63) in (0x21, 0x2D, 0x25) and 0 in s_:
                    src = s_[0] if s_[1] == 0 else s_[1]
                    taint[d[0]] = set(taint.get(src, set()))
                    continue
                for r in d:
                    taint.pop(r, None)
            if out:
                argst[k] = out
        self.arg_writers = defaultdict(set)
        for k, fi in self.info.items():
            for pc, d in fi.callees:
                if d.key not in argst:
                    continue
                st = dict(fi.pre.get(pc, {}))
                slot = fi.ins_map.get(pc + 4)
                if slot is not None:
                    st = const_pass([(pc + 4, slot), (pc + 8, 0)], st)[pc + 8]
                for i, off, sz in argst[d.key]:
                    if (4 + i) in st:
                        a = phys((st[4 + i] + off) & 0xFFFFFFFF)
                        self.store_map[a & ~3].add(d.key)
                        self.arg_writers[a & ~3].add(k)

    def _levels(self):
        lvl = {}
        for k, fi in self.info.items():
            v = 0
            for n in fi.sys:
                if n is None:
                    continue
                n = abs(n)
                v = max(v, 3 if n in BLOCK_SYS else 2 if n in ROTATE_SYS else 1)
            lvl[k] = max(v, PORT_LEVEL.get(fi.fn.name, 0))
        # propagate (fixpoint) through callees
        changed = True
        while changed:
            changed = False
            for k, fi in self.info.items():
                v = lvl[k]
                for _, d in fi.callees:
                    dv = lvl.get(d.key, 0)
                    if dv > v:
                        v = dv
                if v != lvl[k]:
                    lvl[k] = v
                    changed = True
        self.level = lvl

    def _roots(self):
        """Contexts: interrupt handlers and thread entries (PLATFORM.md)."""
        handler = ["Vif1IntcHandler_15e170", "SoundVblankIntrHandler_1bd6f0",
                   "MovieVblankHandler_1d4c90", "MovieDmacHandler_1d4b10",
                   "GfxVblankStartHandler_15df20", "MpegCscDmaHandler_112900",
                   "MpegToIpuDmaHandler_112a48", "SifCmdIntrHandler_119968",
                   "TimerAlarmIntcHandler_121510", "DelayThreadAlarmHandler_117858"]
        thread = ["FileReqThread_182c30", "SoundCmdWorkerThread_1b6c10",
                  "SoundThreadMain_1b6260", "SoundStreamSlotThreadMain_1bc520",
                  "SoundStreamThreadMain_1c1050", "CdDiskWatchThread_17fdc0",
                  "SysTickThreadMain_1c33f0", "DefMain_1d52b0", "VideoDecMain_1d5240",
                  "MovieReadThread_1d4f50", "LoadingScreenThread_343510",
                  "SdrCallbackThread_122fa8", "CdCallbackThread_1292e0"]
        main = self.imgs["main"]
        self.ctx_of = defaultdict(set)
        for kind, names in (("isr", handler), ("thread", thread)):
            for n in names:
                f = main.by_name.get(n)
                if f is None:
                    continue
                seen = {f.key}
                todo = [f.key]
                while todo:
                    k = todo.pop()
                    fi = self.info.get(k)
                    if fi is None:
                        continue
                    for _, d in fi.callees:
                        if d.key not in seen:
                            seen.add(d.key)
                            todo.append(d.key)
                for k in seen:
                    self.ctx_of[k].add(f"{kind}:{n}")

    def writes_memory(self, key, _memo={}):
        """True if the function or anything it calls stores to non-stack
        memory (a store whose base is not $sp)."""
        if key in _memo:
            return _memo[key]
        _memo[key] = False
        fi = self.info.get(key)
        res = fi is None
        if fi is not None:
            for pc, w in fi.ins:
                if (w >> 26) in STORES and (w >> 21) & 31 != 29:
                    res = True
                    break
            if fi.jalr:
                res = True
            if not res:
                res = any(self.writes_memory(d.key) for _, d in fi.callees)
        _memo[key] = res
        return res

    def reach_stores(self, key, depth=6):
        """Constant store addresses (aligned) reachable from fn key through
        non-blocking calls."""
        out = set()
        seen = set()
        todo = [(key, 0)]
        while todo:
            k, d = todo.pop()
            if k in seen:
                continue
            seen.add(k)
            fi = self.info.get(k)
            if fi is None:
                continue
            out.update(phys(a) & ~3 for a, _ in fi.stores)
            if d < depth:
                for _, c in fi.callees:
                    todo.append((c.key, d + 1))
        return out

    # ---- return-value summary (labels $v0/$f0 depend on)
    def ret_labels(self, key, depth=0):
        fi = self.info.get(key)
        if fi is None:
            return {("unknown",)}
        if fi.ret is not None:
            return fi.ret
        fi.ret = set()          # recursion guard
        written = set()
        for pc, w in fi.ins:
            written.update(r for r in regs(w)[0])
        taint = {4: {("arg", 0)}, 5: {("arg", 1)}, 6: {("arg", 2)}, 7: {("arg", 3)}}
        res = set()
        for _ in range(2):
            for pc, w in fi.ins:
                self._step(fi, pc, w, taint, written, fi.pre[pc], depth, fn_scope=True)
                if w == 0x03E00008:      # jr ra
                    res |= taint.get(2, set()) | taint.get(32, set())
        fi.ret = {l for l in res if l[0] != "arg"} | {l for l in res if l[0] == "arg"}
        return fi.ret

    def _load_label(self, pc, w, state, written, taint, fn_scope):
        base = (w >> 21) & 31
        off = sx(w & 0xFFFF)
        a = mem_addr(state, w)
        if a is not None:
            k, nm = addr_kind(a)
            return {("mem", k, nm, phys(a))}
        if base == 29:
            sl = taint.get(("sp", off))
            return set(sl) if sl is not None else {("stack",)}
        bt = taint.get(base, set())
        if fn_scope and len(bt) == 1 and next(iter(bt))[0] == "arg":
            return {("argptr", next(iter(bt))[1], off)}
        if base in written:
            return {("walk",)}
        if fn_scope and base in (4, 5, 6, 7):
            return {("argptr", base - 4, off)}
        return {("ptr", base, off)} | {("via",) + t for t in taint.get(base, set())
                                       if t[0] == "mem"}

    def _step(self, fi, pc, w, taint, written, state, depth, fn_scope=False):
        d, s, k = regs(w)
        if k == "load":
            taint[d[0]] = self._load_label(pc, w, state, written, taint, fn_scope)
            return
        if k == "store":
            if (w >> 21) & 31 == 29:          # spill / volatile local
                op = w >> 26
                rt = (w >> 16) & 31
                src = 32 + rt if op in (0x39, 0x3D) else rt
                taint[("sp", sx(w & 0xFFFF))] = set(taint.get(src, set())) if src else set()
            return
        if k == "jal":
            callee = C.resolve(self.imgs, fi.fn.image, jal_target(pc, w))
            if callee is None:
                lab = {("call", "?")}
            else:
                lab = {("call", callee.name, callee.key)}
                if depth < 3 and self.level.get(callee.key, 0) < 3:
                    sub = self.ret_labels(callee.key, depth + 1)
                    # argument values at the call (state + delay slot)
                    st = dict(state)
                    slot = fi.ins_map.get(pc + 4)
                    if slot is not None:
                        sl = const_pass([(pc + 4, slot)], st)
                        st = sl[pc + 4]
                        op2, rs2, rt2 = slot >> 26, (slot >> 21) & 31, (slot >> 16) & 31
                        if op2 in (0x09, 0x19) and (rs2 == 0 or rs2 in st):
                            st[rt2] = ((st.get(rs2, 0) if rs2 else 0) + sx(slot & 0xFFFF)) & 0xFFFFFFFF
                        elif op2 == 0x0F:
                            st[rt2] = (slot & 0xFFFF) << 16
                        elif op2 == 0 and (slot & 63) in (0x21, 0x2D, 0x25):
                            src = rs2 if rt2 == 0 else rt2
                            rd2 = (slot >> 11) & 31
                            if src in st:
                                st[rd2] = st[src]
                            else:
                                st.pop(rd2, None)
                    for l in sub:
                        while l[0] == "from":          # flatten callee chains
                            l = l[2:]
                        if l[0] == "argptr":
                            ar = 4 + l[1]
                            at = taint.get(ar, set())
                            if not fn_scope and ar in st:
                                a_ = (st[ar] + l[2]) & 0xFFFFFFFF
                                kk, nm = addr_kind(a_)
                                lab.add(("from", callee.name, "mem", kk, nm, phys(a_)))
                            elif fn_scope and len(at) == 1 and next(iter(at))[0] == "arg":
                                lab.add(("from", callee.name, "argptr", next(iter(at))[1], l[2]))
                            else:
                                lab.add(("from", callee.name) + l)
                        elif l[0] in ("mem", "cp"):
                            lab.add(("from", callee.name) + l)
            for r in CALLER_SAVED:
                taint.pop(r, None)
            taint[2] = lab
            taint[32] = lab
            return
        if k == "jalr":
            for r in CALLER_SAVED:
                taint.pop(r, None)
            taint[2] = {("call", "?")}
            return
        if k in ("lui",):
            taint[d[0]] = set()
            return
        u = set()
        for r in s:
            if isinstance(r, tuple):
                u.add(r)
            elif r != 0:
                u |= taint.get(r, set())
        if not fn_scope and k == "alui" and d and d[0] in s and (w >> 26) in (
                0x08, 0x09, 0x18, 0x19):
            u = u | {("ind",)}
        if not fn_scope and k == "alu" and d and d[0] in s and (w >> 26) == 0 and (w & 63) in (
                0x20, 0x21, 0x22, 0x23, 0x2C, 0x2D, 0x2E, 0x2F):
            u = u | {("ind",)}
        if k == "alui" and (w >> 26) == 0x09 and ((w >> 21) & 31) == 0:
            u = set()
        ind = () if fn_scope else getattr(self, "_ind", ())
        for r in d:
            if r != 0:
                taint[r] = set(u) | ({("ind",)} if r in ind else set())

    # ---- loops
    def loops(self, fi: FnInfo):
        f = fi.fn
        heads = defaultdict(list)
        for pc, w in fi.ins:
            b = branch_info(pc, w)
            if b and f.addr <= b[0] <= pc:
                heads[b[0]].append(pc)
        for t, pcs in sorted(heads.items()):
            yield t, max(pcs) + 4, pcs

    def analyse_loop(self, fi: FnInfo, head, end, backs):
        f = fi.fn
        body = [(pc, w) for pc, w in fi.ins if head <= pc <= end]
        written = set()
        for pc, w in body:
            written.update(r for r in regs(w)[0])
        # body constants: pre-state at head minus registers the body writes
        # with anything but a pure constant (lui / li / lui+addiu pair)
        st0 = {r: v for r, v in fi.pre.get(head, {}).items()}
        kill = set()
        while True:
            n0 = len(kill)
            for pc, w in body:
                d, s_, k = regs(w)
                if not d:
                    continue
                op = w >> 26
                rs = (w >> 21) & 31
                pure = op == 0x0F or (op in (0x09, 0x0D, 0x19) and (
                    rs == 0 or rs == 28 or (rs != d[0] and rs not in kill)))
                if not pure:
                    kill.update(r for r in d if r not in (0, 28))
            if len(kill) == n0:
                break
        bstate = const_pass(body, st0, kill)
        # calls in the body
        calls = []
        for pc, w in body:
            if (w >> 26) == 3:
                d = C.resolve(self.imgs, f.image, jal_target(pc, w))
                calls.append((pc, d))
            elif (w >> 26) == 2:
                t = jal_target(pc, w)
                if not (f.addr <= t < f.addr + f.size):
                    calls.append((pc, C.resolve(self.imgs, f.image, t)))
        sysn = [bstate[pc].get(3) for pc, w in body if (w >> 26) == 0 and (w & 63) == 12]
        jalr = [pc for pc, w in body if (w >> 26) == 0 and (w & 63) == 9]
        # skipped-by-branch test for "every iteration"
        brs = [(pc, branch_info(pc, w)) for pc, w in body]
        brs = [(pc, b) for pc, b in brs if b]

        def every(a):
            for pc, b in brs:
                if pc >= a:
                    break
                tgt = b[0]
                if head <= tgt <= end and (tgt > a or tgt == head) and pc not in backs:
                    return False
                if pc in backs and pc < a:
                    return False
            return True

        lvl, lvl_every, yield_via = 0, 0, []
        for pc, d in calls:
            v = self.level.get(d.key, 0) if d is not None else 0
            if v:
                yield_via.append((d.name, v, every(pc)))
            lvl = max(lvl, v)
            if every(pc):
                lvl_every = max(lvl_every, v)
        for n in sysn:
            if n is not None:
                v = 3 if abs(n) in BLOCK_SYS else 2 if abs(n) in ROTATE_SYS else 1
                lvl = max(lvl, v)
                lvl_every = max(lvl_every, v)
        # induction registers: any `r = r +- x` in the body taints every def
        ind = set()
        for pc, w in body:
            dd, ss, kk = regs(w)
            op = w >> 26
            if dd and dd[0] in ss and ((kk == "alui" and op in (0x08, 0x09, 0x18, 0x19)) or (
                    kk == "alu" and op == 0 and (w & 63) in (0x20, 0x21, 0x22, 0x23,
                                                             0x2C, 0x2D, 0x2E, 0x2F)) or (
                    kk == "alu" and op == 0x11 and (w & 63) in (0, 1))):   # add.s/sub.s
                ind.add(dd[0])
        self._ind = ind
        # addresses inside the loop that unconditionally leave it
        leave_at = set()
        for pc, w in body:
            bi = branch_info(pc, w)
            if (bi and not bi[2] and not (head <= bi[0] <= end)) or w == 0x03E00008:
                leave_at.add(pc)
        # taint
        taint: dict = {}
        exits = []
        exit_regs = []
        for it in range(2):
            for pc, w in body:
                b = branch_info(pc, w)
                if b and b[2] and it == 1:
                    tgt = b[0]
                    is_exit = (pc in backs and pc + 8 > end) or not (head <= tgt <= end)                         or tgt in leave_at or (pc + 8) in leave_at
                    if is_exit:
                        lab = set()
                        for r in b[1]:
                            if isinstance(r, tuple):
                                lab.add(r)
                            elif r != 0:
                                lab |= taint.get(r, set())
                        exits.append((pc, lab))
                        exit_regs.append(set(r for r in b[1] if not isinstance(r, tuple) and r != 0))
                self._step(fi, pc, w, taint, written, bstate[pc], 0)
        self._ind = ()
        # self stores
        own_st = set()
        for pc, w in body:
            if (w >> 26) in STORES:
                a = mem_addr(bstate[pc], w)
                if a is not None:
                    own_st.add(phys(a) & ~3)
                elif (w >> 21) & 31 not in written:
                    own_st.add(("ptr", (w >> 21) & 31, sx(w & 0xFFFF)))
        # HALT: nothing in the loop can change its exit condition (the
        # condition registers are not written in the body, no calls, no
        # loads feeding them) -- a deliberate infinite loop (error halt)
        rets = any(w == 0x03E00008 for _, w in body)
        stores = any((w >> 26) in STORES and (w >> 21) & 31 != 29 for _, w in body)
        halt = not calls and not jalr and not rets and not stores and not leave_at and all(
            not (rg & written) and not lab for rg, (_, lab) in zip(exit_regs, exits))
        return dict(halt=halt, calls=calls, jalr=jalr, sysn=sysn, lvl=lvl, lvl_every=lvl_every,
                    yield_via=yield_via, exits=exits, own_st=own_st, body=body)


# --------------------------------------------------------------- source side
# Loops found by the source cross-check (docs/SPIN.md "Method") that the
# retail-asm pass misses.  Each is reviewed by hand; `addr` is the retail
# loop head.
MANUAL = [
    dict(symbol="SoundStreamShutdown_1c0b70", image="main", addr=0x1C0C54, line=105,
         cls="HANDLER-FLAG", polled="stream object b45/b48/rd/wr (inline s_isBusy)",
         setters="SoundStreamThreadMain_1c1050 (stream thread)",
         note="twin of the 0x1C0CF8 loop; its exit flows through a volatile local the "
              "taint pass loses"),
]
RUNTIME = ("libc", "libm", "libgcc", "msl-c++", "mwcc-rt", "crt0")
LOOP_KW = re.compile(r"\b(while|for|do)\b")
LABEL = re.compile(r"(?m)^[ \t]*([A-Za-z_]\w*)[ \t]*:(?!:)")
IMAGE_ID = {"main": 0, "title": 1, "insmenu": 2, "normal": 3, "factory": 4, "insect": 5}


def blank(text):
    sys.path.insert(0, str(PORT / "tools"))
    import portxform as X
    return X.blank_pp(X.blank(text))


def match_close(s, i, o="(", c=")"):
    d = 0
    for k in range(i, len(s)):
        if s[k] == o:
            d += 1
        elif s[k] == c:
            d -= 1
            if d == 0:
                return k
    return -1


def src_loops(code, lo, hi):
    """[(kw, kw_off, cond_lo, cond_hi, body_lo, body_hi)] in a function body."""
    out = []
    do_conds = set()
    for m in LOOP_KW.finditer(code, lo, hi):
        kw = m.group(1)
        i = m.end()
        while i < hi and code[i] in " \t\r\n":
            i += 1
        if kw == "do":
            if code[i] == "{":
                bc = match_close(code, i, "{", "}")
                bl, bh = i, bc
                j = bc + 1
            else:
                j = code.find(";", i)
                bl, bh = i, j
                j += 1
            wm = re.compile(r"\s*while\s*\(").match(code, j)
            if not wm:
                continue
            co = wm.end() - 1
            cc = match_close(code, co)
            do_conds.add(code.find("while", j))
            out.append(["do", m.start(), co, cc, bl, bh])
            continue
        if m.start() in do_conds:
            continue
        if i >= hi or code[i] != "(":
            continue
        cc = match_close(code, i)
        j = cc + 1
        while j < hi and code[j] in " \t\r\n":
            j += 1
        if j < hi and code[j] == "{":
            bh = match_close(code, j, "{", "}")
        else:
            bh = code.find(";", j)
            # nested control statement as body: take to its end roughly
        out.append([kw, m.start(), i, cc, j, bh])
    # goto loops: `label:` with a later `goto label;`
    for m in LABEL.finditer(code, lo, hi):
        name = m.group(1)
        if name in ("default", "case", "public", "private", "protected"):
            continue
        g = re.compile(r"\bgoto\s+" + name + r"\s*;")
        last = None
        for gm in g.finditer(code, m.end(), hi):
            last = gm
        if last is not None:
            out.append(["label", m.start(1), m.start(1), m.end() - 1, m.end(), last.end()])
    out.sort(key=lambda r: r[1])
    return out


# --------------------------------------------------------------- driver
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rebuild", action="store_true")
    ap.add_argument("--out", type=Path, default=PORT / "census" / "spin_loops.tsv")
    a = ap.parse_args()
    facts, imgs, edges, files = C.cached(a.rebuild)
    A = Analysis(imgs, edges)

    # manifest: compiled source per symbol
    manifest = {}
    for ln in (GAME / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split("\t")
        if len(f) >= 5:
            for s in f[4].split(","):
                manifest[(f[2], s)] = (f[0], f[3])
    excluded = {}
    for ln in (GAME / "EXCLUDED.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split("\t")
        excluded[(f[2], f[0])] = f[3]

    src_cache = {}

    def source_of(image, name):
        hit = manifest.get((image, name))
        if hit is None:
            fx = facts.get((image, name))
            if fx is None:
                return None
            hit = (fx[0], "?")
        path = GAME / hit[0]
        if not path.exists():
            return None
        if hit[0] not in src_cache:
            text = path.read_text(encoding="utf-8", errors="replace")
            code = blank(text)
            sys.path.insert(0, str(PORT / "tools"))
            import portxform as X
            src_cache[hit[0]] = (text, code, X.find_funcs(code))
        return hit, src_cache[hit[0]]

    rows = []
    stats = defaultdict(int)
    for key, fi in sorted(A.info.items(), key=lambda kv: (kv[0][0] != "main", kv[0])):
        f = fi.fn
        cand = []
        for head, end, backs in A.loops(fi):
            stats["loops"] += 1
            L = A.analyse_loop(fi, head, end, backs)
            polls = []
            bounded = False
            has_calls = bool(L["jalr"]) or any(
                d is None or A.writes_memory(d.key) for _, d in L["calls"])
            ext_store = any((w >> 26) in STORES and (w >> 21) & 31 != 29
                            for _, w in L["body"])
            varying_exit = False
            for pc, lab in L["exits"]:
                kinds = {l[0] for l in lab}
                if "ind" in kinds or "walk" in kinds:
                    if kinds <= {"ind", "walk", "stack"}:
                        bounded = True
                    else:
                        varying_exit = True
                    continue
                pl = []
                varying = False
                for l in lab:
                    if l[0] == "mem" and l[1] in ("hw", "glob", "spr"):
                        pl.append(l)
                    elif l[0] == "via" and l[1] == "mem":
                        pl.append(l)
                    elif l[0] == "cp":
                        pl.append(l)
                    elif l[0] == "from":
                        if l[2] == "cp" or (l[2] == "mem" and l[3] in ("hw", "glob", "spr")):
                            pl.append(l)
                        elif l[2] != "mem":
                            varying = True   # callee result from its args / pointers
                    elif l[0] == "call" and len(l) > 2 and A.info.get(l[2]) and (
                            STATUS_FN.match(l[1]) or (
                                not f.lib and A.info[l[2]].fn.lib and
                                A.info[l[2]].fn.lib[0] not in RUNTIME)):
                        pl.append(l)
                    elif l[0] == "call":
                        # a game/runtime call result: varies unless the
                        # callee only reads polled memory (its `from` labels)
                        if not any(x[0] == "from" and x[1] == l[1] for x in lab):
                            varying = True
                    elif l[0] == "ptr" and not has_calls and not ext_store:
                        pl.append(l)
                    else:
                        varying = True       # ptr with calls/stores, argptr, stack, ...
                if varying:
                    pl = []
                    varying_exit = True
                if pl:
                    polls.append((pc, pl))
            if polls and varying_exit:
                # another exit depends on something the loop itself changes
                stats["mixed_exit_dropped"] += 1
                continue
            if polls and bounded and not any(
                    l[0] == "cp" or (l[0] == "mem" and l[1] == "hw") or
                    (l[0] == "from" and (l[2] == "cp" or l[3] == "hw"))
                    for _, pl in polls for l in pl):
                stats["bounded_dropped"] += 1
                continue
            L["bounded"] = bounded
            if not polls and L["halt"]:
                stats["halt"] += 1
                cand.append((head, end, L, []))
                continue
            if not polls:
                continue
            stats["poll_loops"] += 1
            cand.append((head, end, L, polls))
        if not cand:
            continue
        lib = f.lib
        libname = "sdk" if lib else "game"
        if lib and lib[0] in ("libc", "libm", "libgcc", "msl-c++", "mwcc-rt", "crt0"):
            libname = "library"
        src = source_of(f.image, f.name)
        sloops = []
        fn_src = None
        if src:
            (rel, kind), (text, code, funcs) = src
            fn_src = next((x for x in funcs if x.name.split("::")[-1] == f.name), None)
            if fn_src is not None:
                sloops = src_loops(code, fn_src.body_open, fn_src.body_close)
        for idx, (head, end, L, polls) in enumerate(cand):
            labels = set()
            for _, pl in polls:
                labels.update(pl)
            r = classify(A, fi, L, labels)
            # source matching
            line, smatch, sl = "", "none", None
            if src:
                (rel, kind), (text, code, funcs) = src
                needles = r["needles"]
                best, bs, bm = None, -1e9, 0
                rel = (head - f.addr) / max(f.size, 4)
                blo, bhi = (fn_src.body_open, max(fn_src.body_close, fn_src.body_open + 1))                     if fn_src is not None else (0, 1)
                for k, lp in enumerate(sloops):
                    cseg = text[lp[2]:lp[3] + 1]
                    bseg = text[lp[4]:lp[5] + 1]
                    m_ = sum(3 if re.search(n, cseg, re.I) else
                             1 if re.search(n, bseg, re.I) else 0 for n in set(needles))
                    body_ = code[lp[4]:lp[5] + 1] if lp[0] != "do" else code[lp[4]:lp[5] + 1]
                    empty = re.fullmatch(r"\s*(\{\s*\}|;)?\s*;?\s*", body_) is not None
                    if r["cls"] == "HALT" and empty:
                        m_ += 3
                    srel = (lp[1] - blo) / (bhi - blo)
                    sc = m_ - abs(srel - rel) - (lp[5] - lp[1]) / 1e4   # innermost wins near-ties
                    if sc > bs:
                        best, bs, bm = k, sc, m_
                if best is not None:
                    sl = sloops[best]
                    smatch = "mention" if bm > 0 else "position"
                    line = text.count("\n", 0, sl[1]) + 1
            row = dict(
                file=(src[0][0] if src else "-"), line=line, symbol=f.name, image=f.image,
                lib=libname, family=("/".join(lib) if lib else "-"),
                addr="0x%06X" % head, back="0x%06X" % (end - 4),
                compiled=(src[0][1] if src else "no-source"),
                cls=r["cls"], polled=r["polled"], poll_kind=r["kind"],
                kcall=r["kcall"], yields=r["yields"], setters=r["setters"],
                poller_ctx=",".join(sorted(A.ctx_of.get(f.key, set()))) or "main",
                handling=handling(r["cls"], libname, src[0][1] if src else "no-source"),
                site="0x%08X" % ((IMAGE_ID[f.image] << 28) | head),
                hint=("halt" if r["cls"] == "HALT" else "hint") if (
                    src and src[0][1] == "unit" and sl is not None and
                    r["cls"] in ("HANDLER-FLAG", "HALT", "REVIEW")) else "",
                src_match=smatch,
                src_loop=(sl[0] + ":" + re.sub(r"\s+", " ", (src[1][0][sl[2]:sl[3] + 1]))[:90]
                          if sl else ""),
                note=r["note"])
            rows.append(row)
    for m in MANUAL:
        f = imgs[m["image"]].by_name[m["symbol"]]
        src = source_of(m["image"], m["symbol"])
        text = src[1][0] if src else ""
        lines = text.splitlines()
        hdr = lines[m["line"] - 1].strip() if src and m["line"] <= len(lines) else ""
        kw = re.match(r"(while|for|do)\b\s*(\([^{]*\))?", hdr)
        rows.append(dict(
            file=src[0][0] if src else "-", line=m["line"], symbol=m["symbol"], image=m["image"],
            lib="game" if not f.lib else "sdk", family="/".join(f.lib) if f.lib else "-",
            addr="0x%06X" % m["addr"], back="", compiled=src[0][1] if src else "no-source",
            cls=m["cls"], poll_kind="manual", polled=m["polled"], yields="-", kcall="-",
            setters=m["setters"], poller_ctx=",".join(sorted(A.ctx_of.get(f.key, set()))) or "main",
            handling=handling(m["cls"], "game", src[0][1] if src else "no-source"),
            site="0x%08X" % ((IMAGE_ID[m["image"]] << 28) | m["addr"]),
            hint="hint" if src and src[0][1] == "unit" else "", src_match="manual",
            src_loop=(kw.group(1) + ":" + (kw.group(2) or "")) if kw else hdr[:60],
            note=m["note"]))
    rows.sort(key=lambda r: (IMAGE_ID[r["image"]], r["addr"]))
    cols = ["file", "line", "symbol", "image", "lib", "family", "addr", "back", "compiled",
            "cls", "poll_kind", "polled", "yields", "kcall", "setters", "poller_ctx",
            "handling", "site", "hint", "src_match", "src_loop", "note"]
    cnt = defaultdict(int)
    for r in rows:
        cnt[(r["lib"], r["cls"])] += 1
    meta = C.meta("spin_loops", {
        "generator": "tools/census/spin_loops.py",
        "loops": f"{stats['loops']} retail loops (back-edge heads), "
                 f"{stats['poll_loops']} with a poll exit",
        "classes": ", ".join(f"{k[0]}/{k[1]}={v}" for k, v in sorted(cnt.items())),
        "doc": "docs/SPIN.md"})
    C.write_tsv(a.out, cols, rows, meta)
    print(f"{len(rows)} rows -> {a.out}")
    for k, v in sorted(cnt.items()):
        print(f"  {k[0]:8s} {k[1]:13s} {v}")
    return 0


def fmt_label(l):
    k = l[0]
    if k == "mem":
        return l[2]
    if k == "ptr":
        return f"*(r{l[1]}+0x{l[2] & 0xFFFF:X})"
    if k == "cp":
        return "CPCOND0(DMA)" if l[1] == 0 else "VU0_STAT"
    if k == "call":
        return f"{l[1]}()"
    if k == "from":
        return f"{l[1]}()->" + fmt_label(l[2:])
    if k == "via":
        return "via " + fmt_label(l[1:])
    if k == "argptr":
        return f"*(arg{l[1]}+0x{l[2] & 0xFFFF:X})"
    return k


SDK_POLL_FNS = re.compile(r"sceCdSync|sceCdDiskReady|sceSifDmaStat|sceMcSync|scePadGetState|"
                          r"sceSifCheckStatRpc|sceCdStatus|sceDmaSync|PollSema|sceGsSyncPath|"
                          r"sceMpeg|sceSifGetReg|ReferThreadStatus|ReferSemaStatus|sceSdRemote|"
                          r"sceIpuSync|sceCdGetError|sceCd", re.I)


def classify(A, fi, L, labels):
    f = fi.fn
    yv = L["yield_via"]
    yields = ";".join(f"{n}:{['-','KCALL','ROTATE','BLOCK'][v]}{'' if e else '?'}"
                      for n, v, e in yv[:4])
    kcall = ["-", "KCALL", "ROTATE", "BLOCK"][L["lvl"]]
    note = []
    needles = []
    polled = []
    kinds = set()
    setters = set()
    cls = None
    body_stores = set()
    for pc, d in L["calls"]:
        if d is not None and A.level.get(d.key, 0) < 3:
            body_stores |= A.reach_stores(d.key)
    hwc = set()
    flag_ok = False
    progress = False
    unknown = False
    sdkpoll = set()

    def mem_case(l):
        nonlocal flag_ok, progress, unknown
        kind, nm, p = l[1], l[2], l[3]
        if kind == "hw":
            hwc.add(hw_class(nm))
            kinds.add("hw")
            needles.extend([re.escape("0x%X" % p), re.escape("0x%X" % (p | 0xA0000000)), nm])
            return
        if kind == "spr":
            kinds.add("spr")
            unknown = True
            return
        w = p & ~3
        needles.append(r"D_%08X" % p)
        needles.append(r"D_%08X" % w)
        if w in L["own_st"]:
            progress = True
            return
        if w in body_stores:
            progress = True
            setters.add("loop-callees")
            return
        ws = A.store_map.get(w, set())
        ctxs = set()
        for k in ws:
            if k == f.key:
                continue
            fn = A.info[k].fn
            c = A.ctx_of.get(k, set())
            ctxs |= c
            setters.add(fn.name + ("[" + ",".join(sorted(x.split(":")[1] for x in c)) + "]"
                                   if c else ""))
        mine = A.ctx_of.get(f.key, set()) or {"main"}
        other = {c for c in ctxs if c not in mine}
        kinds.add("flag")
        if other or (ws - {f.key}):
            flag_ok = True
        else:
            unknown = True
            setters.add("none-const (DMA/IOP or pointer store)")

    for l in sorted(labels, key=str):
        polled.append(fmt_label(l))
        if l[0] == "mem":
            mem_case(l)
        elif l[0] == "cp":
            kinds.add("hw")
            hwc.add("HW")
        elif l[0] == "via":
            if l[1] == "mem":
                mem_case(l[1:])
        elif l[0] in ("ptr",):
            kinds.add("ptr")
            if ("ptr", l[1], l[2]) in L["own_st"]:
                progress = True
            else:
                flag_ok = True
                setters.add("? (field of a pointer held in a register)")
        elif l[0] == "call":
            if len(l) > 2:
                callee = A.info.get(l[2])
                needles.append(re.escape(l[1]))
                if callee and callee.fn.lib:
                    sdkpoll.add(l[1])
        elif l[0] == "from":
            sub = l[2:]
            needles.append(re.escape(l[1]))
            if sub[0] == "mem":
                mem_case(sub)
            elif sub[0] == "cp":
                hwc.add("HW")
                kinds.add("hw")
            elif sub[0] == "argptr":
                kinds.add("argptr")
                unknown = True
    if L.get("halt") and not labels:
        cls = "HALT"
        note.append("deliberate infinite loop (condition is loop-invariant)")
    elif L["lvl_every"] >= 3:
        cls = "SAFE"
    elif progress and not (hwc or flag_ok):
        cls = "PROGRESS"
    elif "TIMER" in hwc:
        cls = "TIMER"
    elif sdkpoll and not f.lib:
        cls = "SDK-POLL"
    elif hwc:
        cls = "HW"
    elif flag_ok:
        cls = "HANDLER-FLAG"
    elif progress:
        cls = "PROGRESS"
    elif sdkpoll:
        cls = "SDK-POLL"
    else:
        cls = "REVIEW"
    if L["lvl"] >= 3 and cls != "SAFE":
        note.append("blocks only on some iterations")
    if L["jalr"]:
        note.append(f"{len(L['jalr'])} indirect call(s)")
    if sdkpoll:
        note.append("sdk status fn: " + ",".join(sorted(sdkpoll)))
    return dict(cls=cls, polled=" | ".join(polled[:6]), kind="+".join(sorted(kinds)) or "call",
                kcall=kcall, yields=yields or "-", setters="; ".join(sorted(setters)[:6]) or "-",
                note="; ".join(note), needles=needles)


def handling(cls, lib, compiled):
    if cls in ("SAFE", "PROGRESS"):
        return "none"
    if cls == "HALT":
        return "spin hint turns it into a reported fatal halt" if compiled == "unit"             else "replaced (sce)"
    if compiled in ("excluded", "no-source"):
        return "replaced: src/sce reimplementation must not spin"
    if cls in ("HW", "TIMER"):
        return "HW accessor (charge+poll per read)"
    if cls == "SDK-POLL":
        return "sce status fn charges+polls"
    return "spin hint (stage spin)"


if __name__ == "__main__":
    sys.exit(main())

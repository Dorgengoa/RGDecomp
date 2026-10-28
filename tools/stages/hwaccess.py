#!/usr/bin/env python3
"""Ingest stage `hwaccess`: PLAN.md transform 5 (address literals) on the
game side.  docs/HWBUS.md documents the rules and the registration.

Rewrites, in compiled GAME files only (SDK/library files -- by path or by
the MAIN address band, portxform.classify_lib -- are left alone; their asm
is cut by asmexclude anyway), outside asm:

  1. Hardware dereferences (address 0x1000_0000-0x10FF_FFFF, 0x1200_0000-
     0x1200_FFFF), volatile or not:
        *(volatile T *)A             -> ((T)HW_R32(A))          rvalue
        *(volatile T *)A = v         -> HW_W32(A, v)            store
        *(volatile T *)A op= v       -> HW_W32(A, (T)HW_R32(A) op (v))
     The width (8/16/32/64) comes from T.  `#define NAME (*(volatile T *)A)`
     aliases: lvalue uses of NAME (NAME = v, NAME op= v) become HW_W*, then
     the define itself becomes the rvalue form, so a missed store would fail
     to compile instead of silently writing nowhere.
  2. Scratchpad pointer literals: (T *)0x7000xxxx -> (T *)PS2_SPR(0xxxxx).
  3. Mirror/mask idioms on DMA addresses (host pointers in the i686 build):
     a TABLE of reviewed sites (MASK_RULES below), each with the exact
     operand, -> `(p)`: the mask / mirror is the identity on a host pointer,
     so the site keeps only the operand (it was the identity marker
     PS2_PHYS(p) / PS2_UNCACHED(p) / PS2_UCAB(p) until 2026-10-25, D9 gate
     `native_only.addr_census`; HWACCESS.tsv still lists every site).
     A literal like 0x0FFFFFFF / 0x20000000 / 0x30000000 is NOT rewritten by
     pattern alone: in this game they are just as often DMAtag ids (REF =
     0x3000_0000, NEXT = 0x2000_0000), CHCR TAG fields or flag bits, which
     must stay.  LEAVE_RULES documents the reviewed sites that stay.
  5. (after 1-4) HW_R*/HW_W* on a register a native service owns -> a direct
     call into the service (NATIVE_REGS: native_read / native_write): T0
     -> rg_logic_t0_*, GS privileged -> rg_gs_reg_r64/w64(RG_GS_<REG>),
     VIF1_FBRST -> rg_vif1_fbrst_w32.  The game code then names no PS2
     address (PLAN.md D9; tools/native/addr_census.py).
  4. MAIN reads of overlay memory by literal address (*(T *)A, A inside an
     overlay's data/bss) -> (*(T *)((unsigned char *)sym + off)), a direct
     reference to the overlay symbol's arena label (declared in the prefix),
     through OVERLAY_SITES (address -> overlay symbol + offset).  It was
     RG_OVL_DATA(T, ovl, sym, symaddr, off) through hwbus's resolver until
     2026-10-18 (docs/UB-AUDIT.md "RG_OVL_DATA").  An overlay literal
     not in the table is an ERROR, never a guess.

Each changed file gets `#include "port/hwaccess.h"` prepended (marked
`/* rgp:hwaccess */`, followed by `#line 1` so presumed line numbers -- and
the census line numbers -- do not move).

Every rewrite is logged (HWACCESS.tsv: file, line, symbol, rule, address,
before, after).  report() reconciles the log with census/addr_literals.tsv:
every game row is either rewritten, inside asm (cut), or left with a reason.
Idempotent: a second pass changes nothing.

Registration (tools/ingest.py, owned by the integration step): LAST, after
`spin` (spin matches loop headers textually, and some hardware polls are
loop conditions):

    import hwaccess
    hw = hwaccess.HwAccessStage()
    Stage("hwaccess", hw.apply, ("unit",), hw)
    # hw.extra_outputs() -> {"HWACCESS.tsv": ...}; hw.report(); hw.errors

Standalone test on a copy of game/:

    python tools/stages/hwaccess.py --game game --out out/hw-test/game
"""
from __future__ import annotations

import argparse
import csv
import re
import shutil
import sys
from dataclasses import dataclass, field
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
import portxform as X  # noqa: E402  (read-only reuse: blank, find_funcs, asm_blocks, classify_lib)

CENSUS = PORT / "census" / "addr_literals.tsv"
MARK = "/* rgp:hwaccess */"
INCLUDE = MARK + ' #include "port/hwaccess.h"\n#line 1\n'

# ------------------------------------------------------------------ tables
# Overlay data/bss ranges [lo, hi): vram 0x004E9E80 + data start, + data + bss
# (../RGDecomp 2efa6b43 config/<ovl>.yaml: header sizes and the `data`
# subsegment start).  tests/hwbus verifies them against git when available.
OVERLAY_DATA = {
    "title":   (0x004F1400, 0x004F1B80),
    "insmenu": (0x004F9780, 0x004FA300),
    "factory": (0x0050B480, 0x00510C00),
    "insect":  (0x00523B00, 0x00526080),
    "normal":  (0x00524D00, 0x00528200),
}
OVERLAY_RANGE = (0x004E9E80, 0x00534CF4)   # census overlay_range

# address -> (overlay, symbol, symbol address).  Evidence: NORMAL's field-HUD
# work block D_00527020 (bss; MAIN references it by name, e.g.
# FieldHudInitOnce_204120, FieldHudAllySuggestCancel_203c80);
# naming config/names.txt (2efa6b43): FieldHudGetSuggestMember_203c20 reads
# "+0x3A2 (D_005273C2) suggest state", FieldHudGetSuggestMemberPtr_203c60
# "D_005273B8 = FieldHud D_00527020 +0x398".
OVERLAY_SITES = {
    0x005273C2: ("normal", "D_00527020", 0x00527020),   # FieldHud +0x3A2 suggest state (s16)
    0x005273CE: ("normal", "D_00527020", 0x00527020),   # FieldHud +0x3AE (s8 flag)
}


@dataclass(frozen=True)
class MaskRule:
    symbol: str      # function / file stem
    kind: str        # phys | uncached | ucab | regex
    operand: str     # exact operand text (whitespace-insensitive), or a regex
    repl: str = ""   # regex rules: replacement template
    count: int = 1   # expected sites in the file
    why: str = ""


# Reviewed address idioms (census rows of category seg_mask / uncached /
# uncached_accel, conf medium/high, plus the shift-mask spelling the census
# cannot see).  `operand` is the C expression the mask/mirror applies to.
MASK_RULES = [
    MaskRule("GfxDrawPerfMeter_1431c0", "phys", "r", why="DMAtag ADDR (GsPktEnd packet)"),
    MaskRule("GfxDrawPerfMeter_1431c0", "phys", "k", why="DMAtag ADDR"),
    MaskRule("DrawListAddVramCopy_1414a0", "phys", "(u32)hdr", why="DMAtag ADDR"),
    MaskRule("DrawListClearScreen_1423c0", "phys", "(u32)r", why="DMAtag ADDR"),
    MaskRule("DrawListClearScreen_1423c0", "phys", "(u32)q", why="DMAtag ADDR"),
    MaskRule("DrawListEmitFrameEnvMaybe_142280", "phys", "(u32)r", why="DMAtag ADDR"),
    MaskRule("DrawListEmitFrameEnvMaybe_142280", "phys", "(u32)q", why="DMAtag ADDR"),
    MaskRule("DrawListFrameBegin_1425d0", "phys", "(u32)func_00436980", why="DMAtag ADDR (packet symbol)"),
    MaskRule("DrawListFrameBegin_1425d0", "phys", "(u32)q", why="DMAtag ADDR"),
    MaskRule("GfxBlitTexRect_141000", "phys", "(a)", why="PUTTAG macro: DMAtag ADDR"),
    MaskRule("GfxEndFrame_141c20", "phys", "(u32)r", why="DMAtag ADDR"),
    MaskRule("GfxEndFrame_141c20", "phys", "(u32)a", why="DMAtag ADDR"),
    MaskRule("MeshMaterialBuildPkt_14ac90", "phys", "(u32)pkt", why="DMA address of the packet"),
    MaskRule("TexBuildClutUploadPkt_157d70", "phys", "(u32)((u8 *)arg1 + 0x410)", why="DMAtag ADDR"),
    MaskRule("TexBuildClutUploadPkt_157d70", "phys", "(u32)((u8 *)arg1 + 0x10)", count=2, why="DMAtag ADDR"),
    MaskRule("TexBuildClutUploadPkt_157d70", "phys", "(u32)((u8 *)arg1 + 0x50)", why="DMAtag ADDR"),
    MaskRule("DmaPktAddCallTagIfSet_141bb0", "phys", "v", why="CALL tag ADDR"),
    MaskRule("DmaPktAddCallTag_141b80", "phys", "v", why="CALL tag ADDR"),
    MaskRule("DrawListAddEnv_1421d0", "phys", "(u32)k", why="DMAtag ADDR"),
    MaskRule("DrawListAddTexLoad_1418c0", "phys", "temp_16", why="DMAtag ADDR (base + count*16)"),
    MaskRule("DrawListEndPrim_141a20", "phys", "(u32)t", why="DMAtag ADDR"),
    MaskRule("DrawListEndPrim_141a20", "phys", "(u32)k", why="DMAtag ADDR"),
    MaskRule("GsUploadImage16Blocks_1d27a0", "uncached", "(u64)(u32)dst",
             why="packet built through the uncached mirror (DMAC.md)"),
    MaskRule("GsUploadImage16Blocks_1d27a0", "phys", "(u64)(u32)src", why="sceGifPkRef address (DMAC.md)"),
    MaskRule("MovieOpen_1d5cf0", "uncached", "F(u32, 4)", why="VoBuf through the uncached mirror"),
    MaskRule("ViBufCreate_1d46f0", "uncached", "param_3", why="ViBuf data through the uncached mirror"),
    MaskRule("ViBufGetFifoIndex_1d4860", "phys", "combined",
             why="compares a ViBuf address (uncached, ViBufCreate) with D4_MADR"),
    MaskRule("DrawListInitDoubleBufMaybe_1427e0", "ucab", "k1", why="MemStack base through the UCAB mirror"),
    MaskRule("DrawListInitDoubleBufMaybe_1427e0", "ucab", "k2", why="MemStack base through the UCAB mirror"),
    MaskRule("VideoDecStrCallback_1d4d50", "regex",
             r"\(\s*\(\s*u64\s*\)\s*\(\s*\(\s*s64\s*\)\s*(\w+)\s*<<\s*0x24\s*\)\s*>>\s*0x24\s*\)"
             r"\s*\|\s*0x20000000\b",
             r"((u64)(u32)\1)", count=2,
             why="64-bit shift pair = & 0x0FFFFFFF, then uncached mirror (IPU output)"),
    # interim snapshot b09ccfa1 (decomp d784320c de-asm): new C spellings
    MaskRule("DrawListEmitBucket_1405a0", "phys", "(u32)(x)", why="ADDR() macro: DMAtag ADDR"),
    MaskRule("ModelMeshBuildUnpackPktMaybe_15b2a0", "phys", "(u32)start", why="DMAtag ADDR"),
    MaskRule("ViBufReset_1d45b0", "phys", "a", why="IPU ring DMAtag ADDR"),
    MaskRule("ViBufReset_1d45b0", "phys", "(u32)r->desc", count=2,
             why="DMAtag ADDR / D4_TADR (tag chain)"),
    MaskRule("ViBufReset_1d45b0", "phys", "(u32)r->buf", why="D4_MADR"),
    MaskRule("VideoDecFlush_1d5310", "uncached", "a", why="IPU output buffer, uncached mirror"),
    MaskRule("VideoDecFlush_1d5310", "uncached", "c", why="IPU output buffer, uncached mirror"),
    MaskRule("ViBufRestartDma_1d3e70", "regex", r"\bLOW28\s*\(\s*(c->phys\b)",
             r"(\1", count=2,
             why="LOW28 on the ring's DMA address (madr); LOW28 on CHCR values stays"),
]

# Reviewed medium/high census rows that are NOT addresses and stay as they are.
LEAVE_RULES = {
    ("ViBufAddDma_1d4240", "0x0FFFFFFF"): "CHCR value: keeps bits 0-27, sets TAG id REF (3<<28)",
    ("ViBufAddDma_1d4240", "0x30000000"): "CHCR TAG field id REF, not a UCAB address",
    ("ViBufRestartDma_1d3e70", "0x0FFFFFFF"): "LOW28 define; the c->phys uses become PS2_PHYS, "
                                             "the CHCR uses (c->unk28) stay",
    ("TexEnvBuildDmaChainMaybe_14abb0", "0x30000000"): "DMAtag: qwc | id REF",
    ("GsBuildImageUploadPkt_1581b0", "0x30000000"): "DMAtag: qwc | id REF",
    ("GsBuildImageUploadRefPkt_158390", "0x30000000"): "DMAtag: qwc | id REF",
    ("ModelMeshBuildUnpackPktMaybe_15b2a0", "0x30000000"): "DMAtag: qwc | id REF",
    ("CharaAssignWeapon_214620", "0x20000000"): "flag bit in +0xA54 (siblings set 0x80000000/0x40000000)",
    ("CharaActionUpdateMaybe_215ca0", "0x20000000"): "action flag bit",
    ("EvObjPreUpdateBase_2f9930", "0x20000000"): "object flag bit",
    ("TrailRibbonSetTextured_32c780", "0x20000000"): "flag bit (TrailRibbonIsTextured tests it)",
}

# ------------------------------------------------------------------ lexing
HEX = r"0x[0-9A-Fa-f]+[uUlL]*"
TYPE = r"(?:(?:const|volatile|signed|unsigned|struct)\s+)*[A-Za-z_]\w*(?:\s+(?:long|int|short|char))*"
DEREF_RX = re.compile(
    r"\*\s*\(\s*(?P<vol1>volatile\s+)?(?P<T>" + TYPE + r")\s*(?P<vol2>volatile\s*)?\*\s*\)\s*"
    r"(?P<A>\(\s*" + HEX + r"\s*\)|" + HEX + r")")
SPR_RX = re.compile(r"\(\s*(?P<T>" + TYPE + r")\s*\*\s*\)\s*(?P<A>0x7000[0-9A-Fa-f]{4}[uUlL]*)\b")
DEFINE_RX = re.compile(
    r"^[ \t]*#[ \t]*define[ \t]+(?P<name>[A-Za-z_]\w*)[ \t]+\(?\s*(?P<deref>\*\s*\([^()\n]*\)\s*"
    r"(?:\(\s*" + HEX + r"\s*\)|" + HEX + r"))\s*\)?[ \t\r]*$", re.M)
ASSIGN_RX = re.compile(r"\s*(<<=|>>=|\+=|-=|\*=|/=|%=|&=|\|=|\^=|=(?!=)|\+\+|--)")

WIDTH = {
    "s8": 8, "u8": 8, "char": 8, "signed char": 8, "unsigned char": 8,
    "s16": 16, "u16": 16, "short": 16, "unsigned short": 16, "signed short": 16,
    "s32": 32, "u32": 32, "int": 32, "unsigned int": 32, "signed int": 32, "unsigned": 32,
    "signed": 32, "long": 32, "unsigned long": 32, "signed long": 32,
    "s64": 64, "u64": 64, "long long": 64, "unsigned long long": 64, "signed long long": 64,
}


# Registers a native service owns (D9: the game names the service, not the PS2 address;
# include/port/hwaccess.h declares the calls, docs/HWBUS.md "Native register sites"):
#   T0_COUNT / T0_MODE     the game's frame clock -> native logic time
#                          (src/native/threads/rg_logic_time.c, NATIVE-CPU.md section 8)
#   GS privileged regs     the renderer's display / CSR state by register id
#                          (src/native/render/nr_hw.c; the oracle twin: src/ps2/hwbus)
#   VIF1_FBRST             the stall cancel (nr_hw.c)
RG_T0_COUNT, RG_T0_MODE, RG_VIF1_FBRST = 0x10000000, 0x10000010, 0x10003C10
GS_REGS = {0x12000000: "PMODE", 0x12000010: "SMODE1", 0x12000020: "SMODE2",
           0x12000030: "SRFSH", 0x12000040: "SYNCH1", 0x12000050: "SYNCH2",
           0x12000060: "SYNCV", 0x12000070: "DISPFB1", 0x12000080: "DISPLAY1",
           0x12000090: "DISPFB2", 0x120000A0: "DISPLAY2", 0x120000B0: "EXTBUF",
           0x120000C0: "EXTDATA", 0x120000D0: "EXTWRITE", 0x120000E0: "BGCOLOR",
           0x12001000: "CSR", 0x12001010: "IMR", 0x12001040: "BUSDIR", 0x12001080: "SIGLBLID"}


def native_read(w: int, addr: int):
    if w == 32 and addr == RG_T0_COUNT:
        return "rg_logic_t0_count()"
    if w == 64 and addr in GS_REGS:
        return f"rg_gs_reg_r64(RG_GS_{GS_REGS[addr]})"
    return None


def native_write(w: int, addr: int, val: str):
    if w == 32 and addr == RG_T0_COUNT:
        return f"rg_logic_t0_set_count({val})"
    if w == 32 and addr == RG_T0_MODE:
        return f"rg_logic_t0_set_mode({val})"
    if w == 32 and addr == RG_VIF1_FBRST:
        return f"rg_vif1_fbrst_w32({val})"
    if w == 64 and addr in GS_REGS:
        return f"rg_gs_reg_w64(RG_GS_{GS_REGS[addr]}, {val})"
    return None


def lit(a: str) -> int:
    return int(re.sub(r"[()\s]|[uUlL]+$", "", a), 16)


def is_hw(addr: int) -> bool:
    return 0x10000000 <= addr <= 0x10FFFFFF or 0x12000000 <= addr <= 0x1200FFFF


def is_ovl(addr: int) -> bool:
    return OVERLAY_RANGE[0] <= addr < OVERLAY_RANGE[1]


def base_type(t: str) -> str:
    t = re.sub(r"\b(const|volatile)\b", " ", t)
    return re.sub(r"\s+", " ", t).strip()


def norm(s: str) -> str:
    return re.sub(r"\s+", "", s)


def ws_regex(s: str) -> str:
    """`s` as a regex that allows any whitespace between its tokens."""
    out = []
    for ch in s:
        if ch.isspace():
            continue
        if out:
            out.append(r"\s*")
        out.append(re.escape(ch))
    return "".join(out)


def _continued(code: str, nl: int) -> bool:
    """Does the line ending at newline `nl` end in a backslash (CRLF-safe)?"""
    return code[max(0, nl - 2):nl].rstrip("\r").endswith("\\")


def pp_line_span(code: str, off: int):
    """(start, end) of the preprocessor line containing off, or None."""
    ls = code.rfind("\n", 0, off) + 1
    while ls > 0 and _continued(code, ls - 1):
        ls = code.rfind("\n", 0, ls - 1) + 1
    if not re.match(r"[ \t]*#", code[ls:]):
        return None
    le = ls
    while True:
        nl = code.find("\n", le)
        if nl < 0:
            return ls, len(code)
        if _continued(code, nl):
            le = nl + 1
            continue
        return ls, nl


def expr_end(code: str, i: int, limit: int) -> int:
    """End (exclusive) of the expression starting at i: stops at a top-level
    `;` / `,` or an unbalanced closer, or at `limit`."""
    depth = 0
    while i < limit:
        ch = code[i]
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            if depth == 0:
                break
            depth -= 1
        elif ch in ";," and depth == 0:
            break
        i += 1
    return i


def presumed_line(text: str, off: int) -> int:
    base, start = 1, 0
    for m in re.finditer(r"^[ \t]*#[ \t]*line[ \t]+(\d+)", text[:off], re.M):
        nl = text.find("\n", m.end())
        if nl < 0 or nl >= off:
            break
        base, start = int(m.group(1)), nl + 1
    return base + text.count("\n", start, off)


def file_image(relpath: str) -> str:
    p = relpath.split("/")
    if len(p) > 2 and p[1] == "overlays":
        return p[2]
    return p[1] if len(p) > 1 else "-"


def file_symbol(relpath: str) -> str:
    return Path(relpath).stem


def file_lib(relpath: str) -> str:
    m = re.search(r"_([0-9a-fA-F]{5,8})\.(?:c|cpp|cc)$", relpath)
    return X.classify_lib(relpath, file_image(relpath), int(m.group(1), 16) if m else None)[0]


# ------------------------------------------------------------------ stage
@dataclass
class Rewrite:
    file: str
    line: int
    symbol: str
    rule: str
    addr: str
    before: str
    after: str


@dataclass
class HwAccessStage:
    census: Path | None = CENSUS
    rows: list = field(default_factory=list)       # Rewrite
    errors: list = field(default_factory=list)     # (file, why)
    stats: dict = field(default_factory=dict)
    seen: set = field(default_factory=set)         # files applied
    _ovl_syms: set = field(default_factory=set)    # overlay symbols named in the current file

    QUICK = re.compile(r"0x(?:1[02]00|7000|0*5[0-3]|0*4[EF])[0-9A-Fa-f]{3,4}\b|0x0?FFFFFFF|"
                       r"0x[23]0000000|LOW28")

    def _bump(self, k: str, n: int = 1):
        self.stats[k] = self.stats.get(k, 0) + n

    # ingest Stage interface: apply(relpath, data) -> (data, sites)
    def __call__(self, relpath: str, data: bytes) -> tuple[bytes, int]:
        text = data.decode("utf-8", errors="surrogateescape")
        if not self.QUICK.search(text):
            return data, 0
        if file_lib(relpath) != "game":
            self._bump("skipped_sdk_or_library_files")
            return data, 0
        self.seen.add(relpath)
        self._ovl_syms = set()
        new, n = self.rewrite(relpath, text)
        if n == 0 or new == text:
            return data, 0
        if MARK not in new:
            link = '"C" ' if relpath.endswith(".cpp") else ""
            decl = "".join(f"{MARK} extern {link}unsigned char {sym}[];" + chr(10)
                           for sym in sorted(self._ovl_syms))
            new = INCLUDE.replace("#line 1", decl + "#line 1") + new
        return new.encode("utf-8", errors="surrogateescape"), n

    apply = __call__

    # -------------------------------------------------------------- core
    def _asm_spans(self, code: str):
        spans = [(a, b) for a, b, _ in X.asm_blocks(code)]
        try:
            for f in X.find_funcs(code):
                if f.is_asm:
                    spans.append((f.start, f.body_close))
        except Exception:                      # pragma: no cover (lexer edge)
            pass
        return spans

    def _log(self, relpath, text, off, rule, addr, before, after):
        self.rows.append(Rewrite(relpath, presumed_line(text, off), file_symbol(relpath), rule,
                                 addr, " ".join(before.split()), " ".join(after.split())))
        self._bump(rule)

    def rewrite(self, relpath: str, text: str) -> tuple[str, int]:
        n = 0
        text, k = self._aliases(relpath, text)
        n += k
        text, k = self._derefs(relpath, text)
        n += k
        text, k = self._spr(relpath, text)
        n += k
        text, k = self._masks(relpath, text)
        n += k
        text, k = self._native(relpath, text)
        n += k
        return text, n

    def _native(self, relpath: str, text: str) -> tuple[str, int]:
        """HW_R*/HW_W* on a register a native service owns (NATIVE_REGS) -> a direct call
        into that service, so the game code names no PS2 address (D9; docs/HWBUS.md
        "Native register sites").  Runs after the deref/alias rewrites (it sees their
        HW_* output, define bodies and read-modify-writes included)."""
        n = 0
        while True:
            code = X.blank(text)
            spans = self._asm_spans(code)
            hit = None
            for m in re.finditer(r"\bHW_([RW])(8|16|32|64)\s*\(", code):
                if any(a <= m.start() <= b for a, b in spans):
                    continue
                close = expr_end(code, m.end(), len(code))
                am = re.fullmatch(r"\s*\(?\s*(" + HEX + r")\s*\)?\s*", code[m.end():close])
                if not am:
                    continue
                addr, w = lit(am.group(1)), int(m.group(2))
                if m.group(1) == "R":
                    if code[close:close + 1] != ")":
                        continue
                    rep = native_read(w, addr)
                    end = close + 1
                else:
                    if code[close:close + 1] != ",":
                        continue
                    vend = expr_end(code, close + 1, len(code))
                    if code[vend:vend + 1] != ")":
                        continue
                    rep = native_write(w, addr, text[close + 1:vend].strip())
                    end = vend + 1
                if rep:
                    hit = (m.start(), end, rep, addr, m.group(1))
            if hit is None:
                return text, n
            s, e, rep, addr, rw = hit          # the LAST site first: offsets before it stay valid
            self._log(relpath, text, s, "native-read" if rw == "R" else "native-write",
                      f"0x{addr:08X}", text[s:e], rep)
            text = text[:s] + rep + text[e:]
            n += 1

    def _aliases(self, relpath: str, text: str) -> tuple[str, int]:
        """`#define NAME (*(volatile T *)A)`: rewrite lvalue uses of NAME."""
        code = X.blank(text)
        n = 0
        for m in DEFINE_RX.finditer(code):
            d = DEREF_RX.fullmatch(m.group("deref").strip())
            if not d or not is_hw(lit(d.group("A"))):
                continue
            name, t = m.group("name"), base_type(d.group("T"))
            addr = lit(d.group("A"))
            w = WIDTH.get(t)
            if w is None:
                self.errors.append((relpath, f"{name}: unsupported register type {t!r}"))
                continue
            while True:
                code = X.blank(text)
                spans = self._asm_spans(code)
                hit = None
                for u in re.finditer(r"\b" + re.escape(name) + r"\b", code):
                    if pp_line_span(code, u.start()) or any(a <= u.start() <= b for a, b in spans):
                        continue
                    a = ASSIGN_RX.match(code, u.end())
                    if a:
                        hit = (u, a)
                if hit is None:
                    break
                u, a = hit
                op = a.group(1)
                if op in ("++", "--"):
                    end = a.end()
                    rhs = "1"
                    op = op[0] + "="
                else:
                    end = expr_end(code, a.end(), len(code))
                    rhs = text[a.end():end].strip()
                val = rhs if op == "=" else f"{name} {op[:-1]} ({rhs})"
                rep = f"HW_W{w}(0x{addr:08X}u, {val})"
                before = text[u.start():end]
                self._log(relpath, text, u.start(), "alias-store", f"0x{addr:08X}", before, rep)
                text = text[:u.start()] + rep + text[end:]
                n += 1
        return text, n

    def _derefs(self, relpath: str, text: str) -> tuple[str, int]:
        n = 0
        done_offsets = set()
        while True:
            code = X.blank(text)
            spans = self._asm_spans(code)
            cands = []
            for m in DEREF_RX.finditer(code):
                if any(a <= m.start() <= b for a, b in spans):
                    continue
                addr = lit(m.group("A"))
                if is_hw(addr) or (is_ovl(addr) and file_image(relpath) == "main"):
                    cands.append(m)
            cands = [m for m in cands if m.start() not in done_offsets]
            if not cands:
                return text, n
            m = cands[-1]
            addr = lit(m.group("A"))
            t_raw = m.group("T")
            t = base_type(t_raw)
            pp = pp_line_span(code, m.start())
            limit = pp[1] if pp else len(code)
            a = ASSIGN_RX.match(code, m.end())
            if is_ovl(addr):
                site = OVERLAY_SITES.get(addr)
                if site is None:
                    self.errors.append((relpath, f"overlay literal 0x{addr:08X} not in OVERLAY_SITES"))
                    done_offsets.add(m.start())
                    continue
                ovl, sym, sa = site
                lo, hi = OVERLAY_DATA[ovl]
                if not (lo <= addr < hi and lo <= sa < hi):
                    self.errors.append((relpath, f"0x{addr:08X} outside {ovl} data/bss"))
                    done_offsets.add(m.start())
                    continue
                # a direct reference to the overlay symbol (the arena label
                # MAIN already links against: docs/OVERLAY.md "named overlay
                # data used by MAIN"); was RG_OVL_DATA through the resolver
                # (docs/UB-AUDIT.md "RG_OVL_DATA")
                rep = f"(*({t} *)((unsigned char *){sym} + 0x{addr - sa:X}))"
                self._ovl_syms.add(sym)
                self._log(relpath, text, m.start(), "overlay-data", f"0x{addr:08X}",
                          text[m.start():m.end()], rep)
                text = text[:m.start()] + rep + text[m.end():]
                n += 1
                continue
            w = WIDTH.get(t)
            if w is None:
                self.errors.append((relpath, f"0x{addr:08X}: unsupported register type {t!r}"))
                done_offsets.add(m.start())
                continue
            A = f"0x{addr:08X}u"
            if a:
                op = a.group(1)
                if op in ("++", "--"):
                    end, rhs, op = a.end(), "1", op[0] + "="
                else:
                    end = expr_end(code, a.end(), limit)
                    rhs = text[a.end():end].strip()
                if op == "=":
                    rep = f"HW_W{w}({A}, {rhs})"
                    rule = "hw-store"
                else:
                    rep = f"HW_W{w}({A}, ({t})HW_R{w}({A}) {op[:-1]} ({rhs}))"
                    rule = "hw-rmw"
            else:
                # prefix ++/-- on a register: not seen in the game; refuse
                pre = code[:m.start()].rstrip()
                if pre.endswith("++") or pre.endswith("--"):
                    self.errors.append((relpath, f"0x{addr:08X}: prefix ++/-- on a register"))
                    done_offsets.add(m.start())
                    continue
                end = m.end()
                rep = f"(({t})HW_R{w}({A}))"
                rule = "hw-load"
            self._log(relpath, text, m.start(), rule, f"0x{addr:08X}", text[m.start():end], rep)
            text = text[:m.start()] + rep + text[end:]
            n += 1

    def _spr(self, relpath: str, text: str) -> tuple[str, int]:
        code = X.blank(text)
        spans = self._asm_spans(code)
        n = 0
        for m in reversed(list(SPR_RX.finditer(code))):
            if any(a <= m.start() <= b for a, b in spans):
                continue
            off = lit(m.group("A")) & 0xFFFF
            rep = f"PS2_SPR(0x{off:X})"
            self._log(relpath, text, m.start(), "scratchpad", m.group("A"),
                      text[m.start("A"):m.end("A")], rep)
            text = text[:m.start("A")] + rep + text[m.end("A"):]
            n += 1
        return text, n

    def _masks(self, relpath: str, text: str) -> tuple[str, int]:
        sym = file_symbol(relpath)
        rules = [r for r in MASK_RULES if r.symbol == sym]
        n = 0
        for r in rules:
            code = X.blank(text)
            spans = self._asm_spans(code)
            if r.kind == "regex":
                rx = re.compile(r.operand)
                done_rx = None
            else:
                op = ws_regex(r.operand)
                if r.kind == "phys":
                    rx = re.compile(r"(?<![\w.>)\]])" + op + r"\s*&\s*0x0?FFFFFFF\b")
                elif r.kind == "uncached":
                    rx = re.compile(r"\(\s*(?<![\w.>)\]])" + op +
                                    r"\s*&\s*0x0?FFFFFFF\s*\)\s*\|\s*0x20000000\b")
                else:  # ucab
                    rx = re.compile(r"(?<![\w.>)\]])" + op + r"\s*\|\s*0x30000000\b")
                macro = {"phys": "PS2_PHYS", "uncached": "PS2_UNCACHED", "ucab": "PS2_UCAB"}[r.kind]
                done_rx = re.compile(re.escape(macro) + r"\(\s*" + op + r"\s*\)")
            ms = [m for m in rx.finditer(code) if not any(a <= m.start() <= b for a, b in spans)]
            already = len(done_rx.findall(code)) if done_rx else 0
            if r.kind == "regex":
                already = 0     # stripped: nothing marks a done site (MARK check below)
            if not ms:
                # stripped sites leave no marker: a file the stage already rewrote (MARK)
                # has none left to find
                if already >= r.count or MARK in text:
                    continue
                self.errors.append((relpath, f"mask rule {r.kind} {r.operand!r}: not found"))
                continue
            if len(ms) + (already if r.kind != "regex" else 0) != r.count and \
                    not (r.kind == "regex" and len(ms) == r.count):
                self.errors.append((relpath, f"mask rule {r.kind} {r.operand!r}: "
                                             f"{len(ms)} sites, expected {r.count}"))
                continue
            for m in reversed(ms):
                # D9: the segment mask / mirror is the identity on a host pointer, so the
                # site keeps just the operand (no marker; HWACCESS.tsv still lists it)
                if r.kind == "regex":
                    rep = m.expand(r.repl)
                elif r.kind == "phys":          # OPERAND & 0x0FFFFFFF
                    k = code.rfind("&", m.start(), m.end())
                    rep = f"({text[m.start():k].strip()})"
                elif r.kind == "ucab":          # OPERAND | 0x30000000
                    k = code.rfind("|", m.start(), m.end())
                    rep = f"({text[m.start():k].strip()})"
                else:                           # (OPERAND & 0x0FFFFFFF) | 0x20000000
                    k = code.rfind("&", m.start(), m.end())
                    rep = f"({text[m.start() + 1:k].strip()})"
                self._log(relpath, text, m.start(), f"mask-{r.kind}" if r.kind != "regex" else
                          "mask-regex", "-", text[m.start():m.end()], rep)
                text = text[:m.start()] + rep + text[m.end():]
                n += 1
        return text, n

    # -------------------------------------------------------------- outputs
    def tsv(self) -> str:
        out = ["file\tline\tsymbol\trule\taddr\tbefore\tafter"]
        for r in sorted(self.rows, key=lambda r: (r.file, r.line, r.rule)):
            out.append("\t".join([r.file, str(r.line), r.symbol, r.rule, r.addr,
                                  r.before.replace("\t", " "), r.after.replace("\t", " ")]))
        return "\n".join(out) + "\n"

    def extra_outputs(self) -> dict[str, bytes]:
        return {"HWACCESS.tsv": self.tsv().encode()}

    def reconcile(self) -> list[tuple]:
        """Every game row of census/addr_literals.tsv -> (row, disposition).
        A rewrite accounts for the census rows of the literals it removed
        (each (rewrite, literal) pair once; nearest line, +-1 because the
        census and the rewrite may see a wrapped statement on adjacent
        lines).  A define-alias row is accounted for by the define's
        rewrite."""
        if not self.census or not Path(self.census).exists():
            return []
        lines = [ln for ln in Path(self.census).read_text(encoding="utf-8").splitlines()
                 if not ln.startswith("#")]
        res = []
        by_file: dict[str, list[Rewrite]] = {}
        for r in self.rows:
            by_file.setdefault(r.file, []).append(r)
        used: set = set()

        def removes(r: Rewrite, v: int) -> bool:
            if r.addr == f"0x{v:08X}" and r.rule != "alias-store":
                return True
            if r.rule == "mask-phys":
                return v == 0x0FFFFFFF
            if r.rule == "mask-uncached":
                return v in (0x0FFFFFFF, 0x20000000)
            if r.rule == "mask-ucab":
                return v == 0x30000000
            if r.rule == "mask-regex":
                return v in (0x0FFFFFFF, 0x20000000) and (
                    "0x20000000" in r.before or "LOW28" in r.before)
            return False

        for row in csv.DictReader(lines, delimiter="	"):
            if row["lib"] != "game":
                continue
            f, ln, val = row["file"], int(row["line"] or 0), row["value"]
            v = int(val, 16)
            cands = sorted(((abs(r.line - ln), i) for i, r in enumerate(by_file.get(f, []))
                            if abs(r.line - ln) <= 1 and (id(r), v) not in used
                            and removes(r, v)), key=lambda c: c[0])
            key = (row["symbol"], f"0x{v:08X}")
            if key not in LEAVE_RULES:     # inline member bodies: census symbol is the method
                key = (file_symbol(f), key[1])
            if row["in_asm"] == "yes":
                disp = "asm: function cut by asmexclude (binds to an override)"
            elif cands:
                r = by_file[f][cands[0][1]]
                used.add((id(r), v))
                disp = f"rewritten: {r.rule} line {r.line}"
            elif key in LEAVE_RULES:
                disp = "left: " + LEAVE_RULES[key]
            elif row["conf"] == "low":
                disp = f"left: low-confidence {row['category']} (tag id / flag / colour / limit)"
            else:
                disp = "UNACCOUNTED"
            res.append((row, disp))
        return res

    def report(self) -> str:
        files = len({r.file for r in self.rows})
        out = [f"hwaccess: {len(self.rows)} rewrites in {files} files, {len(self.errors)} errors; "
               + ", ".join(f"{k}={v}" for k, v in sorted(self.stats.items()))]
        rec = self.reconcile()
        if rec:
            cnt: dict[str, int] = {}
            for _, d in rec:
                k = d.split(":")[0]
                cnt[k] = cnt.get(k, 0) + 1
            out.append("    census game rows: " + ", ".join(f"{k}={v}" for k, v in sorted(cnt.items())))
            for row, d in rec:
                if d == "UNACCOUNTED" and row["file"] in self.seen:
                    out.append(f"    UNACCOUNTED {row['file']}:{row['line']} {row['value']} "
                               f"{row['category']} {row['conf']}")
        for f, why in self.errors:
            out.append(f"    ERROR {f}: {why}")
        return "\n".join(out)


# ------------------------------------------------------------------ CLI
def main() -> int:
    ap = argparse.ArgumentParser(description="apply stage `hwaccess` to a copy of game/")
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--out", type=Path, default=PORT / "out" / "hw-test" / "game")
    ap.add_argument("--census", type=Path, default=CENSUS)
    ap.add_argument("--changed", type=Path, help="write the changed relpaths here")
    ap.add_argument("--one", nargs=2, metavar=("IN", "OUT"),
                    help="apply to one file (relpath = IN relative to --game, or --rel)")
    ap.add_argument("--rel", help="relpath the rules see for --one")
    a = ap.parse_args()
    st = HwAccessStage(a.census)
    if a.one:
        src, dst = Path(a.one[0]), Path(a.one[1])
        rel = a.rel or src.resolve().relative_to(a.game.resolve()).as_posix()
        data = src.read_bytes()
        new, n = st(rel, data)
        again, n2 = HwAccessStage(None)(rel, new)
        if again != new or n2:
            st.errors.append((rel, "NOT idempotent"))
        dst.parent.mkdir(parents=True, exist_ok=True)
        if not dst.exists() or dst.read_bytes() != new:
            dst.write_bytes(new)
        for f, why in st.errors:
            print(f"hwaccess: ERROR {f}: {why}", file=sys.stderr)
        return 1 if st.errors else 0
    rows = [ln.split("\t") for ln in (a.game / "MANIFEST.tsv").read_text().splitlines()[1:]]
    units = [r[0] for r in rows if len(r) > 3 and r[3] == "unit"]
    if a.out.exists():
        shutil.rmtree(a.out)
    for sub in ("include", "config"):
        shutil.copytree(a.game / sub, a.out / sub)
    for f in ("MANIFEST.tsv", "SNAPSHOT.txt", "EXCLUDED.tsv"):
        if (a.game / f).exists():
            shutil.copy2(a.game / f, a.out / f)
    changed = []
    for rel in units:
        data = (a.game / rel).read_bytes()
        new, n = st(rel, data)
        if new != data:
            again, n2 = HwAccessStage(None)(rel, new)
            if again != new or n2:
                st.errors.append((rel, "NOT idempotent"))
            (a.out / rel).parent.mkdir(parents=True, exist_ok=True)
            (a.out / rel).write_bytes(new)
            changed.append(rel)
    (a.out / "HWACCESS.tsv").write_text(st.tsv(), encoding="utf-8")
    rec = st.reconcile()
    with open(a.out / "HWACCESS_census.tsv", "w", encoding="utf-8") as fh:
        fh.write("file\tline\tsymbol\tcategory\tvalue\tconf\tdisposition\n")
        for row, d in rec:
            fh.write(f"{row['file']}\t{row['line']}\t{row['symbol']}\t{row['category']}\t"
                     f"{row['value']}\t{row['conf']}\t{d}\n")
    if a.changed:
        a.changed.write_text("\n".join(changed) + "\n")
    print(st.report())
    print(f"files changed: {len(changed)}")
    unacc = sum(1 for _, d in rec if d == "UNACCOUNTED")
    return 1 if (st.errors or unacc) else 0


if __name__ == "__main__":
    sys.exit(main())

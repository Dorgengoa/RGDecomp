#!/usr/bin/env python3
"""platform_misc.tsv -- the rest of the EE platform surface.

kind column:
  hwreg     loads/stores whose address is a straight-line constant in the EE
            register space (0x1000_0000..0x1100_FFFF: timers, IPU, GIF, VIF,
            DMA channels, INTC, SBUS, VU memories), per function and register
  spr       scratchpad accesses (constant base 0x7000_0000 page): per
            function, offset range and access count; plus functions that only
            execute `lui 0x7000` (ambiguous: SPR base OR a DMA END tag)
  api       per platform area (movie/IPU, memory card, pad, CDVD/streaming,
            timers/clock, IOP memory, SIF DMA): the library functions game code
            calls directly, with game caller counts (from the retail call graph)
Notes: only CONSTANT addresses are seen.  Pointer-held hardware addresses
(e.g. a DMA channel struct from sceDmaGetChan) are libdma's business and show
up via the api rows.
"""
from __future__ import annotations

import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

COLS = ["kind", "area", "name", "addr", "func", "is_game", "count", "detail"]

DMA_CH = {0x8000: "D0_VIF0", 0x9000: "D1_VIF1", 0xA000: "D2_GIF", 0xB000: "D3_fromIPU",
          0xB400: "D4_toIPU", 0xC000: "D5_SIF0", 0xC400: "D6_SIF1", 0xC800: "D7_SIF2",
          0xD000: "D8_fromSPR", 0xD400: "D9_toSPR"}
CH_REG = {0x00: "CHCR", 0x10: "MADR", 0x20: "QWC", 0x30: "TADR", 0x40: "ASR0",
          0x50: "ASR1", 0x80: "SADR"}
HW = {0x10000000: "T0_COUNT", 0x10000010: "T0_MODE", 0x10000020: "T0_COMP",
      0x10000030: "T0_HOLD", 0x10000800: "T1_COUNT", 0x10000810: "T1_MODE",
      0x10000820: "T1_COMP", 0x10000830: "T1_HOLD", 0x10001000: "T2_COUNT",
      0x10001010: "T2_MODE", 0x10001020: "T2_COMP", 0x10001800: "T3_COUNT",
      0x10001810: "T3_MODE", 0x10001820: "T3_COMP", 0x10002000: "IPU_CMD",
      0x10002010: "IPU_CTRL", 0x10002020: "IPU_BP", 0x10002030: "IPU_TOP",
      0x10003000: "GIF_CTRL", 0x10003010: "GIF_MODE", 0x10003020: "GIF_STAT",
      0x10003800: "VIF0_STAT", 0x10003810: "VIF0_FBRST", 0x10003820: "VIF0_ERR",
      0x10003830: "VIF0_MARK", 0x10003C00: "VIF1_STAT", 0x10003C10: "VIF1_FBRST",
      0x10003C20: "VIF1_ERR", 0x10003C30: "VIF1_MARK", 0x10004000: "VIF0_FIFO",
      0x10005000: "VIF1_FIFO", 0x10006000: "GIF_FIFO", 0x10007000: "IPU_out_FIFO",
      0x10007010: "IPU_in_FIFO", 0x1000E000: "D_CTRL", 0x1000E010: "D_STAT",
      0x1000E020: "D_PCR", 0x1000E030: "D_SQWC", 0x1000E040: "D_RBSR",
      0x1000E050: "D_RBOR", 0x1000E060: "D_STADR", 0x1000F000: "INTC_STAT",
      0x1000F010: "INTC_MASK", 0x1000F200: "SBUS_MSCOM", 0x1000F210: "SBUS_SMCOM",
      0x1000F220: "SBUS_MSFLG", 0x1000F230: "SBUS_SMFLG", 0x1000F240: "SBUS_CTRL",
      0x1000F260: "SBUS_F260", 0x1000F520: "D_ENABLER", 0x1000F590: "D_ENABLEW"}

AREAS = [
    ("movie/IPU", lambda f: f.lib and f.lib[0] == "libmpeg"),
    ("memory card", lambda f: f.lib and f.lib[0] == "libmc"),
    ("pad", lambda f: f.lib and f.lib[0] == "libpad"),
    ("cdvd", lambda f: f.lib and f.lib[0] == "libcdvd"),
    ("file I/O (fileio RPC)", lambda f: f.lib and f.lib[1] == "fileio"),
    ("IOP memory/modules", lambda f: f.lib and f.lib[1] in ("iopheap", "loadfile", "iopcontrol")),
    ("SIF DMA/RPC", lambda f: f.lib and f.lib[1] in ("sifcmd", "sifrpc") or
     f.name in ("sceSifSetDma", "sceSifDmaStat", "isceSifSetDma", "sceSifSetDChain")),
    ("sound (sdremote)", lambda f: f.lib and f.lib[0] in ("libsdr", "libsdr-gcc")),
    ("timers/clock", lambda f: f.lib and f.lib[1] in ("timer/alarm", "vsync") or
     f.name.startswith(("DelayThread", "SetAlarm", "iSetAlarm"))),
    ("graphics (libgraph/libdma/libpkt)", lambda f: f.lib and f.lib[0] in
     ("libgraph", "libdma", "libpkt")),
    ("vu0 math (libvu0)", lambda f: f.lib and f.lib[0] == "libvu0"),
    ("cache/intc", lambda f: f.lib and f.lib[1] in ("cache", "intc/dmac/thread") and
     not f.name.startswith(("DelayThread", "StartThread"))),
]


def hwname(a):
    if a in HW:
        return HW[a]
    if 0x10008000 <= a < 0x1000E000:
        base = a & ~0x3FF if (a & 0xFFFF) >= 0xB400 else a & ~0xFFF
        for b in (a & 0xFFFFFC00, a & 0xFFFFF000):
            ch = DMA_CH.get(b & 0xFFFF)
            if ch:
                return f"{ch}_{CH_REG.get(a - b, f'+0x{a - b:X}')}"
    if 0x11000000 <= a < 0x11004000:
        return f"VU0_MICRO+0x{a - 0x11000000:X}"
    if 0x11004000 <= a < 0x11008000:
        return f"VU0_MEM+0x{a - 0x11004000:X}"
    if 0x11008000 <= a < 0x1100C000:
        return f"VU1_MICRO+0x{a - 0x11008000:X}"
    if 0x1100C000 <= a < 0x11010000:
        return f"VU1_MEM+0x{a - 0x1100C000:X}"
    return f"0x{a:08X}"


LOADS = {0x20, 0x21, 0x23, 0x24, 0x25, 0x27, 0x37, 0x1E, 0x31, 0x36}
STORES = {0x28, 0x29, 0x2B, 0x3F, 0x1F, 0x39, 0x3E}


def main():
    facts, imgs, edges, files = C.cached()
    hw = defaultdict(Counter)       # (reg name) -> Counter(func key)
    hw_rw = defaultdict(set)
    spr = defaultdict(list)         # func -> offsets
    spr_form = set()
    funcs = {}
    for iname, im in imgs.items():
        for f in im.fns:
            sim = C.RegSim(im, imgs)
            for pc, w in C.insns(im, f):
                op = w >> 26
                if op in LOADS or op in STORES:
                    rs = (w >> 21) & 31
                    base = sim.r.get(rs)
                    if isinstance(base, int):
                        a = (base + C.sx16(w & 0xFFFF)) & 0xFFFFFFFF
                        if 0x10000000 <= a < 0x11010000:
                            n = hwname(a)
                            hw[n][(iname, f.name)] += 1
                            hw_rw[(n, iname, f.name)].add("W" if op in STORES else "R")
                            funcs[(iname, f.name)] = f
                        elif 0x70000000 <= a < 0x70004000:
                            spr[(iname, f.name)].append(a - 0x70000000)
                            funcs[(iname, f.name)] = f
                if op == 0x0F and (w & 0xFFFF) == 0x7000:
                    spr_form.add((iname, f.name))
                    funcs[(iname, f.name)] = f
                sim.step(w)
                if op == 3 or (op == 0 and (w & 63) == 9):
                    sim.after_call()
    rows = []
    for n in sorted(hw):
        for (iname, fn), c in sorted(hw[n].items()):
            f = funcs[(iname, fn)]
            area = "DMA" if n.startswith("D") else n.split("_")[0]
            rows.append({"kind": "hwreg", "area": area, "name": n, "func": fn,
                         "is_game": "yes" if f.is_game else "no(" + "/".join(f.lib) + ")",
                         "count": c, "addr": "",
                         "detail": "".join(sorted(hw_rw[(n, iname, fn)])) + f" image={iname}"})
    for key in sorted(set(spr) | spr_form):
        f = funcs[key]
        offs = spr.get(key, [])
        rows.append({"kind": "spr", "area": "scratchpad", "name": "SPR",
                     "func": key[1], "is_game": "yes" if f.is_game else "no(" + "/".join(f.lib) + ")",
                     "count": len(offs),
                     "addr": (f"0x{min(offs):X}..0x{max(offs):X}" if offs else ""),
                     "detail": ("direct const-address accesses" if offs else
                                "only `lui 0x7000`: AMBIGUOUS -- 0x7000xxxx is also a DMA END "
                                "tag (id 7, e.g. GfxEndFrame writes 0x70000003); no "
                                "constant-address SPR load/store in this function")
                     + f" image={key[0]}"})
    # api per area
    gc = defaultdict(set)
    for e in edges:
        if e.kind in ("call", "tail") and e.src.is_game and e.dst.lib:
            gc[e.dst.key].add((e.src.image, e.src.name))
    m = imgs["main"]
    for area, pred in AREAS:
        for f in m.fns:
            if f.lib and pred(f) and gc.get(f.key):
                cs = sorted(n for _, n in gc[f.key])
                rows.append({"kind": "api", "area": area, "name": f.name,
                             "addr": f"0x{f.addr:06X}", "func": " ".join(cs[:5]) +
                             (f" (+{len(cs) - 5})" if len(cs) > 5 else ""),
                             "is_game": "yes", "count": len(cs),
                             "detail": "/".join(f.lib)})
    k = Counter(r["kind"] for r in rows)
    C.write_tsv(C.OUT / "platform_misc.tsv", COLS, rows, C.meta(
        "misc", {"rows": len(rows), "kinds": ", ".join(f"{a}={b}" for a, b in sorted(k.items()))}))
    print(k)


if __name__ == "__main__":
    main()

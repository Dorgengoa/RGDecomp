#!/usr/bin/env python3
"""platform_gs.tsv -- GS state the game sets, as far as the retail code shows it.

kind column:
  priv      a store to a privileged GS register (0x12000000 page, const
            base) -- PMODE/SMODE*/SYNC*/DISPFB*/DISPLAY*/BGCOLOR/CSR/IMR...;
            value when it is a straight-line constant
  ad_code   an A+D register id stored as a constant to a qword's high half
            (offset%16 == 8) in code; `value` is the data half stored (sd) at
            offset-8 through the same base register when constant.  Heuristic:
            confidence=high when the function stores >=2 distinct GS ids >1
            this way (a packet builder), low otherwise (could be any small
            int).  Ids 0 (PRIM) and 1 (RGBAQ) count only with a paired sd of
            the data half (bare 0/1 stores are zero-fill noise).
  ad_data   an A+D pair inside a PACKED GIF tag found in .data (REGS=0xE,
            NREG=1, FLG=0, NLOOP<=32, every id a valid GS reg) -- prebuilt packets
  api_arg   constant arguments at call sites of the game's GS state setters
            (GsPkt*/GsTest*/GsEnv*/DrawEnv*/GsFrame*/GsZbuf*/GsTex1*/GsFba*/
            sceGs*): the histogram of values per argument
  table     .data tables the setters index (decoded values)
  summary   per GS register: sites by kind; `dynamic` = sites whose value is
            not a constant
"""
from __future__ import annotations

import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

GS_REGS = {
    0x00: "PRIM", 0x01: "RGBAQ", 0x02: "ST", 0x03: "UV", 0x04: "XYZF2", 0x05: "XYZ2",
    0x06: "TEX0_1", 0x07: "TEX0_2", 0x08: "CLAMP_1", 0x09: "CLAMP_2", 0x0A: "FOG",
    0x0C: "XYZF3", 0x0D: "XYZ3", 0x14: "TEX1_1", 0x15: "TEX1_2", 0x16: "TEX2_1",
    0x17: "TEX2_2", 0x18: "XYOFFSET_1", 0x19: "XYOFFSET_2", 0x1A: "PRMODECONT",
    0x1B: "PRMODE", 0x1C: "TEXCLUT", 0x22: "SCANMSK", 0x34: "MIPTBP1_1",
    0x35: "MIPTBP1_2", 0x36: "MIPTBP2_1", 0x37: "MIPTBP2_2", 0x3B: "TEXA",
    0x3D: "FOGCOL", 0x3F: "TEXFLUSH", 0x40: "SCISSOR_1", 0x41: "SCISSOR_2",
    0x42: "ALPHA_1", 0x43: "ALPHA_2", 0x44: "DIMX", 0x45: "DTHE", 0x46: "COLCLAMP",
    0x47: "TEST_1", 0x48: "TEST_2", 0x49: "PABE", 0x4A: "FBA_1", 0x4B: "FBA_2",
    0x4C: "FRAME_1", 0x4D: "FRAME_2", 0x4E: "ZBUF_1", 0x4F: "ZBUF_2",
    0x50: "BITBLTBUF", 0x51: "TRXPOS", 0x52: "TRXREG", 0x53: "TRXDIR", 0x54: "HWREG",
    0x60: "SIGNAL", 0x61: "FINISH", 0x62: "LABEL"}
PRIV = {0x0000: "PMODE", 0x0010: "SMODE1", 0x0020: "SMODE2", 0x0030: "SRFSH",
        0x0040: "SYNCH1", 0x0050: "SYNCH2", 0x0060: "SYNCV", 0x0070: "DISPFB1",
        0x0080: "DISPLAY1", 0x0090: "DISPFB2", 0x00A0: "DISPLAY2", 0x00B0: "EXTBUF",
        0x00C0: "EXTDATA", 0x00D0: "EXTWRITE", 0x00E0: "BGCOLOR", 0x1000: "CSR",
        0x1010: "IMR", 0x1040: "BUSDIR", 0x1080: "SIGLBLID"}
PRIM_T = ["POINT", "LINE", "LINESTRIP", "TRIANGLE", "TRISTRIP", "TRIFAN", "SPRITE",
          "(7)"]
SETTER = re.compile(r"^(GsPkt|GsTest|GsEnv|DrawEnv|GsFrame|GsZbuf|GsTex1|GsFba|"
                    r"FogColReg|GfxSetVideoMode|sceGs|GsDbuf|GsClear)")

COLS = ["kind", "reg", "name", "value", "decoded", "count", "where", "confidence",
        "note"]


def decode(reg, v):
    if not isinstance(v, int):
        return ""
    n = GS_REGS.get(reg, "")
    if n == "PRIM":
        b = [k for k, bit in (("IIP", 3), ("TME", 4), ("FGE", 5), ("ABE", 6), ("AA1", 7),
                              ("FST", 8), ("CTXT", 9), ("FIX", 10)) if v >> bit & 1]
        return PRIM_T[v & 7] + ("+" + "+".join(b) if b else "")
    if n.startswith("ALPHA"):
        s = ["Cs", "Cd", "0", "?"]
        a = ["As", "Ad", "FIX", "?"]
        return (f"({s[v & 3]}-{s[v >> 2 & 3]})*{a[v >> 4 & 3]}>>7+{s[v >> 6 & 3]}"
                f" FIX={v >> 32 & 0xFF}")
    if n.startswith("TEST"):
        at = ["NEVER", "ALWAYS", "LESS", "LEQUAL", "EQUAL", "GEQUAL", "GREATER", "NOTEQUAL"]
        af = ["KEEP", "FB_ONLY", "ZB_ONLY", "RGB_ONLY"]
        zt = ["NEVER", "ALWAYS", "GEQUAL", "GREATER"]
        out = []
        if v & 1:
            out.append(f"ATE {at[v >> 1 & 7]} ref={v >> 4 & 0xFF} fail={af[v >> 12 & 3]}")
        if v >> 14 & 1:
            out.append(f"DATE DATM={v >> 15 & 1}")
        if v >> 16 & 1:
            out.append(f"ZTE {zt[v >> 17 & 3]}")
        return "; ".join(out) or "all off"
    if n == "TEXA":
        return f"TA0={v & 0xFF} AEM={v >> 15 & 1} TA1={v >> 32 & 0xFF}"
    if n.startswith("CLAMP"):
        m = ["REPEAT", "CLAMP", "REGION_CLAMP", "REGION_REPEAT"]
        return f"WMS={m[v & 3]} WMT={m[v >> 2 & 3]}"
    if n in ("COLCLAMP", "DTHE", "PABE", "PRMODECONT") or n.startswith("FBA"):
        return str(v & 1)
    return ""


def scan_code(imgs):
    priv, ad = [], []
    for iname, im in imgs.items():
        for f in im.fns:
            sim = C.RegSim(im, imgs)
            stores = []          # (base_reg, off, width, value, pc)
            for pc, w in C.insns(im, f):
                op = w >> 26
                if op in (0x2B, 0x3F):   # sw / sd
                    rs, rt = (w >> 21) & 31, (w >> 16) & 31
                    off = C.sx16(w & 0xFFFF)
                    base = sim.r.get(rs)
                    val = sim.r.get(rt)
                    if isinstance(base, int) and 0x12000000 <= (base + off) & 0xFFFFFFFF < 0x12002000:
                        a = (base + off) & 0xFFFFFFFF
                        priv.append((iname, f, a & 0x1FFF, val if isinstance(val, int) else None, pc))
                    stores.append((rs, off, 8 if op == 0x3F else 4, val, pc))
                sim.step(w)
                if op == 3 or (op == 0 and (w & 63) == 9):
                    sim.after_call()
            ids = []
            for rs, off, wd, val, pc in stores:
                if off % 16 == 8 and isinstance(val, int) and val in GS_REGS:
                    data, paired = None, False
                    for rs2, off2, wd2, val2, _ in stores:
                        if rs2 == rs and off2 == off - 8 and wd2 == 8:
                            paired = True
                            data = val2 if isinstance(val2, int) else None
                    if val <= 1 and not paired:
                        continue   # bare 0/1 stores: zero-fill noise, not A+D
                    ids.append((val, data, pc))
            distinct = {i for i, _, _ in ids if i > 1}
            for reg, data, pc in ids:
                ad.append((iname, f, reg, data, pc,
                           "high" if len(distinct) >= 2 else "low"))
    return priv, ad


def scan_data_tags(imgs):
    out = []
    for iname, im in imgs.items():
        d = im.data
        for o in range(0, len(d) - 16, 16):
            a = im.base + o
            if im.fn_at(a) is not None:
                continue
            lo, hi = struct.unpack_from("<QQ", d, o)
            nloop = lo & 0x7FFF
            flg = lo >> 58 & 3
            nreg = lo >> 60 & 0xF
            if hi != 0xE or nreg != 1 or flg != 0 or not 1 <= nloop <= 32:
                continue
            if lo >> 16 & 0x3FFFFFFF and not (lo >> 46 & 1):
                continue   # junk in the unused middle bits
            if o + 16 * (nloop + 1) > len(d):
                continue
            pairs = [struct.unpack_from("<QQ", d, o + 16 * (k + 1)) for k in range(nloop)]
            if not all(r in GS_REGS for _, r in pairs):
                continue
            pre = lo >> 46 & 1
            out.append((iname, a, lo, pairs, pre))
    return out


def api_args(imgs, facts, files):
    m = imgs["main"]
    targets = {}
    for im in imgs.values():
        for f in im.fns:
            if SETTER.match(f.name.split("_", 1)[-1] if im.name != "main" else f.name):
                targets[f.addr] = f
    hist = defaultdict(Counter)
    sites = Counter()
    callers = defaultdict(set)
    for iname, im in imgs.items():
        for f in im.fns:
            if not f.is_game:
                continue
            for site, tgt, (r, _, _) in C.callsites(im, f, set(targets), imgs):
                t = C.resolve(imgs, iname, tgt)
                if t is None or t.addr != tgt:
                    continue
                sites[t.name] += 1
                callers[t.name].add(f.name)
                first = 0 if t.name.startswith("sce") else 1
                ar = C.arity(facts, files, t.image, t.name)
                for k in range(first, 4 if ar is None else min(ar, 4)):
                    v = r.get(4 + k)
                    if isinstance(v, int):
                        hist[(t.name, k)][v] += 1
                    else:
                        hist[(t.name, k)]["dyn"] += 1
    return hist, sites, callers


def main():
    facts, imgs, edges, files = C.cached()
    m = imgs["main"]
    rows = []
    summary = defaultdict(Counter)
    priv, ad = scan_code(imgs)
    pg = defaultdict(list)
    for iname, f, off, val, pc in priv:
        pg[(off, val)].append(f"{f.name}@0x{pc:X}")
    for (off, val), w in sorted(pg.items(), key=lambda kv: (kv[0][0], str(kv[0][1]))):
        nm = PRIV.get(off & ~0xF, f"+0x{off:X}")
        if off & 0xF:
            nm += f"(hi word +{off & 0xF})"
        summary[nm]["priv" if val is not None else "priv-dyn"] += len(w)
        rows.append({"kind": "priv", "reg": f"0x{0x12000000 + off:08X}", "name": nm,
                     "value": f"0x{val:X}" if val is not None else "dyn",
                     "count": len(w), "where": " ".join(sorted(set(w)))[:300],
                     "confidence": "high"})
    ag = defaultdict(list)
    for iname, f, reg, data, pc, conf in ad:
        ag[(reg, data, conf)].append(f.name)
    for (reg, data, conf), fs in sorted(ag.items(), key=lambda kv: (kv[0][0], kv[0][2], str(kv[0][1]))):
        nm = GS_REGS[reg]
        if conf == "high":
            summary[nm]["ad_code" if data is not None else "ad_code-dyn"] += len(fs)
        rows.append({"kind": "ad_code", "reg": f"0x{reg:02X}", "name": nm,
                     "value": f"0x{data:X}" if data is not None else "dyn",
                     "decoded": decode(reg, data), "count": len(fs),
                     "where": " ".join(sorted(set(fs)))[:300], "confidence": conf})
    dg = defaultdict(list)
    tags = scan_data_tags(imgs)
    for iname, a, lo, pairs, pre in tags:
        if pre:
            p = lo >> 47 & 0x7FF
            dg[(0x00, p)].append(f"{iname}:0x{a:X}(tag PRE)")
        for val, reg in pairs:
            dg[(reg, val)].append(f"{iname}:0x{a:X}")
    for (reg, val), w in sorted(dg.items()):
        nm = GS_REGS[reg]
        summary[nm]["ad_data"] += len(w)
        rows.append({"kind": "ad_data", "reg": f"0x{reg:02X}", "name": nm,
                     "value": f"0x{val:X}", "decoded": decode(reg, val), "count": len(w),
                     "where": " ".join(w[:6]) + (f" (+{len(w) - 6})" if len(w) > 6 else ""),
                     "confidence": "high"})
    hist, sites, callers = api_args(imgs, facts, files)
    for (fn, k), h in sorted(hist.items()):
        if all(v == "dyn" for v in h):
            continue
        vals = ", ".join(f"{('0x%X' % v) if isinstance(v, int) else v}x{c}"
                         for v, c in sorted(h.items(), key=lambda kv: -kv[1])[:12])
        note = ""
        if fn in ("GsPktSetPrimType_13f470", "GsPktOpenPrim_13f730") and k == 1:
            note = "PRIM type: " + ", ".join(
                f"{PRIM_T[v & 7]}x{c}" for v, c in h.items() if isinstance(v, int))
        rows.append({"kind": "api_arg", "name": fn, "reg": f"arg{k}", "value": vals,
                     "count": sites[fn], "where": " ".join(sorted(callers[fn]))[:300],
                     "confidence": "high", "note": note})
    # blend preset table used by GsEnvSetBlendPreset_157150 (ALPHA_1 image)
    for i in range(12):
        v = struct.unpack_from("<Q", m.data, 0x449EF0 - m.base + 8 * i)[0]
        rows.append({"kind": "table", "reg": "0x42", "name": "ALPHA_1",
                     "value": f"0x{v:X}", "decoded": decode(0x42, v), "count": 1,
                     "where": f"D_00449EF0[{i}] (GsEnvSetBlendPreset_157150)",
                     "confidence": "high"})
    for nm in sorted(summary):
        c = summary[nm]
        rows.append({"kind": "summary", "name": nm,
                     "value": ", ".join(f"{k}={v}" for k, v in sorted(c.items()))})
    C.write_tsv(C.OUT / "platform_gs.tsv", COLS, rows, C.meta(
        "gs", {"rows": len(rows), "data_gif_tags": len(tags),
               "note": "static only; values computed at runtime show as dyn. "
                       "ad_code low-confidence rows are single small-int stores "
                       "and may be false positives"}))
    print(len(rows), "rows;", len(tags), "data tags;", len(priv), "priv stores;",
          len(ad), "ad_code stores")


if __name__ == "__main__":
    main()

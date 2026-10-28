#!/usr/bin/env python3
"""Census 3: PS2 address literals in code (comments and strings excluded).

category        value range                       default confidence
scratchpad      0x70000000-0x70003FFF (+0x70004000 end)    high
uncached        0x20000000 OR/ADD mask, 0x2xxxxxxx addr    by context
uncached_accel  0x30000000 OR/ADD mask, 0x3xxxxxxx addr    by context
seg_mask        0x0FFFFFFF / 0x1FFFFFFF (strip segment)    by context
kseg0           0x80000000-0x81FFFFFF                      low/medium
kseg1           0xA0000000-0xA1FFFFFF                      medium
bios            0xBFC00000-0xBFFFFFFF, 0x1FC00000-...      medium
hw_reg          0x10000000-0x1000FFFF (block named)        high
vu_mem          0x11000000-0x1100FFFF                      high
gs_priv         0x12000000-0x12001FFF                      high
overlay         0x004E9E80 .. overlay arena end            high if a known
                                                           overlay symbol/entry,
                                                           else medium/low

Context rules (the `conf` + `why` columns):
  * `p | 0x20000000`, `+ 0x20000000`, or a pointer cast on the line -> high
  * `& 0x20000000` / `== 0x2...` / used as a flag word -> low (likely a bit)
  * 0x80000000 exact -> low (sign bit / flag), 0x8000xxxx small offsets ->
    low (SIF command ids, flag words), larger 0x80xxxxxx -> medium
  * `in_asm` = the literal is inside an asm body (lib rows mostly)
  * dereferenced (`*(T *)0x1000...`, a #define, or inside asm) -> high
  * single-bit (or single-bit-cleared) values used with & | ~ == on a
    non-dereferenced operand are EXCLUDED as flags (counts in the header)
  * 0x1000000N not dereferenced, small low half -> low (DMA tag cnt/id=1)
"""
from __future__ import annotations

import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

LIT = re.compile(r"(?<![\w.])(0[xX][0-9A-Fa-f]+|\d{9,10})([uUlL]*)(?![\w.])")
HW_BLOCKS = [
    (0x10000000, 0x10002000, "TIMER"), (0x10002000, 0x10003000, "IPU"),
    (0x10003000, 0x10003800, "GIF"), (0x10003800, 0x10003C00, "VIF0"),
    (0x10003C00, 0x10004000, "VIF1"), (0x10004000, 0x10008000, "FIFO"),
    (0x10008000, 0x1000F000, "DMAC"), (0x1000F000, 0x1000F200, "INTC"),
    (0x1000F200, 0x1000F400, "SIF"), (0x1000F400, 0x1000F500, "MISC"),
    (0x1000F500, 0x1000F600, "DMAC-EN"), (0x1000F600, 0x10010000, "MISC2"),
]


def hw_block(v):
    for lo, hi, n in HW_BLOCKS:
        if lo <= v < hi:
            return n
    return "?"


def popcount(v):
    return bin(v).count("1")


def classify(v: int, ctx: str, lit: str, ovl_lo: int, ovl_hi: int, ovl_syms: dict,
             in_asm: bool):
    """-> (category, conf, why), or ("EXCLUDE", reason, "") for an obvious
    non-address, or None when out of every range."""
    esc = re.escape(lit)
    or_add = re.search(r"(\||\+|\|=|\+=)\s*\(?\s*" + esc + r"|" + esc + r"\s*\)?\s*(\||\+)", ctx)
    and_cmp = re.search(r"(&|==|!=|&=|~)\s*\(?\s*" + esc + r"|" + esc + r"\s*\)?\s*(&|==|!=)", ctx)
    ptrish = re.search(r"\*\s*\)|\(\s*u32\s*\)|\(\s*void\s*\*|\buintptr|\bptr\b|\baddr\b", ctx)
    deref = (in_asm or re.search(r"\*\s*\)\s*\(?\s*" + esc, ctx) is not None
             or re.match(r"\s*#\s*defineb", ctx) is not None)
    bitlike = popcount(v) == 1 or popcount(~v & 0xFFFFFFFF) == 1
    if bitlike and not deref and (and_cmp or re.search(r"(\|=|\|)\s*\(?\s*" + esc, ctx))             and v not in (0x20000000, 0x30000000, 0x70000000):
        return "EXCLUDE", f"single-bit flag/mask use of {lit}", ""
    if 0x70000000 <= v <= 0x70004000:
        if deref or or_add or re.search(r"\(\s*\w+\s*\*\s*\)\s*\(?\s*" + esc, ctx):
            return "scratchpad", "high", "SPR range" + (" end" if v == 0x70004000 else "")
        if v < 0x70010000 and (v & 0xFFFF) < 0x400 and re.search(r"[\]\w]\s*=\s*" + esc, ctx):
            return "scratchpad", "low", "stored as a value: DMA tag id=END qwc=N?"
        return "scratchpad", "medium", "SPR range, not dereferenced here"
    if v in (0x20000000, 0x30000000):
        cat = "uncached" if v == 0x20000000 else "uncached_accel"
        if in_asm:
            return cat, "medium", "in asm"
        field_flag = re.search(r"(->|\.)\s*\w+\s*\|=\s*" + esc + r"|\bflags?\b|\bfl\w*\s*\|", ctx)
        ptr_or = re.search(r"\(\s*u32\s*\)\s*\(?[^;|]*\|\s*\(?\s*" + esc + "|" + esc +
                           r"\s*\)?\s*\|\s*\(?\s*\(\s*u32\s*\)|\(\s*\w+\s*\*\s*\)\s*\(\s*[^;]*\|\s*" + esc +
                           r"|0x0?FFFFFFF\s*\)?\s*\|\s*" + esc, ctx, re.I)
        if or_add and ptr_or:
            return cat, "high", "OR/ADD on a (u32)-cast pointer"
        if field_flag:
            return cat, "low", "OR into a flags field: probably a flag bit"
        if or_add:
            return cat, "medium", "OR/ADD"
        if re.search(r"[\]\w]\s*=\s*" + esc + r"\s*[;|]", ctx):
            return cat, "low", "stored as a value: DMA tag id (next/ref)?"
        if and_cmp:
            return cat, "low", "AND/compare: probably a flag bit"
        return cat, "low", "bare constant"
    if 0x20000000 < v < 0x22000000 or 0x30000000 < v < 0x32000000:
        cat = "uncached" if v < 0x30000000 else "uncached_accel"
        if deref:
            return cat, "high", "segment address, dereferenced"
        return cat, "medium" if ptrish else "low", "segment-range value (not dereferenced: colour/hash constant?)"
    if v in (0x0FFFFFFF, 0x1FFFFFFF):
        if re.search(r"&\s*\(?\s*" + esc + "|" + esc + r"\s*\)?\s*&", ctx):
            return "seg_mask", "medium", "AND strips segment"
        return "seg_mask", "low", "bare (size limit?)"
    if 0x10000000 <= v < 0x10010000:
        if deref:
            return "hw_reg", "high", hw_block(v)
        if v & 0xFFFF < 0x1000 and (v & 0xFFFF0000) == 0x10000000:
            return "hw_reg", "low", "not dereferenced: DMA tag (id=1 cnt) / flag?"
        return "hw_reg", "medium", hw_block(v) + " (not dereferenced here)"
    if 0x11000000 <= v < 0x11010000:
        if deref:
            return "vu_mem", "high", "VU0/VU1 micro/data mem"
        return "vu_mem", "low", "stored as a value: VIF code 0x11 FLUSH?"
    if 0x12000000 <= v < 0x12002000:
        return "gs_priv", "high" if deref else "medium", "GS privileged regs"
    if 0x1FC00000 <= v < 0x20000000 or 0xBFC00000 <= v <= 0xBFFFFFFF:
        return "bios", "medium" if deref else "low", "BIOS ROM"
    if 0x80000000 <= v < 0x82000000:
        if deref and not (in_asm and v == 0x80000000):
            return "kseg0", "high", "dereferenced KSEG0 address" if not in_asm else "KSEG0 constant in asm"
        if v == 0x80000000:
            return "kseg0", "low", "0x80000000: sign bit / flag?"
        if v < 0x80010000:
            return "kseg0", "low", "small offset: SIF cmd id / flag?"
        if ptrish:
            return "kseg0", "medium", "KSEG0 address near a pointer cast"
        return "kseg0", "low", "not dereferenced: RGBA colour (0x80 alpha) / id?"
    if 0xA0000000 <= v < 0xA2000000:
        return "kseg1", "high" if deref else "medium", "KSEG1 address"
    if ovl_lo <= v < ovl_hi and lit.lower().startswith("0x"):
        if v in ovl_syms:
            return "overlay", "high", "overlay symbol " + ovl_syms[v]
        if v == 0x4E9E80:
            return "overlay", "high", "overlay load base"
        if v % 0x1000 == 0:
            return "overlay", "low", "round number: size or address"
        return "overlay", "medium", "inside overlay arena"
    return None


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)
    ovl_syms = {}
    hi = 0x4E9E80
    for img in S.OVERLAYS:
        for n, v in snap.symbols[img].items():
            ovl_syms.setdefault(v, n)
            hi = max(hi, v + S.SIZES.get((img, n), 0))
    ovl_hi = max(hi, 0x4E9E80) + 0x10000  # + room for overlay data/bss
    rows = []
    excluded = Counter()
    for sf in snap.all():
        s = sf.nostr
        asm_spans = [(f.body_open, f.body_close) for f in sf.funcs if f.is_asm]
        asm_spans += [(m.start(), s.find("}", m.end())) for m in
                      re.finditer(r"\basm\s*(?:volatile\s*)?\{", s)]
        for m in LIT.finditer(s):
            lit = m.group(1)
            try:
                v = int(lit, 16) if lit[:2].lower() == "0x" else int(lit)
            except ValueError:
                continue
            if v < 0x004E9E80 or v > 0xFFFFFFFF:
                continue
            ln = sf.line(m.start())
            ctx = sf.line_text(ln, "nostr")
            in_asm = any(a_ <= m.start() <= b_ for a_, b_ in asm_spans)
            r = classify(v, ctx, lit, 0x4E9E80, ovl_hi, ovl_syms, in_asm)
            if r is None:
                continue
            cat, conf, why = r
            if cat == "EXCLUDE":
                excluded[f"0x{v:08X}"] += 1
                continue
            rows.append(dict(file=sf.path, line=ln, symbol=sf.symbol_at(m.start()),
                             image=sf.image, lib=sf.lib, category=cat,
                             value=f"0x{v:08X}", conf=conf, why=why,
                             in_asm="yes" if in_asm else "",
                             kind=sf.kind, context=S.snippet(sf.line_text(ln, "code"))))
    rows.sort(key=lambda r: (r["category"], r["file"], r["line"]))
    cols = S.BASE_COLS + ["value", "conf", "why", "in_asm", "kind", "context"]
    out = Path(a.out) / "addr_literals.tsv"
    S.write_tsv(out, cols, rows, S.meta(snap, "addr_literals",
                                        {"overlay_range": f"0x004E9E80-0x{ovl_hi:08X}",
                                         "excluded_single_bit_flag_uses": " ".join(f"{k}x{v}" for k, v in excluded.most_common())}))
    c = Counter((r["category"], r["lib"], r["conf"]) for r in rows)
    for k, v in sorted(c.items()):
        print(*k, v)
    print(f"wrote {out} ({len(rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

#!/usr/bin/env python3
"""Census of the remaining PS2 hardware / address residue in compiled code
(docs/NATIVE-CPU.md "hwbus").

    python tools/native/hw_census.py static [--out census/native_hw_static.tsv]
    python tools/native/hw_census.py summary [--in census/native_hw_static.tsv]

static   scans the compiled game set (game/ MANIFEST unit/data, overrides/ in place,
         missing/ stand-ins) and the port's SDK/CRT/runtime layers (src/sce, src/crt,
         src/runtime/crt0.c) for:
           hw        HW_R8..HW_W128 accessor sites (hwaccess stage output) and direct
                     hw_r*/hw_w* calls; the address -> register -> owning model
                     (docs/HWBUS.md claims table) -> the lane that removes it
           spr       PS2_SPR(...) scratchpad pointers, hw_spr_base()
           mask      PS2_PHYS / PS2_UNCACHED / PS2_UCAB (identity markers)
           ovl       RG_OVL_DATA (MAIN reading overlay memory by literal address)
           lit-hw    raw hardware addresses left in code (0x1000_0000-0x1200_FFFF)
           lit-spr   raw scratchpad addresses (0x7000_0000-0x7000_3FFF)
           lit-ram   pointer casts of raw EE-RAM addresses ((T *)0x00100000-0x01FFFFFF)
           lit-kseg  KSEG/uncached segment constants used as masks
                     (& 0x0FFFFFFF / & 0x1FFFFFFF / | 0x20000000 / | 0x30000000 /
                     | 0xA0000000 / 0x8000_0000 SPR tag) outside the stage's markers
         One row per site: kind, path, line, function (file stem), address, register,
         owner, lane, text.
summary  per kind x lane counts, and the sites only the emulated GS/VIF/DMAC path
         needs (renderer lane).

Pure text processing, no build needed.
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]

# docs/HWBUS.md claims table: (lo, hi, register group, owning model, lane)
CLAIMS = [
    (0x10000000, 0x10001FFF, "T0-T3 timers", "kernel", "kernel/threads (native clock)"),
    (0x10002000, 0x1000203F, "IPU regs", "ipu", "movie (native player)"),
    (0x10003000, 0x100030AF, "GIF regs", "gs", "renderer"),
    (0x10003800, 0x1000397F, "VIF0 regs", "vif", "renderer"),
    (0x10003C00, 0x10003D7F, "VIF1 regs", "vif", "renderer"),
    (0x10004000, 0x10004FFF, "VIF0 FIFO", "vif", "renderer"),
    (0x10005000, 0x10005FFF, "VIF1 FIFO", "vif", "renderer"),
    (0x10006000, 0x10006FFF, "GIF FIFO", "gs", "renderer"),
    (0x10007000, 0x1000701F, "IPU FIFO", "ipu", "movie (native player)"),
    (0x10008000, 0x100083FF, "D0 VIF0 DMA", "dmac", "renderer"),
    (0x10009000, 0x100093FF, "D1 VIF1 DMA", "dmac", "renderer"),
    (0x1000A000, 0x1000A3FF, "D2 GIF DMA", "dmac", "renderer"),
    (0x1000B000, 0x1000B3FF, "D3 fromIPU DMA", "dmac", "movie (native player)"),
    (0x1000B400, 0x1000B7FF, "D4 toIPU DMA", "dmac", "movie (native player)"),
    (0x1000C000, 0x1000C7FF, "D5/D6 SIF DMA", "dmac", "iop (native IOP)"),
    (0x1000C800, 0x1000CFFF, "D7 SIF2 DMA", "dmac", "iop (native IOP)"),
    (0x1000D000, 0x1000D4FF, "D8/D9 SPR DMA", "dmac", "renderer"),
    (0x1000E000, 0x1000E06F, "DMAC ctrl (D_CTRL..D_STADR)", "dmac", "renderer"),
    (0x1000F000, 0x1000F01F, "INTC", "kernel", "kernel/threads (native clock)"),
    (0x1000F200, 0x1000F26F, "SIF regs", "sif", "iop (native IOP)"),
    (0x1000F500, 0x1000F59F, "D_ENABLER/W", "dmac", "renderer"),
    (0x12000000, 0x120010FF, "GS privileged", "gs", "renderer"),
]


def owner(addr: int):
    for lo, hi, reg, own, lane in CLAIMS:
        if lo <= addr <= hi:
            return reg, own, lane
    return "?", "?", "?"


def compile_set() -> list[tuple[str, Path]]:
    rows = [ln.split("\t") for ln in
            (PORT / "game" / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    provided = set()
    for ln in (PORT / "overrides" / "PORT_PROVIDED.tsv").read_text(encoding="utf-8").splitlines():
        if ln.strip() and not ln.startswith("#"):
            provided.add(ln.split("\t")[0])
    out = []
    for r in rows:
        rel, kind = r[0], r[3]
        ovr = PORT / "overrides" / rel
        if kind == "excluded" and ovr.is_file():
            kind = "unit"
        if kind not in ("unit", "data") or not rel.endswith((".c", ".cpp")) or rel in provided:
            continue
        out.append(("override" if ovr.is_file() else "game", ovr if ovr.is_file() else PORT / "game" / rel))
    for f in sorted((PORT / "missing").rglob("*")):
        if f.suffix in (".c", ".cpp"):
            out.append(("missing", f))
    for d in ("src/sce", "src/crt"):
        for f in sorted((PORT / d).rglob("*")):
            if f.suffix in (".c", ".cpp", ".h"):
                out.append(("port", f))
    out.append(("port", PORT / "src" / "runtime" / "crt0.c"))
    return out


def strip_comments(s: str) -> str:
    """blank comments and string contents, keep offsets/lines"""
    out = list(s)
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if s.startswith("/*", i):
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif s.startswith("//", i):
            j = s.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and s[j] != c:
                j += 2 if s[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                if out[k] != "\n":
                    out[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(out)


HWCALL = re.compile(r"\b(HW_[RW](?:8|16|32|64|128)|hw_[rw](?:8|16|32|64|128))\s*\(\s*([^,()]+)")
MARK = re.compile(r"\b(PS2_SPR|PS2_PHYS|PS2_UNCACHED|PS2_UCAB|RG_OVL_DATA|hw_spr_base)\s*\(")
LIT = re.compile(r"\b0[xX]([0-9A-Fa-f]{1,8})[uUlL]*\b")
RAMCAST = re.compile(r"\(\s*(?:const\s+)?(?:volatile\s+)?[A-Za-z_]\w*\s*\*+\s*\)\s*\(?\s*0[xX]([0-9A-Fa-f]{5,8})")
KSEG = re.compile(r"(&\s*0[xX]0*(?:0FFFFFFF|FFFFFFF|1FFFFFFF)\b|\|\s*0[xX](?:20000000|30000000|A0000000)\b)")


def scan(kind: str, path: Path):
    try:
        raw = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    if not re.search(r"HW_|hw_[rw]|PS2_|RG_OVL_DATA|0[xX](1[0-2]|7000|[0-9A-Fa-f]{5,8})", raw):
        return []
    s = strip_comments(raw)
    rel = path.relative_to(PORT).as_posix()
    fn = path.stem
    rows = []

    def line_of(pos):
        return s.count("\n", 0, pos) + 1

    def text_at(pos):
        a = s.rfind("\n", 0, pos) + 1
        b = s.find("\n", pos)
        return " ".join(s[a:b if b >= 0 else len(s)].split())[:140]
    for m in HWCALL.finditer(s):
        a = m.group(2).strip()
        lm = re.match(r"\(?\s*0[xX]([0-9A-Fa-f]+)", a)
        if lm:
            addr = int(lm.group(1), 16)
            reg, own, lane = owner(addr)
            astr = f"0x{addr:08X}"
        else:
            reg, own, lane, astr = "(computed)", "?", "?", a[:40]
        if path.parts[-2:] == ("port", "hwaccess.h") or "define HW_" in text_at(m.start()):
            continue
        rk = "hw"
        if lm and addr in (0x10000000, 0x10000010) and m.group(1) in ("HW_R32", "HW_W32") and (
                addr == 0x10000000 or m.group(1)[:4] == "HW_W"):
            # include/port/hwaccess.h routes T0_COUNT reads/writes and T0_MODE writes to the
            # native logic-time clock (src/native/threads/rg_logic_time.c), not the bus
            rk, lane = "logic-t0", "done: native logic time (rg_logic_t0_*)"
        rows.append((rk, rel, line_of(m.start()), fn, astr, reg, own, lane, text_at(m.start())))
    for m in MARK.finditer(s):
        k = {"PS2_SPR": "spr", "hw_spr_base": "spr", "RG_OVL_DATA": "ovl"}.get(m.group(1), "mask")
        if "define " in text_at(m.start()):
            continue
        lane = {"spr": "cpu (native: static buffer)", "ovl": "overlay manager",
                "mask": "cpu (identity marker)"}[k]
        rows.append((k, rel, line_of(m.start()), fn, m.group(1), "", "", lane, text_at(m.start())))
    seen = set()
    for m in LIT.finditer(s):
        v = int(m.group(1), 16)
        if 0x10000000 <= v <= 0x1000FFFF or 0x12000000 <= v <= 0x1200FFFF:
            if len(m.group(1)) < 8:
                continue
            reg, own, lane = owner(v)
            t = text_at(m.start())
            if re.search(r"\b(HW_|hw_)[RWrw]", t) or "define" in t:
                continue
            pre = s[max(0, m.start() - 48):m.start()]
            data_file = fn.startswith("data2c_")
            # an address only where it is used as one: a pointer cast / deref,
            # or a word of a data table; anything else (flags, DMAtag/VIFcode
            # bits, limits such as 0x10000000) is not hardware
            if not data_file and not re.search(r"(\*\s*\)\s*\(?\s*|volatile[^;]*\(\s*)$", pre):
                continue
            if data_file and (v < 0x10002000 or v & 0xF):
                continue   # DMAtag / VIFcode words (0x1000000N = CNT tag, ...), not registers
            k = "data-hw" if data_file else "lit-hw"
            rows.append((k, rel, line_of(m.start()), fn, f"0x{v:08X}", reg, own, lane, t))
            seen.add(m.start())
        elif 0x70000000 <= v <= 0x70003FFF and len(m.group(1)) == 8:
            rows.append(("lit-spr", rel, line_of(m.start()), fn, f"0x{v:08X}", "scratchpad?", "", "review (usually a DMAtag END id word, not SPR)", text_at(m.start())))
    for m in RAMCAST.finditer(s):
        v = int(m.group(1), 16)
        if 0x00100000 <= v <= 0x01FFFFFF:
            rows.append(("lit-ram", rel, line_of(m.start()), fn, f"0x{v:08X}", "EE RAM", "", "memory map", text_at(m.start())))
    for m in KSEG.finditer(s):
        rows.append(("lit-kseg", rel, line_of(m.start()), fn, m.group(1).replace(" ", ""), "", "", "review (mask or tag bits)", text_at(m.start())))
    return [(kind,) + r for r in rows]


def cmd_static(a) -> int:
    rows = []
    for kind, p in compile_set():
        rows += scan(kind, p)
    a.out.parent.mkdir(parents=True, exist_ok=True)
    with a.out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("src\tkind\tpath\tline\tfunction\taddr\tregister\towner\tlane\ttext\n")
        for r in sorted(rows, key=lambda r: (r[1], r[2], r[3])):
            f.write("\t".join(str(x) for x in r) + "\n")
    print(f"wrote {a.out} ({len(rows)} rows)")
    return summarize(rows)


def summarize(rows) -> int:
    by = Counter((r[1], r[0]) for r in rows)
    print("sites by kind x source:")
    for (k, src), n in sorted(by.items()):
        print(f"  {k:9s} {src:9s} {n}")
    lanes = Counter((r[1], r[8]) for r in rows if r[1] in ("hw", "lit-hw", "data-hw"))
    print("hardware sites by lane:")
    for (k, lane), n in sorted(lanes.items(), key=lambda x: (-x[1])):
        print(f"  {k:7s} {lane:32s} {n}")
    regs = defaultdict(set)
    for r in rows:
        if r[1] in ("hw", "lit-hw", "data-hw"):
            regs[(r[8], r[6])].add(r[4])
    print("functions per lane/register group:")
    for (lane, reg), fns in sorted(regs.items()):
        print(f"  {lane:32s} {reg:26s} {len(fns):3d}  {', '.join(sorted(fns))[:150]}")
    return 0


def cmd_summary(a) -> int:
    rows = [tuple(l.split("\t")) for l in a.inp.read_text(encoding="utf-8").splitlines()[1:]]
    return summarize(rows)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("static")
    s.add_argument("--out", type=Path, default=PORT / "census" / "native_hw_static.tsv")
    s2 = sub.add_parser("summary")
    s2.add_argument("--in", dest="inp", type=Path, default=PORT / "census" / "native_hw_static.tsv")
    a = ap.parse_args()
    return cmd_static(a) if a.cmd == "static" else cmd_summary(a)


if __name__ == "__main__":
    sys.exit(main())

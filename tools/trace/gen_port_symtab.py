# SPDX-License-Identifier: CC0-1.0
"""Generate the port trace recorder's symbol table: PS2 address -> host object.

  python tools/trace/gen_port_symtab.py --regions tools/trace/regions_golden.cfg \\
         [--src game/src | --symbols FILE] [--only '^sym:'] --out rg_trace_symtab_gen.c

The PCSX2 harness hashes EE address ranges; on the port the same bytes live in
host objects (the game's D_xxxxxxxx data symbols).  This writes a C file that
takes `&D_xxxxxxxx` of every data symbol the selected regions touch, with the
PS2 address range each one covers, and registers them with
rg_trace_add_symbols() (src/trace/rg_trace.h).  It also writes <out>.tsv
(rows: sym / region / gap) for review.

Symbol sources:
  --src DIR      D_00xxxxxx names referenced by the game sources (comments
                 stripped), like gen_regions.py.  A symbol's size is the
                 distance to the next referenced name (the decomp's own data
                 boundaries; the same rule gen_regions.py uses for 'auto').
  --symbols F    lines 'addr name [size]' (a data2c symbol list, or a fixture).
                 Missing sizes are the distance to the next listed symbol.

Addresses in the overlay arena [0x004E9E80, 0x00528200) and the heap
(>= 0x00528200) are skipped: the recorder maps those through the overlay
registry and the crt0 RAM block.  A region whose bytes no symbol covers is
listed as a 'gap' row; the recorder then skips it with an '# unmapped' note.
"""
import argparse
import bisect
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import trace  # noqa: E402  (shared region-file parser)

ARENA = (0x004E9E80, 0x00528200)
HEAP = 0x00528200
EXTRA = {0x004810C4: "game VBlank counter", 0x004B51A0: "GameModeStack[0] (events)",
         0x0047E254: "LoadedOverlayId (events)",
         # the timing record's per-VBlank words (src/trace/timing.c, probe.py T_*)
         0x004810A4: "frame context (timing)", 0x00481998: "scene (timing)",
         0x004B51E0: "GameModePhaseStack[0] (timing)", 0x0047E224: "sysmode (timing)",
         0x0048276C: "pause step (timing)", 0x00482278: "task depth (timing)",
         0x0047DF18: "vsync sema (timing)", 0x004810C0: "vsync wait flag (timing)",
         0x0047E250: "tick ready (timing)", 0x00481558: "disk watch (timing)",
         0x00481554: "sequence owner (timing)", 0x004810B4: "VIF1 time (timing)"}

_COMMENT = re.compile(rb"/\*.*?\*/|//[^\n]*", re.S)
_DSYM = re.compile(rb"\bD_00([0-9A-Fa-f]{6})\b")


def scan_src(src):
    """{addr: name} of D_ symbols referenced outside comments."""
    found = {}
    for root, _, files in os.walk(src):
        for f in files:
            if f.endswith((".c", ".cpp", ".h", ".inc")):
                with open(os.path.join(root, f), "rb") as fh:
                    text = _COMMENT.sub(b" ", fh.read())
                for m in _DSYM.finditer(text):
                    a = int(m.group(1), 16)
                    name = m.group(0).decode()
                    # several spellings: keep the upper-case one (the corpus's)
                    if a not in found or name.upper() == name:
                        found[a] = name
    return {a: (n, None) for a, n in found.items()}


def read_symbols(path):
    out = {}
    with open(path, encoding="utf-8") as f:
        for ln, line in enumerate(f, 1):
            t = line.split("#", 1)[0].split()
            if not t:
                continue
            if len(t) < 2:
                raise SystemExit("%s:%d: need 'addr name [size]'" % (path, ln))
            out[int(t[0], 0)] = (t[1], int(t[2], 0) if len(t) > 2 else None)
    return out


def build(regions, syms, only):
    """-> (table rows [(addr, size, name, users)], gaps [(region, start, end)])."""
    addrs = sorted(syms)

    def size_of(a):
        n, sz = syms[a]
        if sz:
            return sz
        i = bisect.bisect_right(addrs, a)
        end = addrs[i] if i < len(addrs) else a + 4
        # never claim the arena or the heap: those are mapped elsewhere
        for lim in (ARENA[0], HEAP):
            if a < lim < end:
                end = lim
        return end - a

    def containing(a):
        i = bisect.bisect_right(addrs, a) - 1
        if i >= 0 and a - addrs[i] < size_of(addrs[i]):
            return addrs[i]
        return None

    def mapped_elsewhere(a):
        return ARENA[0] <= a < ARENA[1] or a >= HEAP

    used = {}
    gaps = []

    def need(start, end, who):
        a = start
        while a < end:
            if mapped_elsewhere(a):
                a = ARENA[1] if a < ARENA[1] else end
                continue
            s = containing(a)
            if s is None:
                i = bisect.bisect_right(addrs, a)
                nxt = addrs[i] if i < len(addrs) else end
                gaps.append((who, a, min(nxt, end)))
                a = min(nxt, end)
                continue
            used.setdefault(s, set()).add(who)
            a = s + size_of(s)

    rx = re.compile(only) if only else None
    for space, name, a, b, deref in regions:
        if space != "ee" or (rx and not rx.search(name)):
            continue
        if deref:
            need(deref[0], deref[0] + 4, name)
        else:
            need(a, b, name)
    for a, why in EXTRA.items():
        if containing(a) is not None:
            need(a, a + 4, "(%s)" % why)
    rows = [(a, size_of(a), syms[a][0], sorted(used[a])) for a in sorted(used)]
    return rows, gaps


def write_c(path, rows, func, origin):
    lines = ["/* GENERATED by tools/trace/gen_port_symtab.py -- do not edit.",
             " * %s" % origin,
             " * PS2 data symbol -> host object for the trace recorder (docs/TRACE-PORT.md). */",
             '#include "rg_trace.h"', ""]
    for a, size, name, users in rows:
        lines.append("extern char %s[];" % name)
    lines += ["", "static const rg_trace_sym k_syms[] = {"]
    for a, size, name, users in rows:
        lines.append('    {0x%08Xu, 0x%Xu, %s, "%s"}, /* %s */' % (a, size, name, name, " ".join(users)[:90]))
    if not rows:
        lines.append("    {0, 0, 0, 0}")
    lines += ["};", "",
              "int %s(void)" % func, "{",
              "    return rg_trace_add_symbols(k_syms, %d);" % len(rows), "}", ""]
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--regions", required=True, help="region file (trace.py grammar)")
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--src", help="game source tree to scan for D_ names")
    g.add_argument("--symbols", help="symbol list: 'addr name [size]' per line")
    ap.add_argument("--only", default="^sym:", help="regex over region names (default '^sym:'; '' = all)")
    ap.add_argument("--func", default="rg_trace_register_game_symtab")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()
    if args.symbols:
        syms, origin = read_symbols(args.symbols), "symbols: %s" % args.symbols
    else:
        src = args.src or os.path.join(os.path.dirname(os.path.dirname(HERE)), "game", "src")
        syms, origin = scan_src(src), "symbols: D_ names referenced under %s" % src
    regions = trace.load_regions(args.regions)
    rows, gaps = build(regions, syms, args.only)
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    write_c(args.out, rows, args.func, origin + "; regions: %s" % args.regions)
    tsv = os.path.splitext(args.out)[0] + ".tsv"
    with open(tsv, "w", encoding="utf-8", newline="\n") as f:
        f.write("# kind\taddr\tsize\tname\tregions\n")
        for a, size, name, users in rows:
            f.write("sym\t0x%08X\t0x%X\t%s\t%s\n" % (a, size, name, " ".join(users)))
        for who, a, b in gaps:
            f.write("gap\t0x%08X\t0x%X\t-\t%s\n" % (a, b - a, who))
    print("wrote %s: %d symbols, %d gaps (%s)" % (args.out, len(rows), len(gaps), tsv))


if __name__ == "__main__":
    main()

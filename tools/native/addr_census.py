#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""D9 gate census: PS2 address arithmetic left in what a native-only rg-game compiles
(PLAN.md "Native end state": "no PS2 address arithmetic remains in game code").

    python tools/native/addr_census.py [--build build/nd9-i686] [--tsv out.tsv] [--sites]

Scans the compiled game set (game/ MANIFEST unit/data files, overrides in place,
missing/ stand-ins; tools/native/hw_census.py `compile_set`), the port's SDK / CRT
layers (src/sce, src/crt, crt0.c), the native services that replace the models
(src/native: overlay module table, VU0) and the overlay sources the build generated
(<build>/overlay-gen: ovl_native_gen.c + ovl_ctors_gen.c, the ones a native-only
rg-game with RG_NATIVE_OVL links), plus game/DATARELOC.tsv for data words left raw.

Kinds (one row per site; `class` says whether it is arithmetic on retail addresses):
  hw / data-hw / lit-hw   hardware register accessors / words / literals   (hw_census)
  spr / lit-spr           scratchpad pointers / literals                   (hw_census)
  mask / lit-kseg         PS2_PHYS/UNCACHED/UCAB markers, KSEG masks        (hw_census)
  ovl-data                RG_OVL_DATA (MAIN reading overlay memory by retail address)
  arena                   RG_OVL_ARENA_PTR / RG_MAIN_BSS_PTR / data2c_overlay_load_base
                          + offset / rg_ovl_host_ptr / rg_ovl_ps2_addr / rg_ovl_resolve_fn
                          (the overlay arena's address map)
  ps2-addr-def            `#define RG_PS2_ADDR_xxx 0x...` (a retail address spelled as a
                          number for arithmetic the game does on it)
  ram-cast                pointer cast of a literal EE-RAM address ((T *)0x00100000..)
  raw-word                DATARELOC rows kept as numbers inside a PS2 address range
                          (dead jump-table words, packed shorts, ASCII): data, not
                          arithmetic, listed so the gate sees them
  dead-data               a hardware / scratchpad word in a data table no compiled code
                          reaches (reachability over D_xxxxxxxx references from the code,
                          through other tables: e.g. the SDK's DMA-channel and TLB tables)
  dmatag / flag           a reviewed literal that only looks like an address (REVIEWED below:
                          DMAtag END ids 0x7000_000N, CHCR / DMAtag REF ids, flag bits)
  native-reg              a call into the native service that owns a register the game
                          used to touch (hwaccess stage NATIVE_REGS: rg_logic_t0_*,
                          rg_gs_reg_*, rg_vif1_fbrst_w32): done, listed for the record
Classes: `arith` (address arithmetic / an address used as an address: must go for
D9), `marker` (PS2_PHYS / UNCACHED / UCAB identity markers or an unreviewed KSEG
mask: must go too since 2026-10-25, the stage strips them), `inert` (a number that
only looks like an address), `done`.

--check (ctest native_only.addr_census): exit 1 when any `arith` or `marker` row is
left -- every new site fails the gate until it is removed or, if it is not an address,
reviewed into REVIEWED with a reason.  --inject (the control test) adds one synthetic
site of each kind, so --check --inject must fail.

Pure text processing; no build needed (--build only adds the generated overlay sources).
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import hw_census  # noqa: E402

ARENA = re.compile(r"\b(RG_OVL_ARENA_PTR|RG_MAIN_BSS_PTR|rg_ovl_host_ptr|rg_ovl_ps2_addr|"
                   r"rg_ovl_resolve_fn|rg_ovl_resident_ptr)\s*\(|"
                   r"data2c_overlay_load_base\s*\)?\s*\+|\brg_ovl_arena\s*\+")
PS2DEF = re.compile(r"#\s*define\s+(RG_PS2_ADDR_\w+)\s+(0[xX][0-9A-Fa-f]+)")
RAW_RULES = {"arena-text-interior", "arena-unaligned", "main-data-unaligned",
             "main-data-unowned", "short-main-candidate", "micro-unsym"}
# KSEG0 / KSEG1 mirrors of the hardware range used as pointers ((volatile T *)0xB000xxxx)
KSEGHW = re.compile(r"\b0[xX]([89ABab][0-9A-Fa-f]{7})[uUlL]*\b")
NATIVE_REG = re.compile(r"\b(rg_logic_t0_count|rg_logic_t0_set_count|rg_logic_t0_set_mode|"
                        r"rg_gs_reg_r64|rg_gs_reg_w64|rg_vif1_fbrst_w32)\s*\(")
DSYM = re.compile(r"\bD_[0-9A-Fa-f]{8}\b")
DDEF = re.compile(r"^[ \t]*(?!extern\b)[A-Za-z_][\w \t*]*?\b(D_[0-9A-Fa-f]{8})\s*\[[^\]]*\][^;=]*=", re.M)

# Reviewed literals that only look like addresses: (file stem, value) -> (kind, reason).
# A row matching none stays `arith` / `marker` and fails --check.  The lit-kseg rows of the
# game files are the hwaccess stage's own reviewed LEAVE_RULES (tools/stages/hwaccess.py).
REVIEWED = {
    ("GfxEndFrame_141c20", 0x70000003): ("dmatag", "DMAtag END, QWC 3: pkt->w[0] of the end packet"),
    ("data2c_00445810", 0x70000000): ("dmatag", "DMAtag END closing the VIF0 init packet "
                                                "(Vif0SendInitPacketMaybe_13bcc0 sends the table)"),
    ("data2c_00455310", 0x70000000): ("dmatag", "DMAtag END closing a GS A+D packet in the table"),
    ("libpkt", 0x70000000): ("dmatag", "sceVif1PkEnd / sceGifPkEnd: open_tag(id END)"),
    ("crt_eelibm", 0x20000000): ("flag", "sqrt seed: exponent-bit arithmetic on a float word"),
}
INJECT = ("/* addr_census --inject: one synthetic site per gated kind */\n"
          "void rg_addr_census_inject(void *p) {\n"
          "    HW_W64(0x12000000u, 0x7F23);\n"
          "    *(volatile int *)0xB0001820 = 0;\n"
          "    p = PS2_PHYS(p);\n"
          "#define A_(x) PS2_UCAB(x)\n"
          "    *(unsigned int *)p = 0x70000001u | ((unsigned int)p | 0x20000000);\n"
          "}\n")


def leave_rules():
    """the hwaccess stage's reviewed (symbol, value) sites that are not addresses"""
    sys.path.insert(0, str(PORT / "tools" / "stages"))
    try:
        import hwaccess  # noqa: E402
        return {(k[0], int(k[1], 16)): ("flag", v) for k, v in hwaccess.LEAVE_RULES.items()}
    except Exception as e:   # pragma: no cover
        print(f"addr_census: hwaccess LEAVE_RULES unavailable ({e})", file=sys.stderr)
        return {}


def data_liveness(files) -> dict[str, bool]:
    """data2c file -> does compiled code reach one of its tables?  Roots: every D_xxxxxxxx
    spelled in a compiled code file (not a data2c table, not an extern-only line); then a
    reached table reaches what its words reference."""
    defs: dict[str, set] = {}
    refs: dict[str, set] = {}
    alive: set = set()
    for src, f in files:
        try:
            s = hw_census.strip_comments(f.read_text(encoding="utf-8", errors="replace"))
        except OSError:
            continue
        key = f.as_posix()
        if f.stem.startswith("data2c_"):
            defs[key] = set(DDEF.findall(s))
            refs[key] = set(DSYM.findall(s)) - defs[key]
        else:
            for ln in s.splitlines():
                if "D_" in ln and not ln.lstrip().startswith("extern"):
                    alive.update(DSYM.findall(ln))
    changed = True
    live: dict[str, bool] = {k: False for k in defs}
    while changed:
        changed = False
        for k, d in defs.items():
            if not live[k] and d & alive:
                live[k] = True
                alive |= refs[k]
                changed = True
    return live


HW_CLASS = {"hw": "arith", "data-hw": "arith", "lit-hw": "arith", "spr": "arith",
            "lit-spr": "arith", "mask": "marker", "lit-kseg": "marker", "logic-t0": "done",
            "ovl": "arith", "lit-ram": "arith"}


def extra_files(build: Path | None):
    out = []
    for d in ("src/native/ovl", "src/native/vu0"):
        for f in sorted((PORT / d).glob("*.[ch]")):
            if not f.name.endswith("_tests.c"):
                out.append(("native", f))
    if build:
        g = build.resolve() / "overlay-gen"
        for n in ("ovl_native_gen.c", "ovl_ctors_gen.c"):
            if (g / n).is_file():
                out.append(("generated", g / n))
    return out


def scan_extra(src: str, path: Path):
    try:
        raw = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    s = hw_census.strip_comments(raw)
    try:
        rel = path.relative_to(PORT).as_posix()
    except ValueError:
        rel = path.as_posix()
    rows = []

    def line(pos):
        return s.count("\n", 0, pos) + 1

    def text(pos):
        a = s.rfind("\n", 0, pos) + 1
        b = s.find("\n", pos)
        return " ".join(s[a:b if b >= 0 else len(s)].split())[:140]
    for m in ARENA.finditer(s):
        t = text(m.start())
        if "define " in t or path.suffix == ".h":   # macro / prototype, not a use
            continue
        rows.append(("arena", "arith", src, rel, line(m.start()), m.group(0).strip(), t))
    for m in PS2DEF.finditer(raw):
        rows.append(("ps2-addr-def", "arith", src, rel, raw.count("\n", 0, m.start()) + 1,
                     f"{m.group(1)}={m.group(2)}", text(m.start())))
    for m in hw_census.RAMCAST.finditer(s):
        v = int(m.group(1), 16)
        if 0x00100000 <= v < 0x02000000:
            rows.append(("ram-cast", "arith", src, rel, line(m.start()), f"0x{v:08X}", text(m.start())))
    if not path.stem.startswith("data2c_"):
        for m in KSEGHW.finditer(s):
            v = int(m.group(1), 16)
            p = v & 0x1FFFFFFF
            if not (0x10000000 <= p <= 0x1000FFFF or 0x12000000 <= p <= 0x1200FFFF):
                continue
            pre = s[max(0, m.start() - 48):m.start()]
            if re.search(r"(\*\s*\)\s*\(?\s*|volatile[^;]*\(\s*)$", pre):
                rows.append(("lit-hw", "arith", src, rel, line(m.start()), f"0x{v:08X}",
                             text(m.start())))
    # identity markers inside a macro body (hw_census skips define lines): still a marker
    for m in re.finditer(r"\b(PS2_PHYS|PS2_UNCACHED|PS2_UCAB)\s*\(", s):
        t = text(m.start())
        if "define " in t and not re.search(r"define\s+" + m.group(1) + r"\b", t):
            rows.append(("mask", "marker", src, rel, line(m.start()), m.group(1), t))
    if path.suffix != ".h":
        for m in NATIVE_REG.finditer(s):
            t = text(m.start())
            if "define " in t:
                continue
            rows.append(("native-reg", "done", src, rel, line(m.start()), m.group(1), t))
    return rows


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--build", type=Path, default=None, help="build dir (generated overlay sources)")
    ap.add_argument("--tsv", type=Path, default=None)
    ap.add_argument("--sites", action="store_true", help="print every arith / marker site")
    ap.add_argument("--check", action="store_true",
                    help="exit 1 if any arith or marker site is left (ctest native_only.addr_census)")
    ap.add_argument("--inject", action="store_true",
                    help="add one synthetic site per gated kind (the gate's control test)")
    a = ap.parse_args(argv)
    rows = []
    files = hw_census.compile_set() + extra_files(a.build)
    if a.inject:
        tmp = PORT / "out" / "addr_census"
        tmp.mkdir(parents=True, exist_ok=True)
        (tmp / "inject_site.c").write_text(INJECT, encoding="utf-8")
        files.append(("inject", tmp / "inject_site.c"))
    live = data_liveness(files)
    reviewed = dict(leave_rules())
    reviewed.update(REVIEWED)
    used_rev: set = set()
    for src, f in files:
        for r in hw_census.scan(src, f):
            _src, kind, rel, ln, fn, addr, reg, own, lane, t = r
            cl = HW_CLASS.get(kind, "arith")
            if kind in ("data-hw", "lit-spr") and live.get(f.as_posix()) is False:
                kind, cl = "dead-data", "inert"
                t = "table unreachable from compiled code | " + t
            elif kind in ("lit-spr", "lit-kseg"):
                try:
                    v = int(addr.lstrip("|&"), 16)
                except ValueError:
                    v = -1
                k = (fn, v)
                if k in reviewed:
                    used_rev.add(k)
                    kind, why = reviewed[k]
                    cl = "inert"
                    t = why + " | " + t
                elif kind == "lit-kseg":
                    cl = "marker"
            rows.append((kind, cl, src, rel, ln, addr, t))
        rows += scan_extra(src, f)
    dr = PORT / "game" / "DATARELOC.tsv"
    if dr.is_file():
        for ln in dr.read_text(encoding="utf-8").splitlines()[1:]:
            f = ln.split("\t")
            if f[0] in RAW_RULES:
                rows.append(("raw-word", "inert", "data", f"game/DATARELOC.tsv:{f[2]}", 0,
                             f"{f[1]}={f[4]}", f[0]))
    seen = set()
    uniq = []
    for r in rows:
        k = (r[0], r[3], r[4], r[5])
        if k not in seen:
            seen.add(k)
            uniq.append(r)
    rows = uniq
    if a.tsv:
        a.tsv.parent.mkdir(parents=True, exist_ok=True)
        with open(a.tsv, "w", encoding="utf-8", newline="\n") as fh:
            fh.write("kind\tclass\tsource\tpath\tline\twhat\ttext\n")
            for r in rows:
                fh.write("\t".join(str(x) for x in r) + "\n")
    c = Counter((r[1], r[0], r[2]) for r in rows)
    print("class\tkind\tsource\tsites")
    for (cl, k, s), n in sorted(c.items()):
        print(f"{cl}\t{k}\t{s}\t{n}")
    tot = Counter(r[1] for r in rows)
    print("totals: " + ", ".join(f"{k}={v}" for k, v in sorted(tot.items())))
    stale = sorted(set(REVIEWED) - used_rev)
    for k in stale:
        print(f"note: REVIEWED entry {k[0]} 0x{k[1]:08X} matched no site (remove it?)")
    bad = [r for r in rows if r[1] in ("arith", "marker")]
    if a.sites or (a.check and bad):
        for r in rows:
            if r[1] in ("arith", "marker"):
                print(f"  {r[0]:13} {r[3]}:{r[4]}  {r[5]}  | {r[6]}")
    if a.check:
        if bad:
            print(f"addr_census: FAIL, {len(bad)} PS2 address site(s) left (arith / marker); "
                  f"remove them, or review a non-address literal into REVIEWED with a reason")
            return 1
        print("addr_census: PASS, 0 arith, 0 marker")
    return 0


if __name__ == "__main__":
    sys.exit(main())

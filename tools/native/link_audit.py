#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""D9 link audit: which emulation (src/ps2/*, HLE, oracle) code the game exe links.

    python tools/native/link_audit.py report MAP [--by lib|object] [--all] [--tsv OUT]
    python tools/native/link_audit.py check  MAP [--forbid SET[,SET..]] [--extra LIB,..]
    python tools/native/link_audit.py diff   MAP_BEFORE MAP_AFTER
    python tools/native/link_audit.py refs   MAP [--build DIR] [--forbid SET] [--nm PATH]

MAP is the lld-link /MAP file rg-game writes next to the exe (rg-game.map), or the
ld.lld -Map file of a Linux build (same name; sizes there are exact per input section,
objects are `member.o`, libraries `libX.a` -> X; docs/LINUX.md).  Every
public and static symbol row names its `lib:object` (game objects have no lib);
a symbol's size is the distance to the next symbol of its section (so padding
and unnamed data in an object count towards it).  Sizes are approximate to a few
bytes per object, exact in sum per section.

report  per library (or object): bytes of code / data, object count and the D9
        class: `forbidden` (must not be linked by a native-only exe), `pending`
        (emulation still needed, with the lane that owns removing it), `native`
        and `port` (native services, host, game objects, generated code).
        --all lists every library, otherwise only the emulation classes.
check   the native-only gate (ctest `native_only.link_audit`): exit 1 if any
        library of the forbidden sets is linked (--skip-missing: 77 without a map).  Sets: `iop` (SIF / IOP / pad and
        card servers / sound HLE / SPU2 / CDVD sector model / libcdvd / FS oracle;
        the default), `render`, `kernel`, `cpu` (the register bus), `vu0` (the VU0
        model + vcallms bridge: never linked outside RG_VU0_MODE=model), `vu0lib`
        (libvu0 on the VU register struct), `overlay` (the arena manager, arena,
        RG_OVL_DATA backing), `all` (= every set: the D9 end-state gate).
diff    before / after per library (bytes), e.g. default build vs RG_NATIVE_ONLY.
refs    who pulls the forbidden code in: llvm-nm over the build's port libraries
        (--game: and the game objects, slow), then every linked object that
        references a symbol a forbidden library defines (the edges to cut).
        Needs the build dir (default: the map's directory).

Pure text processing (refs runs llvm-nm).  docs/NATIVE-ONLY.md.
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

# ---- D9 classes ---------------------------------------------------------------------
# library -> (set, lane).  Sets other than `native`/`port` are emulation; `iop` is
# what RG_NATIVE_ONLY removes today.
CLASSES = {
    # IOP / SIF / pad+card servers / sound HLE / SPU2 / CDVD: removed by RG_NATIVE_ONLY
    "rg_ps2_sif": ("iop", "native-only (IOP lane)"),
    "rg_ps2_iop": ("iop", "native-only (IOP lane)"),
    "rg_ps2_iop_hle": ("iop", "native-only (IOP lane): FILEIO / LOADFILE / iopheap HLE"),
    "rg_ps2_padmc": ("iop", "native-only (IOP lane): padman / mcserv"),
    "rg_ps2_sound": ("iop", "native-only (audio lane): sound HLE"),
    "rg_snd_tools": ("iop", "native-only (audio lane)"),
    "rg_ps2_spu": ("iop", "native-only (audio lane): SPU2 model"),
    "rg_ps2_cdvd": ("iop", "native-only (FS lane): CDVD sector / drive model"),
    "rg_sce_cdvd": ("iop", "native-only (FS lane): libcdvd over the sector model"),
    "rg_native_fs_oracle": ("iop", "native-only (FS lane): sector-model oracle"),
    # renderer lane (docs/NATIVE-RENDER.md)
    # `render-dma`: the DMAC model and libdma over it -- out of an RG_NATIVE_ONLY rg-game since
    # 2026-10-18 (7) (frame chain walker, rg_sce_graphics_native); `render-vu`: VIF1 / VU1 --
    # out since 2026-10-18 (8) (every VU1 program native: nr_vux.c at the walker); `render`: the GS
    # model + its GPU renderer -- out since 2026-10-24 (10) (the native state block, GIF input and
    # device in rg_native_render: nr_gs.c, nr_dev.cpp, nr_d3d11.cpp) -- and, as a --forbid set,
    # render-dma and render-vu too
    "rg_ps2_gs": ("render", "renderer lane: GS model (register file, local memory, GIF parser; oracle builds and headless Linux)"),
    "rg_gpu": ("render", "renderer lane: GS renderer on the GPU (GS-exact raster; oracle builds)"),
    "rg_ps2_vif": ("render-vu", "renderer lane: VIF1 model (oracle builds; native-only: nr_vux.c)"),
    "rg_ps2_vu": ("render-vu", "renderer lane: VU1 interpreter/translator (oracle builds; native-only: nr_vux.c)"),
    "rg_ps2_dmac": ("render-dma", "renderer lane: DMAC"),
    "rg_sce_graphics": ("render-dma", "renderer lane: libgraph/libdma/libvif* over the models"),
    # kernel (threads lane, docs/NATIVE-THREADS.md)
    # (RG_NATIVE_ONLY replaces all three: rg_native_kernel_ps2k, rg_native_spin,
    # rg_sce_kernel_native; docs/NATIVE-THREADS.md "Native-only")
    "rg_ps2_kernel": ("kernel", "threads lane: EE kernel HLE (scheduler, oracle) + dispatcher"),
    "rg_ps2_spin": ("kernel", "threads lane: spin-loop hooks over the HLE"),
    "rg_sce_kernel": ("kernel", "threads lane: eekernel SDK surface + census recorder"),
    # CPU / VU0 / memory (VU0/CPU lane)
    "rg_ps2_hwbus": ("cpu", "renderer lane (GS privileged + VIF1 FBRST: the only HW_* sites left; "
                            "T0 / IPU / D3-D4 / D_ENABLE gone, docs/NATIVE-CPU.md section 8)"),
    # libvu0 transcribed onto the VU register struct (oracle / default builds); a native-only
    # rg-game links rg_native_vu0 instead (plain C lanes, docs/NATIVE-CPU.md section 9)
    "rg_sce_vu0": ("vu0lib", "VU0/CPU lane: libvu0 on the VU register struct (native-only: rg_native_vu0)"),
    # the VU0 model: the global register file + vcallms on the VU interpreter.  Only
    # RG_VU0_MODE=model links it (the runtime binds it there); local / native never do
    # (docs/NATIVE-CPU.md section 8), so a native-only rg-game must not.
    "rg_vu0": ("vu0", "VU0 model + vcallms bridge (oracle: RG_VU0_MODE=model, tests)"),
    "rg_vu0_oracle": ("vu0", "VU0 model (tests)"),
    "rg_sce_vu0_oracle": ("vu0", "libvu0 on the VU0 model (tests)"),
    # the overlay arena manager: retail-address arena, address-keyed resolvers, the
    # RG_OVL_DATA backing (oracle / default builds); a native-only rg-game with RG_NATIVE_OVL
    # links the native module table rg_native_ovl instead (docs/OVERLAY.md section 8)
    "rg_ps2_overlay": ("overlay", "overlay arena manager (native-only: rg_native_ovl)"),
    "rg_ps2_overlay_bind": ("overlay", "overlay arena binding + RG_OVL_DATA resolver"),
    "rg_ovl_arena": ("overlay", "overlay arena (retail-address block)"),
    "rg_ovl_data": ("overlay", "RG_OVL_DATA backing (overlay memory by retail address)"),
}
SETS = ("iop", "render", "render-dma", "render-vu", "kernel", "cpu", "vu0", "vu0lib", "overlay")
EMU = set(SETS)
NATIVE_PREFIX = ("rg_native_",)


def classify(lib: str) -> tuple[str, str]:
    # (native-only clones keep the original library names: cmake/native_only.cmake)
    if lib == "rg_sce_cdvd_native":
        return ("native", "native-only libcdvd (no sector model)")
    if lib == "rg_sce_graphics_native":
        return ("native", "native-only libdma / libgraph: sends moved at the call, no DMAC "
                          "(the native GIF input and privileged registers behind it)")
    if lib == "rg_sce_kernel_native":
        return ("native", "native-only libkernl over the native kernel table (no census recorder)")
    if lib in CLASSES:
        return CLASSES[lib]
    if lib.startswith(NATIVE_PREFIX):
        return ("native", "")
    if lib == "":
        return ("port", "game / generated objects")
    return ("port", "")


# ---- map parsing ----------------------------------------------------------------------
ROW = re.compile(r"^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]+)\s+(?:f\s+)?(?:i\s+)?(\S+)\s*$")
SECT = re.compile(r"^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+([0-9a-fA-F]+)H\s+(\S+)\s+(CODE|DATA)\s*$")


# ld.lld (ELF, Linux) -Map: "VMA LMA Size Align" then the output section (column 0 of the
# rest), input sections (8 spaces: `path/libX.a(member.o):(.text.f)` or `path/x.o:(.data)`)
# and their symbols (16 spaces)
ELF_ROW = re.compile(r"^\s*([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\d+) (.*)$")
ELF_IN = re.compile(r"^(.*?)(?:\(([^()]+)\))?:\((.*)\)$")
ELF_CODE = (".text", ".init", ".fini", ".plt")


def lib_name(path: str) -> str:
    """library name of an archive path: rg_runtime.lib (lld-link) / librg_runtime.a (ELF)"""
    stem = Path(path).stem
    if path.endswith(".a") and stem.startswith("lib"):
        stem = stem[3:]
    return stem


class MapInfo:
    def __init__(self, path: Path):
        self.path = path
        self.sec_end: dict[int, int] = {}
        self.sec_code: dict[int, bool] = {}
        with open(path, encoding="utf-8", errors="replace") as f:
            first = f.readline()
        if "VMA" in first and "LMA" in first:
            self._parse_elf(path)
            return
        rows = []
        in_syms = False
        with open(path, encoding="utf-8", errors="replace") as f:
            for line in f:
                if not in_syms:
                    m = SECT.match(line)
                    if m:
                        s = int(m.group(1), 16)
                        end = int(m.group(2), 16) + int(m.group(3), 16)
                        self.sec_end[s] = max(self.sec_end.get(s, 0), end)
                        if m.group(5) == "CODE":
                            self.sec_code[s] = True
                        else:
                            self.sec_code.setdefault(s, False)
                        continue
                    if "Publics by Value" in line:
                        in_syms = True
                    continue
                m = ROW.match(line)
                if not m:
                    continue
                s = int(m.group(1), 16)
                if s == 0:
                    continue
                lo = m.group(5)
                lib, _, obj = lo.rpartition(":")
                rows.append((s, int(m.group(2), 16), m.group(3), lib, obj))
        rows.sort(key=lambda r: (r[0], r[1]))
        # size = distance to the next symbol at a higher address in the same section
        self.objs: dict[tuple[str, str], list[int]] = defaultdict(lambda: [0, 0, 0])  # code, data, syms
        self.syms: list[tuple[str, str, str]] = []
        n = len(rows)
        i = 0
        while i < n:
            s, off = rows[i][0], rows[i][1]
            j = i
            while j < n and rows[j][0] == s and rows[j][1] == off:
                j += 1
            nxt = rows[j][1] if j < n and rows[j][0] == s else self.sec_end.get(s, off)
            size = max(0, nxt - off)
            # aliases at one address: the first row owns the bytes
            for k in range(i, j):
                _, _, name, lib, obj = rows[k]
                e = self.objs[(lib, obj)]
                if k == i:
                    e[0 if self.sec_code.get(s) else 1] += size
                e[2] += 1
                self.syms.append((name, lib, obj))
            i = j

    def _parse_elf(self, path: Path) -> None:
        """ld.lld -Map: sizes are the input sections' own (exact), not symbol distances"""
        self.objs = defaultdict(lambda: [0, 0, 0])
        self.syms = []
        out_sec = ""
        cur = None
        with open(path, encoding="utf-8", errors="replace") as f:
            f.readline()
            for line in f:
                m = ELF_ROW.match(line)
                if not m:
                    continue
                vma, size, rest = int(m.group(1), 16), int(m.group(3), 16), m.group(5)
                ind = len(rest) - len(rest.lstrip(" "))
                rest = rest.strip()
                if ind == 0:
                    out_sec, cur = rest, None
                    continue
                if ind <= 8:
                    cur = None
                    if vma == 0:          # not loaded (.debug_*, .comment, .symtab)
                        continue
                    mi = ELF_IN.match(rest)
                    if not mi or mi.group(1).startswith("<"):
                        continue          # <internal>, linker-script assignments
                    file, member = mi.group(1), mi.group(2)
                    if member:
                        lib, obj = lib_name(file), member
                    else:
                        lib, obj = "", Path(file).name
                    cur = (lib, obj)
                    e = self.objs[cur]
                    e[0 if out_sec.startswith(ELF_CODE) else 1] += size
                    continue
                if cur is not None and "=" not in rest:
                    self.objs[cur][2] += 1
                    self.syms.append((rest, cur[0], cur[1]))

    def by_lib(self) -> dict[str, list[int]]:
        out: dict[str, list[int]] = defaultdict(lambda: [0, 0, 0])  # code, data, objects
        for (lib, _obj), (c, d, _s) in self.objs.items():
            e = out[lib]
            e[0] += c
            e[1] += d
            e[2] += 1
        return out

    def libs(self) -> set[str]:
        return {lib for (lib, _o) in self.objs if lib}


def exe_path(map_path: Path) -> Path:
    exe = map_path.with_suffix(".exe")
    return exe if exe.exists() else map_path.with_suffix("")   # ELF: no suffix


def exe_size(map_path: Path) -> int | None:
    exe = exe_path(map_path)
    return exe.stat().st_size if exe.is_file() else None


def kb(n: int) -> str:
    return f"{n / 1024:.1f}"


# ---- commands -------------------------------------------------------------------------
def missing(a) -> bool:
    if Path(a.map).exists():
        return False
    print(f"link_audit: {a.map} not found (build rg-game first)")
    return True


def cmd_report(a) -> int:
    if missing(a):
        return 77 if a.skip_missing else 2
    mi = MapInfo(Path(a.map))
    rows = []
    if a.by == "object":
        for (lib, obj), (c, d, _s) in mi.objs.items():
            cls, lane = classify(lib)
            if not a.all and cls not in EMU:
                continue
            rows.append((cls, lib or "-", obj, c, d, 1, lane))
    else:
        for lib, (c, d, no) in mi.by_lib().items():
            cls, lane = classify(lib)
            if not a.all and cls not in EMU:
                continue
            rows.append((cls, lib or "(objects)", "", c, d, no, lane))
    order = {s: i for i, s in enumerate(list(SETS) + ["native", "port"])}
    rows.sort(key=lambda r: (order.get(r[0], 9), -(r[3] + r[4])))
    out = sys.stdout
    print(f"# {a.map}" + (f"  (exe {exe_size(Path(a.map)):,} bytes)" if exe_size(Path(a.map)) else ""), file=out)
    hdr = ("class", "library", "object", "code_kb", "data_kb", "objects", "lane")
    print("\t".join(h for h in hdr if a.by == "object" or h != "object"), file=out)
    for r in rows:
        cols = [r[0], r[1]] + ([r[2]] if a.by == "object" else []) + [kb(r[3]), kb(r[4]), str(r[5]), r[6]]
        print("\t".join(cols), file=out)
    # totals per class
    tot: dict[str, list[int]] = defaultdict(lambda: [0, 0, 0])
    for lib, (c, d, no) in mi.by_lib().items():
        e = tot[classify(lib)[0]]
        e[0] += c
        e[1] += d
        e[2] += 1 if lib else 0
    print("\n# totals per class (libraries; code KB, data KB)")
    for cls in sorted(tot, key=lambda k: order.get(k, 9)):
        c, d, nl = tot[cls]
        print(f"{cls}\t{kb(c)}\t{kb(d)}\t{nl} libs")
    emu = [tot[s] for s in EMU if s in tot]
    print(f"emulation (all sets)\t{kb(sum(e[0] for e in emu))}\t{kb(sum(e[1] for e in emu))}\t"
          f"{sum(e[2] for e in emu)} libs")
    if a.tsv:
        with open(a.tsv, "w", encoding="utf-8", newline="\n") as f:
            f.write("class\tlibrary\tobject\tcode_bytes\tdata_bytes\tobjects\tlane\n")
            for r in rows:
                f.write(f"{r[0]}\t{r[1]}\t{r[2]}\t{r[3]}\t{r[4]}\t{r[5]}\t{r[6]}\n")
    return 0


def forbidden_sets(spec: str) -> set[str]:
    sets = set()
    for s in spec.split(","):
        s = s.strip()
        if s == "all":
            sets |= set(SETS)
        elif s in SETS:
            sets.add(s)
        elif s:
            raise SystemExit(f"link_audit: unknown set '{s}' (sets: {', '.join(SETS)}, all)")
    if "render" in sets:
        sets.add("render-dma")   # the whole renderer emulation
        sets.add("render-vu")
    return sets


def forbidden_libs(spec: str, extra: str = "") -> set[str]:
    sets = forbidden_sets(spec)
    libs = {lib for lib, (cls, _l) in CLASSES.items() if cls in sets}
    libs |= {x.strip() for x in extra.split(",") if x.strip()}
    return libs


def cmd_check(a) -> int:
    if missing(a):
        return 77 if a.skip_missing else 2
    mi = MapInfo(Path(a.map))
    forb = forbidden_libs(a.forbid, a.extra)
    bl = mi.by_lib()
    bad = sorted(lib for lib in bl if lib in forb)
    pend = sorted(lib for lib in bl if classify(lib)[0] in EMU and lib not in forb)
    for lib in bad:
        c, d, no = bl[lib]
        print(f"FORBIDDEN\t{lib}\t{kb(c)} KB code\t{kb(d)} KB data\t{no} objects\t{classify(lib)[1]}")
    for lib in pend:
        c, d, no = bl[lib]
        print(f"pending\t{lib}\t{kb(c)} KB code\t{kb(d)} KB data\t{no} objects\t{classify(lib)[1]}")
    if bad:
        print(f"link_audit: FAIL: {len(bad)} forbidden libraries linked (sets: {a.forbid})")
        return 1
    print(f"link_audit: PASS: no library of the sets [{a.forbid}] is linked "
          f"({len(pend)} pending emulation libraries still linked)")
    return 0


def cmd_diff(a) -> int:
    A, B = MapInfo(Path(a.before)).by_lib(), MapInfo(Path(a.after)).by_lib()
    print("class\tlibrary\tbefore_kb\tafter_kb\tdelta_kb")
    rows = []
    for lib in set(A) | set(B):
        ba = sum(A.get(lib, [0, 0])[:2])
        bb = sum(B.get(lib, [0, 0])[:2])
        if ba != bb:
            rows.append((classify(lib)[0], lib or "(objects)", ba, bb))
    rows.sort(key=lambda r: r[3] - r[2])
    for r in rows:
        print(f"{r[0]}\t{r[1]}\t{kb(r[2])}\t{kb(r[3])}\t{kb(r[3] - r[2])}")
    ta = sum(sum(v[:2]) for v in A.values())
    tb = sum(sum(v[:2]) for v in B.values())
    print(f"total\t\t{kb(ta)}\t{kb(tb)}\t{kb(tb - ta)}")
    for p in (a.before, a.after):
        s = exe_size(Path(p))
        if s:
            print(f"exe\t{Path(p).with_suffix('.exe')}\t{s:,} bytes")
    return 0


NM_ROW = re.compile(r"^(.*?\.(?:lib|obj|a|o))(?::([^:]+?\.(?:obj|o)))?:\s+(?:[0-9a-fA-F]+\s+)?([A-Za-z?-])\s+(\S+)\s*$")


def nm_symbols(nm: str, files: list[Path]) -> dict[str, tuple[set[str], set[str]]]:
    """member key -> (defined, undefined) external symbols.  Key: 'lib:obj' or 'obj'."""
    out: dict[str, tuple[set[str], set[str]]] = {}
    rsp = Path(os.environ.get("TEMP", "/tmp")) / f"link_audit_{os.getpid()}.rsp"
    rsp.write_text("\n".join(f'"{f}"' for f in files), encoding="utf-8")
    try:
        p = subprocess.run([nm, "-A", "--extern-only", "--no-sort", f"@{rsp}"], capture_output=True, text=True,
                           errors="replace")
    finally:
        rsp.unlink(missing_ok=True)
    for line in p.stdout.splitlines():
        m = NM_ROW.match(line)
        if not m:
            continue
        path, member, t, sym = m.groups()
        if member:
            key = f"{lib_name(path)}:{member}"
        else:
            key = Path(path).name
        e = out.setdefault(key, (set(), set()))
        if t == "U":
            e[1].add(sym)
        elif t not in ("w", "v"):
            e[0].add(sym)
    return out


def cmd_refs(a) -> int:
    mp = Path(a.map)
    build = Path(a.build) if a.build else mp.parent
    mi = MapInfo(mp)
    linked = set(mi.objs)
    forb = forbidden_libs(a.forbid, a.extra)
    libfiles = {}
    for root, dirs, fnames in os.walk(build):
        dirs[:] = [x for x in dirs if x not in ("_deps", "CMakeFiles", "Testing", "game-gen")]
        for fn in fnames:
            if fn.endswith(".lib") or (fn.endswith(".a") and fn.startswith("lib")):
                stem = lib_name(fn)
                # native-only clones (<build>/nonly/) shadow the originals of the same name
                if stem not in libfiles or Path(root).name == "nonly":
                    libfiles[stem] = Path(root) / fn
    files = [libfiles[l] for l in sorted(mi.libs()) if l in libfiles]
    for pat in ("*.obj", "*.o"):
        files.extend((build / "CMakeFiles" / "rg-game.dir").rglob(pat))
    if a.game:   # every linked game object (thousands: slow on a cold disk)
        gameobjs = {o for (l, o) in linked if not l}
        for d in build.glob("CMakeFiles/rg_game_*.dir"):
            files.extend(p for p in d.rglob("*.o*") if p.name in gameobjs)
    syms = nm_symbols(a.nm, files)
    owner: dict[str, str] = {}
    for key, (defs, _u) in syms.items():
        lib = key.split(":")[0] if ":" in key else ""
        if lib in forb and (lib, key.split(":", 1)[1]) in linked:
            for s in defs:
                owner.setdefault(s, key)
    edges = defaultdict(set)
    for key, (_d, undef) in syms.items():
        lib, _, obj = key.rpartition(":")
        if lib in forb or (lib, obj) not in linked:
            continue
        for s in undef:
            if s in owner:
                edges[key].add((s, owner[s]))
    if not edges:
        print("link_audit refs: no linked non-forbidden object references a forbidden library")
    for key in sorted(edges):
        print(key)
        for s, o in sorted(edges[key]):
            print(f"\t{s}\t-> {o}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    r = sp.add_parser("report")
    r.add_argument("map")
    r.add_argument("--by", choices=("lib", "object"), default="lib")
    r.add_argument("--all", action="store_true")
    r.add_argument("--tsv")
    r.add_argument("--skip-missing", action="store_true", help="exit 77 (ctest skip) without a map")
    c = sp.add_parser("check")
    c.add_argument("map")
    c.add_argument("--forbid", default="iop")
    c.add_argument("--extra", default="")
    c.add_argument("--skip-missing", action="store_true", help="exit 77 (ctest skip) without a map")
    d = sp.add_parser("diff")
    d.add_argument("before")
    d.add_argument("after")
    f = sp.add_parser("refs")
    f.add_argument("map")
    f.add_argument("--build")
    f.add_argument("--forbid", default="iop")
    f.add_argument("--extra", default="")
    f.add_argument("--game", action="store_true", help="also scan the game objects (slow)")
    f.add_argument("--nm", default=os.environ.get("RG_LLVM_NM", r"../tools\llvm\bin\llvm-nm.exe"))
    a = ap.parse_args()
    return {"report": cmd_report, "check": cmd_check, "diff": cmd_diff, "refs": cmd_refs}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())

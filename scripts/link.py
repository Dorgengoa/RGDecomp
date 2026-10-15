#!/usr/bin/env python3
"""Assemble the reference disassembly and link the whole main ELF.

    link.py                 build build/link/SCUS_974.90 and report the delta
    link.py --control       split at the same boundaries but keep every slot
                            in ASSEMBLY -- the arm that proves the splitting
                            itself moves no bytes
    link.py --no-c          ignore config/cunits.txt entirely (the Phase-1 link)

PHASE 1 IS COMPLETE as of 2026-08-22: this rebuilds SCUS_974.90 BYTE FOR BYTE
-- 3,675,336 bytes, sha1 87e9eff1d795c894fc09047270baab70d6a8d2c8.

config/cunits.txt names the functions that are COMPILED FROM C into that image
instead of assembled from the reference. Each one cuts asm/main.s in two and
takes the slot between the halves; the trailing padding after a function goes
to the following part, so nothing in the layout depends on linker padding.
The file staying byte-identical is what makes a converted function proven.

Nothing here crosses the wire except the compile and the link.
"""
import os
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

# One worker per core for the assemble stage, capped -- see main().
JOBS = max(2, min(12, (os.cpu_count() or 4)))

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hosted
import rgd
import textsplit
import data2c_integration as data2c

HOST = rgd.BUILD_HOST
REMOTE = rgd.REMOTE_ROOT + "/mainlink"
LD = "../mwcps2-3.0.1b210-060308/mwldps2.exe"
# `-m entry` names the entry point; `-nodead` keeps mwld from dropping a
# section nothing references, which is most of a game image.
LD_FLAGS = ["-nostdlib", "-m", "entry", "-nodead", "-sym", "on,noelf"]
SSH = ["ssh", "-i", str(rgd.SSH_KEY),
       "-o", "StrictHostKeyChecking=no", "-o", "UserKnownHostsFile=/dev/null",
       "-o", "BatchMode=yes"]
AS = rgd.binutil("as")
NM = rgd.binutil("nm")
AS_FLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-mno-pdr", "-non_shared",
            "-G0", "-I", "include"]

OUT = rgd.ROOT / "build" / "link"
PARTS = OUT / "parts"
CUNITS = rgd.ROOT / "config" / "cunits.txt"
CRODATA = rgd.ROOT / "config" / "crodata.txt"
HOSTED = rgd.ROOT / "config" / "hosted.txt"  # GUEST HOST: see hosted.py
TAIL_UNITS = [("main_data", "asm/data/main_data.data.s"),
              ("main_bss", "asm/bss/main_bss.s"),
              ("main_overlays", "asm/bss/main_overlays.s")]


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=rgd.ROOT, **kw)


def cunits() -> list:
    if not CUNITS.exists():
        return []
    return [ln.split("#")[0].strip() for ln in CUNITS.read_text().splitlines()
            if ln.split("#")[0].strip()]


def crodata() -> list:
    """[(symbol, vram, size)] -- where each C unit's own .rodata belongs.

    A compiled `switch` puts its jump table in the unit's `.rodata`, which
    admission condition 3 refuses because the lcf's only home for it was the
    trailing `*(.rodata)` wildcard -- past the end of the image, shifting
    everything.  Retail's tables live INSIDE `asm/main.s`, so they cut out of
    the text the same way a function does; this file says which table belongs
    to which unit and how big it is.

    ⚠ The size is checked against the object, not trusted: a declared size
    that is too small links byte-identical anyway (the leftover words simply
    stay in the following assembly part) while the shipped unit is not the
    function.  That is the same silent failure the `size:` screens exist for.

    Format, one per line:   <symbol> <hex addr> <hex size>   # comment
    """
    if not CRODATA.exists():
        return []
    out = []
    for ln in CRODATA.read_text().splitlines():
        ln = ln.split("#")[0].strip()
        if not ln:
            continue
        sym, addr, size = ln.split()
        out.append((sym, int(addr, 16), int(size, 16)))
    return out


def obj_section(path: Path, want: str) -> tuple:
    """(size, addralign) of a named section, or (0, 0) if it has none."""
    import struct
    d = path.read_bytes()
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    strtab, = struct.unpack_from("<I", d, shoff + shstrndx * shentsize + 16)
    for i in range(shnum):
        off = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, off)
        end = d.index(b"\x00", strtab + nameoff)
        if d[strtab + nameoff:end] == want.encode():
            return (struct.unpack_from("<I", d, off + 20)[0],
                    struct.unpack_from("<I", d, off + 32)[0])
    return (0, 0)


# --- s37 INFRA prototype: multi-slot .rodata -------------------------------
#
# A unit with N switch statements emits N anonymous `.rodata` ELF sections
# (all literally named ".rodata", disambiguated only by section INDEX, which
# is file order = first-use order in the compiled .text). `obj_section()`
# above returns only the FIRST such section, so a unit's 2nd..Nth jump table
# was invisible to the old size/alignment check and unplaceable in the lcf.
#
# Measured on VariantPromoteTypes_36e510 (build/obj-s37INFRA/VariantPromoteTypes_36e510.o, 2026-09-07):
# 11 `.rodata` sections, EACH sh_size=0x2C, EACH sh_addralign=16. Retail's
# own 11 jtbl_ addresses for this unit are exactly 0x30 apart (0x004632A0,
# 0x004632D0, ... 0x00463480) -- i.e. each table is followed by a 4-byte gap
# that is precisely what mwld's own 16-byte alignment rule inserts before
# the NEXT section. This is the SAME shape `laid_out_text_size()` above
# already exploits for a multi-entry-point `.text` (mwcc emits one `.text`
# PER entry point; a single lcf line `<name>.o (.text)` "already matches
# every `.text` in the file and mwld lays them down in file order" -- see
# that function's docstring, proven in production). LCF section-selection
# syntax `object.o (sectionname)` is generic, not `.text`-specific, so the
# same "one line captures every same-named section, laid out from the line's
# address in file order honouring each section's own sh_addralign" behaviour
# is expected to apply identically to `.rodata`.
#
# So: NO crodata.txt FORMAT CHANGE is needed for a unit whose own N tables
# are retail-CONTIGUOUS (which is the expected case -- they all come out of
# that one function's own former .rodata hole, same as rodata_cuts() already
# assumes for a single table). One row, same three columns as today:
#   <symbol>  <lowest table's hex addr>  <hex TOTAL LAID-OUT SPAN>
# where the span is measured from the lowest address to the end of the
# HIGHEST (last-emitted) table -- exactly what laid_out_rodata_size() below
# computes. A single-section row is numerically UNCHANGED by this: with only
# one section there is no trailing pad, so laid_out_rodata_size() returns
# exactly obj_section()'s size, the same value every existing crodata.txt
# row already carries. Existing rows do not need to be rewritten.
#
# ⚠ UNVERIFIED ASSUMPTION, flagged for the orchestrator: this design relies
# on mwld laying out ALL same-named sections from ONE lcf line starting at
# that line's address (the .text precedent). It has NOT been re-proven here
# against a real mwld invocation -- see PATCH.md. If a future multi-table
# unit's retail tables are NOT contiguous (something else interleaved
# between two of its own tables), this single-base design cannot place it
# and the alternative (multiple explicit-address rows, one lcf line per
# row, relying on mwld consuming one unplaced same-named section per line)
# would need its own from-scratch verification -- it is a DIFFERENT,
# unproven linker assumption, not a generalisation of this one.

def obj_rodata_sections(path: Path) -> list:
    """[(size, addralign), ...] for every section named ".rodata", in file
    (section-index) order -- the order mwcc emitted them, which is the
    order the compiled .text first uses each jump table.
    """
    import struct
    d = path.read_bytes()
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    strtab, = struct.unpack_from("<I", d, shoff + shstrndx * shentsize + 16)
    out = []
    for i in range(shnum):
        off = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, off)
        end = d.index(b"\x00", strtab + nameoff)
        if d[strtab + nameoff:end] == b".rodata":
            out.append((struct.unpack_from("<I", d, off + 20)[0],
                         struct.unpack_from("<I", d, off + 32)[0]))
    return out


def laid_out_rodata_size(path: Path, vram: int) -> int:
    """Extent mwld occupies from `vram` for EVERY `.rodata` section in the
    file, laid out one after another in file order, each one padded up to
    its own sh_addralign (capped the same way laid_out_text_size() caps
    against the largest power of two dividing `vram`) -- the multi-slot
    twin of laid_out_text_size(). A single-section object returns exactly
    obj_section()'s size, so every already-linking single-slot unit is
    unaffected by construction, not by measurement (same argument as
    laid_out_text_size's own single-.text case).
    """
    want = 16
    while want > 4 and vram % want:
        want //= 2
    cur = vram
    for size, align in obj_rodata_sections(path):
        a = min(align, want) or 1
        cur = (cur + a - 1) & ~(a - 1)
        cur += size
    return cur - vram


# asm/reginfo_pin.s rides with main_data: it pins retail's .reginfo register
# masks, which the image would otherwise lose one register at a time as the
# last assembly user of each is converted to C (mwcc objects carry no
# .reginfo).  gasfixup.py drops its .reginfo_pin section, so it adds no bytes.
REGINFO_PIN = {"main_data": "asm/reginfo_pin.s"}


def assemble(name: str, src: str) -> bool:
    raw = OUT / f"{name}.raw.o"
    srcs = [src] + ([REGINFO_PIN[name]] if name in REGINFO_PIN else [])
    if sh([str(AS)] + AS_FLAGS + srcs + ["-o", str(raw)]).returncode != 0:
        return False
    # gasfixup.py biases the R_MIPS_PC16 addends gas and mwld disagree about.
    return sh([sys.executable, "scripts/gasfixup.py", str(raw),
               str(OUT / f"{name}.o")]).returncode == 0


ADDR_IN_NAME = __import__("re").compile(r"_([0-9A-Fa-f]{6,8})$")


def obj_text_size(path: Path) -> int:
    """TOTAL size of an ELF object's .text, read off its section headers.

    * mwcc emits ONE `.text` PER FUNCTION -- measured 2026-09-01 in BOTH C and
    C++, so it is not a C++/comdat artefact.  A symbol spanning more than one
    ENTRY POINT (the lcf names 83 such on MAIN, 6,184 B still open) therefore
    compiles to several `.text` sections whose sizes SUM to retail's size, and
    reading only the first refused the unit with a length error quoting the
    FIRST function's size.  The lcf line `<name>.o (.text)` already matches
    every `.text` in the file and mwld lays them down in file order, which is
    source order, which is retail's order.

    !! This only ever SUMS: a single-`.text` object returns exactly what it
    returned before, so every already-linking unit is bit-for-bit unaffected.
    `build/zz/s22_textsize_arm.py` proves that over the whole merged corpus.
    """
    import struct
    d = path.read_bytes()
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    strtab, = struct.unpack_from("<I", d, shoff + shstrndx * shentsize + 16)
    total = 0
    for i in range(shnum):
        off = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, off)
        end = strtab + nameoff
        while d[end]:
            end += 1
        if d[strtab + nameoff:end] == b".text":
            total += struct.unpack_from("<I", d, off + 20)[0]
    return total


def laid_out_text_size(path: Path, vram: int) -> int:
    """Extent mwld actually OCCUPIES from `vram` for every `.text` in the file.

    ⚠ `obj_text_size()` above is WRONG for a multi-entry unit and this replaces
    it at the slot-fill check.  It returns the RAW SUM of the section sizes;
    mwld does not concatenate the sections, it honours each one's
    `sh_addralign` (16 from mwcc, after `relax_text_align` has lowered it) and
    PADS each non-final function up to the next boundary.  Retail does the same
    -- a MIPS pad word 0x00000000 IS `nop`, and the pads are visible in the
    listings: `TimeOfDayGetFixedIndex_18d2b0` entry 1 is 0x8 at 0x18D2B0, two nops, entry 2 at
    0x18D2C0, total 0x18 where the raw sum is 0x10.

    So a multi-entry unit whose bodies are byte-perfect was refused for a
    "wrong length" it did not have.  Measured on MAIN s33 over the 11,980
    merged objects: **5 fixed, 0 regressions** -- and those 5 are exactly the
    units the session 31 link refused.

    ★ SINGLE-`.text` OBJECTS ARE UNCHANGED BY CONSTRUCTION, not by measurement.
    `want` is the largest power of two ≤16 dividing `vram`, and each section's
    effective alignment `a` divides `want`, hence divides `vram`.  The first
    (only) section therefore starts at `vram` with no padding and the extent is
    identically the raw size.  Every already-linking unit is bit-for-bit
    unaffected.
    """
    import struct
    d = path.read_bytes()
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    strtab, = struct.unpack_from("<I", d, shoff + shstrndx * shentsize + 16)
    want = 16
    while want > 4 and vram % want:
        want //= 2
    cur = vram
    for i in range(shnum):
        off = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, off)
        end = strtab + nameoff
        while d[end]:
            end += 1
        if d[strtab + nameoff:end] != b".text":
            continue
        size, = struct.unpack_from("<I", d, off + 20)
        align, = struct.unpack_from("<I", d, off + 32)
        a = min(align, want) or 1
        cur = (cur + a - 1) & ~(a - 1)
        cur += size
    return cur - vram


def cross_part_symbols(objs: list, body: str) -> list:
    """Assignments for labels a split turned into cross-object references.

    splat emits branch targets and alternate entry points as `alabel` --
    deliberately LOCAL, because a branch to a global becomes an R_MIPS_PC16
    that gas and mwld disagree about. That is correct while all of .text is
    ONE object. Cutting a C unit out of it can put such a label's definition
    in one part and a reference to it in another, and the link then fails with
    a single `Undefined :` line that reads like a missing function.

    Every one of these names encodes its own address, exactly like the 3,282
    assignments the lcf already carries, so the fix is mechanical -- but it is
    generated here rather than hand-added, because which labels cross depends
    on where the cuts fall.
    """
    # ONE `nm` PER TEXT OBJECT, AND IT WAS SERIAL. At 13,937 objects that is
    # 13,937 process spawns on Windows -- minutes of a link with the build
    # host idle and nothing in the log, the same shape as the assemble stage
    # above and as rgd.src_path(). memory/levers.d/main-hostbuild-src-walk.md
    # priced it and deliberately left it unfixed rather than ship an
    # unexercised concurrency change into the tool that certifies the project.
    # Nothing here is order-dependent: every object is read independently and
    # both accumulators are SETS, so the only thing concurrency can change is
    # the wall clock. The proof that it does not change the ANSWER is
    # build/p28_nmproof.py, which runs both implementations over the objects a
    # serial link already produced and compares the emitted assignment list --
    # pass 25's p25_asmproof.py pattern, and it does not need a link.
    def _nm(o):
        return subprocess.run([str(NM), str(OUT / o)],
                              capture_output=True, text=True).stdout

    defined, undefined = set(), set()
    with ThreadPoolExecutor(max_workers=JOBS) as pool:
        for out in pool.map(_nm, objs):
            for line in out.splitlines():
                f = line.split()
                if len(f) == 2 and f[0] == "U":
                    undefined.add(f[1])
                elif len(f) == 3 and f[1].isupper() and f[1] != "U":
                    defined.add(f[2])
    already = set(__import__("re").findall(r"^\s*(\w+)\s*=\s*0x", body,
                                           __import__("re").M))
    out_lines = []
    for name in sorted(undefined - defined - already):
        m = ADDR_IN_NAME.search(name)
        if not m:
            print(f"link: {name} is undefined after the split and its address "
                  f"is not derivable from its name")
            return None
        out_lines.append(f"        {name} = 0x{int(m.group(1), 16):08X};")
    return out_lines


def relax_text_align(data: bytes, vram: int) -> bytes:
    """Lower a compiled object's .text sh_addralign to what `vram` needs.

    mwcc gives every `.text` sh_addralign 16. mwld honours it, so a function
    whose real address is only 8-aligned gets its slot bumped to the next 16
    boundary and every byte after it shifts -- `textsplit.py` used to refuse
    the cut outright rather than let that happen silently.

    RG pads its OWN functions to 16 everywhere (the measurement that killed
    the padding signal for TU recovery), so this never came up until library
    code entered the scope. The prebuilt archives are 8-aligned and ALL FIVE
    library units in `config/units.txt` are affected -- `kill` 0x00116D78,
    `abs` 0x0012DE98, `unlink` 0x00116DC8, `sceSifGetSreg` 0x001193B8,
    `sceVu0CopyVectorXYZ` 0x0010B408.

    Lowering the field is safe because the lcf says ALIGNALL(1) and the
    assembly parts on either side are gas objects with sh_addralign 4 already
    -- the same value this drops to when the address needs it. It only ever
    LOWERS, so a 16-aligned function is untouched and the 45 units that were
    already linking are bit-for-bit unaffected.
    """
    import struct
    d = bytearray(data)
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    strtab, = struct.unpack_from("<I", d, shoff + shstrndx * shentsize + 16)
    want = 16
    while want > 4 and vram % want:
        want //= 2
    for i in range(shnum):
        off = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, off)
        end = d.index(0, strtab + nameoff)
        if d[strtab + nameoff:end] != b".text":
            continue
        have, = struct.unpack_from("<I", d, off + 32)
        if have > want:
            struct.pack_into("<I", d, off + 32, want)
    return bytes(d)


def main() -> int:
    control = "--control" in sys.argv
    syms = [] if "--no-c" in sys.argv else cunits()

    OUT.mkdir(parents=True, exist_ok=True)
    data_active = data2c.enabled()
    if data_active and (control or not syms):
        raise SystemExit("data2c admission requires the matched C text link")
    arming_address = None
    if "--arming-address" in sys.argv:
        arming_address = int(sys.argv[sys.argv.index("--arming-address")+1], 0)
    if data_active:
        data2c.prepare(OUT, arming_address)
    tail_units = ([("data2c_reginfo", "asm/reginfo_pin.s")]
                  if data_active else TAIL_UNITS)
    data_sections = data2c.placements() if data_active else {}
    rodata = [r for r in crodata() if r[0] in set(syms)] if syms else []
    if syms:
        order = textsplit.split(syms, PARTS, cunit_slots=not control,
                                rodata_slots=rodata,
                                data_slots=data2c.text_slots() if data_active else ())
    else:
        order = [("main_text", "asm")]

    # ASSEMBLE THE PARTS CONCURRENTLY.  Each part is an independent
    # `as` plus an independent `gasfixup.py`, i.e. TWO process spawns, and at
    # 5,300 parts the serial loop is the whole cost of a link -- process
    # creation on Windows, not compute, so the box sat at one busy core.
    # Nothing orders the parts: each reads one .s and writes its own .o.
    # `order` still decides the LCF's object order.  This only moves WHEN
    # each object is written, never which or in what sequence they are named.
    asm_jobs = [(name, "asm/main.s" if name == "main_text"
                 else f"build/link/parts/{name}.s")
                for name, kind in order if kind == "asm"] + list(tail_units)
    with ThreadPoolExecutor(max_workers=JOBS) as pool:
        ok = list(pool.map(lambda ns: (ns[0], assemble(*ns)), asm_jobs))
    bad = [n for n, good in ok if not good]
    if bad:
        print("link: failed to assemble " + " ".join(bad[:8]))
        return 1

    # (object, section) in lcf order.  A unit with a jump table appears twice:
    # once for its .text at the function's address and once for its .rodata at
    # the table's -- two lcf lines naming ONE object file.
    placements = []
    rodata_want = {s: (a, n) for s, a, n in rodata}
    # `textsplit.symbol_table()` RE-READS AND RE-PARSES config/main.symbols.txt
    # on every call, and the loop below used to call it TWICE per C unit: at
    # 6,968 units and 17,679 symbol lines that is 13,936 full parses of an
    # 830 KB file. Hoisted. Behaviour-identical by construction -- same
    # function, same dict, nothing in the loop mutates it -- and
    # build/p28_symtbl_proof.py checks that the table is stable across calls.
    sym_tbl = textsplit.symbol_table()
    guests = hosted.load(HOSTED)
    hosts = {}
    for g, h in guests.items():
        hosts.setdefault(h, []).append(g)
    for name, kind in order:
        if kind == "asm":
            placements.append((f"{name}.o", ".text"))
        elif kind == "data":
            placements.append((name + ".o", data_sections[name]))
        elif kind == "rodata":
            # The unit's own jump table, taking the hole its retail table left.
            # The object itself is written by this loop's "c" pass -- the two
            # entries name the same file -- so all that is checked here is that
            # what mwcc emitted is the SIZE and ALIGNMENT the slot was cut for.
            obj = rgd.OBJ_DIR / f"{name}.o"
            addr, want = rodata_want[name]
            # s37 INFRA: `want` is the LAID-OUT SPAN of every same-named
            # `.rodata` section in the object (see laid_out_rodata_size()
            # above), not one section's raw size -- identical to a
            # single-section unit's own size when there is only one, so
            # every existing crodata.txt row is unaffected.
            got = laid_out_rodata_size(obj, addr) if obj.exists() else 0
            if got != want:
                print(f"link: {name}'s .rodata lays out to 0x{got:X} bytes "
                      f"from 0x{addr:08X}, the slot wants 0x{want:X} -- a "
                      f"wrong-size rodata run shifts the whole image")
                return 1
            secs = obj_rodata_sections(obj) if obj.exists() else []
            align = secs[0][1] if secs else 0
            if align and addr % align:
                print(f"link: {name}'s .rodata wants {align}-alignment and "
                      f"0x{addr:08X} is not {align}-aligned")
                return 1
            placements.append((f"{name}.o", ".rodata"))
        else:
            # Compiled by hostbuild.py. A stale object here would silently
            # link the PREVIOUS build of the function, so require it present
            # and stamped by the host build.
            # A GUEST (config/hosted.txt) has no object of its own: it is a
            # `static` in its HOST's TU, carved out of HOST.o by section name.
            host = guests.get(name)
            src_name = host or name
            obj = rgd.OBJ_DIR / f"{src_name}.o"
            stamp = rgd.OBJ_DIR / ".built-by"
            if not obj.exists():
                print(f"link: no compiled object for {src_name}; "
                      f"run scripts/hostbuild.py {src_name}")
                return 1
            if not stamp.exists() or stamp.read_text().strip() != "host":
                print("link: build/obj was written by the LOCAL stand-in "
                      "compiler; run scripts/hostbuild.py first")
                return 1
            data = obj.read_bytes()
            for g in hosts.get(src_name, ()):
                try:
                    data = hosted.rename_guest(data, g)
                except ValueError as e:
                    print(f"link: {e}")
                    return 1
            out_obj = OUT / f"{src_name}.o"
            # Measure on the object as compiled (renamed but not yet relaxed),
            # exactly as before hosted units existed; relax afterwards.
            out_obj.write_bytes(data)
            # A compiled .text of the wrong LENGTH shifts every byte after it,
            # so the report would be a three-megabyte diff with no information
            # in it. Say which function is the wrong size instead.
            vram, want = sym_tbl[name]
            if host:
                sec = f".text.{name}"
                got, align = hosted.section_size(out_obj.read_bytes(), sec)
                if align and vram % align:
                    print(f"link: {name} ({sec} of {host}.o) wants "
                          f"{align}-alignment and 0x{vram:08X} is not")
                    return 1
            else:
                sec = ".text"
                got = laid_out_text_size(out_obj, vram)
            if got != want:
                print(f"link: {name} compiles to 0x{got:X} bytes, retail's is "
                      f"0x{want:X} -- it is not matched yet, and a wrong-length "
                      f"slot shifts the whole image")
                return 1
            out_obj.write_bytes(relax_text_align(data, sym_tbl[src_name][0]))
            placements.append((f"{src_name}.o", sec))

    # One name per FILE for the link line; one line per SECTION for the lcf.
    text_objs = list(dict.fromkeys(o for o, _ in placements))
    objs = list(dict.fromkeys(text_objs +
        ([o for o, sec in data2c.tail()+data2c.reservations()] if data_active else []) +
        [f"{n}.o" for n, _ in tail_units]))

    # The lcf names the text objects explicitly and in address order; the
    # template carries one placeholder line for the single-object Phase-1 link.
    lcf = rgd.ROOT / "SCUS_974.90.lcf"
    body = lcf.read_text()
    if data_active:
        body = data2c.external_assignments(body)
    if data_active:
        initialized = [(o, s) for o, s in data2c.tail() if s != ".bss"]
        zero = [(o, s) for o, s in data2c.tail() if s == ".bss"]
        body = body.replace("        main_data.o (.data)",
            "\n".join("        %s (%s)" % (o, s) for o, s in initialized))
        body = body.replace("        main_bss.o (.bss)",
            "\n".join("        %s (%s)" % (o, s) for o, s in zero))
        for o, s in data2c.reservations():
            body = body.replace("main_overlays.o (%s)" % s, "%s (%s)" % (o, s))
    placeholder = "        main_text.o (.text)"
    if placeholder not in body:
        print("link: the lcf no longer carries the main_text.o (.text) line")
        return 1
    placed = "\n".join(f"        {o} ({sec})" for o, sec in placements)
    body = body.replace(placeholder, placed)

    extra = cross_part_symbols(objs, body)
    if extra is None:
        return 1
    if extra:
        anchor = "        D_0044B778 = 0x0044B778;"
        if anchor not in body:
            print("link: the lcf's assignment block no longer starts at "
                  "D_0044B778")
            return 1
        body = body.replace(
            anchor,
            "        // Labels the C-unit split turned into cross-object\n"
            "        // references; generated by link.py, not hand-written.\n"
            + "\n".join(extra) + "\n\n" + anchor)
        print(f"cross-part refs : {len(extra)} ("
              f"{' '.join(l.split()[0] for l in extra[:6])}"
              f"{' ...' if len(extra) > 6 else ''})")
    (OUT / "SCUS_974.90.lcf").write_text(body, encoding="ascii")

    sh(SSH + [HOST, f"rm -rf {REMOTE} && mkdir -p {REMOTE}"])
    # The object list goes over as a FILE (`@o_files`) rather than on the
    # command line: at 13,937 objects the argv is megabytes and the remote
    # shell refuses it. mwld reads the @-file one name per line, and the
    # names must be bare -- they are all in the link directory already.
    (OUT / "o_files").write_text("\n".join(objs) + "\n", encoding="ascii",
                                 newline="\n")

    # ONE tar over the whole set, not one scp per object.
    bundle = OUT / "push.tar.gz"
    (OUT / "tar_files").write_text(
        "\n".join(list(objs) + ["SCUS_974.90.lcf", "o_files"]) + "\n",
        encoding="utf-8", newline="\n")
    if sh(["tar", "czf", str(bundle), "-C", str(OUT), "-T",
           str(OUT / "tar_files")]).returncode != 0:
        return 1
    with open(bundle, "rb") as fh:
        if sh(SSH + [HOST, f"tar xzf - -C {REMOTE}"], stdin=fh).returncode != 0:
            return 1

    r = sh(SSH + [HOST, f"cd {REMOTE} && ../wibo {LD} "
                        f"{' '.join(LD_FLAGS)}"
                        f" -o SCUS_974.90 SCUS_974.90.lcf @o_files"],
           capture_output=True, text=True)
    if r.stdout.strip():
        print(r.stdout.strip())

    # Delete the previous ELF first: a failed link otherwise leaves the old
    # one in place and report() scores THAT.
    (OUT / "SCUS_974.90").unlink(missing_ok=True)
    # A two-hour link is followed by one small copy; retry it rather than
    # lose the link to a dropped connection.
    for _ in range(4):
        sh(["scp", "-q", "-i", str(rgd.SSH_KEY),
            "-o", "StrictHostKeyChecking=no", "-o", "UserKnownHostsFile=/dev/null",
            "-o", "BatchMode=yes", f"{HOST}:{REMOTE}/SCUS_974.90",
            str(OUT / "SCUS_974.90")])
        if (OUT / "SCUS_974.90").exists():
            break
        __import__("time").sleep(10)
    if not (OUT / "SCUS_974.90").exists():
        print("link: no ELF came back -- the link failed")
        return 1

    if not syms:
        arm = "asm only (Phase 1)"
    elif control:
        arm = f"CONTROL -- split at {len(syms)} boundary/ies, every slot asm"
    else:
        arm = "C: " + " ".join(syms)
    print(f"\narm             : {arm}")
    print(f"text objects    : {len(text_objs)}")
    return report()


def report() -> int:
    import struct
    import hashlib

    def parse(p):
        d = Path(p).read_bytes()
        entry, phoff = struct.unpack_from("<II", d, 24)
        phentsize, phnum = struct.unpack_from("<HH", d, 42)
        ph = [struct.unpack_from("<IIIIIIII", d, phoff + i * phentsize)
              for i in range(phnum)]
        return d, entry, ph

    rd, rent, rph = parse(str(rgd.RETAIL_DIR / "SCUS_974.90"))
    od, oent, oph = parse(OUT / "SCUS_974.90")
    same = (rd[rph[0][1]:rph[0][1] + rph[0][4]]
            == od[oph[0][1]:oph[0][1] + oph[0][4]])
    print(f"loadable image  : {'BYTE-IDENTICAL' if same else 'DIFFERS'} (0x"
          f"{oph[0][4]:x} bytes)")
    print(f"entry           : retail 0x{rent:08x}  ours 0x{oent:08x}")
    print(f"filesz / memsz  : retail 0x{rph[0][4]:x} / 0x{rph[0][5]:x}   ours 0x"
          f"{oph[0][4]:x} / 0x{oph[0][5]:x}")
    print(f"program headers : retail {len(rph)}  ours {len(oph)}")
    exact = rd == od
    print(f"file sha1       : retail {hashlib.sha1(rd).hexdigest()}")
    print(f"                  ours   {hashlib.sha1(od).hexdigest()}")
    if not exact:
        n = min(len(rd), len(od))
        diffs = [i for i in range(n) if rd[i] != od[i]]
        print(f"differing bytes : {len(diffs)}"
              + (f"  (len retail {len(rd)} ours {len(od)})"
                 if len(rd) != len(od) else ""))
        for i in diffs[:8]:
            print(f"  0x{i:06x}: retail {rd[i]:02x}  ours {od[i]:02x}")
    print(f"\nSCUS_974.90     : {'BYTE-IDENTICAL' if exact else 'DIFFERS'}")
    return 0 if exact else 1


if __name__ == "__main__":
    if data2c.enabled():
        import data2c_runner
        sys.argv.insert(1, "link")
        raise SystemExit(data2c_runner.main())
    raise SystemExit(main())

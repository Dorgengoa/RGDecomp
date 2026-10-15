#!/usr/bin/env python3
"""Build an MWo3 overlay .BIN with COMPILED C in it, and compare byte for byte.

    olink.py title --no-c        every slot in assembly (the Phase-4 link)
    olink.py title --control     same cuts, every slot still in ASSEMBLY
    olink.py title               config/ocunits/title.txt compiled from C

Overlay twin of scripts/link.py.  scripts/link_overlay.py already rebuilds all
seven overlays byte-identically from reference assembly, but it has no path for
a compiled function -- no textsplit, no cunits, no mwcc.  This adds one, using
the same cut rule, the same alignment relaxation and the same three arms that
made the main image's C admissible.

ISOLATION, because a second session may be grinding main units at any moment:

    remote   ~/rgd/nmlc          (link_overlay.py uses ~/rgd/ovl)
    local    build/overlay-c-nm/    (link_overlay.py uses build/overlays/)
    objects  build/obj-nm/       written by sandbox_build.py --tag nm,
                                 NEVER build/obj (hostbuild.py's, shared)
    lists    config/ocunits/<n>.txt, not config/cunits.txt

Nothing here writes anything scripts/link.py, status.py or hostbuild.py read.
"""
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import rgd
import otextsplit
import t_lit4
import n_jtbl
import n_data

HOST = rgd.BUILD_HOST
REMOTE = rgd.REMOTE_ROOT + "/nmlc"
LD = "../mwcps2-3.0.1b210-060308/mwldps2.exe"
LD_FLAGS = ["-nostdlib", "-nodead", "-sym", "on,noelf"]
SSH = ["ssh", "-i", str(rgd.SSH_KEY),
       "-o", "StrictHostKeyChecking=no", "-o", "UserKnownHostsFile=/dev/null",
       "-o", "BatchMode=yes"]
SCP = ["scp", "-q", "-i", str(rgd.SSH_KEY),
       "-o", "StrictHostKeyChecking=no", "-o", "UserKnownHostsFile=/dev/null",
       "-o", "BatchMode=yes"]
AS = rgd.binutil("as")
NM = rgd.binutil("nm")
AS_FLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-mno-pdr", "-non_shared",
            "-G0", "-I", "include"]
OUT = rgd.ROOT / "build" / "overlay-c-nm"
PARTS = OUT / "parts"
OBJ = rgd.ROOT / "build" / "obj-nm"
LIT4_WORDS = t_lit4.retail_words()      # retail's float pool, read once
OCUNITS = rgd.ROOT / "config" / "ocunits"
REF_BIN = rgd.RETAIL_DIR / "BIN"
LOAD = 0x004E9E80
HDR = 0x40
# Main's _gp. An overlay runs inside the loaded main image and reaches main's
# small data through main's $28, so a compiled overlay unit's GPREL16
# relocations resolve against this and not against anything overlay-local.
bytecheck_GP = 0x00485170
IDS = {"viewer": 1, "title": 2, "insmenu": 3, "launcher": 4,
       "normal": 5, "factory": 6, "insect": 7}


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=rgd.ROOT, **kw)


def cunits(name: str) -> list:
    f = OCUNITS / f"{name}.txt"
    if not f.exists():
        return []
    return [ln.split("#")[0].strip() for ln in f.read_text().splitlines()
            if ln.split("#")[0].strip()]


def tail_units(name: str):
    """The overlay's data and bss assembly, unchanged by the text split."""
    d = rgd.ROOT / "asm" / "overlays" / name
    out = []
    for tag, p in ((f"{name}_data", d / "data" / f"{name}_data.data.s"),
                   (f"{name}_bss", d / f"{name}_bss.s")):
        if p.exists():
            out.append((tag, p))
    return out


def assemble(tag: str, src) -> bool:
    raw, obj = OUT / f"{tag}.raw.o", OUT / f"{tag}.o"
    obj.unlink(missing_ok=True)
    if sh([str(AS)] + AS_FLAGS + [str(src), "-o", str(raw)]).returncode:
        return False
    return sh([sys.executable, "scripts/gasfixup.py",
               str(raw), str(obj)]).returncode == 0


def obj_text_size(path: Path) -> int:
    d = path.read_bytes()
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    strtab, = struct.unpack_from("<I", d, shoff + shstrndx * shentsize + 16)
    for i in range(shnum):
        off = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, off)
        end = d.index(b"\0", strtab + nameoff)
        if d[strtab + nameoff:end] == b".text":
            return struct.unpack_from("<I", d, off + 20)[0]
    return 0


def relax_text_align(data: bytes, vram: int) -> bytes:
    """Lower a compiled object's .text sh_addralign to what vram needs.

    mwcc gives every .text sh_addralign 16 and mwld honours it, so a function
    at an only-8-aligned address gets its slot bumped and every byte after it
    shifts.  Lowering is safe: the lcf says ALIGNALL(1) and the assembly parts
    either side are gas objects at 4 already.  It only ever LOWERS.
    """
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


def unresolved(objs):
    """Symbols undefined once the overlay's own objects are linked.

    Count only GLOBAL definitions as satisfying a reference: splat emits some
    labels as `alabel`, LOCAL by design, and cutting .text into parts turns
    intra-object references to them into cross-object ones.  Those then show up
    here and get an absolute assignment read off their own name -- the same
    mechanism link.py generates for the main image, reached from the overlay
    side.  A name with no address in it is a hard error, deliberately.
    """
    import re
    undef, defined = set(), set()
    for o in objs:
        r = sh([str(NM), str(OUT / o)], capture_output=True, text=True)
        for line in r.stdout.splitlines():
            f = line.split()
            if len(f) == 2 and f[0] == "U":
                undef.add(f[1])
            elif len(f) == 3 and f[1].isupper():
                defined.add(f[2])
    out, bad = {}, []
    for sym in sorted(undef - defined):
        m = re.search(r"([0-9A-Fa-f]{6,8})$", sym)
        if not m:
            bad.append(sym)
            continue
        out[sym] = int(m.group(1), 16)
    return out, bad


def write_lcf(name: str, text_objs, objs):
    syms, bad = unresolved(objs)
    if bad:
        for s in bad:
            print(f"olink: {s} is undefined and its address is not derivable "
                  f"from its name")
        return None
    undef = rgd.ROOT / "build" / "splat" / f"{name}.undefined_syms.txt"
    if undef.exists():
        import re
        for line in undef.read_text().splitlines():
            m = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", line)
            if m:
                syms.setdefault(m.group(1), int(m.group(2), 16))
    print(f"   {len(syms)} unresolved symbols -> absolute assignments")
    # ★ _gp IS NEEDED HERE, and the note saying mwld ignores an lcf _gp for an
    # overlay does NOT apply: that was measured on the pure-assembly link,
    # where the overlay config disassembles gp-relative operands as literal
    # offsets and NOTHING asks the linker to compute one -- so "ignored" meant
    # "unused".  A compiled C unit emits real R_MIPS_GPREL16 relocations, and
    # without _gp every one of them dies with "GP offset overflow / Recompile
    # with a lower limit for Small Data", which reads as a compiler flag
    # problem and is not one.  11 of title's first 19 units hit it at once.
    #
    # The value is MAIN'S gp: an overlay is loaded into the running main image
    # and addresses main's small data through main's $28.  obytecheck.py
    # already resolves these correctly at 0x00485170 and reads MATCH.
    syms.setdefault("_gp", bytecheck_GP)
    nl = chr(10)
    body = nl.join(f"        {k} = 0x{v:08X};" for k, v in sorted(syms.items()))
    # Name every text object explicitly and IN ADDRESS ORDER.  A bare *(.text)
    # would leave the layout to whatever order mwld happens to see the objects
    # in -- exactly what must not be left to discretion once the text is more
    # than one object.
    textlines = nl.join(f"        {o} (.text)" for o in text_objs)
    bssline = (f"        // explicit: a bare *(.bss) misses the NOBITS input{nl}"
               f"        {name}_bss.o (.bss){nl}"
               if f"{name}_bss.o" in objs else "")
    lcf = OUT / f"{name}.lcf"
    lcf.write_text(f"""// Generated by scripts/olink.py for {name}.bin -- do not edit.
//
// The overlay is loaded VERBATIM at 0x{LOAD:08X} INCLUDING its 0x40 MWo3
// header, so vram = load + file offset and .text starts at 0x{LOAD + HDR:08X}.
//
// mwld rejects slash-star comments; MEMORY needs the full
// `name (attrs) : ORIGIN = .., LENGTH = ..` form; a second output section into
// an already-allocated region needs `>>`; and symbol assignments must sit
// INSIDE a section body or mwld silently ignores them.
MEMORY
{{
    ovl (RWX) : ORIGIN = 0x{LOAD + HDR:08X}, LENGTH = 0
}}

SECTIONS
{{
    .text :
    {{
        ALIGNALL(1);
{textlines}
    }} > ovl

    .data :
    {{
        // No _gp: mwld IGNORES an lcf _gp for an overlay, and the overlay
        // config disassembles gp-relative operands as literal offsets, so
        // nothing asks the linker to compute one.
        *(.data)
        *(.rodata)
        *(.rdata)
        *(.sdata)
    }} >> ovl

    .bss :
    {{
{bssline}        *(.bss)
        *(.sbss)
        *(.scommon)
        *(SCOMMON)
        *(.common)
        *(COMMON)

{body}
    }} >> ovl
}}
""", encoding="ascii")
    return lcf


def ctor_dtor(data: bytes, data_vram: int, end: int):
    """ctor table = the maximal run of words at the END of .data that are
    addresses inside the loaded overlay, ignoring trailing zeros; the dtor
    pointer is immediately after it.  DERIVED, and validated 5/5 against the
    non-trivial overlays before being used.
    """
    words = [(i, int.from_bytes(data[i:i + 4], "little"))
             for i in range(0, len(data) - 3, 4)]
    i = len(words) - 1
    while i >= 0 and words[i][1] == 0:
        i -= 1
    stop = i + 1
    while i >= 0 and LOAD <= words[i][1] < end:
        i -= 1
    start = i + 1
    if start >= stop:
        return end, end
    return data_vram + words[start][0], data_vram + words[stop - 1][0] + 4


def emit(name: str) -> int:
    """Header fields come from the LINKED OUTPUT, never from retail's header,
    so a byte match is a real check and not a tautology.

    Read the sizes off the PROGRAM headers: mwld writes the bss section header
    as PROGBITS size 0 while its LOAD segment correctly says filesz 0.
    """
    elf = (OUT / f"{name}.elf").read_bytes()
    phoff, = struct.unpack_from("<I", elf, 28)
    phentsize, phnum = struct.unpack_from("<HH", elf, 42)
    loads = []
    for i in range(phnum):
        typ, off, vaddr, paddr, filesz, memsz, flags, align = struct.unpack_from(
            "<IIIIIIII", elf, phoff + i * phentsize)
        if typ == 1:
            loads.append((vaddr, off, filesz, memsz))
    loads.sort()
    if not loads:
        print(f"{name}: linked ELF has no LOAD segments")
        return 1
    text = data = b""
    bss = 0
    for n, (vaddr, off, filesz, memsz) in enumerate(loads):
        bss += memsz - filesz
        if filesz == 0:
            continue
        if n == 0:
            text = elf[off:off + filesz]
        else:
            data += elf[off:off + filesz]
    body = text + data
    end = LOAD + HDR + len(body)
    ctor, dtor = ctor_dtor(data, LOAD + HDR + len(text), end)
    hdr = struct.pack("<4sIIIIIII", b"MWo3", IDS[name], LOAD,
                      len(text), len(data), bss, ctor, dtor)
    hdr += name.encode() + b".bin"
    hdr = hdr.ljust(HDR, bytes(1))
    out = OUT / f"{name.upper()}.BIN"
    out.write_bytes(hdr + body)

    ref = (REF_BIN / f"{name.upper()}.BIN").read_bytes()
    ours = out.read_bytes()
    ok = ref == ours
    print(f"{name.upper()}.BIN : {'BYTE-IDENTICAL' if ok else 'DIFFERS'} "
          f"({len(ours)} bytes vs retail {len(ref)}; "
          f"text 0x{len(text):X} data 0x{len(data):X} bss 0x{bss:X})")
    if not ok:
        n = min(len(ref), len(ours))
        d = [i for i in range(n) if ref[i] != ours[i]]
        print(f"   {len(d)} differing bytes"
              f"{', first at 0x%X' % d[0] if d else ''}"
              f"{'' if len(ref) == len(ours) else '  LENGTH DIFFERS'}")
        for i in d[:8]:
            print(f"     0x{i:04X}: retail {ref[i]:02X}  ours {ours[i]:02X}  "
                  f"(vram 0x{LOAD + i:08X})")
    return 0 if ok else 1


def build(name: str, syms: list, control: bool) -> int:
    OUT.mkdir(parents=True, exist_ok=True)
    src = otextsplit.text_path(name)
    if not src.exists():
        print(f"{name}: no asm/overlays/{name}/{name}.s -- viewer and launcher "
              f"are 48 nops and have no split to make")
        return 1
    entry = None
    for line in src.read_text(errors="replace").splitlines():
        if line.startswith("glabel "):
            entry = line.split()[1].strip()
            break
    if entry is None:
        print(f"{name}: no glabel in {src.name}")
        return 1

    if syms:
        order = otextsplit.split(name, syms, PARTS, cunit_slots=not control)
    else:
        order = [(f"{name}_text", "asm")]

    text_objs = []
    table = otextsplit.symbol_table(name)
    # The length guard must compare against the slot, not against the recorded
    # size: on title 74 of 107 `size:` attributes swallow trailing padding, so
    # a CORRECT compile would read as the wrong length. See otextsplit.real_size.
    _, _, words = otextsplit.load_text(name)
    for tag, kind in order:
        if kind == "asm":
            p = (src if tag == f"{name}_text" else PARTS / f"{tag}.s")
            if not assemble(tag, p):
                return 1
        else:
            o = OBJ / f"{tag}.o"
            if not o.exists():
                print(f"olink: no compiled object for {tag}; run "
                      f"scripts/sandbox_build.py --tag nm {tag}")
                return 1
            # Resolve mwcc's `.lit4` float pool against retail's, exactly as
            # t_olink.py/i_olink.py do. Without it the lwc1 gp displacement
            # links as a ZERO offset -- a wrong image that still links. No-op
            # without `.lit4`, idempotent if already patched.
            st, _, _ = t_lit4.patch(name, tag, LIT4_WORDS, objdir=OBJ)
            if st not in ("ok", "already", "no .lit4"):
                print(f"olink: {tag}: t_lit4 {st}")
                return 1
            vram, want = table[tag]
            want = otextsplit.real_size(vram, want, words)
            got = obj_text_size(o)
            if got != want:
                print(f"olink: {tag} compiles to 0x{got:X} bytes, retail's is "
                      f"0x{want:X} -- a wrong-length slot shifts every byte "
                      f"after it")
                return 1
            # A compiled `switch` brings its own jump table in .rodata, which
            # the lcf would collect into .data on top of the one the overlay's
            # own data assembly already carries -- so the overlay would hold the
            # table TWICE and every byte after it would shift.  n_jtbl moves the
            # two immediates onto retail's table and empties the section; it is
            # a no-op for an object without one.  See scripts/n_jtbl.py.
            blob, tables = n_jtbl.retarget(o.read_bytes(), vram, name)
            for _, addr, n in tables:
                print(f"   {tag}: {n}-entry jump table -> retail's "
                      f"jtbl_{addr:08X}")
            # A local array with a brace initialiser brings mwcc's own
            # TEMPLATE in the object's .data, and the lcf would collect it on
            # top of the copy the overlay's data assembly already carries --
            # the same double-placement the jump table has.  n_data moves the
            # lui/addiu pair onto retail's copy and empties the section; it is
            # a no-op for an object without one.  See scripts/n_data.py.
            blob, templates = n_data.retarget(blob, vram, name)
            for _, addr, n in templates:
                print(f"   {tag}: {n}-byte array template -> retail's "
                      f"D_{addr:08X}")
            (OUT / f"{tag}.o").write_bytes(relax_text_align(blob, vram))
        text_objs.append(f"{tag}.o")

    objs = list(text_objs)
    for tag, p in tail_units(name):
        if not assemble(tag, p):
            return 1
        objs.append(f"{tag}.o")

    if write_lcf(name, text_objs, objs) is None:
        return 1

    # Delete the previous ELF first: a failed link otherwise leaves the old one
    # in place and emit() scores THAT.
    (OUT / f"{name}.elf").unlink(missing_ok=True)
    sh(SSH + [HOST, f"rm -rf {REMOTE} && mkdir -p {REMOTE}"])
    # scp needs RELATIVE posix paths -- a "B:\..." argument is parsed as a
    # remote spec and lands on the host named with the Windows path.
    rel = [f"build/overlay-c-nm/{o}" for o in objs] + [f"build/overlay-c-nm/{name}.lcf"]
    # +-- WINDOWS COMMAND-LINE LIMIT (WinError 206), hit at 460 compiled units. --+
    # Both the local `scp` argv AND the single ssh argument carrying the remote
    # `ld` line blow past 32,767 chars once the object list is long enough.  At
    # 195 units this script worked; at 460 it did not, and the failure looks
    # like a link error rather than a length one.  So: scp in CHUNKS, and pass
    # the object list to the remote ld through a FILE.
    # +-- ORDER IS SLOT ORDER.  `$(cat objs.txt)` preserves it; a remote glob --+
    # would sort and silently relocate every function.  Never use a glob here.
    CHUNK = 60
    for i in range(0, len(rel), CHUNK):
        sh(SCP + rel[i:i + CHUNK] + [f"{HOST}:{REMOTE}/"])
    (OUT / "objs.txt").write_bytes(
        (chr(10).join(objs) + chr(10)).encode("utf-8"))
    sh(SCP + [f"build/overlay-c-nm/objs.txt", f"{HOST}:{REMOTE}/"])
    r = sh(SSH + [HOST, f"cd {REMOTE} && ../wibo {LD} {' '.join(LD_FLAGS)} "
                        f"-m {entry} -o {name}.elf {name}.lcf "
                        f"$(cat objs.txt)"],
           capture_output=True, text=True)
    if r.stdout.strip():
        print(r.stdout.strip())
    if r.stderr.strip():
        print(r.stderr.strip())
    sh(SCP + [f"{HOST}:{REMOTE}/{name}.elf", "build/overlay-c-nm/"])
    if not (OUT / f"{name}.elf").exists():
        print(f"{name}: link produced no ELF")
        return 1
    return emit(name)


def main() -> int:
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    control = "--control" in sys.argv
    noc = "--no-c" in sys.argv
    if not args:
        print(__doc__)
        return 2
    rc = 0
    for n in args:
        syms = [] if noc else cunits(n)
        arm = "no-c" if noc or not syms else ("control" if control else "C")
        print(f"== {n} [{arm}] {len(syms)} unit(s)")
        rc |= build(n, syms, control)
    return rc


raise SystemExit(main())

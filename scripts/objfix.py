#!/usr/bin/env python3
"""objfix.py -- object post-processing between the host compile and the link.

    objfix.py SYMBOL OBJ [gcc29|mwcc]     fix one object in place (hostbuild calls apply())

Two jobs, both measured on the objects they apply to (2026-09-30):

1. gcc29 objects (config/toolchain.txt).  Sony `as` emits the same zero-size
   .text/.data/.bss that gasfixup.py drops for GNU as (mwld refuses them), and
   hostbuild compiles gcc TUs with `-ffunction-sections`, so every function sits
   in `.text.<name>`.  Those sections are renamed back to `.text`: link.py then
   sums them for the host exactly like mwcc's one-`.text`-per-function output,
   and hosted.rename_guest() carves each guest out by its FUNC symbol.

2. config/objfix.txt `redirect` rows:  <symbol> redirect <section> <D_symbol>
   The object's <section> is retail DATA that asm/data already carries at
   <D_symbol> -- e.g. mwcc's anonymous local-initializer object `@N` that
   `-sdatathreshold 16` puts in .sdata.  Every relocation against a symbol
   defined in <section> is retargeted to an undefined global <D_symbol>, then
   the section (and those symbols) is removed, so the object carries no data
   of its own and nothing lands in the lcf's trailing `*(.sdata)` wildcard.
   Only a symbol at offset 0 of the section is accepted: the REL addend lives
   in the instruction and is left untouched.

3. `redirect_each` rows:  <symbol> redirect_each <section> <D_1> <D_2> ...
   Every relocation against ANY <section> symbol, taken in .text offset order,
   gets its OWN target (i-th reloc -> D_i), then all <section> sections are
   dropped.  For retail literal pools that give each load its own word even
   when values repeat (HeadLookUpdate_1c5460/XformRecUpdateMaybe_1c5ee0: -pi twice), which a section
   redirect cannot split.  Ported from build/s88m/1c5/tools/litscore.py (s88m).

4. `drop` rows:  <symbol> drop <section>
   Removes <section> (and .rel<section>) outright.  For mwcc C++ exception
   tables (.exceptix/.exception) that retail does not carry: the throw()-spec
   handler code is in retail .text, but no table points at it (libdeasm 100840).

5. `rename` rows:  <symbol> rename <old_sym> <new_sym>
   objcopy --redefine-sym old=new, defined or undefined.  For a real C++
   member function whose mangled name must become the retail FUN_ unit symbol
   (e.g. __ct__13basic_istreamFPv -> IstreamCtor_103f50), and for compiler-referenced
   vtables/methods that become retail D_/FUN_ symbols (libdeasm 103f50).

6. `dropfn` rows:  <symbol> dropfn <defined_sym>
   Removes the one .text section that DEFINES <defined_sym>, with its .rel.text
   and its .mwcats/.rel.mwcats, although other sections share those names (mwcc
   emits one .text per function).  The sections get a unique name (sh_name+1,
   ".text" -> "text") and are removed in the same objcopy call as every `drop`
   row, so a vtable that points at the function can go with it.  For a C++ key
   function written only to make mwcc emit its class's vtable + virtual-base
   this-adjustor thunks (libdeasm 1067f0).

7. `globalize` rows:  <symbol> globalize <sym>
   objcopy --globalize-symbol, after the renames: mwcc emits thunks
   (@8@72@__dt__...) as LOCAL functions; the retail unit symbol is global.
"""
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OBJCOPY = __import__("rgd").binutil("objcopy")
RULES = ROOT / "config" / "objfix.txt"
SHT_SYMTAB, SHT_REL = 2, 9


def rules() -> dict:
    out = {}
    if RULES.exists():
        for ln in RULES.read_text().splitlines():
            f = ln.split("#")[0].split()
            if f:
                out.setdefault(f[0], []).append(f[1:])
    return out


def _shdrs(d):
    shoff, = struct.unpack_from("<I", d, 32)
    es, n, sx = struct.unpack_from("<HHH", d, 46)
    hs = [list(struct.unpack_from("<10I", d, shoff + i * es)) for i in range(n)]
    return shoff, es, hs, sx


def _name(d, hs, sx, off):
    base = hs[sx][4]
    return d[base + off:d.index(b"\0", base + off)].decode()


def objcopy(path: Path, args: list) -> None:
    r = subprocess.run([str(OBJCOPY)] + args + [str(path), str(path)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(r.stderr.strip())


def gcc_fold(path: Path) -> None:
    d = path.read_bytes()
    shoff, es, hs, sx = _shdrs(d)
    drop = sorted({_name(d, hs, sx, h[0]) for h in hs
                   if _name(d, hs, sx, h[0]) in (".text", ".data", ".bss")
                   and h[5] == 0})
    if drop:
        objcopy(path, [f"--remove-section={s}" for s in drop])
    d = bytearray(path.read_bytes())
    shoff, es, hs, sx = _shdrs(d)
    so, ssz = hs[sx][4], hs[sx][5]
    blob = bytes(d[so:so + ssz]) + b".text\0"
    at = len(d)
    d += blob
    struct.pack_into("<II", d, shoff + sx * es + 16, at, len(blob))
    n = 0
    for i, h in enumerate(hs):
        if _name(d, hs, sx, h[0]).startswith(".text."):
            struct.pack_into("<I", d, shoff + i * es, ssz)
            n += 1
    if not n:
        raise RuntimeError("gcc object has no .text.<function> section")
    path.write_bytes(bytes(d))


# A `.lit4`/`.lit8` float literal is loaded through R_MIPS_LITERAL (8). Once it is
# redirected to a retail pool symbol it is an ordinary gp-relative load, so it is
# rewritten as R_MIPS_GPREL16 (7): same S+A-GP field, and the type bytecheck and
# mwld resolve against an external symbol (s88m: build/s64m/sdscore.py did 8 -> 7).
R_MIPS_GPREL16, R_MIPS_LITERAL = 7, 8


def _retype(info: int) -> int:
    t = info & 0xFF
    return R_MIPS_GPREL16 if t == R_MIPS_LITERAL else t


def redirect(path: Path, section: str, target: str) -> None:
    d = bytearray(path.read_bytes())
    shoff, es, hs, sx = _shdrs(d)
    sec = [i for i, h in enumerate(hs) if _name(d, hs, sx, h[0]) == section]
    if len(sec) != 1:
        raise RuntimeError(f"expected one {section} section, found {len(sec)}")
    sec = sec[0]
    st = [i for i, h in enumerate(hs) if h[1] == SHT_SYMTAB][0]
    so, ssz, strx = hs[st][4], hs[st][5], hs[st][6]
    stro, strsz = hs[strx][4], hs[strx][5]
    inside = []
    for k in range(ssz // 16):
        nm, val, size, info, other, shndx = struct.unpack_from("<IIIBBH", d, so + k * 16)
        if shndx == sec:
            if val != 0:
                raise RuntimeError(f"symbol #{k} at {section}+0x{val:X}; only offset 0 is supported")
            inside.append(k)
    # Append the undefined global target: new .strtab and .symtab copies at EOF.
    newstr = bytes(d[stro:stro + strsz]) + target.encode() + b"\0"
    str_at = len(d)
    d += newstr
    struct.pack_into("<II", d, shoff + strx * es + 16, str_at, len(newstr))
    newsym = bytes(d[so:so + ssz]) + struct.pack("<IIIBBH", strsz, 0, 0, 0x10, 0, 0)
    while len(d) % 4:
        d += b"\0"
    sym_at = len(d)
    d += newsym
    struct.pack_into("<II", d, shoff + st * es + 16, sym_at, len(newsym))
    tidx = ssz // 16
    moved = 0
    for h in hs:
        if h[1] != SHT_REL or h[6] != st:
            continue
        for off in range(h[4], h[4] + h[5], 8):
            r_off, info = struct.unpack_from("<II", d, off)
            if (info >> 8) in inside:
                struct.pack_into("<I", d, off + 4, (tidx << 8) | _retype(info))
                moved += 1
    if not moved:
        raise RuntimeError(f"no relocation references {section}")
    path.write_bytes(bytes(d))
    # objcopy rewrites the file cleanly: drops the section, its now-unreferenced
    # symbols, and the stale table copies left in the middle of the file.
    objcopy(path, [f"--remove-section={section}", f"--remove-section=.rel{section}"])


def redirect_multi(path: Path, section: str, targets: list) -> None:
    d = bytearray(path.read_bytes())
    shoff, es, hs, sx = _shdrs(d)
    secs = [i for i, h in enumerate(hs) if _name(d, hs, sx, h[0]) == section]
    if len(secs) != len(targets):
        raise RuntimeError(f"{len(secs)} {section} sections vs {len(targets)} targets")
    st = [i for i, h in enumerate(hs) if h[1] == SHT_SYMTAB][0]
    so, ssz, strx = hs[st][4], hs[st][5], hs[st][6]
    stro, strsz = hs[strx][4], hs[strx][5]
    inside = {}
    for k in range(ssz // 16):
        nm, val, size, info, other, shndx = struct.unpack_from("<IIIBBH", d, so + k * 16)
        if shndx in secs:
            if val != 0:
                raise RuntimeError(f"symbol #{k} at +0x{val:X}; only offset 0 is supported")
            inside[k] = secs.index(shndx)
    newstr = bytes(d[stro:stro + strsz])
    offs = []
    for t in targets:
        offs.append(len(newstr))
        newstr += t.encode() + b"\0"
    str_at = len(d)
    d += newstr
    struct.pack_into("<II", d, shoff + strx * es + 16, str_at, len(newstr))
    newsym = bytes(d[so:so + ssz])
    for o in offs:
        newsym += struct.pack("<IIIBBH", o, 0, 0, 0x10, 0, 0)
    while len(d) % 4:
        d += b"\0"
    sym_at = len(d)
    d += newsym
    struct.pack_into("<II", d, shoff + st * es + 16, sym_at, len(newsym))
    base = ssz // 16
    for h in hs:
        if h[1] != SHT_REL or h[6] != st:
            continue
        for off in range(h[4], h[4] + h[5], 8):
            r_off, info = struct.unpack_from("<II", d, off)
            if (info >> 8) in inside:
                struct.pack_into("<I", d, off + 4, ((base + inside[info >> 8]) << 8) | _retype(info))
    path.write_bytes(bytes(d))
    objcopy(path, [f"--remove-section={section}", f"--remove-section=.rel{section}"])


def redirect_each(path: Path, section: str, targets: list) -> None:
    d = bytearray(path.read_bytes())
    shoff, es, hs, sx = _shdrs(d)
    secs = {i for i, h in enumerate(hs) if _name(d, hs, sx, h[0]) == section}
    if not secs:
        raise RuntimeError(f"no {section} section")
    st = [i for i, h in enumerate(hs) if h[1] == SHT_SYMTAB][0]
    so, ssz, strx = hs[st][4], hs[st][5], hs[st][6]
    stro, strsz = hs[strx][4], hs[strx][5]
    inside = set()
    for k in range(ssz // 16):
        nm, val, size, info, other, shndx = struct.unpack_from("<IIIBBH", d, so + k * 16)
        if shndx in secs:
            if val != 0:
                raise RuntimeError(f"symbol #{k} at +0x{val:X}; only offset 0 is supported")
            inside.add(k)
    rel = []
    for h in hs:
        if h[1] != SHT_REL or h[6] != st:
            continue
        for off in range(h[4], h[4] + h[5], 8):
            r_off, info = struct.unpack_from("<II", d, off)
            if (info >> 8) in inside:
                rel.append((r_off, off, info))
    rel.sort()
    if len(rel) != len(targets):
        raise RuntimeError(f"{len(rel)} {section} relocs vs {len(targets)} targets")
    newstr = bytes(d[stro:stro + strsz])
    offs = []
    for t in targets:
        offs.append(len(newstr))
        newstr += t.encode() + b"\0"
    str_at = len(d)
    d += newstr
    struct.pack_into("<II", d, shoff + strx * es + 16, str_at, len(newstr))
    newsym = bytes(d[so:so + ssz])
    for o in offs:
        newsym += struct.pack("<IIIBBH", o, 0, 0, 0x10, 0, 0)
    while len(d) % 4:
        d += b"\0"
    sym_at = len(d)
    d += newsym
    struct.pack_into("<II", d, shoff + st * es + 16, sym_at, len(newsym))
    base = ssz // 16
    for i, (r_off, off, info) in enumerate(rel):
        struct.pack_into("<I", d, off + 4, ((base + i) << 8) | _retype(info))
    path.write_bytes(bytes(d))
    objcopy(path, [f"--remove-section={section}", f"--remove-section=.rel{section}"])


def _dropfn_names(path: Path, sym: str) -> list:
    """Rename the sections of the function defining `sym` to unique names; return them."""
    d = bytearray(path.read_bytes())
    shoff, es, hs, sx = _shdrs(d)
    st = next(h for h in hs if h[1] == SHT_SYMTAB)
    strb = hs[st[6]][4]
    idx = None
    for o in range(st[4], st[4] + st[5], 16):
        nm, val, size, info, oth, shn = struct.unpack_from("<IIIBBH", d, o)
        if d[strb + nm:d.index(b"\0", strb + nm)].decode() == sym and shn != 0:
            idx = shn
    if idx is None:
        raise RuntimeError(f"dropfn: {sym} not defined in {path}")
    secs = {idx} | {i for i, h in enumerate(hs) if
                    (h[1] == SHT_REL and h[7] == idx) or   # .rel.text: sh_info
                    (h[6] == idx and _name(d, hs, sx, h[0]) == ".mwcats")}  # sh_link
    secs |= {i for i, h in enumerate(hs) if h[1] == SHT_REL and h[7] in secs}
    out = []
    for i in sorted(secs):
        assert _name(d, hs, sx, hs[i][0]).startswith(".")
        hs[i][0] += 1
        struct.pack_into("<I", d, shoff + i * es, hs[i][0])
        out.append(_name(d, hs, sx, hs[i][0]))
    names = [_name(d, hs, sx, h[0]) for h in hs]
    for n in out:
        if names.count(n) != 1:
            raise RuntimeError(f"dropfn: section name {n!r} not unique in {path}")
    path.write_bytes(bytes(d))
    return out


def apply(symbol: str, path: Path, kind: str = "mwcc") -> None:
    if kind == "gcc29":
        gcc_fold(path)
    rs = rules().get(symbol, [])
    for r in rs:
        if r[0] not in ("redirect", "redirect_each", "drop", "rename", "dropfn", "globalize"):
            raise RuntimeError(f"unknown objfix action {r[0]!r}")
    rm = []
    for r in rs:
        if r[0] == "dropfn":
            rm += [f"--remove-section={n}" for n in _dropfn_names(path, r[1])]
    for r in rs:
        if r[0] == "drop":
            rm += [f"--remove-section={r[1]}", f"--remove-section=.rel{r[1]}"]
    if rm:
        objcopy(path, rm)
    ren = [f"--redefine-sym={r[1]}={r[2]}" for r in rs if r[0] == "rename"]
    if ren:
        objcopy(path, ren)
    glo = [f"--globalize-symbol={r[1]}" for r in rs if r[0] == "globalize"]
    if glo:
        objcopy(path, glo)
    for r in rs:
        if r[0] == "redirect_each":
            redirect_each(path, r[1], r[2:])
    rs = [r for r in rs if r[0] == "redirect"]
    # Several redirect rows for ONE section name = several same-named sections
    # (mwcc emits one .sdata per local-initializer object), mapped in section
    # order to the rows' targets.  A single row keeps the original path.
    bysec = {}
    for r in rs:
        bysec.setdefault(r[1], []).append(r[2])
    for sec, targets in bysec.items():
        if len(targets) == 1:
            redirect(path, sec, targets[0])
        else:
            redirect_multi(path, sec, targets)


if __name__ == "__main__":
    apply(sys.argv[1], Path(sys.argv[2]), sys.argv[3] if len(sys.argv) > 3 else "mwcc")

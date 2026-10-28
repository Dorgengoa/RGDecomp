#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Ingest stage `datareloc`: make MAIN's generated data C (data2c,
src/main_data/) link and run on the i686 host (docs/LINK.md "Data layer").

data2c writes every MAIN .data/.rodata/.sdata span as one C object
(`const u32 D_0044AF90[24] = {...}`), symbolising the pointer words it could
attribute (`(u32)&Sym`).  On i686 a pointer is 32 bits, so `(u32)&Sym` is a
link-time relocation and those words are already correct.  What is left:

1. **Raw address words.**  Words that still hold a numeric PS2 address:
   * arena words (0x004E9E80..0x00528200): overlay data/bss/function addresses
     (OVERLAY.md open issue 1, 190 at 2efa6b43).  A data address becomes its
     overlay's symbol + offset (`(u32)((u8 *)&factory_D_0050CF00 + 0x8)`: the
     nearest label at or below it among the names the overlay's C uses, else
     `<ov>_seg`, the data start; rule `arena-data`), valid for the arena manager
     (labels at retail offsets) and the native module table (labels in the
     overlay's own segment) alike: no arena pointer arithmetic.  NORMAL's and
     INSECT's data ranges overlap: such words are attributed by ARENA_DATA_OWNER
     (verified by content), any other ambiguous word is an error.  The arena end
     (retail `_end`, the heap start: D_004461F4, read only by the asm sbrk the
     port binds natively) becomes 0 (rule `arena-end`); an overlay function
     entry becomes the host function when exactly one overlay defines a
     function there (`<ov>_<name>`), else the import trampoline
     (`func_<ADDR>` / the address-style name the registry generates);
   * MAIN data words (0x00436980..0x004E9E80) pointing into a data object or
     MAIN bss: `(u32)((u8 *)&OBJ + off)`, e.g. D_0044AF90's raw string
     pointers 0x0045AD30.., the 0x00459D88-style string-table entries;
   * MAIN function entries (exact address of a C function), not inside a
     VU-microcode blob.
   Words in a non-u32 object (s16 pairs, f32 bit patterns: PLAN.md "addresses
   typed as floats") are relocated by re-emitting the WHOLE object as a u32
   array with the same bytes (same size; alignment >= the old one).  The
   object's type in other files is untouched (game code declares its own
   extern; C does not check data types across TUs).
2. **VU microcode blobs.** data2c symbolised words of VU microprograms that
   happen to equal a function address (`(u32)&IconStealthStep_202950` inside
   D_00441660).  In an object recognised as microcode (upper-NOP 0x000002FF /
   0x8000033C density), `(u32)&F` with F a MAIN function is reverted to the
   address number.
3. **MAIN bss = one block.**  `data2c_bss.c` (`u8 data2c_main_bss[0x68E00]`,
   0x00481080..0x004E9E80) is rewritten as a top-level-asm .bss block with a
   global label for EVERY MAIN-bss name the corpus uses (`D_004853D0`, ...)
   at its retail offset, so the named view and RG_MAIN_BSS_PTR (lifted overlay
   ctors) are the same bytes.
4. **Overlay reservations** (`data2c_ov<N>_bss.c`: `data2c_overlay_reserve_N`)
   are MAIN's empty LOAD segments for the overlays; the overlay arena
   (ovl_arena_gen.c) owns that memory, so they are emptied.
5. **Hardware addresses in data** (0x1000xxxx/0x1100xxxx/0x1200xxxx EE
   registers, 0x70000000 scratchpad) cannot be relocated at link time: they
   are reported (`hw-word`), not rewritten.

6. **Interior names** (`D_004803FC` inside data2c's D_00480390): a global
   asm equate `D_x = OBJ + off` in the object's file.
7. **Writable**: `const` is dropped from every definition (the game writes
   data2c-const objects, e.g. D_00449DD0).
8. **One contiguous image**: every object goes to COFF section
   `.data$rg<ADDR>` with the retail alignment (16/8 from its address); the
   linker orders grouped sections by suffix, so objects sit in retail order
   at retail relative offsets (needs /OPT:NOREF on the link).  Code that reads
   past an object into its neighbour (ctor table end = next object's address,
   8-byte views of 4-byte objects) then works.
9. **Gaps** between objects (bytes C units own, e.g. the static-init code at
   0x00469300) get a zero pad of the same size.
10. **Pointers printed as text**: data2c emitted some pointer words as
   `char D_x[4] = " FF\0"` (0x00464620); a byte-typed object's 4-aligned
   word that is a 4-aligned address inside a MAIN data object becomes a
   pointer (`bytes-ptr`; the object is re-emitted as u32[] with the same bytes).
Plus CODE_IN_DATA: data words pointing at MIPS code inside a data object
(MAIN's first two static ctors) are bound to their C ports in missing/.

Every decision is a row of DATARELOC.tsv (extra output).  Idempotent: a
rewritten file carries `/* rg:datareloc */`.
"""
from __future__ import annotations

import bisect
import re
import struct
import sys
from collections import defaultdict

MARK = b"/* rg:datareloc */"
ARENA_BASE = 0x004E9E80
ARENA_END = 0x00528200
MAIN_TEXT = (0x00100000, 0x00436980)
MAIN_DATA_LO = 0x00436980
MAIN_BSS = (0x00481080, 0x004E9E80)
OVL_TEXT = 0x004E9EC0
OVERLAY_DATA = {
    "title":   (0x004F1400, 0x004F1B80),
    "insmenu": (0x004F9780, 0x004FA300),
    "normal":  (0x00524D00, 0x00528200),
    "factory": (0x0050B480, 0x00510C00),
    "insect":  (0x00523B00, 0x00526080),
}
# MAIN data words whose value lies in BOTH NORMAL's and INSECT's data/bss range
# (0x00524D00..0x00526080), by word address -> owner.  Checked against the snapshot's
# overlay data listings (2026-10-25): D_004684C0 is the ResGroupCmdListDefine key ->
# list table (0x00525C80 = a NORMAL (id, ptr) list, INSECT has ctor code there;
# 0x00526020 = NORMAL's ThinkMenu cursor-callback table, INSECT's bss);
# D_00480390's words point at INSECT strings ("insect", "menu", "effect", two SJIS
# words; NORMAL has a short table / zeros there).
ARENA_DATA_OWNER = {
    0x0046850C: "normal", 0x00468524: "normal",
    0x00481000: "insect", 0x00481004: "insect", 0x00481008: "insect",
    0x00481020: "insect", 0x00481024: "insect",
}
OVL_LABEL_RE = re.compile(r"\b(title|insmenu|normal|factory|insect)_(?:D|jtbl)_([0-9A-Fa-f]{8})\b")
OVL_DATA_SYM = re.compile(r"^(title|insmenu|normal|factory|insect)_(?:D_|jtbl_|seg$)")
# names the overlay arena (ovl_arena_gen.c) defines; never defined by data
ARENA_ALIASES = {"D_00527020", "D_005273B8", "D_00528200", "data2c_overlay_load_base"}
HW_RANGES = ((0x10000000, 0x10010000), (0x11000000, 0x11010000),
             (0x12000000, 0x12002000), (0x70000000, 0x70004000))

OBJ_RE = re.compile(
    r"^(?P<const>const\s+)?(?P<type>u32|s32|f32|s16|u16|u8|s8|char)\s+(?P<name>\w+)"
    r"\[(?P<n>[^\]]*)\]\s*=\s*(?P<init>\{.*?\}|\".*?\")\s*;", re.S | re.M)
SIZE_RE = re.compile(r"sizeof\((\w+)\)\s*==\s*(\d+)")
ADDR_RE = re.compile(r"([0-9A-Fa-f]{8})(?:_e\d+)?$")
NAME_USE = re.compile(r"\bD_([0-9A-Fa-f]{8})\b")
SYM_TOK = re.compile(r"\(u32\)\s*&\s*(\w+)$")
# Rule `fn-number`: words data2c spelled as a MAIN function address that are
# really numbers (docs/UNBOUND-TRIAGE.md, P0 item 7 and P1): the flag bits
# 0x00100000 / 0x00200000 in the ActCfg name/flag tables, EvScript flags, the
# gaiji metrics, the menu panel layouts and NavCfg (`func_00200000` is not
# even an entry: it is the listing splitter's alabel inside a function), and
# the packed u16 pair (0x11, 0x08) in the main-menu layout D_00450480.
# symbol -> (number, only in this object or None = every object).
# Audit (out/bringup-checkpoint/fnword_audit.py, 2026-10-12): every other
# function word in a mostly-numeric object is a real callback (insect cage /
# menu layout callbacks, vtables), or dead SDK data (D_00446648, D_00447868).
NUMERIC_FN_WORDS = {
    "EntryPad_100000": (0x00100000, None),
    "func_00200000": (0x00200000, None),
    "MpegNextPictureMaybe_110008": (0x00110008, "D_00450480"),
}
# D_0047D130 really is the .text start (MainStaticInit_100580 /
# EhFindExceptionTableMaybe_102690 compare code addresses against it): it
# stays a relocation.
NUMERIC_FN_KEEP = {"D_0047D130"}
SYM_OFF_TOK = re.compile(r"\(u32\)\s*\(\s*\(\s*u8\s*\*\s*\)\s*&\s*(\w+)\s*\+\s*(0x[0-9A-Fa-f]+[uU]?|\d+[uU]?)\s*\)$")
# MIPS code that lives inside a MAIN data object and is CALLED (the first two
# static constructors of D_0046F9C0, MIPS words in D_00469140): the C port in
# missing/src/main/sys/MainSinit_469180.c; a data word pointing there becomes
# the host function (docs/LINK.md "Data layer")
CONST_DEF = re.compile(r"^const\s+((?:u32|s32|f32|s16|u16|u8|s8|char)\s+\w+\[[^\]]*\]\s*=)", re.M)
ALIGN_DEF = re.compile(r"^((?:u32|s32|f32|s16|u16|u8|s8|char)\s+(\w+)\[[^\]]*\])(\s*=)", re.M)
CODE_IN_DATA = {0x00469180: "MainSinit_469180", 0x00469190: "MainSinit_469190"}
ESC_RE = re.compile(r"\\([0-7]{1,3}|x[0-9A-Fa-f]+|.)", re.S)
SIMPLE_ESC = {"n": 10, "t": 9, "r": 13, "0": 0, "\\": 92, "'": 39, '"': 34, "a": 7,
              "b": 8, "f": 12, "v": 11, "?": 63}


def c_string_bytes(lit: str) -> bytes:
    out = bytearray()
    for part in re.findall(r'"((?:[^"\\]|\\.)*)"', lit, re.S):
        i = 0
        while i < len(part):
            c = part[i]
            if c != "\\":
                out += c.encode("utf-8")
                i += 1
                continue
            m = ESC_RE.match(part, i)
            e = m.group(1)
            if e[0] in "01234567":
                out.append(int(e, 8) & 0xFF)
            elif e[0] == "x":
                out.append(int(e[1:], 16) & 0xFF)
            else:
                out.append(SIMPLE_ESC.get(e, ord(e)))
            i = m.end()
    return bytes(out)


def is_hw(v: int) -> bool:
    return any(lo <= v < hi for lo, hi in HW_RANGES)


class Obj:
    __slots__ = ("name", "addr", "size", "ctype", "const", "rel", "words", "span",
                 "init", "count")

    def __init__(self, name, addr, size, ctype, const, rel):
        self.name, self.addr, self.size, self.ctype, self.const, self.rel = \
            name, addr, size, ctype, const, rel
        self.words = None          # list of int | str (symbolic, u32 objects)
        self.span = None
        self.init = None
        self.count = None


def parse_words(o: Obj, init: str):
    """The object's content as 4-byte words (int, or a symbolic token string for
    u32 objects).  None when not word-shaped."""
    t = o.ctype
    if t == "char":
        b = c_string_bytes(init)
        b = b + bytes(max(0, o.size - len(b)))
        return None, b[:o.size]
    body = init.strip()[1:-1]
    toks = [x.strip() for x in body.split(",")]
    toks = [x for x in toks if x]
    if t in ("u32", "s32"):
        words = []
        for x in toks:
            xs = x.rstrip("uUlL")
            if re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", xs):
                words.append(int(xs, 0) & 0xFFFFFFFF)
            else:
                words.append(x)
        return words, None
    if t == "f32":
        b = b"".join(struct.pack("<f", float(x.rstrip("fF"))) for x in toks)
    elif t in ("s16", "u16"):
        b = b"".join(struct.pack("<H", int(x.rstrip("uU"), 0) & 0xFFFF) for x in toks)
    elif t in ("u8", "s8"):
        b = bytes(int(x.rstrip("uU"), 0) & 0xFF for x in toks)
    else:
        return None, None
    b = b + bytes(max(0, o.size - len(b)))
    return None, b[:o.size]


def microcode_like(words) -> bool:
    if not words or len(words) < 16:
        return False
    nops = sum(1 for w in words if isinstance(w, int) and w in (0x000002FF, 0x8000033C))
    return nops * 8 >= len(words)


class DataRelocStage:
    """Whole-corpus stage over src/main_data/*.c (kind data)."""

    def __init__(self):
        self.errors: list[tuple[str, str]] = []
        self.stats: dict[str, int] = defaultdict(int)
        self.rows: list[tuple] = []
        self.addr_table: dict | None = None      # protos.snapshot_addr_table()
        self.ovl_funcs: dict[str, dict[int, str]] = {}   # ov -> addr -> C name
        self.objs: dict[str, Obj] = {}
        self.entries = None                      # ingest: relpath -> Entry
        self.plan: dict[str, str] = {}           # relpath -> new text

    # ------------------------------------------------------------ prepare
    def prepare(self, files: dict[str, bytes]):
        main_funcs = dict((self.addr_table or {}).get("main", {}))
        # only functions the corpus defines in C are relocation targets
        # (ingest hands the MANIFEST entries: symbols of kind `unit` files)
        defined_fn: set[str] = set()
        for e in (self.entries or {}).values():
            if e.kind == "unit":
                defined_fn.update(e.symbols)
        bss_uses: set[int] = set()
        data_uses: set[str] = set()
        for rel, data in files.items():
            if not rel.endswith((".c", ".cpp")):
                continue
            text = data.decode("utf-8", errors="replace")
            for m in NAME_USE.finditer(text):      # MAIN, overlay (gp) and data uses
                a = int(m.group(1), 16)
                if MAIN_BSS[0] <= a < MAIN_BSS[1]:
                    bss_uses.add(a)
                elif MAIN_DATA_LO <= a < MAIN_BSS[0]:
                    data_uses.add(m.group(0))
        self.main_fn = {a: n for a, n in main_funcs.items() if n in defined_fn}
        self.ovl_fn: dict[int, list[tuple[str, str]]] = defaultdict(list)
        for ov, tab in self.ovl_funcs.items():
            for a, n in tab.items():
                if n in defined_fn:
                    self.ovl_fn[a].append((ov, n))
        # entries the overlay C defines inside a symbols.txt function (Ghidra
        # missed them): `title_FUN_004eab00(..) {` in title_TitleSceneOverlay
        # ModeOn_4eaa40.c -- the title state table D_00454760 holds 0x004EAB00
        # (state 6) and 0x004E9FF0 (state 17) as raw words.  `_sub_` too (2026-10-25,
        # soak finding): `factory_sub_004EC7F0` in factory_FactoryRelated_4ec7e0.cpp is
        # the UI draw-callback table D_00468380's id 0x1A; left raw, the FACTORY Place
        # screen called host address 0x004EC7F0 (a MAIN function) and crashed
        def_rx = re.compile(r"\b((title|insmenu|normal|factory|insect)_(?:FUN|func|sub)_"
                            r"([0-9A-Fa-f]{8}))\s*\([^;{}()]*\)\s*\{")
        for rel, data in files.items():
            if not rel.startswith("src/overlays/") or not rel.endswith((".c", ".cpp")):
                continue
            for m in def_rx.finditer(data.decode("utf-8", errors="replace")):
                n, ov, a = m.group(1), m.group(2), int(m.group(3), 16)
                if ov in OVERLAY_DATA and OVL_TEXT <= a < OVERLAY_DATA[ov][0] \
                        and (ov, n) not in self.ovl_fn[a]:
                    self.ovl_fn[a].append((ov, n))
                    self.stats["ovl-c-entries"] += 1
        self.bss_uses = bss_uses
        self.data_named = {n for n in data_uses}
        # overlay data/bss labels the overlays' C names (the generator defines exactly
        # these, plus `<ov>_seg`): targets for arena data words
        self.ovl_labels: dict[str, list[int]] = {ov: [] for ov in OVERLAY_DATA}
        for rel, data in files.items():
            if not rel.startswith("src/overlays/") or not rel.endswith((".c", ".cpp")):
                continue
            for m in OVL_LABEL_RE.finditer(data.decode("utf-8", errors="replace")):
                ov, a = m.group(1), int(m.group(2), 16)
                lo, hi = OVERLAY_DATA[ov]
                if lo <= a < hi:
                    self.ovl_labels[ov].append(a)
        for ov in self.ovl_labels:
            self.ovl_labels[ov] = sorted(set(self.ovl_labels[ov]))
        # parse the data objects
        for rel, data in files.items():
            if not (rel.startswith("src/main_data/") and rel.endswith(".c")):
                continue
            text = data.decode("utf-8", errors="replace")
            sizes = dict((n, int(s)) for n, s in SIZE_RE.findall(text))
            for m in OBJ_RE.finditer(text):
                name = m.group("name")
                am = ADDR_RE.search(name)
                if not am:
                    self.errors.append((rel, f"{name}: no address in the name"))
                    continue
                o = Obj(name, int(am.group(1), 16), sizes.get(name, 0), m.group("type"),
                        bool(m.group("const")), rel)
                o.span = (m.start(), m.end())
                o.init = m.group("init")
                o.count = m.group("n")
                if not o.size:
                    self.errors.append((rel, f"{name}: no sizeof check"))
                    continue
                self.objs[name] = o
        self.by_addr = sorted((o.addr, o.size, o.name) for o in self.objs.values())
        self.addrs = [x[0] for x in self.by_addr]
        for rel in files:
            if rel.startswith("src/main_data/"):
                self._plan_file(rel, files[rel].decode("utf-8", errors="surrogateescape"))
        self._plan_aliases(files, data_uses)
        self._plan_pads(files)

    def _plan_pads(self, files):
        """9. Gaps.  data2c leaves the bytes it does not own (text-embedded
        code/data owned by C units, e.g. the static-init functions at
        0x00469300..) out of src/main_data; a zero pad of the gap's size in
        `.data$rg<gap>` keeps every later object at its retail offset."""
        for (a, sz, n), (b, _sz2, _m) in zip(self.by_addr, self.by_addr[1:]):
            end = a + sz
            if end >= b or end >= MAIN_BSS[0]:
                continue
            rel = self.objs[n].rel
            text = self.plan.get(rel)
            if text is None:
                text = MARK.decode() + "\n" + files[rel].decode("utf-8", errors="surrogateescape")
            text = (text.rstrip("\n") + "\n/* gap 0x%08X..0x%08X (datareloc: retail offsets) */\n"
                    "static unsigned char rg_pad_%08X[0x%X] __attribute__((section(\".data$rg%08X\"), used));\n"
                    % (end, b, end, b - end, end))
            self.plan[rel] = text
            self.rows.append(("gap-pad", f"0x{end:08X}", n, "-", f"0x{b - end:X} bytes"))
            self.stats["gap-pads"] += 1

    def _plan_aliases(self, files, data_uses):
        """6. Interior names.  data2c merged some objects into a larger one
        (or named the object data2c_fragment_/data2c_gap_), but game code
        still names an address inside it (`D_004803FC` in D_00480390): the
        object's file gets a global asm label `D_x = OBJ + off` (an assembler
        equate on a symbol of the same object file -> a COFF symbol in the
        object's section, no copy)."""
        by_rel: dict[str, list[tuple[str, str, int]]] = defaultdict(list)
        for n in sorted(data_uses):
            if n in self.objs or n in ARENA_ALIASES:
                continue
            a = int(n.split("_")[1], 16)
            i = bisect.bisect_right(self.addrs, a) - 1
            if i < 0:
                self.rows.append(("alias-unowned", f"0x{a:08X}", n, "-", "no data object"))
                self.stats["alias-unowned"] += 1
                continue
            oa, sz, on = self.by_addr[i]
            if not (oa <= a < oa + sz):
                self.rows.append(("alias-unowned", f"0x{a:08X}", n, "-", "no data object"))
                self.stats["alias-unowned"] += 1
                continue
            by_rel[self.objs[on].rel].append((n, on, a - oa))
            self.rows.append(("alias", f"0x{a:08X}", n, on, f"+0x{a - oa:X}"))
            self.stats["alias"] += 1
        for rel, al in by_rel.items():
            text = self.plan.get(rel)
            if text is None:
                text = files[rel].decode("utf-8", errors="surrogateescape")
                if MARK.decode() in text:
                    continue
                text = MARK.decode() + "\n" + text
            lines = ["", "/* interior names (datareloc stage, docs/LINK.md) */",
                     "#if defined(_WIN32) && defined(__i386__)",
                     "#define RG_DR_ASYM(s) \"_\" #s",
                     "#else",
                     "#define RG_DR_ASYM(s) #s",
                     "#endif",
                     "__asm__("]
            for n, on, off in al:
                lines.append(f"    \".globl \" RG_DR_ASYM({n}) \"\\n\" "
                             f"RG_DR_ASYM({n}) \" = \" RG_DR_ASYM({on}) \" + 0x{off:X}\\n\"")
            lines.append(");")
            self.plan[rel] = text.rstrip("\n") + "\n" + "\n".join(lines) + "\n"

    # ------------------------------------------------------------ targets
    def data_target(self, v: int):
        """(object name, offset) for a MAIN data address, bss -> data2c_main_bss."""
        if MAIN_BSS[0] <= v < MAIN_BSS[1]:
            return "data2c_main_bss", v - MAIN_BSS[0]
        i = bisect.bisect_right(self.addrs, v) - 1
        if i >= 0:
            a, sz, n = self.by_addr[i]
            if a <= v < a + sz:
                return n, v - a
            if v == a + sz:                     # one past the end
                return n, v - a
        return None

    SHORT_PTR_MAX_OFF = 0x40

    def short_main_symbol(self, v: int):
        """(name, off) when v is a 4-aligned address in MAIN data/bss that lies
        INSIDE a symbol the corpus names (offset > 0: a bss label within
        SHORT_PTR_MAX_OFF bytes below it, or a named data object), the proposal
        of BRINGUP.md 2026-10-18 (d).  Used only for words of s16/u16-typed
        objects (rule `short-main-ptr`).  Exact symbol starts are NOT taken:
        the census (`short-main-candidate` rows) has one, D_0047EAC8's
        (0, 24, 48, 72, ...) short table reading as 0x00480030 = D_00480030."""
        if v % 4:
            return None
        if MAIN_BSS[0] <= v < MAIN_BSS[1]:
            if not hasattr(self, "_bss_sorted"):
                self._bss_sorted = sorted(self.bss_uses)
            i = bisect.bisect_right(self._bss_sorted, v) - 1
            if i >= 0 and 0 < v - self._bss_sorted[i] <= self.SHORT_PTR_MAX_OFF:
                return f"D_{self._bss_sorted[i]:08X}", v - self._bss_sorted[i]
            return None
        t = self.data_target(v)
        if t and t[0] != "data2c_main_bss" and t[0] in self.data_named and t[1] > 0:
            return t
        return None

    def classify(self, o: Obj, idx: int, v: int, micro: bool):
        """-> (expr, rule) or (None, rule-or-None)."""
        if ARENA_BASE <= v <= ARENA_END:
            if v >= OVL_TEXT and v in self.ovl_fn:
                c = self.ovl_fn[v]
                text_owner = [(ov, n) for ov, n in c
                              if OVL_TEXT <= v < OVERLAY_DATA[ov][0]]
                if len(text_owner) == 1:
                    return f"(u32)&{text_owner[0][1]}", "arena-fn"
                return f"(u32)&func_{v:08X}", "arena-fn-import"
            in_data = v in (ARENA_BASE, ARENA_END) or any(
                lo <= v < hi for lo, hi in OVERLAY_DATA.values())
            if not in_data:
                return None, "arena-text-interior"
            if v % 4:
                # odd words in the overlay data range are ASCII ("IER\0")
                return None, "arena-unaligned"
            if v == ARENA_END:
                return "0x00000000u", "arena-end"
            if v == ARENA_BASE:
                return "(u32)&data2c_overlay_load_base", "arena-data"
            owners = [ov for ov, (lo, hi) in OVERLAY_DATA.items() if lo <= v < hi]
            where = o.addr + 4 * idx
            if len(owners) > 1:
                if where not in ARENA_DATA_OWNER:
                    self.errors.append((o.rel, f"0x{where:08X} = 0x{v:08X}: in {owners}' data; "
                                               "add it to ARENA_DATA_OWNER"))
                    return None, "arena-ambiguous"
                owners = [ARENA_DATA_OWNER[where]]
            ov = owners[0]
            labs = self.ovl_labels.get(ov, [])
            i = bisect.bisect_right(labs, v) - 1
            if i >= 0:
                n, off = f"{ov}_D_{labs[i]:08X}", v - labs[i]
            else:
                n, off = f"{ov}_seg", v - OVERLAY_DATA[ov][0]
            return (f"(u32)&{n}" if off == 0 else f"(u32)((u8 *)&{n} + 0x{off:X})"), "arena-data"
        if MAIN_DATA_LO <= v < MAIN_BSS[1]:
            t = self.data_target(v)
            if t is None:
                return None, "main-data-unowned"
            n, off = t
            tgt = self.objs.get(n)
            if off % 4 and n != "data2c_main_bss" and tgt is not None and                     tgt.ctype not in ("char", "u8", "s8") and not n.startswith("data2c_gap_"):
                return None, "main-data-unaligned"
            if off == 0 and n != "data2c_main_bss":
                return f"(u32)&{n}", "main-data"
            return f"(u32)((u8 *)&{n} + 0x{off:X})" if n != "data2c_main_bss" else \
                f"(u32)(data2c_main_bss + 0x{off:X})", \
                ("main-bss" if n == "data2c_main_bss" else "main-data-interior")
        if MAIN_TEXT[0] <= v < MAIN_TEXT[1] and v in self.main_fn and not micro:
            return f"(u32)&{self.main_fn[v]}", "main-fn"
        if is_hw(v):
            return None, "hw-word"
        return None, None

    # ------------------------------------------------------------ per file
    def _plan_file(self, rel: str, text: str):
        if MARK.decode() in text:
            return
        base = rel.rsplit("/", 1)[1]
        if base == "data2c_bss.c":
            self.plan[rel] = self._bss_block(text)
            return
        if re.fullmatch(r"data2c_ov\d_bss\.c", base):
            new = re.sub(r"^u8 (data2c_overlay_reserve_\d+)\[(0x[0-9A-Fa-f]+)\];",
                         r"/* \1[\2]: owned by the overlay arena (ovl_arena_gen.c) */",
                         text, flags=re.M)
            self.stats["ovl-reserve-dropped"] += 1
            self.plan[rel] = MARK.decode() + "\n" + new
            return
        objs = [o for o in self.objs.values() if o.rel == rel]
        if not objs:
            return
        edits = []
        for o in objs:
            words, raw = parse_words(o, o.init)
            if o.name in ARENA_ALIASES:
                self.errors.append((rel, f"{o.name} is defined by the overlay arena"))
            byte_obj = False
            if words is None and raw is not None:
                if o.addr % 4 or o.size % 4:
                    continue
                # byte-typed objects (char/u8/s8) are scanned too, but only
                # for pointers into MAIN data (below, rule `bytes-ptr`)
                byte_obj = o.ctype in ("char", "u8", "s8")
                words = list(struct.unpack(f"<{o.size // 4}I", raw))
            if words is None:
                continue
            micro = microcode_like(words)
            if micro:
                self.stats["microcode-objects"] += 1
                self.rows.append(("microcode", f"0x{o.addr:08X}", o.name, o.ctype, f"{o.size} bytes"))
            new_words = list(words)
            changed = False
            for i, w in enumerate(words):
                a = o.addr + 4 * i
                if isinstance(w, str):
                    m = SYM_TOK.match(w)
                    if (m and m.group(1) in NUMERIC_FN_WORDS and o.name not in NUMERIC_FN_KEEP
                            and NUMERIC_FN_WORDS[m.group(1)][1] in (None, o.name)):
                        num = NUMERIC_FN_WORDS[m.group(1)][0]
                        new_words[i] = f"0x{num:08X}u"
                        changed = True
                        self.stats["fn-number"] += 1
                        self.rows.append(("fn-number", f"0x{a:08X}", o.name, m.group(1),
                                          f"0x{num:08X}"))
                        continue
                    if m and micro:
                        s = m.group(1)
                        back = next((ad for ad, n in self.main_fn.items() if n == s), None)
                        if back is not None:
                            new_words[i] = f"0x{back:08X}u"
                            changed = True
                            self.stats["micro-unsym"] += 1
                            self.rows.append(("micro-unsym", f"0x{a:08X}", o.name, s,
                                              f"0x{back:08X}"))
                    m2 = SYM_OFF_TOK.match(w)
                    if m2 and m2.group(1) in self.objs:
                        t = self.objs[m2.group(1)].addr + int(m2.group(2).rstrip("uU"), 0)
                        if t in CODE_IN_DATA:
                            new_words[i] = f"(u32)&{CODE_IN_DATA[t]}"
                            changed = True
                            self.stats["code-in-data"] += 1
                            self.rows.append(("code-in-data", f"0x{a:08X}", o.name, w,
                                              CODE_IN_DATA[t]))
                    continue
                if w in CODE_IN_DATA:
                    new_words[i] = f"(u32)&{CODE_IN_DATA[w]}"
                    changed = True
                    self.stats["code-in-data"] += 1
                    self.rows.append(("code-in-data", f"0x{a:08X}", o.name, f"0x{w:08X}",
                                      CODE_IN_DATA[w]))
                    continue
                if byte_obj:
                    # 10. Pointers data2c printed as strings: a word whose bytes
                    # look like text (" FF\0" = 0x00464620) but is a 4-aligned
                    # address inside a MAIN .data/.rodata object (D_00480010:
                    # DataTable file-name pointers into D_004644F0, read by
                    # DataTableDefaultParam_417330 through D_00483DB8;
                    # D_00454710, D_00453E50, typeinfo func_00455BC0).  Real
                    # text words (" END", "IMG", "EFF", "NaN") are odd, point
                    # off a word boundary, or into bss: they stay.
                    t = self.data_target(w) if MAIN_DATA_LO <= w < MAIN_BSS[0] else None
                    if t is None or t[0] == "data2c_main_bss" or t[1] % 4 or micro:
                        continue
                    n, off = t
                    expr = f"(u32)&{n}" if off == 0 else f"(u32)((u8 *)&{n} + 0x{off:X})"
                    self.stats["bytes-ptr"] += 1
                    self.rows.append(("bytes-ptr", f"0x{a:08X}", o.name, o.ctype,
                                      f"0x{w:08X} -> {expr}"))
                    new_words[i] = expr
                    changed = True
                    continue
                expr, rule = self.classify(o, i, w, micro)
                if rule is None:
                    continue
                if o.ctype in ("s16", "u16") and not rule.startswith("arena"):
                    # pairs of shorts that merely fall in a MAIN range
                    # ((64, 64) = 0x00400040): only arena words are taken,
                    # plus (rule `short-main-ptr`) a 4-aligned word inside a
                    # MAIN symbol the corpus names (bss label / data object):
                    # D_004807F8 = 0x00484A38 = D_00484A30 + 8, the FACTORY
                    # menu's Slot pointer (BRINGUP.md 2026-10-18 (d))
                    sym = self.short_main_symbol(w) if expr is not None and not micro else None
                    self.rows.append(("short-main-candidate", f"0x{a:08X}", o.name, o.ctype,
                                      f"0x{w:08X} " + (f"in {sym[0]}+0x{sym[1]:X}" if sym else
                                                       "no named symbol")))
                    if sym is None:
                        continue
                    rule = "short-main-ptr"
                # f32-typed words in a MAIN/arena range are denormal floats
                # (< 7.2e-39): real game constants never are, they are the
                # addresses data2c mis-typed (PLAN hazard; D_0047E010 = the
                # two language path strings CdDatArchiveOpen_183110 strcats)
                if o.ctype == "f32" and rule not in ("main-fn", "main-data", "arena-fn",
                                                     "arena-fn-import", "arena-data",
                                                     "main-data-interior", "main-bss"):
                    continue
                if micro and rule != "hw-word":
                    continue
                if expr is None:
                    self.stats[rule] += 1
                    self.rows.append((rule, f"0x{a:08X}", o.name, o.ctype, f"0x{w:08X}"))
                    continue
                self.stats[rule] += 1
                self.rows.append((rule, f"0x{a:08X}", o.name, o.ctype,
                                  f"0x{w:08X} -> {expr}"))
                new_words[i] = expr
                changed = True
            if not changed:
                continue
            body = ", ".join(w if isinstance(w, str) else f"0x{w:08X}u" for w in new_words)
            decl = (f"u32 {o.name}[{len(new_words)}] = {{\n"
                    f"    {body}\n}};")
            if o.ctype not in ("u32", "s32"):
                self.stats[f"retyped-{o.ctype}"] += 1
                self.rows.append(("retyped", f"0x{o.addr:08X}", o.name, o.ctype,
                                  f"u32[{len(new_words)}]"))
            edits.append((o.span, decl))
        # 7. writable: every PS2 page is RW and the game writes some data2c
        # `const` objects (VuMicrocodeTableInitMaybe_152830 fills D_00449DD0);
        # a const definition would land in .rdata and fault.
        # 8. one contiguous image: every object goes to the COFF grouped
        # section `.data$rg<ADDR>`; the linker concatenates grouped sections in
        # suffix order, so the objects sit in retail address order with retail
        # alignment (up to 16; code moves qwords = movaps through 16-aligned
        # PS2 objects) and no gaps (data2c covers every byte).  Code that reads
        # past one object into the next (an 8-byte NA view of the 4-byte
        # D_0047E010, a ctor table whose end is the next object's address)
        # sees the retail neighbour.
        out = text
        for (s, e), decl in sorted(edits, key=lambda x: x[0], reverse=True):
            out = out[:s] + decl + out[e:]
        out = CONST_DEF.sub(r"\1", out)
        if any(o.const for o in objs):
            self.stats["const-dropped-files"] += 1

        def align(m):
            am = ADDR_RE.search(m.group(2))
            a = int(am.group(1), 16) if am else 1
            al = 16 if a % 16 == 0 else 8 if a % 8 == 0 else 0
            attr = f" __attribute__((section(\".data$rg{a:08X}\")"
            attr += f", aligned({al})))" if al else "))"
            self.stats["sectioned"] += 1
            if al:
                self.stats[f"aligned-{al}"] += 1
            return f"{m.group(1)}{attr}{m.group(3)}"
        out = ALIGN_DEF.sub(align, out)
        edits = [(s, d) for s, d in edits if d is not None]
        if not edits:
            self.plan[rel] = MARK.decode() + "\n" + out
            return
        need = set(re.findall(r"&\s*(\w+)", "".join(d for _, d in edits)))
        need |= {"data2c_overlay_load_base"} if "data2c_overlay_load_base" in out else set()
        ext = []
        for n in sorted(need):
            if re.search(rf"\b(?:extern\b[^;]*|^(?:const\s+)?\w+\s+){re.escape(n)}\b", out, re.M):
                continue
            if n in self.objs or n in ("data2c_main_bss", "data2c_overlay_load_base") \
                    or n.startswith(("data2c_", "D_", "jtbl_")) or OVL_DATA_SYM.match(n):
                ext.append(f"extern unsigned char {n}[];")
            else:
                ext.append(f"extern void {n}();")
        if "data2c_main_bss" in out and not re.search(r"extern\s+u8\s+data2c_main_bss", out):
            ext.append("extern unsigned char data2c_main_bss[];")
        ext = sorted(set(ext))
        hdr = MARK.decode() + "\n" + "\n".join(ext) + ("\n" if ext else "")
        self.plan[rel] = hdr + out

    def _bss_block(self, text: str) -> str:
        m = re.search(r"u8 data2c_main_bss\[(0x[0-9A-Fa-f]+)\];", text)
        size = int(m.group(1), 16) if m else MAIN_BSS[1] - MAIN_BSS[0]
        if MAIN_BSS[0] + size != MAIN_BSS[1]:
            self.errors.append(("src/main_data/data2c_bss.c", f"bss size 0x{size:X} != layout"))
        labels = sorted((a, f"D_{a:08X}") for a in self.bss_uses
                        if MAIN_BSS[0] <= a < MAIN_BSS[0] + size)
        # named MAIN bss symbols of config/main.symbols.txt (gEventContext,
        # gSystemVm: absolute in the decomp lcf)
        for a, n in sorted((self.addr_table or {}).get("main", {}).items()):
            if MAIN_BSS[0] <= a < MAIN_BSS[0] + size and not n.startswith(("D_", "func_", "FUN_")):
                labels.append((a, n))
                self.stats["bss-named-labels"] += 1
        labels.sort()
        self.stats["bss-labels"] = len(labels)
        lines = [MARK.decode(),
                 "/* MAIN .sbss/.bss 0x00481080..0x004E9E80 as ONE block (docs/LINK.md):",
                 " * data2c_main_bss plus a global label for every MAIN bss name the",
                 " * corpus uses, at its retail offset (datareloc stage). */",
                 "#include \"types.h\"",
                 "#if defined(_WIN32) && defined(__i386__)",
                 "#define RG_DR_SYM(s) \"_\" #s",
                 "#else",
                 "#define RG_DR_SYM(s) #s",
                 "#endif",
                 "__asm__(",
                 "    \".bss\\n\"",
                 "    \".p2align 7\\n\"",
                 "    \".globl \" RG_DR_SYM(data2c_main_bss) \"\\n\"",
                 "    RG_DR_SYM(data2c_main_bss) \":\\n\""]
        pos = MAIN_BSS[0]
        for a, name in labels:
            if a > pos:
                lines.append(f"    \".zero 0x{a - pos:X}\\n\"")
                pos = a
            lines.append(f"    \".globl \" RG_DR_SYM({name}) \"\\n\" RG_DR_SYM({name}) \":\\n\"")
        if MAIN_BSS[0] + size > pos:
            lines.append(f"    \".zero 0x{MAIN_BSS[0] + size - pos:X}\\n\"")
        lines.append("    \".text\\n\");")
        return "\n".join(lines) + "\n"

    # ------------------------------------------------------------ stage API
    def apply(self, relpath: str, data: bytes) -> tuple[bytes, int]:
        new = self.plan.get(relpath)
        if new is None:
            return data, 0
        return new.encode("utf-8", errors="surrogateescape"), 1

    __call__ = apply

    def extra_outputs(self) -> dict[str, bytes]:
        rows = ["rule\taddr\tobject\ttype\tdetail"]
        rows += ["\t".join(map(str, r)) for r in sorted(self.rows, key=lambda r: (r[0], r[1]))]
        return {"DATARELOC.tsv": ("\n".join(rows) + "\n").encode()}

    def report(self) -> str:
        out = [f"datareloc: {len(self.plan)} files rewritten, {len(self.errors)} errors; "
               + ", ".join(f"{k}={v}" for k, v in sorted(self.stats.items()))]
        out += [f"  ERROR {f}: {why}" for f, why in self.errors]
        return "\n".join(out)


def ovl_func_table(addr_of: dict) -> dict[str, dict[int, str]]:
    """{ov: {addr: name}} from ingest's (image, name) -> addr table."""
    out: dict[str, dict[int, str]] = defaultdict(dict)
    for (img, name), a in addr_of.items():
        if img in OVERLAY_DATA and OVL_TEXT <= a < OVERLAY_DATA[img][0]:
            out[img].setdefault(a, name)
    return out


if __name__ == "__main__":
    print(__doc__)
    sys.exit(0)

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Generate the overlay registry C for src/ps2/overlay (docs/OVERLAY.md).

    python tools/gen_overlay_registry.py --out build/ovl-gen
        [--game game] [--source ../RGDecomp --rev 2efa6b43]
        [--data2c ../RGDecomp@d784320c] [--bin data/BIN] [--check]

Inputs (read-only):
  * the pinned snapshot (git objects at --rev; default: game/SNAPSHOT.txt):
      config/<ov>.yaml           text/data split, bss size (when absent, as in the
                                 published decomp: from the overlay's data/bss listings)
      config/<ov>.symbols.txt    overlay function entries (+ sizes)
      config/main.symbols.txt    MAIN functions
      asm/overlays/<ov>/data/<ov>_data.data.s   overlay .data as words (when
                                 the overlay's data is still asm, as at 2efa6b43)
      asm/data/*.s, SCUS_974.90.lcf             MAIN data labels / absolutes
  * game/ (ingested): MANIFEST.tsv (defined symbols), include/port/game_protos.h
    (callee prototypes), the MAIN and overlay sources (which overlay-range
    names they use), and src/<ov>_data/*.c when overlay data is C (data2c).
  * optional: config/data2c.json (MAIN data pointer slots into overlays, d784320c)
  * optional: data/BIN/*.BIN -- ONLY to cross-check the derived MWo3 header
    fields and data words; nothing from the BINs is emitted.

Outputs (--out):
  ovl_registry_gen.c   descriptors, pristine .data images (relocated),
                       function/label maps, MAIN->overlay import table,
                       the import trampolines (RG_OVL_TRAMPOLINE)
  ovl_arena_gen.c      the shared arena block + every overlay data/bss label
                       and MAIN's aliases into it (top-level asm)
  ovl_ctors_gen.c      the 62 static-initializers lifted from MIPS (ovl_lift.py);
                       own / MAIN-bss addresses spelled `label + offset` (both managers)
  ovl_native_gen.c     the native module table (src/native/ovl): per-overlay data
                       segments with their labels, .data images, ctors, the import x
                       module table and trampolines -- no retail addresses
  OVERLAY_REGISTRY.tsv per-item census (imports, unbound refs, raw words)
  report on stdout; exit 1 on any error.

Compile ovl_registry_gen.c with -DRG_OVL_TABLE_ONLY for a registry that needs
no game symbols (pointers 0, raw retail words): tests/overlay uses it.
"""
from __future__ import annotations

import argparse
import bisect
import json
import re
import struct
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ovl_lift  # noqa: E402

PORT = Path(__file__).resolve().parent.parent
ARENA_BASE = 0x004E9E80
HDR = 0x40
# Loader index (OverlayLoad_1c3210 argument = column of D_0044AF90) and MWo3 id.
# D_0044AF90 rows: VIEWER LAUNCHER TITLE NORMAL FACTORY INSECT INSMENU
# (cdrom0:, cdrom1:, host0: variants).  MWo3 ids: viewer 1, title 2, insmenu 3,
# launcher 4, normal 5, factory 6, insect 7 (each .BIN's header).
OVERLAYS = [  # (name, loader index, MWo3 id)
    ("title", 2, 2),
    ("insmenu", 6, 3),
    ("normal", 3, 5),
    ("factory", 4, 6),
    ("insect", 5, 7),
]
STUBS = [("viewer", 0, 1), ("launcher", 1, 4)]   # 256-byte nop stubs, no data/bss
MAIN_BSS = (0x00481080, 0x004E9E80)
NAME_RE = re.compile(r"\b(D|jtbl)_([0-9A-Fa-f]{8})\b")
OVL_NAME_RE = re.compile(r"\b(?:(title|insmenu|normal|factory|insect)_)?(D|jtbl)_([0-9A-Fa-f]{8})\b")
FUNC_IMPORT_RE = re.compile(r"\b(?:func|FUN)_([0-9A-Fa-f]{6,8})\b")


class GenError(Exception):
    pass


# ------------------------------------------------------------------ sources
class Source:
    """Files of the pinned snapshot: git objects at rev (never the worktree)."""

    def __init__(self, repo: Path, rev: str):
        self.repo, self.rev = repo, rev
        self.cache: dict[str, str | None] = {}

    def read(self, path: str) -> str | None:
        if path not in self.cache:
            r = subprocess.run(["git", "-C", str(self.repo), "show", f"{self.rev}:{path}"],
                               capture_output=True)
            self.cache[path] = (r.stdout.decode("utf-8", errors="replace")
                                if r.returncode == 0 else None)
        return self.cache[path]

    def ls(self, prefix: str) -> list[str]:
        r = subprocess.run(["git", "-C", str(self.repo), "ls-tree", "-r", "--name-only",
                            self.rev, prefix], capture_output=True, text=True)
        return r.stdout.split() if r.returncode == 0 else []


def parse_symbols(text: str) -> dict[int, tuple[str, int, str]]:
    """symbols.txt -> {addr: (name, size, type)}."""
    out = {}
    for line in text.splitlines():
        m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$", line)
        if not m:
            continue
        rest = m.group(3)
        t = re.search(r"type:(\w+)", rest)
        s = re.search(r"size:(0x[0-9A-Fa-f]+)", rest)
        out[int(m.group(2), 16)] = (m.group(1), int(s.group(1), 16) if s else 0,
                                    t.group(1) if t else "")
    return out


def parse_yaml_layout(text: str):
    """(text_vram, data_file_off, bss_size) from config/<ov>.yaml."""
    code = re.search(r"type:\s*code\s*\n\s*start:\s*(0x[0-9A-Fa-f]+)\s*\n\s*vram:\s*(0x[0-9A-Fa-f]+)"
                     r"\s*\n\s*bss_size:\s*(0x[0-9A-Fa-f]+)", text)
    data = re.search(r"\{start:\s*(0x[0-9A-Fa-f]+),\s*type:\s*data", text)
    if not code or not data:
        raise GenError("yaml: code segment / data subsegment not found")
    start, vram, bss = (int(code.group(i), 16) for i in (1, 2, 3))
    if start != HDR or vram != ARENA_BASE + HDR:
        raise GenError(f"yaml: code segment start {start:#x} vram {vram:#x} (expected 0x40 / 0x4E9EC0)")
    return vram, int(data.group(1), 16), bss


def listing_layout(data_text: str, bss_text: str):
    """(text_vram, data_file_off, bss_size) without config/<ov>.yaml (the
    published decomp ships no splat yamls): the data subsegment's file offset
    and VRAM are the comment columns of the first line of
    asm/overlays/<ov>/data/<ov>_data.data.s, the bss size is the `.space` of
    <ov>_bss.s, and .text starts right after the MWo3 header.  Equal to the
    yaml values for all five overlays of 2efa6b43 / b09ccfa1."""
    m = re.search(r"/\*\s*([0-9A-Fa-f]{6})\s+([0-9A-Fa-f]{8})\s", data_text)
    b = re.search(r"\.space\s+(0x[0-9A-Fa-f]+)", bss_text or "")
    if not m or not b:
        raise GenError("listing layout: data offset / bss .space not found")
    off, vram = int(m.group(1), 16), int(m.group(2), 16)
    if vram != ARENA_BASE + off:
        raise GenError(f"listing layout: data vram {vram:#x} != arena + file offset {off:#x}")
    return ARENA_BASE + HDR, off, int(b.group(1), 16)


@dataclass
class DataWord:
    off: int          # byte offset in .data
    raw: int          # retail word
    sym: str | None   # symbol spimdisasm put in the .word, if any


def parse_data_asm(text: str, data_vram: int):
    """<ov>_data.data.s -> (words, labels{name: addr}).  Each line carries its
    VRAM and raw bytes in the comment column, so the raw word is exact even for
    symbolic `.word sym` and `.float` lines."""
    buf = bytearray()
    relocs: dict[int, str] = {}
    labels: dict[str, int] = {}
    pending: list[str] = []
    widths = {"word": 4, "float": 4, "short": 2, "byte": 1}
    for line in text.splitlines():
        m = re.match(r"\s*glabel\s+(\w+)", line)
        if m:
            pending.append(m.group(1))
            continue
        m = re.match(r"\s*/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*([0-9A-Fa-f]*)\s*\*/\s*"
                     r"\.(word|float|short|byte)\s+(\S+)", line)
        if not m:
            if re.match(r"\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s", line):
                raise GenError(f"data asm: unsupported line {line.strip()!r}")
            continue
        vram = int(m.group(2), 16)
        kind, arg = m.group(4), m.group(5)
        width = widths[kind]
        for p in pending:
            labels[p] = vram
        pending = []
        off = vram - data_vram
        if off != len(buf):
            raise GenError(f"data asm: gap/overlap at 0x{vram:08X}")
        if m.group(3):                         # raw bytes in the comment column
            raw = bytes.fromhex(m.group(3))
            if len(raw) != width:
                raise GenError(f"data asm: {kind} with {len(raw)} raw bytes at 0x{vram:08X}")
        elif re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", arg):
            raw = (int(arg, 0) & ((1 << (8 * width)) - 1)).to_bytes(width, "little")
        else:
            raise GenError(f"data asm: no raw bytes for {line.strip()!r}")
        if kind == "word" and not re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", arg):
            if not re.fullmatch(r"[A-Za-z_]\w*", arg) or off % 4:
                raise GenError(f"data asm: unsupported operand {arg!r} at 0x{vram:08X}")
            relocs[off] = arg
        buf += raw
    if len(buf) % 4:
        raise GenError(f"data asm: size 0x{len(buf):X} not a multiple of 4")
    words = [DataWord(o, struct.unpack_from("<I", buf, o)[0], relocs.get(o))
             for o in range(0, len(buf), 4)]
    return words, labels


def parse_lcf_absolutes(text: str) -> dict[str, int]:
    out = {}
    for m in re.finditer(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", text, re.M):
        out[m.group(1)] = int(m.group(2), 16)
    return out


# ------------------------------------------------------------------ model
@dataclass
class Ovl:
    name: str
    index: int
    oid: int
    text_vram: int = 0
    data_vram: int = 0
    text_size: int = 0
    data_size: int = 0
    bss_size: int = 0
    ctor_start: int = 0
    dtor_start: int = 0
    ctor_targets: list = field(default_factory=list)
    words: list = field(default_factory=list)
    data_labels: dict = field(default_factory=dict)      # glabels from the data asm
    funcs: dict = field(default_factory=dict)            # addr -> name (defined in game/)
    all_funcs: dict = field(default_factory=dict)        # addr -> (name, size) (symbols.txt)
    labels: dict = field(default_factory=dict)           # prefixed name -> addr (arena labels)
    c_objects: list = field(default_factory=list)        # data2c mode: (name, addr, size)
    data_mode: str = "asm"                               # asm | c

    @property
    def bss_vram(self):
        return self.data_vram + self.data_size

    @property
    def end(self):
        return self.bss_vram + self.bss_size

    def prefixed(self, name: str) -> str:
        return f"{self.name}_{name}"


class Gen:
    def __init__(self, a):
        self.a = a
        self.errors: list[str] = []
        self.notes: list[str] = []
        self.tsv: list[tuple] = []
        game = a.game
        snap = (game / "SNAPSHOT.txt").read_text(encoding="utf-8") if (game / "SNAPSHOT.txt").exists() else ""
        src = a.source or (re.search(r"^source\t(.+)$", snap, re.M) or [None, None])[1]
        rev = a.rev or (re.search(r"^rev\t(\w+)$", snap, re.M) or [None, None])[1]
        if not src or not rev:
            raise GenError("no --source/--rev and no game/SNAPSHOT.txt")
        self.src = Source(Path(src), rev)
        self.rev = rev
        self.manifest = []
        for ln in (game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]:
            r = ln.split("\t")
            if len(r) >= 5:
                self.manifest.append(r)
        self.defined = {}     # symbol -> (image, relpath, kind)
        for rel, _sha, image, kind, syms in self.manifest:
            if syms == "-":
                continue
            for s in syms.split(","):
                self.defined[s] = (image, rel, kind)
        protos_h = game / "include" / "port" / "game_protos.h"
        self.protos = ovl_lift.parse_protos(protos_h.read_text(encoding="utf-8")) if protos_h.exists() else {}

    def err(self, msg: str):
        self.errors.append(msg)

    def need(self, path: str) -> str:
        t = self.src.read(path)
        if t is None:
            raise GenError(f"{path} not found at {self.rev}")
        return t

    # ------------------------------------------------------------ loading
    def load(self):
        self.main_syms = parse_symbols(self.need("config/main.symbols.txt"))
        self.main_funcs = {a: n for a, (n, _s, t) in self.main_syms.items() if t == "func"}
        self.main_func_names = set(self.main_funcs.values())
        lcf = self.src.read("SCUS_974.90.lcf") or ""
        self.lcf_abs = parse_lcf_absolutes(lcf)
        # MAIN data labels (containing-object lookup): asm/data/*.s glabels with
        # sizes from the next label; data2c objects (src/main_data) when present.
        self.main_labels: list[tuple[int, str, int]] = []
        for p in self.src.ls("asm/data") + ["asm/main.s"]:     # .data/.sdata; .rodata in main.s
            if p.endswith(".s"):
                self._main_labels_from_asm(self.src.read(p) or "")
        for rel, _sha, image, kind, syms in self.manifest:
            if kind == "data" and image == "main" and rel.endswith(".c"):
                self._main_labels_from_data2c((self.a.game / rel).read_text(encoding="utf-8"))
        self.main_labels.sort()
        self.main_label_addrs = [x[0] for x in self.main_labels]
        self.ovls = [Ovl(n, i, d) for n, i, d in OVERLAYS]
        for o in self.ovls:
            self._load_ovl(o)
        self.arena_size = max(o.end for o in self.ovls) - ARENA_BASE

    def _main_labels_from_asm(self, text: str):
        labs = []
        for m in re.finditer(r"glabel\s+(D_\w+)\s*\n\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})", text):
            labs.append((int(m.group(2), 16), m.group(1)))
        last = 0
        for m in re.finditer(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*[0-9A-Fa-f]*\s*\*/\s*\.(word|float|short|byte)", text):
            w = {"word": 4, "float": 4, "short": 2, "byte": 1}[m.group(2)]
            last = max(last, int(m.group(1), 16) + w - 4)
        labs.sort()
        for i, (a, n) in enumerate(labs):
            end = labs[i + 1][0] if i + 1 < len(labs) else last + 4
            self.main_labels.append((a, n, end - a))

    def _main_labels_from_data2c(self, text: str):
        for m in re.finditer(r"sizeof\((D_([0-9A-Fa-f]{8}))\)\s*==\s*(\d+)", text):
            self.main_labels.append((int(m.group(2), 16), m.group(1), int(m.group(3))))

    def _load_ovl(self, o: Ovl):
        yaml = self.src.read(f"config/{o.name}.yaml")
        if yaml is not None:
            o.text_vram, data_off, o.bss_size = parse_yaml_layout(yaml)
        else:
            o.text_vram, data_off, o.bss_size = listing_layout(
                self.need(f"asm/overlays/{o.name}/data/{o.name}_data.data.s"),
                self.src.read(f"asm/overlays/{o.name}/{o.name}_bss.s") or "")
        o.data_vram = ARENA_BASE + data_off
        o.text_size = o.data_vram - o.text_vram
        syms = parse_symbols(self.need(f"config/{o.name}.symbols.txt"))
        for a, (n, s, t) in syms.items():
            if t == "func":
                o.all_funcs[a] = (n, s)
                d = self.defined.get(n)
                if d and d[0] == o.name and d[2] == "unit":
                    o.funcs[a] = n
        # entries the C defines inside a symbols.txt function (Ghidra missed
        # them: title_FUN_004eaa80 in title_TitleSceneOverlayModeOn_4eaa40.c, a
        # menu callback MAIN data calls through func_004EAA80)
        def_rx = re.compile(rf"\b({o.name}_(?:FUN|func)_([0-9A-Fa-f]{{8}}))\s*\([^;{{}}()]*\)\s*\{{")
        for rel, _s, image, kind, _y in self.manifest:
            if image != o.name or kind != "unit" or not rel.endswith((".c", ".cpp")):
                continue
            p = self.a.game / rel
            if not p.exists():
                continue
            for m in def_rx.finditer(p.read_text(encoding="utf-8", errors="replace")):
                n, a = m.group(1), int(m.group(2), 16)
                if a not in o.funcs and o.text_vram <= a < o.data_vram:
                    o.funcs[a] = n
                    o.all_funcs.setdefault(a, (n, 0))
                    self.defined.setdefault(n, (o.name, rel, "unit"))
                    self.notes.append(f"{o.name}: C entry {n} at {a:#x} (not in symbols.txt)")
        # overlay data as C (data2c, future) or as asm (2efa6b43)
        cdata = [(rel, kind) for rel, _s, image, kind, _y in self.manifest
                 if image == o.name and kind == "data" and rel.endswith(".c")]
        if cdata:
            o.data_mode = "c"
            for rel, _k in cdata:
                text = (self.a.game / rel).read_text(encoding="utf-8")
                for m in re.finditer(r"sizeof\((\w+?_?D_([0-9A-Fa-f]{8})|\w+)\)\s*==\s*(\d+)", text):
                    name = m.group(1)
                    am = re.search(r"([0-9A-Fa-f]{8})$", name)
                    if not am:
                        continue
                    o.c_objects.append((name, int(am.group(1), 16), int(m.group(3))))
            o.c_objects.sort(key=lambda x: x[1])
            if not o.c_objects:
                self.err(f"{o.name}: overlay data is C but no data2c size checks found")
            o.data_size = (max(a + s for _n, a, s in o.c_objects) - o.data_vram) if o.c_objects else 0
            self.notes.append(f"{o.name}: data is C ({len(o.c_objects)} objects) -- object mode")
            return
        text = self.need(f"asm/overlays/{o.name}/data/{o.name}_data.data.s")
        o.words, o.data_labels = parse_data_asm(text, o.data_vram)
        o.data_size = 4 * len(o.words)
        bss = self.src.read(f"asm/overlays/{o.name}/{o.name}_bss.s") or ""
        m = re.search(r"\.space\s+(0x[0-9A-Fa-f]+)", bss)
        if m and int(m.group(1), 16) != o.bss_size:
            self.err(f"{o.name}: bss .space {m.group(1)} != yaml bss_size {o.bss_size:#x}")
        image = b"".join(struct.pack("<I", w.raw) for w in o.words)
        o.ctor_start, o.dtor_start, o.ctor_targets = ovl_lift.ctor_table(
            image, o.data_vram, o.data_vram, o.end)
        o.image = image

    # ------------------------------------------------------------ checks
    def check_bins(self):
        if not self.a.bin:
            return
        for o in self.ovls:
            p = self.a.bin / f"{o.name.upper()}.BIN"
            if not p.exists():
                self.notes.append(f"{p.name}: not present, header cross-check skipped")
                continue
            b = p.read_bytes()
            magic, oid, load, ts, ds, bs, c0, c1 = struct.unpack_from("<4sIIIIIII", b, 0)
            name = b[0x20:0x30].split(b"\0")[0].decode()
            want = (b"MWo3", o.oid, ARENA_BASE, o.text_size, o.data_size, o.bss_size,
                    o.ctor_start, o.dtor_start, f"{o.name}.bin")
            got = (magic, oid, load, ts, ds, bs, c0, c1, name)
            if want != got:
                self.err(f"{p.name}: header {got} != derived {want}")
            if o.data_mode == "asm":
                d = b[HDR + o.text_size:HDR + o.text_size + o.data_size]
                if d != o.image:
                    self.err(f"{p.name}: .data bytes differ from the snapshot's data asm")
            self.tsv.append(("bin-check", o.name, p.name, "ok" if want == got else "MISMATCH", ""))

    # ------------------------------------------------------------ naming
    def ovl_at(self, a: int) -> list[Ovl]:
        return [o for o in self.ovls if o.data_vram <= a < o.end]

    def main_data_name(self, a: int):
        i = bisect.bisect_right(self.main_label_addrs, a) - 1
        if i >= 0:
            la, n, sz = self.main_labels[i]
            if la <= a < la + max(sz, 1):
                return n, a - la
        for n, v in self.lcf_abs.items():
            if v == a and n.startswith("D_"):
                return n, 0
        return None

    def exact_symbol(self, o: Ovl | None, v: int) -> str | None:
        """A symbol whose address is exactly v (pointer-candidate census)."""
        if v < 0x00100000 or v >= ARENA_BASE + self.arena_size:
            return None
        if v >= ARENA_BASE:
            for x in ([o] if o else self.ovls):
                if v in x.all_funcs:
                    return x.all_funcs[v][0]
                for n, a in x.labels.items():
                    if a == v:
                        return n
            return None
        if v in self.main_funcs:
            return self.main_funcs[v]
        i = bisect.bisect_left(self.main_label_addrs, v)
        if i < len(self.main_label_addrs) and self.main_label_addrs[i] == v:
            return self.main_labels[i][1]
        return None

    def census_main_data(self):
        """MAIN data words that hold a raw arena address (2efa6b43 asm data, or
        data2c C where pointer slots were not symbolized, e.g. .sdata typed s16)."""
        text = "\n".join(self.src.read(p) or "" for p in self.src.ls("asm/data") if p.endswith(".s"))
        buf = {}
        for m in re.finditer(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*([0-9A-Fa-f]*)\s*\*/\s*"
                             r"\.(word|short|byte)\s+(\S+)", text):
            a = int(m.group(1), 16)
            w = {"word": 4, "short": 2, "byte": 1}[m.group(3)]
            arg = m.group(4)
            if m.group(2):
                raw = bytes.fromhex(m.group(2))
            elif re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", arg):
                raw = (int(arg, 0) & ((1 << (8 * w)) - 1)).to_bytes(w, "little")
            else:
                continue          # a symbolic word: already a relocation
            for i, b in enumerate(raw):
                buf[a + i] = b
        n = 0
        for a in sorted(k for k in buf if k % 4 == 0):
            if all(a + i in buf for i in range(4)):
                v = int.from_bytes(bytes(buf[a + i] for i in range(4)), "little")
                if ARENA_BASE <= v < ARENA_BASE + self.arena_size:
                    owners = [f"{x.name}:{self.exact_symbol(x, v) or 'interior'}" for x in self.ovls
                              if x.text_vram <= v < x.end]
                    self.tsv.append(("main-raw-ovl-word", f"0x{a:08X}", f"0x{v:08X}",
                                     " ".join(owners) or "-", "MAIN data holds a raw arena address"))
                    n += 1
        self.notes.append(f"MAIN data words holding a raw arena address (asm data at the "
                          f"snapshot): {n} (OVERLAY_REGISTRY.tsv main-raw-ovl-word)")

    def collect_labels(self):
        """Arena labels per overlay: every data glabel, plus every overlay-range
        D_/jtbl_ the overlay's C uses (data or bss), all `<ov>_`-prefixed (the
        ovlsyms stage renames the uses)."""
        uses: dict[str, set[str]] = {o.name: set() for o in self.ovls}
        main_uses: dict[str, set[str]] = {}
        self.main_func_imports: dict[str, set[str]] = {}
        for rel, _sha, image, kind, _syms in self.manifest:
            if kind not in ("unit", "data") or not rel.endswith((".c", ".cpp")):
                continue
            if image not in uses and image != "main":
                continue
            text = (self.a.game / rel).read_text(encoding="utf-8", errors="replace")
            # game/ is staged: overlay files spell their own names
            # `<ov>_D_XXXXXXXX` (ovlsyms), which NAME_RE's \b does not see
            for m in OVL_NAME_RE.finditer(text):
                a = int(m.group(3), 16)
                if not (ARENA_BASE <= a < ARENA_BASE + 0x100000):
                    continue
                n = f"{m.group(2)}_{m.group(3)}"
                if image == "main":
                    if m.group(1) is None:
                        main_uses.setdefault(n, set()).add(rel)
                    elif m.group(1) in uses:
                        uses[m.group(1)].add(n)     # datareloc: MAIN data -> overlay label
                elif m.group(1) is None or m.group(1) == image:
                    uses[image].add(n)
            if image == "main":
                for m in FUNC_IMPORT_RE.finditer(text):
                    a = int(m.group(1), 16)
                    if ARENA_BASE <= a < ARENA_BASE + 0x100000 and m.group(0) not in self.defined:
                        self.main_func_imports.setdefault(m.group(0), set()).add(rel)
        for o in self.ovls:
            for n, a in o.data_labels.items():
                o.labels[o.prefixed(n)] = a
            for n in sorted(uses[o.name]):
                a = int(n.split("_")[1], 16)
                if o.data_vram <= a < o.end:
                    o.labels[o.prefixed(n)] = a
                elif a < o.data_vram:
                    self.err(f"{o.name}: C uses {n} inside its own text range")
                else:
                    self.err(f"{o.name}: C uses {n} beyond its bss end 0x{o.end:08X}")
            o.labels[o.prefixed("bss")] = o.bss_vram
            # the segment start: every own address has a label at or below it, so
            # generated code spells any own address as `label + offset` (no arena
            # pointer arithmetic; native module table and arena alike)
            o.labels[o.prefixed("seg")] = o.data_vram
        # MAIN names that point into the arena: must be covered by exactly one
        # overlay's data/bss (they alias the shared arena), or be the arena end.
        self.main_aliases: dict[str, int] = {}
        for n in sorted(main_uses):
            a = int(n.split("_")[1], 16)
            cov = self.ovl_at(a)
            if a == ARENA_BASE + self.arena_size:
                self.main_aliases[n] = a
                self.tsv.append(("main-alias", n, f"0x{a:08X}", "arena-end",
                                 ",".join(sorted(main_uses[n]))))
            elif len(cov) == 1:
                self.main_aliases[n] = a
                self.tsv.append(("main-alias", n, f"0x{a:08X}", cov[0].name,
                                 ",".join(sorted(main_uses[n]))))
            else:
                self.err(f"MAIN uses {n}: covered by {[o.name for o in cov]} (need exactly one)")

    def check_stage_table(self):
        sys.path.insert(0, str(PORT / "tools" / "stages"))
        try:
            import ovlsyms
        except ImportError:
            self.err("tools/stages/ovlsyms.py missing")
            return
        for o in self.ovls:
            want = (o.data_vram, o.end)
            got = ovlsyms.OVERLAY_DATA.get(o.name)
            if got != want:
                self.err(f"ovlsyms.OVERLAY_DATA[{o.name}] = {got} but the snapshot gives {want}")

    # ------------------------------------------------------------ imports
    def collect_imports(self):
        """MAIN -> overlay call targets: (a) func_XXXXXX names MAIN code calls
        (absolute in the decomp lcf), (b) data2c pointer slots (d784320c)."""
        self.imports: list[dict] = []
        for n in sorted(self.main_func_imports):
            a = int(FUNC_IMPORT_RE.match(n).group(1), 16)
            cands = [o.name for o in self.ovls if a in o.all_funcs]
            bound = [o.name for o in self.ovls if a in o.funcs]
            if n in self.lcf_abs and self.lcf_abs[n] != a:
                self.err(f"{n}: lcf says 0x{self.lcf_abs[n]:08X}")
            self.imports.append(dict(name=n, addr=a, domain=None, kind="call",
                                     cands=cands, bound=bound,
                                     files=sorted(self.main_func_imports[n])))
            if not bound:
                self.err(f"import {n}: 0x{a:08X} is not a defined function in any overlay")
        lcf_ovl = {n for n, v in self.lcf_abs.items()
                   if ARENA_BASE <= v < ARENA_BASE + self.arena_size and FUNC_IMPORT_RE.fullmatch(n)}
        missing = lcf_ovl - set(self.main_func_imports)
        if missing:
            self.notes.append(f"lcf overlay imports not referenced by game/ MAIN code: {sorted(missing)}")
        d2c = self.load_data2c()
        if d2c:
            slots: dict[str, list[str]] = {}
            for a, s in d2c["external_pointer_slots"].items():
                slots.setdefault(s, []).append(a)
            for n, v in sorted(d2c["external_symbols"].items()):
                dom = v.get("domain", "")
                a = int(v["address"], 16)
                if dom == "overlay_load_arena":
                    self.main_aliases.setdefault(n, a)
                    self.tsv.append(("main-alias", n, f"0x{a:08X}", "arena-base",
                                     " ".join(sorted(slots.get(n, [])))))
                    continue
                if not dom.startswith("overlay:"):
                    continue
                o = dom.split(":", 1)[1]
                oi = next(i for i, x in enumerate(self.ovls) if x.name == o)
                d = self.defined.get(n)
                if d and d[0] == o:
                    self.tsv.append(("data-slot", n, f"0x{a:08X}", o, "static: overlay defines the name"))
                    continue
                if a not in self.ovls[oi].funcs:
                    self.err(f"data2c {n}: 0x{a:08X} not a defined {o} function")
                self.imports.append(dict(name=n, addr=a, domain=oi, kind="slot",
                                         cands=[x.name for x in self.ovls if a in x.all_funcs],
                                         bound=[x.name for x in self.ovls if a in x.funcs],
                                         files=sorted(slots.get(n, []))))
        for im in self.imports:
            # the overlay definitions' prototypes at this address (MAIN declares
            # func_XXXXXX on its own; protos cannot see they are the same function)
            ps = {}
            for x in self.ovls:
                n = x.funcs.get(im["addr"])
                if n and n in self.protos:
                    ret, params = self.protos[n]
                    ps[x.name] = f"{ret}({', '.join(params) or 'void'})"
            if ps:
                self.tsv.append(("import-proto", im["name"], f"0x{im['addr']:08X}",
                                 "agree" if len(set(ps.values())) == 1 else "DISAGREE",
                                 "; ".join(f"{k}: {v}" for k, v in sorted(ps.items()))))
            self.tsv.append(("import", im["name"], f"0x{im['addr']:08X}", im["kind"],
                             f"domain={self.ovls[im['domain']].name if im['domain'] is not None else '-'}"
                             f" bound={','.join(im['bound']) or '-'} cands={','.join(im['cands']) or '-'}"
                             f" refs={len(im['files'])}"))

    def load_data2c(self):
        spec = self.a.data2c
        text = None
        if spec:
            repo, _, rev = spec.partition("@")
            text = Source(Path(repo), rev or "HEAD").read("config/data2c.json")
            if text is None:
                self.err(f"--data2c {spec}: config/data2c.json not found")
        else:
            text = self.src.read("config/data2c.json")
            if text is None:
                self.notes.append("no config/data2c.json at the snapshot: MAIN data pointer "
                                  "slots into overlays are not imported (pass --data2c)")
        return json.loads(text) if text else None

    # ------------------------------------------------------------ ctors
    def lift_ctors(self):
        self.ctors: dict[str, list[ovl_lift.Lifted]] = {}
        self.ctor_externs: dict[str, str] = {}
        for o in self.ovls:
            self.ctors[o.name] = []
            if o.data_mode != "asm":
                self.notes.append(f"{o.name}: object mode -- ctors must come from C (not lifted)")
                continue
            lab_by_addr = {}
            for n, a in o.labels.items():
                lab_by_addr.setdefault(a, n)

            def callee_name(t, o=o):
                if t in self.main_funcs:
                    return self.main_funcs[t]
                if t in o.funcs:
                    return o.funcs[t]
                return None

            def namer(v, is_addr, want, o=o, lab_by_addr=lab_by_addr):
                cls = ovl_lift._ptype_class(want)
                if not is_addr or v == 0 or not (0x00100000 <= v < 0x02000000):
                    return f"({want})0x{v:X}"
                if ARENA_BASE <= v < ARENA_BASE + self.arena_size:
                    if v in o.funcs:
                        self.ctor_externs[o.funcs[v]] = "void {}(void);"
                        return f"({want})&{o.funcs[v]}"
                    if not (o.data_vram <= v < o.end):
                        raise ovl_lift.LiftError(f"address 0x{v:08X} in {o.name}'s text, not a function")
                    lab, off = self.own_ref(o, v)
                    self.ctor_externs[lab] = "extern unsigned char {}[];"
                    return f"({want}){lab}" if off == 0 else f"({want})({lab} + 0x{off:X})"
                if v in self.main_funcs:
                    self.ctor_externs[self.main_funcs[v]] = "void {}(void);"
                    return f"({want})&{self.main_funcs[v]}"
                if MAIN_BSS[0] <= v < MAIN_BSS[1]:
                    for n, la in self.lcf_abs.items():
                        if la == v and n.startswith("D_"):
                            self.ctor_externs[n] = "extern unsigned char {}[];"
                            return f"({want}){n}"
                    # MAIN's .bss is one block (datareloc): symbol + offset
                    self.ctor_externs["data2c_main_bss"] = "extern unsigned char {}[];"
                    return f"({want})(data2c_main_bss + 0x{v - MAIN_BSS[0]:X})"
                nm = self.main_data_name(v)
                if nm:
                    n, off = nm
                    self.ctor_externs[n] = "extern unsigned char {}[];"
                    return f"({want}){n}" if off == 0 else f"({want})({n} + 0x{off:X})"
                raise ovl_lift.LiftError(f"address 0x{v:08X}: no MAIN symbol")

            lifter = ovl_lift.Lifter(o.image, o.data_vram, namer, callee_name, self.protos)
            for t in o.ctor_targets:
                cname = f"{o.name}_sinit_{t:08X}"
                try:
                    L = lifter.lift(t, cname)
                except ovl_lift.LiftError as e:
                    self.err(f"{o.name} ctor 0x{t:08X}: {e}")
                    continue
                for c in L.callees:
                    if c not in self.ctor_externs and c not in ovl_lift.BUILTIN_PROTOS:
                        ret, params = lifter.protos[c]
                        self.ctor_externs[c] = f"{ret} {{}}({', '.join(params) or 'void'});"
                    elif c in ovl_lift.BUILTIN_PROTOS:
                        ret, params = ovl_lift.BUILTIN_PROTOS[c]
                        self.ctor_externs[c] = f"{ret} {{}}({', '.join(params)});"
                self.ctors[o.name].append(L)
                self.tsv.append(("ctor", o.name, f"0x{t:08X}", cname,
                                 f"{L.ninsn} insns, calls {','.join(sorted(L.callees))}"))

    def own_ref(self, o: Ovl, v: int):
        """(label, offset) for an address inside o's data/bss: the nearest label
        at or below it (`<ov>_seg` = the data start at the latest)."""
        best = None
        for n, a in o.labels.items():
            if a <= v and (best is None or a > best[1] or (a == best[1] and n < best[0])):
                best = (n, a)
        if best is None or not (o.data_vram <= v < o.end):
            raise GenError(f"{o.name}: 0x{v:08X} is not inside its data/bss")
        return best[0], v - best[1]

    # ------------------------------------------------------------ emit
    def word_expr(self, o: Ovl, w: DataWord, externs: dict) -> str:
        """C initializer for one pristine data word (RG_W raw / RG_R reloc)."""
        if w.sym is None:
            v = w.raw
            where = f"0x{o.data_vram + w.off:08X}"
            if o.text_vram <= v < o.end:
                # A raw word holding this overlay's own address.  Values in
                # 0x004E9EC0.. are implausible as data (denormal as f32, ~5M as
                # int), and these tables (insmenu/normal callback tables,
                # factory self-pointers) were simply not symbolized by splat:
                # relocate, and log every one for review.
                if v in o.funcs:
                    externs[o.funcs[v]] = "void {}(void);"
                    self.tsv.append(("raw-reloc", o.name, where, f"0x{v:08X}", o.funcs[v]))
                    return f"RG_R(&{o.funcs[v]}, 0x{v:08X})"
                if v >= o.data_vram:
                    lab = next((n for n, a in o.labels.items() if a == v), None)
                    if lab:
                        externs[lab] = "extern unsigned char {}[];"
                        self.tsv.append(("raw-reloc", o.name, where, f"0x{v:08X}", lab))
                        return f"RG_R({lab}, 0x{v:08X})"
                    lab, off = self.own_ref(o, v)
                    externs[lab] = "extern unsigned char {}[];"
                    self.tsv.append(("raw-reloc", o.name, where, f"0x{v:08X}", f"{lab}+0x{off:X}"))
                    return f"RG_R({lab} + 0x{off:X}, 0x{v:08X})"
                self.tsv.append(("raw-text-word", o.name, where, f"0x{v:08X}",
                                 "inside own text but not a function entry; kept raw"))
                return f"RG_W(0x{v:08X})"
            hit = self.exact_symbol(None, v) if v < ARENA_BASE else None
            if hit:
                self.tsv.append(("raw-ptr-candidate", o.name, f"0x{o.data_vram + w.off:08X}",
                                 f"0x{w.raw:08X}", f"equals {hit}; kept raw (the snapshot did not "
                                 "symbolize it -- a pointer would need a relocation)"))
            return f"RG_W(0x{w.raw:08X})"
        s = w.sym
        a = w.raw
        if s in o.data_labels:
            n = o.prefixed(s)
            externs[n] = "extern unsigned char {}[];"
            return f"RG_R({n}, 0x{a:08X})"
        if a in o.ctor_targets:
            return f"RG_R(&{o.name}_sinit_{a:08X}, 0x{a:08X})"
        d = self.defined.get(s)
        if d and d[2] == "unit" and d[0] in (o.name, "main"):
            externs[s] = "void {}(void);"
            return f"RG_R(&{s}, 0x{a:08X})"
        if s in self.main_func_names:
            externs[s] = "void {}(void);"
            self.tsv.append(("main-func-ref", o.name, f"0x{o.data_vram + w.off:08X}", s,
                             "MAIN function without a C unit (asm-bodied: needs a binding)"))
            return f"RG_R(&{s}, 0x{a:08X})"
        if s.startswith("D_") and a < ARENA_BASE:
            externs[s] = "extern unsigned char {}[];"
            return f"RG_R({s}, 0x{a:08X})"
        self.tsv.append(("unbound-ref", o.name, f"0x{o.data_vram + w.off:08X}", s,
                         f"no host definition; retail word 0x{a:08X} kept"))
        return f"RG_W(0x{a:08X})"

    def emit(self, out: Path):
        out.mkdir(parents=True, exist_ok=True)
        hdr = ["/* GENERATED by tools/gen_overlay_registry.py -- do not edit.",
               f" * snapshot {self.src.repo.as_posix()} @ {self.rev} (docs/OVERLAY.md) */"]
        self._words = {o.name: None for o in self.ovls}
        self._emit_arena(out, hdr)
        self._emit_ctors(out, hdr)
        self._emit_registry(out, hdr)
        self._emit_native(out, hdr)
        rows = ["kind\ta\tb\tc\td"] + ["\t".join(map(str, r)) for r in self.tsv]
        write_if_changed(out / "OVERLAY_REGISTRY.tsv", "\n".join(rows) + "\n")

    def _emit_arena(self, out: Path, hdr):
        """One zero-filled block for the 0x004E9E80 arena, with every overlay's
        data/bss label (and MAIN's aliases) as a plain label at its retail
        offset: overlays share the memory exactly as on the PS2."""
        labs: list[tuple[int, str]] = [(0, "rg_ovl_arena")]
        for o in self.ovls:
            for n, a in o.labels.items():
                labs.append((a - ARENA_BASE, n))
        for n, a in self.main_aliases.items():
            labs.append((a - ARENA_BASE, n))
        labs.append((self.arena_size, "rg_ovl_arena_end"))
        labs.sort()
        names = [n for _o, n in labs]
        dup = {n for n in names if names.count(n) > 1}
        if dup:
            self.err(f"arena: duplicate labels {sorted(dup)[:5]}")
        lines = hdr + [
            "/* The shared overlay arena: PS2 0x%08X..0x%08X (0x%X bytes = 0x40 header +"
            % (ARENA_BASE, ARENA_BASE + self.arena_size, self.arena_size),
            " * the largest overlay's text+data+bss).  Every overlay's .data/.bss symbol is a",
            " * label at its retail offset, so the five overlays alias the same bytes as on",
            " * the PS2; src/ps2/overlay restores the resident one's .data on load. */",
            "#include \"ovl_asm.h\"",
            "",
            "#ifndef RG_OVL_TABLE_ONLY",
            "__asm__(",
            "    RG_OVL_ASM_BSS_SECTION \"\\n\"",
            "    \".p2align 7\\n\"",
        ]
        cur = 0
        for off, n in labs:
            if off > cur:
                lines.append(f"    \".zero 0x{off - cur:X}\\n\"")
                cur = off
            lines.append(f"    \".globl \" RG_OVL_ASM_SYM({n}) \"\\n\" RG_OVL_ASM_SYM({n}) \":\\n\"")
        lines += ["    RG_OVL_ASM_PREVIOUS \"\\n\");", "#endif", ""]
        write_if_changed(out / "ovl_arena_gen.c", "\n".join(lines))

    def _emit_ctors(self, out: Path, hdr):
        lines = hdr + [
            "/* The overlays' static initializers (.ctors targets), lifted from the",
            " * MIPS code that sits in each overlay's .data at the snapshot (tools/ovl_lift.py).",
            " * Each body is the retail instruction sequence's effect, in order: calls with",
            " * the callee's C prototype, gp/absolute loads and stores as C statements.",
            " * Addresses are symbols (+ offset): shared by both managers. */",
            "#include \"ovl_gen.h\"",
            "",
            "#ifndef RG_OVL_TABLE_ONLY",
        ]
        for n in sorted(self.ctor_externs):
            lines.append(self.ctor_externs[n].replace("{}", n, 1)
                         if self.ctor_externs[n].startswith("extern") else
                         self.ctor_externs[n].replace("{}", n, 1))
        lines.append("")
        for o in self.ovls:
            for L in self.ctors[o.name]:
                lines.append(f"/* {o.name} .ctors target 0x{L.addr:08X} ({L.ninsn} instructions) */")
                lines.append(f"void {L.name}(void)\n{{")
                lines += [f"    {s}" for s in L.body] or ["    /* empty */"]
                lines.append("}\n")
        lines += ["#endif", ""]
        write_if_changed(out / "ovl_ctors_gen.c", "\n".join(lines))

    def _emit_registry(self, out: Path, hdr):
        externs: dict[str, str] = {}
        body: list[str] = []
        for oi, o in enumerate(self.ovls):
            p = f"rg_ovl_{o.name}"
            if o.data_mode == "asm":
                ws = self.data_words(o, externs)
                body.append(f"static const uint32_t {p}_data[{len(ws)}] = {{")
                for i in range(0, len(ws), 4):
                    body.append("    " + ", ".join(ws[i:i + 4]) + ",")
                body.append("};")
            else:
                body.append(f"static const rg_ovl_object {p}_objects[] = {{")
                for n, a, s in o.c_objects:
                    externs[n] = "extern unsigned char {}[];"
                    body.append(f"    {{0x{a:08X}u, 0x{s:X}u, RG_P({n}), \"{n}\"}},")
                body.append("};")
            # ctors / dtors
            cs = [L.name for L in self.ctors[o.name]]
            body.append(f"static const rg_ovl_fn {p}_ctors[] = {{")
            body += [f"    RG_F(&{c})," for c in cs] or ["    0, /* none */"]
            body.append("};")
            for c in cs:
                externs[c] = "void {}(void);"
            # functions (every defined entry; sorted by address)
            body.append(f"static const rg_ovl_func {p}_funcs[] = {{")
            for a in sorted(o.funcs):
                externs[o.funcs[a]] = "void {}(void);"
                body.append(f"    {{0x{a:08X}u, \"{o.funcs[a]}\", RG_F(&{o.funcs[a]})}},")
            body.append("};")
            body.append(f"static const rg_ovl_label {p}_labels[] = {{")
            for n, a in sorted(o.labels.items(), key=lambda kv: (kv[1], kv[0])):
                body.append(f"    {{0x{a:08X}u, \"{n}\"}},")
            body.append("};")
        body.append("const rg_ovl_desc rg_ovl_generated_descs[] = {")
        for o in self.ovls:
            p = f"rg_ovl_{o.name}"
            img = f"{p}_data" if o.data_mode == "asm" else "0"
            objs = (f"{p}_objects, (int)(sizeof {p}_objects / sizeof {p}_objects[0])"
                    if o.data_mode == "c" else "0, 0")
            nct = len(self.ctors[o.name])
            body.append(
                f"    {{\"{o.name}\", \"{o.name.upper()}.BIN\", {o.index}, {o.oid}u,\n"
                f"     0x{ARENA_BASE:08X}u, 0x{o.text_size:X}u, 0x{o.data_size:X}u, 0x{o.bss_size:X}u,\n"
                f"     0x{o.ctor_start:08X}u, 0x{o.dtor_start:08X}u, {img}, {objs},\n"
                f"     {p}_ctors, {nct}, 0, 0,\n"
                f"     {p}_funcs, (int)(sizeof {p}_funcs / sizeof {p}_funcs[0]),\n"
                f"     {p}_labels, (int)(sizeof {p}_labels / sizeof {p}_labels[0]), 0}},")
        body.append("};")
        # imports + trampolines
        body.append("const rg_ovl_import rg_ovl_generated_imports[] = {")
        for im in self.imports:
            dom = im["domain"] if im["domain"] is not None else -1
            body.append(f"    {{\"{im['name']}\", 0x{im['addr']:08X}u, {dom}, "
                        f"{1 if im['kind'] == 'slot' else 0}, 0}},")
        if not self.imports:
            body.append("    {0, 0, -1, 0, 0},")
        body.append("};")
        body.append("#ifndef RG_OVL_TABLE_ONLY")
        for i, im in enumerate(self.imports):
            body.append(f"RG_OVL_TRAMPOLINE({im['name']}, rg_ovl_generated_imports, {i})")
        body.append("#endif")
        body.append("const rg_ovl_registry rg_ovl_generated_registry = {")
        body.append(f"    rg_ovl_generated_descs, {len(self.ovls)},")
        body.append("    RG_P(rg_ovl_arena), 0x%08Xu, 0x%Xu," % (ARENA_BASE, self.arena_size))
        body.append(f"    rg_ovl_generated_imports, {len(self.imports)},")
        body.append(f"    \"{self.rev}\"")
        body.append("};")
        externs["rg_ovl_arena"] = "extern unsigned char {}[];"
        lines = hdr + [
            "#include \"ovl.h\"",
            "#include \"ovl_asm.h\"",
            "",
            "#ifdef RG_OVL_TABLE_ONLY",
            "#define RG_W(v) (v##u)",
            "#define RG_R(sym, raw) (raw##u)",
            "#define RG_F(f) ((rg_ovl_fn)0)",
            "#define RG_P(p) ((unsigned char *)0)",
            "#else",
            "#define RG_W(v) (v##u)",
            "#define RG_R(sym, raw) ((uint32_t)(sym))",
            "#define RG_F(f) ((rg_ovl_fn)(f))",
            "#define RG_P(p) ((unsigned char *)(p))",
        ]
        for n in sorted(externs):
            lines.append(externs[n].replace("{}", n, 1))
        lines += ["#endif", ""] + body + [""]
        write_if_changed(out / "ovl_registry_gen.c", "\n".join(lines))

    def data_words(self, o: Ovl, externs: dict) -> list:
        """o's pristine .data as C initializers, computed once (word_expr logs TSV
        rows) and shared by the arena registry and the native module table."""
        if self._words.get(o.name) is None:
            ext: dict = {}
            self._words[o.name] = ([self.word_expr(o, w, ext) for w in o.words], ext)
        ws, ext = self._words[o.name]
        externs.update(ext)
        return ws

    def _emit_native(self, out: Path, hdr):
        """ovl_native_gen.c: the native module table (src/native/ovl, docs/OVERLAY.md
        section 8).  Per overlay one data segment `<ov>_seg` (.data then .bss, 128-
        aligned like the retail data start) with every data/bss label at its offset in
        the segment, the pristine .data image, the ctors; per import the host function
        of each module (resolved here, at build time); the trampolines.  No retail
        address is emitted (descriptor load/ctor fields and import addresses are 0).
        text_size is kept (a size: the text bytes between the 0x40 header and .data in the
        retail file): the trace recorder's address map (src/trace/trace_map.c) places the
        active module's segment at the retail data start = arena base + 0x40 + text_size."""
        externs: dict[str, str] = {}
        body: list[str] = []
        seg_asm: list[str] = []
        for o in self.ovls:
            if o.data_mode != "asm":
                self.err(f"native module table: {o.name} has C data (object mode) -- not supported")
                continue
            labs = [(a - o.data_vram, n) for n, a in o.labels.items()]
            for n, a in self.main_aliases.items():
                if o.data_vram <= a < o.end and len(self.ovl_at(a)) == 1 and self.ovl_at(a)[0] is o:
                    labs.append((a - o.data_vram, n))
            labs.sort(key=lambda x: (x[0], x[1]))
            size = o.data_size + o.bss_size
            seg_asm.append(f"    /* {o.name}: .data 0x{o.data_size:X} + .bss 0x{o.bss_size:X} */")
            seg_asm.append('    ".p2align 7\\n"')
            cur = 0
            for off, n in labs:
                if off > cur:
                    seg_asm.append(f'    ".zero 0x{off - cur:X}\\n"')
                    cur = off
                seg_asm.append(f'    ".globl " RG_OVL_ASM_SYM({n}) "\\n" RG_OVL_ASM_SYM({n}) ":\\n"')
            if size > cur:
                seg_asm.append(f'    ".zero 0x{size - cur:X}\\n"')
            p = f"rg_ovl_{o.name}"
            ws = self.data_words(o, externs)
            if getattr(self.a, "arch", "i686") == "x64":
                # x64 (docs/X64-PLAN.md step 3): a pointer truncated to a 32-bit word is
                # not a C constant; the pristine image goes out as asm `.long` words
                # (IMAGE_REL_AMD64_ADDR32, the exe lies below 2 GB: tools/x64/pecheck.py)
                body.append(f"extern const uint32_t {p}_data[{len(ws)}];")
                body.append("__asm__(")
                body.append('    ".section .rdata,\\"dr\\"\\n"')
                body.append('    ".p2align 2\\n"')
                body.append(f'    ".globl " RG_OVL_ASM_SYM({p}_data) "\\n" RG_OVL_ASM_SYM({p}_data) ":\\n"')
                for i in range(0, len(ws), 4):
                    body.append('    ".long ' + ", ".join(asm_word(w) for w in ws[i:i + 4]) + '\\n"')
                body.append('    RG_OVL_ASM_PREVIOUS "\\n");')
            else:
                body.append(f"static const uint32_t {p}_data[{len(ws)}] = {{")
                for i in range(0, len(ws), 4):
                    body.append("    " + ", ".join(ws[i:i + 4]) + ",")
                body.append("};")
            cs = [L.name for L in self.ctors[o.name]]
            body.append(f"static const rg_ovl_fn {p}_ctors[] = {{")
            body += [f"    RG_F(&{c})," for c in cs] or ["    0, /* none */"]
            body.append("};")
            for c in cs:
                externs[c] = "void {}(void);"
            externs[o.prefixed("seg")] = "extern unsigned char {}[];"
        # the load-slot token: OverlayLoadFile's `load` argument (D_0047D134[0]); names
        # no memory (each module has its own segment), the binding ignores it
        base_alias = sorted(n for n, a in self.main_aliases.items() if a == ARENA_BASE)
        end_alias = sorted(n for n, a in self.main_aliases.items() if a == ARENA_BASE + self.arena_size)
        if end_alias:
            self.notes.append(f"native module table: arena-end aliases {end_alias} not defined "
                              "(retail heap start; no compiled code may reference them)")
        body.append("const rg_ovl_desc rg_ovl_generated_descs[] = {")
        for o in self.ovls:
            p = f"rg_ovl_{o.name}"
            nct = len(self.ctors[o.name])
            body.append(
                f"    {{\"{o.name}\", \"{o.name.upper()}.BIN\", {o.index}, {o.oid}u,\n"
                f"     0u, 0x{o.text_size:X}u, 0x{o.data_size:X}u, 0x{o.bss_size:X}u, 0u, 0u, {p}_data, 0, 0,\n"
                f"     {p}_ctors, {nct}, 0, 0, 0, 0, 0, 0, {o.prefixed('seg')}}},")
        body.append("};")
        for i, im in enumerate(self.imports):
            fs = []
            for x in self.ovls:
                n = x.funcs.get(im["addr"])
                if n:
                    externs[n] = "void {}(void);"
                    fs.append(f"RG_F(&{n})")
                else:
                    fs.append("0")
            body.append(f"static const rg_ovl_fn rg_ovl_imp_{i}[{len(self.ovls)}] = {{{', '.join(fs)}}};")
        body.append("const rg_ovl_import rg_ovl_generated_imports[] = {")
        for i, im in enumerate(self.imports):
            dom = im["domain"] if im["domain"] is not None else -1
            body.append(f"    {{\"{im['name']}\", 0u, {dom}, {1 if im['kind'] == 'slot' else 0}, "
                        f"rg_ovl_imp_{i}}},")
        if not self.imports:
            body.append("    {0, 0, -1, 0, 0},")
        body.append("};")
        for i, im in enumerate(self.imports):
            body.append(f"RG_OVL_TRAMPOLINE({im['name']}, rg_ovl_generated_imports, {i})")
        body.append("const rg_ovl_registry rg_ovl_generated_registry = {")
        body.append(f"    rg_ovl_generated_descs, {len(self.ovls)},")
        body.append("    0, 0u, 0u,   /* no arena */")
        body.append(f"    rg_ovl_generated_imports, {len(self.imports)},")
        body.append(f"    \"{self.rev}\"")
        body.append("};")
        lines = hdr + [
            "/* The native module table (src/native/ovl/ovl_native.c, docs/OVERLAY.md section 8):",
            " * each overlay is a statically linked module with its own data segment; load =",
            " * restore .data, zero .bss, activate, run ctors.  No retail addresses. */",
            "#include \"ovl.h\"",
            "#include \"ovl_gen.h\"",
            "",
            "#define RG_W(v) (v##u)",
            "#define RG_R(sym, raw) ((uint32_t)(sym))",
            "#define RG_F(f) ((rg_ovl_fn)(f))",
        ]
        for n in sorted(externs):
            lines.append(externs[n].replace("{}", n, 1))
        lines += ["", "/* data segments (module .data + .bss; labels at their offsets) */",
                  "__asm__(", "    RG_OVL_ASM_BSS_SECTION \"\\n\""]
        lines += seg_asm
        if base_alias:
            lines.append("    /* the load-slot token (OverlayLoadFile's ignored `load` argument) */")
            lines.append('    ".p2align 4\\n"')
            for n in base_alias:
                lines.append(f'    ".globl " RG_OVL_ASM_SYM({n}) "\\n" RG_OVL_ASM_SYM({n}) ":\\n"')
            lines.append('    ".zero 0x10\\n"')
        lines += ["    RG_OVL_ASM_PREVIOUS \"\\n\");", ""] + body + [""]
        write_if_changed(out / "ovl_native_gen.c", "\n".join(lines))

    # ------------------------------------------------------------ report
    def report(self) -> str:
        r = [f"overlay registry @ {self.rev}: arena 0x{ARENA_BASE:08X}+0x{self.arena_size:X}"]
        for o in self.ovls:
            r.append(f"  {o.name:8} idx {o.index} id {o.oid}: text 0x{o.text_size:X} data 0x{o.data_size:X} "
                     f"({o.data_mode}) bss 0x{o.bss_size:X}  .ctors 0x{o.ctor_start:08X}..0x{o.dtor_start:08X} "
                     f"({len(o.ctor_targets)}, lifted {len(self.ctors.get(o.name, []))})  "
                     f"funcs {len(o.funcs)}/{len(o.all_funcs)}  labels {len(o.labels)}")
        kinds = {}
        for row in self.tsv:
            kinds[row[0]] = kinds.get(row[0], 0) + 1
        r.append("  census: " + ", ".join(f"{k}={v}" for k, v in sorted(kinds.items())))
        nslot = sum(1 for i in self.imports if i["kind"] == "slot")
        r.append(f"  imports: {len(self.imports) - nslot} MAIN call names, {nslot} data2c slot names; "
                 f"MAIN aliases {len(self.main_aliases)}")
        amb = [i for i in self.imports if len(i["bound"]) > 1]
        r.append(f"  imports whose address is a function in >1 overlay: {len(amb)}")
        for n in self.notes:
            r.append(f"  note: {n}")
        for e in self.errors:
            r.append(f"  ERROR: {e}")
        return "\n".join(r)


def asm_word(w: str) -> str:
    """An RG_W(v) / RG_R(sym, raw) initializer -> an assembler operand (x64 mode).
    Symbols are spelled bare (no `_` decoration on x64)."""
    m = re.fullmatch(r"RG_W\((0x[0-9A-Fa-f]+)\)", w)
    if m:
        return m.group(1)
    m = re.fullmatch(r"RG_R\((.*), 0x[0-9A-Fa-f]+\)", w)
    if m:
        e = m.group(1).replace("&", "").replace(" ", "")
        if re.fullmatch(r"[A-Za-z_]\w*(?:[+-]0x[0-9A-Fa-f]+)?", e):
            return e
    raise GenError(f"x64 data word not understood: {w}")


def write_if_changed(p: Path, text: str):
    data = text.encode()
    if not p.exists() or p.read_bytes() != data:
        p.write_bytes(data)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--source", default=None, help="snapshot repo (default: game/SNAPSHOT.txt)")
    ap.add_argument("--rev", default=None)
    ap.add_argument("--data2c", default=None, help="REPO@REV holding config/data2c.json")
    ap.add_argument("--bin", type=Path, default=None, help="retail BIN dir for cross-checks only")
    ap.add_argument("--arch", choices=("i686", "x64"), default="i686",
                    help="x64: the native module table's data images as asm words "
                         "(docs/X64-PLAN.md step 3); i686 output is unchanged")
    a = ap.parse_args(argv)
    try:
        g = Gen(a)
        g.load()
        g.check_bins()
        g.collect_labels()
        g.check_stage_table()
        g.collect_imports()
        g.census_main_data()
        g.lift_ctors()
        g.emit(a.out)
    except GenError as e:
        print(f"gen_overlay_registry: ERROR: {e}", file=sys.stderr)
        return 1
    print(g.report())
    return 1 if g.errors else 0


if __name__ == "__main__":
    sys.exit(main())

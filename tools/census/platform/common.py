"""Shared layer for the platform censuses (PLAN.md step 2b).

Ground truth for "who calls what" is the RETAIL BINARY, not the C text:
every image's functions come from config/<image>.symbols.txt at the pinned
decomp commit, and edges are decoded from the retail instructions:

  call      jal <func start>                        (direct call)
  tail      j <func start> outside the current fn   (tail call)
  addr      lui+addiu/ori pair = a function start   (address taken in code:
            thread entries, handlers, callbacks)
  data      aligned word outside any function = a function start
            (vtables, callback tables, ctor lists)

Library vs game: MAIN's library code is one contiguous link band
(0x100000..0x13BC20) plus two islands (see LIB_RANGES).  Everything else in
MAIN and every overlay function is GAME code.  Overlays contain no library code.

Source facts (C vs asm body, file path) come from tools/census/snapshot.py
(another census lane's loader; imported read-only, never edited).
"""
from __future__ import annotations

import bisect
import csv
import re
import struct
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[2]
sys.path.insert(0, str(HERE.parent))
import snapshot as S  # noqa: E402

PIN = "2efa6b43548fed253fafdee4d22c8d61d506acde"
SOURCE = "../RGDecomp"
WORK = Path("../work")
OUT = PORT / "census"
IMAGES = S.IMAGES
OVL_FILES = {"title": "TITLE.BIN", "insmenu": "INSMENU.BIN", "normal": "NORMAL.BIN",
             "factory": "FACTORY.BIN", "insect": "INSECT.BIN"}
OVL_BASE = 0x004E9E80

# MAIN library link order (addresses from config/main.symbols.txt; each
# boundary is the first function of the next library object group).
# (lo, hi, family, sub)
LIB_RANGES = [
    (0x100000, 0x100230, "crt0", "crt0"),
    (0x100230, 0x100400, "mwcc-rt", "softfloat-cmp"),
    (0x100400, 0x100580, "mwcc-rt", "mwo3-overlay"),
    (0x100580, 0x108110, "msl-c++", "runtime/eh/iostream/string"),
    (0x108110, 0x109cd8, "libgraph", "gs"),
    (0x109cd8, 0x10a400, "libdma", "dma"),
    (0x10a400, 0x10a8c0, "libpkt", "gifpk"),
    (0x10a8c0, 0x10b610, "libvu0", "vu0"),
    (0x10b610, 0x116180, "libmpeg", "mpeg+ipu"),
    (0x116180, 0x116a30, "libkernl", "syscall-stubs"),
    (0x116a30, 0x116b68, "libkernl", "vsync"),
    (0x116b68, 0x116df0, "libkernl", "newlib-glue"),
    (0x116df0, 0x117070, "libkernl", "cache"),
    (0x117070, 0x117880, "libkernl", "intc/dmac/thread"),
    (0x117880, 0x118120, "libkernl", "deci2/tty"),
    (0x118120, 0x119388, "libkernl", "printf"),
    (0x119388, 0x119b60, "libkernl", "sifcmd"),
    (0x119b60, 0x11ac18, "libkernl", "sifrpc"),
    (0x11ac18, 0x11e850, "libkernl", "fileio"),
    (0x11e850, 0x11eda0, "libkernl", "iopheap"),
    (0x11eda0, 0x11f930, "libkernl", "loadfile"),
    (0x11f930, 0x11fde0, "libkernl", "iopcontrol"),
    (0x11fde0, 0x120f38, "libkernl", "tlb/init/patch"),
    (0x120f38, 0x122630, "libkernl", "timer/alarm"),
    (0x122630, 0x122890, "libkernl", "iop-reset-cb"),
    (0x122890, 0x123110, "libsdr", "sdremote"),
    (0x123110, 0x129240, "libm", "msun"),
    (0x129240, 0x12af88, "libcdvd", "cdvd"),
    (0x12af88, 0x12c648, "libpad", "pad"),
    (0x12c648, 0x12de80, "libmc", "mc"),
    (0x12de80, 0x139110, "libc", "newlib"),
    (0x139110, 0x13bc20, "libgcc", "di3/softfloat"),
    (0x165608, 0x1660e0, "libsdr-gcc", "sdremote-cmd-island(gcc)"),
    (0x446000, 0x448000, "libkernl", "kernel-patch(copied to kernel)"),
]
_LIB_LO = [r[0] for r in LIB_RANGES]


def lib_of(image: str, addr: int):
    """(family, sub) for MAIN library code, else None (= game code)."""
    if image != "main":
        return None
    k = bisect.bisect_right(_LIB_LO, addr) - 1
    if k >= 0 and LIB_RANGES[k][0] <= addr < LIB_RANGES[k][1]:
        return LIB_RANGES[k][2], LIB_RANGES[k][3]
    return None


# --------------------------------------------------------------------------
# images
# --------------------------------------------------------------------------
@dataclass(eq=False)
class Fn:
    image: str
    name: str
    addr: int
    size: int
    lib: tuple | None = None

    @property
    def is_game(self):
        return self.lib is None

    @property
    def key(self):
        return (self.image, self.addr)


@dataclass
class Image:
    name: str
    base: int
    data: bytes
    fns: list = field(default_factory=list)   # sorted by addr
    by_addr: dict = field(default_factory=dict)
    by_name: dict = field(default_factory=dict)
    starts: list = field(default_factory=list)

    def word(self, addr: int) -> int | None:
        o = addr - self.base
        if 0 <= o <= len(self.data) - 4:
            return struct.unpack_from("<I", self.data, o)[0]
        return None

    def fn_at(self, addr: int):
        k = bisect.bisect_right(self.starts, addr) - 1
        if k >= 0:
            f = self.fns[k]
            if f.addr <= addr < f.addr + max(f.size, 4):
                return f
        return None


def load_images(tree) -> dict:
    S.load_symbols(tree)  # fills S.SIZES
    syms = S.load_symbols(tree)
    imgs = {}
    raw = (WORK / "SCUS_974.90").read_bytes()
    phoff = struct.unpack_from("<I", raw, 0x1C)[0]
    ty, off, vaddr, _, filesz, *_ = struct.unpack_from("<8I", raw, phoff)
    imgs["main"] = Image("main", vaddr, raw[off:off + filesz])
    for ov, fn in OVL_FILES.items():
        imgs[ov] = Image(ov, OVL_BASE, (WORK / "BIN" / fn).read_bytes())
    for name, im in imgs.items():
        for sym, a in syms[name].items():
            f = Fn(name, sym, a, S.SIZES.get((name, sym), 0), lib_of(name, a))
            im.fns.append(f)
        im.fns.sort(key=lambda f: f.addr)
        im.starts = [f.addr for f in im.fns]
        im.by_addr = {f.addr: f for f in im.fns}
        im.by_name = {f.name: f for f in im.fns}
    return imgs


def resolve(imgs, image: str, target: int):
    """Function starting at target, seen from code in `image`."""
    if image != "main" and target >= OVL_BASE:
        return imgs[image].by_addr.get(target)
    return imgs["main"].by_addr.get(target)


# --------------------------------------------------------------------------
# instruction decode (just enough)
# --------------------------------------------------------------------------
def insns(im: Image, f: Fn):
    o = f.addr - im.base
    n = max(f.size, 0) // 4
    for i in range(n):
        if o + 4 * i + 4 > len(im.data):
            break
        yield f.addr + 4 * i, struct.unpack_from("<I", im.data, o + 4 * i)[0]


def sx16(v):
    return v - 0x10000 if v & 0x8000 else v


@dataclass
class Edge:
    kind: str      # call | tail | addr | data
    src: Fn | None
    site: int      # instruction / data word address
    dst: Fn
    src_image: str


def build_edges(imgs) -> list:
    edges = []
    for name, im in imgs.items():
        for f in im.fns:
            hi = {}  # reg -> (value, addr)
            for pc, w in insns(im, f):
                op = w >> 26
                rs = (w >> 21) & 31
                rt = (w >> 16) & 31
                if op in (2, 3):
                    tgt = ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                    d = resolve(imgs, name, tgt)
                    if d is not None:
                        if op == 3:
                            edges.append(Edge("call", f, pc, d, name))
                        elif not (f.addr <= tgt < f.addr + f.size):
                            edges.append(Edge("tail", f, pc, d, name))
                    hi.clear()
                    continue
                if op == 0x0F:  # lui
                    hi[rt] = (w & 0xFFFF) << 16
                    continue
                if op in (0x09, 0x0D) and rs in hi:  # addiu / ori
                    v = (hi[rs] + sx16(w & 0xFFFF)) & 0xFFFFFFFF if op == 9 \
                        else hi[rs] | (w & 0xFFFF)
                    d = resolve(imgs, name, v)
                    if d is not None:
                        edges.append(Edge("addr", f, pc, d, name))
                    if rt != rs:
                        pass
                    continue
        # data words outside function bodies
        n = len(im.data) // 4
        for i in range(n):
            a = im.base + 4 * i
            if im.fn_at(a) is not None:
                continue
            v = struct.unpack_from("<I", im.data, 4 * i)[0]
            if v & 3:
                continue
            d = resolve(imgs, name, v)
            if d is not None and d.addr != 0x100000:
                edges.append(Edge("data", None, a, d, name))
    return edges


# --------------------------------------------------------------------------
# source facts
# --------------------------------------------------------------------------
ASM_STMT = re.compile(r"\basm\s*(volatile\s*)?\{|\b__asm__\b|\basm\s*(volatile\s*)?\(")


def source_facts(snap) -> dict:
    """(image, fn name) -> (path, body) where body is
    C | asm (whole-asm function) | C+asm (asm statement inside C)."""
    out = {}
    for sf in snap.files:
        for fn in sf.funcs:
            if fn.kind not in ("func", "member"):
                continue
            nm = fn.name.split("::")[-1]
            body = sf.nostr[fn.body_open:fn.body_close + 1]
            if fn.is_asm:
                kind = "asm"
            elif ASM_STMT.search(body):
                # whole body is one asm block?
                inner = body.strip()[1:-1].strip()
                kind = "asm" if re.fullmatch(
                    r"(asm|__asm__)\s*(volatile)?\s*[\{\(].*[\}\)]\s*;?", inner,
                    re.S) else "C+asm"
            else:
                kind = "C"
            out.setdefault((sf.image, nm), (sf.path, kind))
    return out


def load_all(quiet=True):
    snap = S.load(SOURCE, PIN, quiet=quiet)
    imgs = load_images(snap.tree)
    return snap, imgs


def write_tsv(path: Path, cols, rows, meta: dict):
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", newline="", encoding="utf-8") as fh:
        for k, v in meta.items():
            fh.write(f"# {k}: {v}\n")
        w = csv.writer(fh, delimiter="\t", lineterminator="\n")
        w.writerow(cols)
        for r in rows:
            w.writerow([S.clean(r.get(c, "")) for c in cols])


def meta(name: str, extra: dict | None = None):
    m = {"census": name, "source": SOURCE, "commit": PIN,
         "binaries": "../work/SCUS_974.90 + BIN/*.BIN (retail)",
         "generator": f"tools/census/platform/{name}.py"}
    if extra:
        m.update(extra)
    return m


CACHE = PORT / "out" / "platform_cache.pkl"


def cached(rebuild=False):
    """(snap-lite facts, imgs, edges) with a pickle cache keyed on PIN."""
    import pickle
    if CACHE.exists() and not rebuild:
        d = pickle.load(open(CACHE, "rb"))
        if d.get("pin") == PIN:
            return d["facts"], d["imgs"], d["edges"], d["files"]
    snap, imgs = load_all()
    facts = source_facts(snap)
    edges = build_edges(imgs)
    files = {(sf.image, sf.path): sf.text for sf in snap.files}
    files.update({("hdr", sf.path): sf.text for sf in snap.headers})
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    pickle.dump({"pin": PIN, "facts": facts, "imgs": imgs, "edges": edges,
                 "files": files}, open(CACHE, "wb"))
    return facts, imgs, edges, files


# --------------------------------------------------------------------------
# linear constant propagation (argument recovery at call sites)
# --------------------------------------------------------------------------
GP = 0x485170
CLOBBER = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 31}


class RegSim:
    """Straight-line simulation from the function start.  Values are ints
    (constants), ('sp', off) for stack addresses, ('load', addr) for an
    unknown word read from a constant address, ('q', addr) for a 128-bit lq
    from a constant address (expanded from the image on sq), or None.
    Branch targets are NOT joined: a value is reported only if the last
    straight-line definition before the site is constant -- callers mark
    these values static-linear."""

    def __init__(self, im=None, imgs=None):
        self.r = {0: 0, 28: GP, 29: ("sp", 0)}
        self.r.update({n: ("arg", n - 4) for n in range(4, 12)})
        self.stack = {}
        self.mem = {}
        self.im = im
        self.imgs = imgs

    def rd_word(self, addr):
        if self.imgs is None:
            return None
        im = self.im if (self.im.name != "main" and addr >= OVL_BASE)             else self.imgs["main"]
        return im.word(addr)

    def _store(self, base, off, v, nbytes):
        if isinstance(base, tuple) and base[0] == "sp":
            tgt, k = self.stack, base[1] + off
        elif isinstance(base, int):
            tgt, k = self.mem, (base + off) & 0xFFFFFFFF
        else:
            return
        if nbytes == 16 and isinstance(v, tuple) and v[0] == "q":
            for j in range(4):
                tgt[k + 4 * j] = self.rd_word(v[1] + 4 * j)
        elif nbytes == 16 and v == 0:
            for j in range(4):
                tgt[k + 4 * j] = 0
        elif nbytes == 8:
            tgt[k] = v
            tgt[k + 4] = 0 if v == 0 or isinstance(v, int) and v < 0x80000000 else None
        elif nbytes == 16:
            for j in range(4):
                tgt[k + 4 * j] = None
        else:
            tgt[k] = v

    def _load(self, base, off):
        if isinstance(base, tuple) and base[0] == "sp":
            return self.stack.get(base[1] + off)
        if isinstance(base, int):
            a = (base + off) & 0xFFFFFFFF
            if a in self.mem:
                return self.mem[a]
            return ("load", a)
        return None

    def step(self, w):
        op = w >> 26
        rs = (w >> 21) & 31
        rt = (w >> 16) & 31
        rd = (w >> 11) & 31
        imm = w & 0xFFFF
        a = self.r.get(rs)

        def setr(n, v):
            if n != 0:
                self.r[n] = v
        if op == 0x0F:
            setr(rt, imm << 16)
        elif op in (0x09, 0x19, 0x08, 0x18):  # addiu/daddiu/addi/daddi
            if isinstance(a, int):
                setr(rt, (a + sx16(imm)) & 0xFFFFFFFF)
            elif isinstance(a, tuple) and a[0] == "sp":
                setr(rt, ("sp", a[1] + sx16(imm)))
            else:
                setr(rt, None)
        elif op == 0x0D:  # ori
            setr(rt, (a | imm) if isinstance(a, int) else None)
        elif op == 0x0C:  # andi
            setr(rt, (a & imm) if isinstance(a, int) else None)
        elif op == 0:
            fn = w & 63
            b = self.r.get(rt)
            if fn in (0x21, 0x25, 0x2D, 0x20, 0x2C):  # addu/or/daddu/add/dadd
                if b == 0:
                    setr(rd, a)
                elif a == 0:
                    setr(rd, b)
                elif isinstance(a, int) and isinstance(b, int):
                    setr(rd, (a + b) & 0xFFFFFFFF if fn != 0x25 else a | b)
                else:
                    setr(rd, None)
            elif fn in (0x08, 0x0C, 0x0D, 0x0F, 0x18, 0x19, 0x1A, 0x1B, 0x11, 0x13):
                pass  # jr/syscall/break/sync/mult/div/mthi/mtlo
            elif fn == 0x00 and rd == 0:
                pass
            else:
                setr(rd, None)
        elif op in (0x2B, 0x3F, 0x29, 0x28, 0x1F, 0x2F):  # sw/sd/sh/sb/sq/sdr
            n = {0x2B: 4, 0x3F: 8, 0x29: 2, 0x28: 1, 0x1F: 16, 0x2F: 8}[op]
            v = self.r.get(rt)
            if n < 4 and isinstance(v, int):
                v &= (1 << (8 * n)) - 1
            self._store(a, sx16(imm), v, n)
        elif op in (0x23, 0x37):  # lw / ld
            v = self._load(a, sx16(imm))
            if isinstance(v, tuple) and v[0] == "load":
                w2 = self.rd_word(v[1])
                v = ("load", v[1], w2)
            setr(rt, v)
        elif op == 0x1E:  # lq
            if isinstance(a, int):
                setr(rt, ("q", (a + sx16(imm)) & 0xFFFFFFFF))
            else:
                setr(rt, None)
        elif op in (0x20, 0x21, 0x24, 0x25, 0x27, 0x1A, 0x1B, 0x22, 0x26):
            setr(rt, None)
        elif op in (0x0A, 0x0B, 0x0E):  # slti sltiu xori
            setr(rt, None)
        elif op in (0x11, 0x12):  # cop1/cop2 moves into GPR
            if rs in (0, 1, 2):
                setr(rt, None)
        elif op == 0x1C:  # mmi
            setr(rd, None)

    def after_call(self):
        for n in CLOBBER:
            self.r.pop(n, None)


def callsites(im: Image, f: Fn, targets: set, imgs=None):
    """Yield (site, target_addr, (regs, stack, mem)) for each jal into
    targets (after the delay slot)."""
    sim = RegSim(im, imgs)
    seq = list(insns(im, f))
    i = 0
    while i < len(seq):
        pc, w = seq[i]
        op = w >> 26
        if op == 3 or (op == 0 and (w & 63) == 9):
            if i + 1 < len(seq):
                sim.step(seq[i + 1][1])
            if op == 3:
                tgt = ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if tgt in targets:
                    yield pc, tgt, (dict(sim.r), dict(sim.stack), dict(sim.mem))
            sim.after_call()
            i += 2
            continue
        sim.step(w)
        i += 1


def fmt(v, imgs=None, image="main"):
    if v is None:
        return "?"
    if isinstance(v, tuple):
        if v[0] == "arg":
            return f"arg{v[1]}"
        if v[0] == "sp":
            return f"sp{'-' if v[1] < 0 else '+'}0x{abs(v[1]):X}"
        if v[0] == "load":
            nm = sym_or_hex(imgs, image, v[1]) if imgs else f"0x{v[1]:X}"
            init = v[2] if len(v) > 2 else None
            return f"[{nm}]" + (f"(init {fmt(init, imgs, image)})" if init is not None else "")
        return str(v)
    if imgs:
        d = resolve(imgs, image, v)
        if d is not None:
            return d.name
    return f"0x{v:X}" if v > 9 else str(v)


def sym_or_hex(imgs, image, a):
    d = resolve(imgs, image, a)
    return d.name if d else f"0x{a:X}"


def src_lines(facts, files, image, fn, rx):
    """Matching source lines (stripped, ';'-joined) of fn's C file."""
    pf = facts.get((image, fn))
    if not pf:
        return ""
    t = files.get((image, pf[0])) or ""
    out = []
    for ln in t.splitlines():
        s = ln.strip()
        if s.startswith(("//", "/*", "*")):
            continue
        if re.search(rx, s):
            out.append(s)
    return " ; ".join(out)


def arity(facts, files, image, fn):
    """Parameter count from the C definition (None if unknown / asm)."""
    pf = facts.get((image, fn))
    if not pf or pf[1] == "asm":
        return None
    t = files.get((image, pf[0])) or ""
    m = re.search(r"(?<![\w])" + re.escape(fn) + r"\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*\{", t)
    if not m:
        return None
    a = m.group(1).strip()
    if a in ("", "void"):
        return 0
    if "..." in a:
        return None
    depth, n = 0, 1
    for ch in a:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "," and depth == 0:
            n += 1
    return n

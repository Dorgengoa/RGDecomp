#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""gamedata_fill.py: put the retail game's data values into the published source tree.

The published tree carries no values from the game's files.  Every data initializer in
game/src/main_data/*.c, overrides/src/main_data/*.c and pregen/overlay-gen/ovl_native_gen.c
holds placeholders instead, and this script fills them from your own extracted disc
(rg-extract's data/ folder: SCUS_974.90 and BIN/*.BIN).  Run it once after cloning:

    python tools/gamedata_fill.py --data data            # fill in place
    python tools/gamedata_fill.py --data data --check    # only report what is unfilled

Placeholders (positions and formats only, never values):
    @X@AAAAAAAA@      u32 at address A, written 0x%08Xu
    @F@AAAAAAAA@      f32 at A, written %.9g (+ ".0" when integral) + "f"
    @H@AAAAAAAA@      s16 at A, decimal
    @B@AAAAAAAA@      u8 at A, decimal
    @S@AAAAAAAA@N@    N bytes at A as a C string literal (octal escapes)
    @W@KEY@OFFSET@    u32 at byte OFFSET of data file KEY (overlay images), 0x%08X
Addresses are MAIN virtual addresses, read from SCUS_974.90's program headers.
A filled file is byte-identical to the one the port was built from; each file's SHA-256
is listed in pregen/DATAFILL.tsv and checked.

`--blank` (maintainers, tools/release/make_source.py) does the reverse on a copy.
"""
import argparse
import hashlib
import re
import struct
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[1]

DECL = re.compile(r'^(u32|f32|s16|u8|char)\s+(?:D_|data2c_fragment_|data2c_gap_|func_|jtbl_)([0-9A-F]{8})\[(\d+)\]'
                  r'([^=\n]*=\s*)(\{.*?\n\}|"(?:[^"\\\n]|\\.)*")(;)', re.S | re.M)
STR = r'"(?:[^"\\\n]|\\.)*"'
TOK = re.compile(r'/\*.*?\*/|' + STR + r'|\(u32\)[^,}\n]*|-?0x[0-9A-Fa-f]+u|-?(?:\d+\.\d*|\d+)(?:[eE][-+]?\d+)?f|-?\d+')
PH = re.compile(r'@([XFHBS])@([0-9A-F]{8})@(?:(\d+)@)?|@W@([A-Za-z0-9_./]+)@([0-9A-F]+)@')
OVL_ARR = re.compile(r'static const uint32_t rg_ovl_(\w+)_data\[(\d+)\] = \{(.*?)\n\};', re.S)
OVL_FILES = {"title": "BIN/TITLE.BIN", "normal": "BIN/NORMAL.BIN", "factory": "BIN/FACTORY.BIN",
             "insect": "BIN/INSECT.BIN", "insmenu": "BIN/INSMENU.BIN"}


class Retail:
    def __init__(self, data: Path):
        self.data = data
        self.elf = (data / "SCUS_974.90").read_bytes()
        phoff, = struct.unpack_from("<I", self.elf, 0x1C)
        phsz, n = struct.unpack_from("<HH", self.elf, 0x2A)
        self.segs = []
        for i in range(n):
            t, off, va, _, fs, _, _, _ = struct.unpack_from("<8I", self.elf, phoff + i * phsz)
            if t == 1 and fs:
                self.segs.append((va, off, fs))
        self.files = {}

    def main(self, va, n):
        for sva, off, fs in self.segs:
            if sva <= va and va + n <= sva + fs:
                return self.elf[off + va - sva: off + va - sva + n]
        raise KeyError(f"address {va:#x} not in the ELF's loaded data")

    def file(self, key):
        if key not in self.files:
            self.files[key] = (self.data / key).read_bytes()
        return self.files[key]


def c_string(b: bytes) -> str:
    out = []
    for c in b:
        ch = chr(c)
        if 32 <= c < 127 and ch not in '"\\?':  # data2c writes these three as octal too
            out.append(ch)
        else:
            out.append('\\%03o' % c)
    return '"' + ''.join(out) + '"'


def c_float(v: float) -> str:
    s = '%.9g' % v
    if s in ('inf', '-inf', 'nan', '-nan'):
        raise ValueError(f"non-finite float {s}")
    if '.' not in s and 'e' not in s:
        s += '.0'
    return s + 'f'


def render(r: Retail, m) -> str:
    if m.group(1):
        kind, va = m.group(1), int(m.group(2), 16)
        if kind == 'X':
            return '0x%08Xu' % struct.unpack('<I', r.main(va, 4))[0]
        if kind == 'F':
            return c_float(struct.unpack('<f', r.main(va, 4))[0])
        if kind == 'H':
            return str(struct.unpack('<h', r.main(va, 2))[0])
        if kind == 'B':
            return str(r.main(va, 1)[0])
        return c_string(r.main(va, int(m.group(3))))
    b = r.file(m.group(4))
    off = int(m.group(5), 16)
    return '0x%08X' % struct.unpack_from('<I', b, off)[0]


def fill_text(r: Retail, text: str) -> str:
    return PH.sub(lambda m: render(r, m), text)


# ---- blanking (maintainers) ---------------------------------------------------------

def unescape_len(tok: str) -> int:
    body, n, i = tok[1:-1], 0, 0
    while i < len(body):
        if body[i] == '\\':
            if body[i + 1] in '01234567':
                j = i + 1
                while j < len(body) and j < i + 4 and body[j] in '01234567':
                    j += 1
                i = j
            else:
                i += 2
        else:
            i += 1
        n += 1
    return n


def blank_data2c(text: str, r: Retail) -> str:
    """Placeholders for every literal that equals the retail bytes at its address; a literal
    the port changed (datareloc fix-ups) is not retail content and stays as written."""
    size = {'u32': 4, 'f32': 4, 's16': 2, 'u8': 1}

    def one(m):
        typ, base, init = m.group(1), int(m.group(2), 16), m.group(5)
        if typ == 'char':
            if not init.startswith('"'):
                raise ValueError("char array without a string initializer")
            ph = '@S@%08X@%d@' % (base, unescape_len(init))
            if fill_text(r, ph) != init:
                return m.group(0)
            return m.group(0).replace(init, ph, 1)
        out, last, k = [], 0, 0
        for t in TOK.finditer(init):
            out.append(init[last:t.start()])
            tok = t.group(0)
            va = base + k * size[typ]
            if tok.startswith('/*'):  # comment: not an element
                out.append(tok)
                last = t.end()
                continue
            if tok.startswith('(u32)'):
                out.append(tok)
            elif tok.startswith('"'):
                raise ValueError("string inside a numeric array")
            else:
                ph = '@%s@%08X@' % ({'u32': 'X', 'f32': 'F', 's16': 'H', 'u8': 'B'}[typ], va)
                out.append(ph if fill_text(r, ph) == tok else tok)
            last = t.end()
            k += 1
        out.append(init[last:])
        return m.group(0).replace(init, ''.join(out), 1)
    return DECL.sub(one, text)


def blank_ovl(text: str, r: Retail) -> str:
    def one(m):
        ov, words = m.group(1), m.group(3)
        key = OVL_FILES[ov]
        b = r.file(key)
        toks = list(re.finditer(r'RG_W\((0x[0-9A-F]{8})\)|RG_R\([^)]*\)', words))
        # find where the image starts in the BIN: the offset whose words match every RG_W
        vals = [(i, int(t.group(1), 16)) for i, t in enumerate(toks) if t.group(1)]
        start = None
        for cand in range(0, len(b) - 4 * len(toks) + 1, 4):
            if all(struct.unpack_from('<I', b, cand + 4 * i)[0] == v for i, v in vals[:64]) and \
               all(struct.unpack_from('<I', b, cand + 4 * i)[0] == v for i, v in vals):
                start = cand
                break
        if start is None:
            raise ValueError(f"overlay {ov}: image not found in {key}")
        out, last = [], 0
        for i, t in enumerate(toks):
            out.append(words[last:t.start()])
            out.append('RG_W(@W@%s@%X@)' % (key, start + 4 * i) if t.group(1) else t.group(0))
            last = t.end()
        out.append(words[last:])
        return m.group(0).replace(words, ''.join(out), 1)
    return OVL_ARR.sub(one, text)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--data", default=str(PORT / "data"), help="rg-extract output folder")
    ap.add_argument("--root", default=str(PORT), help="tree to fill (default: this checkout)")
    ap.add_argument("--check", action="store_true", help="report unfilled files, change nothing")
    a = ap.parse_args()
    root = Path(a.root)
    table = root / "pregen" / "DATAFILL.tsv"
    rows = [l.split("\t") for l in table.read_text(encoding="utf-8").splitlines()
            if l and not l.startswith("#")]
    unfilled = [rel for rel, _ in rows if PH.search((root / rel).read_text(encoding="latin-1"))]
    if a.check:
        print(f"gamedata_fill: {len(unfilled)} of {len(rows)} files still hold placeholders")
        return 1 if unfilled else 0
    if not unfilled:
        print(f"gamedata_fill: all {len(rows)} files already filled")
        return 0
    r = Retail(Path(a.data))
    bad = 0
    for rel, want in rows:
        p = root / rel
        text = p.read_text(encoding="latin-1")
        if not PH.search(text):
            continue
        new = fill_text(r, text).encode("latin-1")
        if hashlib.sha256(new).hexdigest() != want.strip():
            print(f"gamedata_fill: {rel}: result does not match (wrong disc data?)", file=sys.stderr)
            bad += 1
            continue
        p.write_bytes(new)
    if bad:
        print(f"gamedata_fill: {bad} files failed; nothing else changed for them", file=sys.stderr)
        return 1
    print(f"gamedata_fill: filled {len(unfilled)} files from {a.data}, all checksums OK")
    protect(root, [rel for rel, _ in rows])
    return 0


def protect(root: Path, rels):
    """In a git checkout, mark the filled files skip-worktree so the game's data values are
    never committed by accident (`git update-index --no-skip-worktree` to undo)."""
    if not (root / ".git").exists():
        return
    for i in range(0, len(rels), 500):
        r = subprocess.run(["git", "update-index", "--skip-worktree", "--"] + rels[i:i + 500],
                           cwd=root, capture_output=True, text=True)
        if r.returncode:
            print("gamedata_fill: could not mark the filled files skip-worktree; do not commit "
                  "game/src/main_data, overrides/src/main_data or pregen/overlay-gen", file=sys.stderr)
            return
    print("gamedata_fill: filled files marked skip-worktree in git (they now hold game data; "
          "never commit them)")


if __name__ == "__main__":
    sys.exit(main())

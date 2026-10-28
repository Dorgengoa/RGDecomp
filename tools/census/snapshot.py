"""Shared loader for the game-code censuses (PLAN.md step 2a).

Reads a decomp tree at a pinned commit WITHOUT touching its working tree:
`git ls-tree` + `git cat-file --batch` against `<rev>`.  With `--rev WORKTREE`
(or a --source that is not a git repo) it reads files from disk instead, which
is what a re-run on an extracted clean snapshot uses.

Scope = REGISTERED LINKED UNITS only, learned the same way the matching build
learns them:

  main     config/cunits.txt           (link.py: names compiled from C)
  <ovl>    config/ocunits/<ovl>.txt    (olink.py / *_olink.py)
  unit -> file   rgd.src_path(): the first of sorted src/**/<unit>.c, then
                 sorted src/**/<unit>.cpp
  hosted   config/hosted.txt GUEST HOST: GUEST is static inside HOST's file,
           so it maps to HOST's file (no file of its own)
  data     generated data sources (src/main_data/** from data2c, and
           src/*_data/** for any overlay equivalents) when the snapshot has them

Registered units that resolve to no file are reported (`unresolved`), never
silently dropped.
"""
from __future__ import annotations

import argparse
import bisect
import csv
import os
import re
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
DEFAULT_SOURCE = "../RGDecomp"
DEFAULT_OUT = PORT / "census"
IMAGES = ["main", "title", "insmenu", "normal", "factory", "insect"]
OVERLAYS = IMAGES[1:]

# Library address bands in MAIN (memory: sdk-library-track, main-linked-asm-census)
LIB_BANDS = [
    (0x00100000, 0x00108000, "library", "band:crt0+MSL-runtime"),
    (0x00108000, 0x00140000, "sdk", "band:sce-sdk"),
    (0x00165608, 0x001660D4, "sdk", "band:sdremote-gcc-island"),
    (0x00446000, 0x00448000, "sdk", "band:libkernl"),
]


# --------------------------------------------------------------------------
# reading the tree
# --------------------------------------------------------------------------
class Tree:
    def __init__(self, source: str, rev: str | None):
        self.source = source
        src = Path(source)
        is_git = (src / ".git").exists() or (src / "HEAD").exists()
        if rev is None:
            rev = "HEAD" if is_git else "WORKTREE"
        self.worktree = (rev == "WORKTREE") or not is_git
        if self.worktree:
            self.rev = "WORKTREE"
            self.commit = "WORKTREE"
        else:
            self.commit = self._git("rev-parse", rev).strip()
            self.rev = rev
        self._cache: dict[str, str] = {}
        self._paths: list[str] | None = None

    def _git(self, *args: str, inp: bytes | None = None) -> str:
        r = subprocess.run(["git", "-C", self.source, *args], input=inp,
                           capture_output=True, check=True)
        return r.stdout.decode("utf-8", "replace")

    def paths(self) -> list[str]:
        if self._paths is None:
            if self.worktree:
                root = Path(self.source)
                out = []
                for top in ("src", "include", "config"):
                    d = root / top
                    if d.exists():
                        for p in d.rglob("*"):
                            if p.is_file():
                                out.append(p.relative_to(root).as_posix())
                self._paths = sorted(out)
            else:
                self._paths = self._git("ls-tree", "-r", "--name-only",
                                        self.commit, "--", "src", "include",
                                        "config").splitlines()
        return self._paths

    def read_many(self, paths: list[str]) -> None:
        need = [p for p in paths if p not in self._cache]
        if not need:
            return
        if self.worktree:
            for p in need:
                try:
                    self._cache[p] = (Path(self.source) / p).read_bytes().decode(
                        "utf-8", "replace")
                except FileNotFoundError:
                    self._cache[p] = None
            return
        inp = "".join(f"{self.commit}:{p}\n" for p in need).encode()
        r = subprocess.run(["git", "-C", self.source, "cat-file", "--batch"],
                           input=inp, capture_output=True, check=True)
        buf = r.stdout
        pos = 0
        for p in need:
            nl = buf.index(b"\n", pos)
            hdr = buf[pos:nl].split()
            pos = nl + 1
            if len(hdr) >= 2 and hdr[1] == b"missing":
                self._cache[p] = None
                continue
            size = int(hdr[2])
            self._cache[p] = buf[pos:pos + size].decode("utf-8", "replace")
            pos += size + 1

    def read(self, path: str) -> str | None:
        if path not in self._cache:
            self.read_many([path])
        return self._cache[path]


def reglines(text: str | None) -> list[str]:
    out = []
    for ln in (text or "").splitlines():
        s = ln.split("#")[0].strip()
        if not s or s.startswith("//"):
            continue
        out.append(s)
    return out


# --------------------------------------------------------------------------
# comment stripping (line numbers and columns preserved)
# --------------------------------------------------------------------------
_INTERESTING = re.compile(r"[/\"']")


def strip_comments(text: str) -> tuple[str, str]:
    """Return (code, code_nostr): comments blanked; in code_nostr string and
    char literal CONTENTS are blanked too.  Newlines always kept."""
    out = []
    out2 = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i)); out2.append(" " * (j - i))
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            seg = re.sub(r"[^\n]", " ", text[i:j])
            out.append(seg); out2.append(seg)
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
            out.append(text[i:j])
            inner = re.sub(r"[^\n]", " ", text[i + 1:j - 1])
            out2.append(c + inner + (c if j - i >= 2 else ""))
            i = j
        else:
            # fast path: copy up to the next interesting char
            m = _INTERESTING.search(text, i + 1)
            j = m.start() if m else n
            out.append(text[i:j]); out2.append(text[i:j])
            i = j
    return "".join(out), "".join(out2)


@dataclass
class Func:
    name: str
    header: str          # text from end of previous decl to the '{'
    start: int           # offset of header start
    body_open: int       # offset of '{'
    body_close: int      # offset of matching '}'
    kind: str            # "func" | "class" | "member"
    is_asm: bool = False


@dataclass
class SrcFile:
    path: str
    image: str
    units: list = field(default_factory=list)
    kind: str = "code"     # code | data | header
    text: str = ""
    code: str = ""
    nostr: str = ""
    _ls: list = field(default_factory=list)
    funcs: list = field(default_factory=list)
    _fstarts: list = field(default_factory=list)
    lib: str = "game"
    lib_reason: str = ""

    def line(self, off: int) -> int:
        return bisect.bisect_right(self._ls, off)

    def line_text(self, lineno: int, which: str = "code") -> str:
        src = getattr(self, which)
        a = self._ls[lineno - 1]
        b = self._ls[lineno] - 1 if lineno < len(self._ls) else len(src)
        return src[a:b]

    def enclosing(self, off: int) -> Func | None:
        k = bisect.bisect_right(self._fstarts, off) - 1
        while k >= 0:
            f = self.funcs[k]
            if f.start <= off <= f.body_close:
                return f
            k -= 1
            if k >= 0 and self.funcs[k].body_close < off and f.kind == "func":
                break
        return None

    def symbol_at(self, off: int) -> str:
        f = self.enclosing(off)
        if f is None:
            return self.units[0] if self.units else Path(self.path).stem
        return f.name


IDENT = re.compile(r"[A-Za-z_]\w*")
NOT_FUNC_HDR = re.compile(r"(^|[^\w])(class|struct|union|enum|namespace)\b")


def _match_paren_back(s: str, close: int) -> int:
    depth = 0
    for k in range(close, -1, -1):
        if s[k] == ")":
            depth += 1
        elif s[k] == "(":
            depth -= 1
            if depth == 0:
                return k
    return -1


_BRACES = re.compile(r"[{};]")
_PP = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)


def find_funcs(s: str) -> list[Func]:
    """Top-level function/class bodies.  `extern "C" {` and `namespace x {`
    are transparent.  Classes are recorded (kind=class) and their inline
    member bodies recorded as kind=member."""
    res: list[Func] = []
    stack: list[tuple] = []     # (kind, Func|None)
    last = 0                    # start of the current top-level "statement"
    n = len(s)
    # blank preprocessor lines (with continuations) so '#define X {' etc. do
    # not confuse the brace walk
    s = _PP.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), s)
    for mm in _BRACES.finditer(s):
        i = mm.start()
        c = s[i]
        if c == "{":
            hdr = s[last:i]
            transparent = bool(re.search(r'extern\s+"[^"]*"\s*$|\bnamespace\s+\w*\s*$',
                                         hdr))
            in_func = any(k in ("func", "member", "init") for k, _ in stack)
            if transparent and not in_func:
                stack.append(("transparent", None))
                last = i + 1
            elif in_func:
                stack.append(("block", None))
            else:
                h = hdr.strip()
                in_class = any(k == "class" for k, _ in stack)
                if "=" in h.split("(")[0] or h.endswith("="):
                    stack.append(("init", None))
                elif NOT_FUNC_HDR.search(h.split("(")[0]) and not h.endswith(")"):
                    m = re.search(r"\b(class|struct|union|enum)\s+(\w+)?", h)
                    nm = (m.group(2) or "<anon>") if m else "<anon>"
                    f = Func(nm, hdr, last, i, -1, "class")
                    res.append(f)
                    stack.append(("class", f))
                    last = i + 1
                else:
                    hh = re.sub(r"\s+(const|throw\s*\(\s*\))\s*$", "", h)
                    ci = re.search(r"\)\s*:(?!:)", hh)  # ctor init list
                    if ci:
                        hh = hh[:ci.start() + 1]
                    name = "<anon>"
                    if hh.endswith(")"):
                        o = _match_paren_back(hh, len(hh) - 1)
                        m = re.search(r"([\w:~]+)\s*$", hh[:o]) if o > 0 else None
                        if m:
                            name = m.group(1)
                            if name in ("if", "while", "for", "switch"):
                                name = "<anon>"
                    is_asm = bool(re.match(r"(?:static\s+|inline\s+|extern\s+)*asm\b",
                                           h))
                    f = Func(name, hdr, last, i, -1,
                             "member" if in_class else "func", is_asm)
                    res.append(f)
                    stack.append(("member" if in_class else "func", f))
        elif c == "}":
            if stack:
                k, f = stack.pop()
                if f is not None:
                    f.body_close = i
                if k in ("func", "member", "class", "transparent", "init"):
                    if not any(kk in ("func", "member", "init") for kk, _ in stack):
                        last = i + 1
            else:
                last = i + 1
        elif c == ";":
            if not any(k in ("func", "member", "init", "block") for k, _ in stack):
                last = i + 1
    for f in res:
        if f.body_close < 0:
            f.body_close = n - 1
    res.sort(key=lambda f: f.start)
    return res


# --------------------------------------------------------------------------
# the registry
# --------------------------------------------------------------------------
@dataclass
class Snapshot:
    tree: Tree
    files: list            # SrcFile, code + data
    headers: list          # SrcFile kind=header (included by registered files)
    unresolved: list       # (image, unit, why)
    symbols: dict          # image -> {name: vram}
    unit_count: dict       # image -> registered unit count
    hosted: dict

    def all(self, headers: bool = True):
        return self.files + (self.headers if headers else [])


SIZES: dict = {}   # (image, name) -> size, filled by load_symbols


def load_symbols(tree: Tree) -> dict:
    rx = re.compile(r"^\s*(\S+)\s*=\s*0x([0-9A-Fa-f]+);.*type:func")
    rs = re.compile(r"size:(0x[0-9A-Fa-f]+)")
    out = {}
    for img in IMAGES:
        t = tree.read(f"config/{img}.symbols.txt") or ""
        d = {}
        for ln in t.splitlines():
            m = rx.match(ln)
            if m:
                d[m.group(1)] = int(m.group(2), 16)
                z = rs.search(ln)
                SIZES[(img, m.group(1))] = int(z.group(1), 16) if z else 0
        out[img] = d
    return out


def classify_lib(path: str, image: str, addrs: list[int]) -> tuple[str, str]:
    parts = path.split("/")
    for p in parts[1:-1]:
        if p == "sdk":
            return "sdk", "path:sdk"
        if p == "libc":
            return "library", "path:libc"
        if p == "gcc" or p.startswith("lib"):
            return "library", f"path:{p}"
    if image == "main":
        for a in addrs:
            for lo, hi, cls, why in LIB_BANDS:
                if lo <= a < hi:
                    return cls, why
    return "game", ""


def _prep(sf: SrcFile, text: str) -> None:
    sf.text = text
    sf.code, sf.nostr = strip_comments(text)
    sf._ls = [0] + [m.end() for m in re.finditer(r"\n", sf.code)]
    sf.funcs = find_funcs(sf.nostr)
    sf._fstarts = [f.start for f in sf.funcs]


def load(source: str, rev: str | None, quiet: bool = False) -> Snapshot:
    tree = Tree(source, rev)
    paths = tree.paths()
    src = [p for p in paths if p.startswith("src/") and p.endswith((".c", ".cpp"))]
    by_stem: dict[str, list[str]] = defaultdict(list)
    for p in src:
        by_stem[Path(p).stem].append(p)

    def src_path(sym: str) -> str | None:
        hits = by_stem.get(sym)
        if not hits:
            return None
        c = sorted(h for h in hits if h.endswith(".c"))
        cpp = sorted(h for h in hits if h.endswith(".cpp"))
        return (c + cpp)[0]

    hosted = {}
    for ln in reglines(tree.read("config/hosted.txt")):
        f = ln.split()
        if len(f) >= 2:
            hosted[f[0]] = f[1]

    reg: dict[str, tuple[str, list]] = {}  # path -> (image, units)
    unresolved = []
    unit_count = {}
    lists = [("main", "config/cunits.txt")] + [
        (o, f"config/ocunits/{o}.txt") for o in OVERLAYS]
    for img, lp in lists:
        units = [ln.split()[0] for ln in reglines(tree.read(lp))]
        seen = []
        for u in units:
            if u in seen:
                continue
            seen.append(u)
            p = src_path(u)
            if p is None and u in hosted:
                p = src_path(hosted[u])
            if p is None:
                unresolved.append((img, u, "no src file and not a hosted guest"))
                continue
            if p in reg and reg[p][0] != img:
                unresolved.append((img, u, f"file already registered to {reg[p][0]}"))
            reg.setdefault(p, (img, []))[1].append(u)
        unit_count[img] = len(seen)

    # generated data sources (data2c): src/main_data/**, src/<ovl>_data/**
    data_files = []
    for p in paths:
        m = re.match(r"src/(main|title|insmenu|normal|factory|insect)_data/", p)
        if m and p.endswith((".c", ".cpp", ".h")):
            data_files.append((p, m.group(1)))

    tree.read_many(list(reg) + [p for p, _ in data_files])
    symbols = load_symbols(tree)
    files = []
    for p, (img, units) in sorted(reg.items()):
        sf = SrcFile(p, img, units, "code")
        _prep(sf, tree.read(p) or "")
        addrs = [symbols[img][u] for u in units if u in symbols[img]]
        sf.lib, sf.lib_reason = classify_lib(p, img, addrs)
        files.append(sf)
    for p, img in data_files:
        sf = SrcFile(p, img, [Path(p).stem], "data")
        _prep(sf, tree.read(p) or "")
        sf.lib, sf.lib_reason = "game", "generated-data"
        files.append(sf)

    # headers transitively included by registered files
    inc_rx = re.compile(r'^\s*#\s*include\s*[<"]([^">]+)[">]', re.M)
    hdr_imgs: dict[str, set] = defaultdict(set)
    hdr_lib: dict[str, set] = defaultdict(set)
    pathset = set(paths)
    todo = [(sf.path, sf.code, sf.image, sf.lib) for sf in files]
    while todo:
        p, code, img, lib = todo.pop()
        for m in inc_rx.finditer(code):
            name = m.group(1)
            cands = [f"include/{name}",
                     (Path(p).parent / name).as_posix()]
            hp = next((c for c in cands if c in pathset), None)
            if hp is None:
                continue
            new = img not in hdr_imgs[hp] or lib not in hdr_lib[hp]
            hdr_imgs[hp].add(img)
            hdr_lib[hp].add(lib)
            if new:
                t = tree.read(hp) or ""
                todo.append((hp, strip_comments(t)[0], img, lib))
    headers = []
    for hp in sorted(hdr_imgs):
        sf = SrcFile(hp, ",".join(i for i in IMAGES if i in hdr_imgs[hp]),
                     ["(header)"], "header")
        _prep(sf, tree.read(hp) or "")
        sf.lib = "game" if "game" in hdr_lib[hp] else sorted(hdr_lib[hp])[0]
        sf.lib_reason = "header:" + "+".join(sorted(hdr_lib[hp]))
        headers.append(sf)
    if not quiet:
        print(f"snapshot {tree.commit}: {len(files)} files "
              f"({sum(1 for f in files if f.kind == 'data')} data), "
              f"{len(headers)} headers, {len(unresolved)} unresolved units",
              file=sys.stderr)
    return Snapshot(tree, files, headers, unresolved, symbols, unit_count, hosted)


# --------------------------------------------------------------------------
# output
# --------------------------------------------------------------------------
BASE_COLS = ["file", "line", "symbol", "image", "lib", "category"]


def write_tsv(path: Path, cols: list[str], rows: list[dict], meta: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", newline="", encoding="utf-8") as fh:
        for k, v in meta.items():
            fh.write(f"# {k}: {v}\n")
        # plain TSV, no quoting: clean() strips tabs/newlines from every cell
        fh.write("\t".join(cols) + "\n")
        for r in rows:
            fh.write("\t".join(clean(r.get(c, "")) for c in cols) + "\n")


def clean(v) -> str:
    s = str(v)
    s = s.replace("\t", " ").replace("\r", " ").replace("\n", " ")
    return re.sub(r" {2,}", " ", s).strip()


def snippet(s: str, n: int = 140) -> str:
    s = re.sub(r"\s+", " ", s).strip()
    return s if len(s) <= n else s[:n - 3] + "..."


def arg_parser(desc: str) -> argparse.ArgumentParser:
    ap = argparse.ArgumentParser(description=desc)
    ap.add_argument("--source", default=DEFAULT_SOURCE,
                    help="decomp tree (git repo, or a plain directory with --rev WORKTREE)")
    ap.add_argument("--rev", default=None,
                    help="commit/branch to read (default HEAD, pinned to its hash); "
                         "WORKTREE reads files on disk")
    ap.add_argument("--out", default=str(DEFAULT_OUT), help="output directory")
    return ap


def meta(snap: Snapshot, name: str, extra: dict | None = None) -> dict:
    m = {"census": name, "source": snap.tree.source, "commit": snap.tree.commit,
         "generator": f"tools/census/{name}.py"}
    if extra:
        m.update(extra)
    return m

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Ingest stage `interior`: every access of an interior data label goes through its container
symbol (distinct-symbol aliasing; docs/LINUX.md "Linux ABI differences", PLAN.md ingest stages).

The data layer defines interior labels as separate global symbols (data2c_bss.c:
`D_004DAE8C:` = D_004DAE60 + 0x2C).  A game file that declares both

    extern u8 D_004DAE60[0x100];
    extern void *D_004DAE8C[0x10];

and stores through one, loads through the other, has a hazard: clang treats two distinct
globals as never aliasing, so the scheduler may move the load above the store (the
i686-linux-gnu build hoisted StaticInitTaskTable_46bcc0's vptr load above its store; the same
UB is latent on Windows i686 and x64).  This stage keeps every declaration and adds, after the
last extern declaration of the pair,

    #define D_004DAE8C (*(__typeof__(D_004DAE8C) *)((u8 *)&D_004DAE60 + 0x2C))   /* rg-interior */

so every later mention of the interior label is an lvalue of the container (same address, same
declared type: indexing, &, sizeof and assignment read as before) and alias analysis sees one
object.  __typeof__ takes the file's own declaration, so the x64 derive (ptr32's `global` rule
rewrites that extern to RG_P32 words) keeps the 4-byte game table (docs/X64-PLAN.md 0.15,
tools/x64/interiorcheck.py).  A macro does not expand its own name, so `D_004DAE8C` inside is
the real symbol, unevaluated.

Which pairs: per file, the D_XXXXXXXX symbols declared `extern` with a known extent (array
dims x element size, or a scalar type; tools/linux/overlapscan.py's rule) and every symbol B
whose address lies inside [A, A + size(A)).  The USED symbols whose declared extents overlap
form components (a chain A[0x10], A+8[0x10], A+0x10[0x10] is one); every member is routed to
the component's lowest address, its ROOT.  A pair with an unused side needs nothing (no access
through that name).  Function-
pointer declarators have no plain spelling here and are left alone (reported; 0 at the pin).

True extents (lane tidy, 2026-11-02): a chain member that lies PAST the root's declared extent
(`beyond`) means the declarations, not the data, made the chain: the decomp declared
neighbouring data-layer objects as over-long arrays (`extern s8 D_0045A9D0[0x10]` for the
8-byte string object data2c defines, `s32 D_004DB920[4]` for a 4-byte bss slot), the overlaps
chain them, and the member was routed through &root + off past root's object.  The rows of
tools/stages/interior_extent.tsv (file, symbol, declared dims, true dims) rewrite those
declarators to the data layer's extent (data2c object size, or the bss label's span) before the
analysis; the false chains then dissolve.  A `beyond` member left is a stage ERROR (ingest
exits 1; `--check` FAILs); `--check` also verifies every row against the data layer (true
bytes <= the data-layer extent) and that every row applied (a stale row is an error).
`--propose-extents` prints candidate rows: every used symbol of a component whose declared
extent is larger than its data-layer extent and covers another used symbol past that extent
(lane tidy2, 2026-11-02: not only `beyond` chains), each with a scan of the file's uses
(scan_uses: constant / variable indices, pointer arithmetic, sizeof, derefs wider than the
true extent, member access, the address held in a local or passed to a function or macro
defined in the file).  A row with such a use prints as `#FLAG` for review; reviewed rows and
the kept declarations are in out/tidy2 (scripts/review.tsv); rows whose file has an override
are scanned against the override too (it is what compiles).  At tidy2: 428 rows, 57 defines in
10 files left, each a real sub-object of one object (struct / table the data layer splits into
labels), docs/LINUX.md "Linux ABI differences".

A define goes after the line of the LAST extern statement that declares B or its root (a
later redeclaration would otherwise macro-expand); a use of B before that line is reported
as `uncovered` (0 at the pin) and fails the stage (errors).  Idempotent: tagged lines are
removed and regenerated.  Extra output INTERIOR.tsv (file, B, root, offset).  It runs LAST
(after hwaccess), on the final declarations.  RG_INGEST_NO_INTERIOR=1 disables it (control).

Standalone dry run on game/:  python tools/stages/interior.py [--game game] [--list] [--file F]
       [--check] [--control] [--propose-extents]
"""
from __future__ import annotations

import argparse
import os
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
import portxform as X  # noqa: E402  (read-only reuse: blank)

TAG = "/* rg-interior */"
SCALAR = {"u8": 1, "s8": 1, "char": 1, "u16": 2, "s16": 2, "short": 2, "u32": 4, "s32": 4,
          "int": 4, "f32": 4, "float": 4, "u64": 8, "s64": 8, "f64": 8, "double": 8, "u128": 16}
EXTERN = re.compile(r"\bextern\b[^;{}]*;")
SYM = re.compile(r"D_[0-9A-Fa-f]{8}")
OLD = re.compile(r"[ \t]*#define D_[0-9A-Fa-f]{8} [^\n]*" + re.escape(TAG) + r"[ \t]*\r?\n")
EXTENT_TSV = Path(__file__).resolve().with_name("interior_extent.tsv")


def load_extents(path: Path = EXTENT_TSV) -> dict:
    """file -> [(symbol, declared dims, true dims)] from interior_extent.tsv."""
    rows: dict = {}
    if not path.exists():
        return rows
    for ln in path.read_text(encoding="utf-8").splitlines():
        if not ln.strip() or ln.startswith("#") or ln.startswith("file\t"):
            continue
        c = ln.split("\t")
        rows.setdefault(c[0], []).append((c[1], c[2], c[3]))
    return rows


def apply_extents(text: str, rows) -> tuple[str, list[str]]:
    """Rewrite `D_x[from]` -> `D_x[to]` in every extern statement of the file (true extents);
    a row matching no declarator in either form is an error (stale row)."""
    errs = []
    if not rows:
        return text, errs
    code = X.blank(text)
    edits = []
    for sym, frm, to in rows:
        rx = re.compile(r"\b" + sym + r"\s*\[\s*([^\]]*?)\s*\]")
        hit = done = 0
        for m in EXTERN.finditer(code):
            for d in rx.finditer(code, m.start(), m.end()):
                if d.group(1) == frm:
                    edits.append((d.start(1), d.end(1), to))
                    hit += 1
                elif d.group(1) == to:
                    done += 1
        if not hit and not done:
            errs.append(f"{sym}: extent row [{frm}] -> [{to}] matches no extern declarator (stale)")
    for s, e, to in sorted(edits, reverse=True):
        text = text[:s] + to + text[e:]
    return text, errs


def _ev(x: str):
    x = x.strip()
    if not re.fullmatch(r"[0-9A-Fa-fxX+\-*/() \t]+", x or "?"):
        return None
    try:
        return int(eval(x, {"__builtins__": {}}, {}))
    except Exception:
        return None


def _declarators(body: str):
    """[(sym, size or None, simple)] of one extern statement body (after `extern`)."""
    m = re.match(r"\s*((?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+\w+\s+)*)(\w+)\s*", body)
    if not m or body.lstrip().startswith('"'):
        return []
    base = m.group(2)
    out = []
    for part in re.split(r",(?![^\[\(]*[\]\)])", body[m.end():]):
        part = part.strip()
        d = re.fullmatch(r"(\**)\s*(?:const\s+|volatile\s+)*(D_[0-9A-Fa-f]{8})\s*((?:\[[^\]]*\])*)", part)
        if not d:
            for s in SYM.findall(part):
                out.append((s, None, False))
            continue
        ptr, sym, dims = d.groups()
        esz = 4 if ptr else SCALAR.get(base)
        n = 1
        for x in re.findall(r"\[([^\]]*)\]", dims):
            v = _ev(x)
            if v is None:
                n = None
                break
            n *= v
        out.append((sym, n * esz if (n is not None and esz) else None, True))
    if not out and SYM.fullmatch(base or ""):
        pass
    return out


def analyse(text: str, extents=()):
    """(clean text, defines [(pos, B, A, off)], info dict).  extents: this file's
    interior_extent.tsv rows, applied to the declarators first."""
    text = OLD.sub("", text)
    text, ext_errs = apply_extents(text, extents)
    code = X.blank(text)
    stmts = [(m.start(), m.end(), m.group(0)) for m in EXTERN.finditer(code)]
    size, simple, last_decl = {}, {}, {}
    for s, e, st in stmts:
        for sym, sz, ok in _declarators(st[len("extern"):-1]):
            if sz is not None:
                size[sym] = max(size.get(sym, 0), sz)
            simple[sym] = simple.get(sym, True) and ok
            last_decl[sym] = e
    info = {"beyond": 0, "beyond_list": [], "pairs": 0, "pairs_unused": 0, "pairs_routed": 0,
            "uncovered": [], "skipped": [], "ifdef": [], "extent_errors": ext_errs, "size": size,
            "root": {}, "used": set()}
    if len(size) < 2 and len(simple) < 2:
        return text, [], info
    # uses: every mention outside extern statements (macro bodies count)
    mask = list(code)
    for s, e, _ in stmts:
        mask[s:e] = " " * (e - s)
    body = "".join(mask)
    uses = {}
    for m in SYM.finditer(body):
        if m.group(0) in simple:
            uses.setdefault(m.group(0), []).append(m.start())
    syms = sorted(simple, key=lambda s: int(s[2:], 16))
    addr = {s: int(s[2:], 16) for s in syms}
    # components of USED symbols whose declared extents overlap (a chain A[0x10], A+8[0x10],
    # A+0x10 is one component); every member is routed to the component's lowest address
    root, cur, end = {}, None, -1
    for s in syms:
        if s not in uses:
            continue
        if cur is not None and addr[s] < end:
            root[s] = cur
        else:
            cur = s
        end = max(end, addr[s] + (size.get(s) or 0))
    # pair census (overlapscan's pairs: A with a known size, B inside it)
    for i, A in enumerate(syms):
        sa = size.get(A)
        if not sa:
            continue
        for B in syms[i + 1:]:
            if addr[B] >= addr[A] + sa:
                break
            info["pairs"] += 1
            if A not in uses or B not in uses:
                info["pairs_unused"] += 1
            elif root.get(A, A) == root.get(B, B):
                info["pairs_routed"] += 1
    info["root"], info["used"] = root, set(uses)
    defs = []
    info["beyond"] = 0
    for B, A in root.items():
        if B not in uses:
            continue
        if not simple.get(B, False):
            info["skipped"].append(B)
            continue
        pos = max(last_decl[B], last_decl[A])
        nl = text.find("\n", pos)
        pos = len(text) if nl < 0 else nl + 1
        early = [u for u in uses[B] if u < pos]
        if early:
            info["uncovered"].append((B, len(early)))
        if addr[B] - addr[A] >= (size.get(A) or 0):
            info["beyond"] += 1
            info["beyond_list"].append((B, A, addr[B] - addr[A], size.get(A) or 0))
        defs.append((pos, B, A, addr[B] - addr[A]))
    # a define inside a conditional block would not always be seen
    if defs:
        depth = 0
        cond_at = []
        for m in re.finditer(r"(?m)^[ \t]*#[ \t]*(if|ifdef|ifndef|endif)\b", code):
            depth += 1 if m.group(1).startswith("if") else -1
            cond_at.append((m.start(), depth))
        for pos, B, _, _ in defs:
            d = 0
            for p, dd in cond_at:
                if p < pos:
                    d = dd
            if d > 0 and not text.startswith("#ifndef") and not re.match(r"\s*#\s*ifndef\s+\w+_H", text):
                info["ifdef"].append(B)
    return text, sorted(defs), info


def transform(text: str, extents=()):
    clean, defs, info = analyse(text, extents)
    if not defs:
        return clean, defs, info
    out, last = [], 0
    for pos, B, A, off in defs:
        nl = "\r\n" if clean[max(0, pos - 2):pos] == "\r\n" else "\n"
        out.append(clean[last:pos])
        out.append(f"#define {B} (*(__typeof__({B}) *)((u8 *)&{A} + 0x{off:X}))   {TAG}{nl}")
        last = pos
    out.append(clean[last:])
    return "".join(out), defs, info


def wanted(relpath: str) -> bool:
    return relpath.endswith((".c", ".cpp")) and "/main_data/" not in "/" + relpath


class InteriorStage:
    def __init__(self):
        self.rows: list[str] = []
        self.errors: list[str] = []
        self.census = {"files": 0, "defines": 0, "pairs": 0, "pairs_unused": 0,
                      "pairs_routed": 0, "skipped": 0, "uncovered": 0, "ifdef": 0, "beyond": 0,
                       "extent_rows": 0}
        self.off = bool(os.environ.get("RG_INGEST_NO_INTERIOR"))
        self.extents = load_extents()
        self.extent_seen: set = set()
        self.extent_sizes: dict = {}
        self.beyond_files: dict = {}

    def apply(self, relpath: str, data: bytes):
        if self.off or not wanted(relpath) or b"D_" not in data:
            return data, 0
        text = data.decode("utf-8", "surrogateescape")
        rows = self.extents.get(relpath, ())
        if rows:
            self.extent_seen.add(relpath)
        new, defs, info = transform(text, rows)
        for sym, _, _ in rows:
            self.extent_sizes[(relpath, sym)] = info["size"].get(sym)
        if info["beyond_list"]:
            self.beyond_files[relpath] = (defs, info)
        st = self.census
        st["extent_rows"] += len(rows)
        for e in info["extent_errors"]:
            self.errors.append(f"{relpath}: {e}")
        for B, A, off, sa in info["beyond_list"]:
            self.errors.append(f"{relpath}: {B}: chain member at {A} + 0x{off:X}, past the root's "
                               f"declared extent 0x{sa:X} (declarations, not data: a true-extent "
                               f"row in tools/stages/interior_extent.tsv; --propose-extents)")
        st["pairs"] += info["pairs"]
        st["pairs_unused"] += info["pairs_unused"]
        st["pairs_routed"] += info["pairs_routed"]
        st["beyond"] += info["beyond"]
        for B in info["skipped"]:
            st["skipped"] += 1
            self.errors.append(f"{relpath}: {B}: interior label with a declarator the stage cannot spell")
        for B, n in info["uncovered"]:
            st["uncovered"] += 1
            self.errors.append(f"{relpath}: {B}: {n} use(s) before the last declaration")
        for B in info["ifdef"]:
            st["ifdef"] += 1
            self.errors.append(f"{relpath}: {B}: define would land inside #if")
        if defs:
            st["files"] += 1
            st["defines"] += len(defs)
            for _, B, A, off in defs:
                self.rows.append(f"{relpath}\t{B}\t{A}\t0x{off:X}")
        return new.encode("utf-8", "surrogateescape"), len(defs)

    def finish_errors(self):
        """rows of interior_extent.tsv whose file the stage never saw (renamed / dropped)."""
        if self.off:
            return
        for f in sorted(set(self.extents) - self.extent_seen):
            self.errors.append(f"{f}: interior_extent.tsv row for a file the stage did not see (stale)")

    def extra_outputs(self):
        self.finish_errors()
        return {"INTERIOR.tsv": ("file\tlabel\troot\toffset\n" + "".join(r + "\n" for r in sorted(self.rows))).encode()}

    def report(self):
        s = self.census
        unrouted = s["pairs"] - s["pairs_unused"] - s["pairs_routed"]
        txt = (f"interior: {s['defines']} defines in {s['files']} files; overlapping declared pairs "
               f"{s['pairs']} = {s['pairs_routed']} routed to one root + {s['pairs_unused']} with an "
               f"unused side + {unrouted} unrouted; skipped {s['skipped']}, uncovered {s['uncovered']}, "
               f"in #if {s['ifdef']}; true-extent declarator rows {s['extent_rows']}; chain members past the "
               f"root's declared extent {s['beyond']} (must be 0)")
        if self.errors:
            txt += "\n" + "\n".join("  interior ERROR " + e for e in self.errors[:40])
        return txt


OVR_RX = re.compile(r"rg-override:\s*replaces\s+game/(\S+)\s+sha256\s+([0-9a-fA-F]{64})")


def _norm(t: str) -> str:
    t = OLD.sub("", t.replace("\r\n", "\n"))
    return t


def port_overrides(root: Path, old_game: Path, game: Path, orig: Path | None, retire: list[str],
                   write: bool) -> int:
    """Re-port overrides after the stage moved their game/ file: each STALE override whose old
    game/ file (old_game) is the recorded hash and whose new game/ file is exactly the stage's
    output of it gets the stage applied to its own text and the new hash.  An override whose
    body equals the new game/ file (header comment and EOL aside) is RETIRED (deleted): the
    stage does what it did (linuxrun's interiorfix overrides).  --retire names overrides retired
    although they differ (a hand edit the stage subsumes).  Prints one line per action."""
    import hashlib
    man = {}
    for ln in (game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        c = ln.split("\t")
        man[c[0]] = c[1]
    bad = 0
    for f in sorted((root / "overrides").rglob("*")):
        if not f.is_file() or f.suffix not in (".c", ".cpp"):
            continue
        rel = f.relative_to(root).as_posix()
        text = f.read_bytes().decode("utf-8", "surrogateescape")
        m = OVR_RX.search(text[:4096])
        if not m:
            continue
        target, want = m.group(1), m.group(2).lower()
        rows = load_extents().get(target, ())
        new_sha = man.get(target)
        gnew = (game / target).read_bytes().decode("utf-8", "surrogateescape")
        hdr_end = text.find("*/", m.start()) + 2
        body = text[hdr_end:].lstrip("\r\n")
        act = None
        if rel in retire or _norm(body) == _norm(gnew):
            act = "RETIRE"
        else:
            ported = transform(text, rows)[0]
            if new_sha != want:
                gold = (old_game / target).read_bytes()
                if hashlib.sha256(gold).hexdigest() != want:
                    print(f"STALE-OTHER {rel}: old game/ file is not the recorded hash (not this stage)")
                    bad += 1
                    continue
                if transform(gold.decode("utf-8", "surrogateescape"), rows)[0] != gnew:
                    print(f"STALE-OTHER {rel}: game/ moved by more than the interior stage")
                    bad += 1
                    continue
                ported = ported.replace(want, new_sha, 1)
                act = "REHASH+PORT" if transform(text, rows)[0] != text else "REHASH"
            elif ported != text:
                act = "PORT"
            text_new = ported
        if act is None:
            continue
        print(f"{act} {rel}")
        if not write:
            continue
        if orig is not None:
            o = orig / rel
            if not o.exists():
                o.parent.mkdir(parents=True, exist_ok=True)
                o.write_bytes(f.read_bytes())
        if act == "RETIRE":
            f.unlink()
        else:
            f.write_bytes(text_new.encode("utf-8", "surrogateescape"))
    return bad


def main() -> int:
    ap = argparse.ArgumentParser(description="dry run of the interior stage over a game/ tree")
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--file", action="append", default=[], help="transform one file (any path) to stdout")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--port-overrides", metavar="OLD_GAME",
                    help="after an ingest with the stage: re-port / retire overrides (OLD_GAME = "
                         "a copy of game/ from before it); dry run unless --write")
    ap.add_argument("--root", default=str(PORT), help="tree whose overrides/ to port")
    ap.add_argument("--retire", action="append", default=[], help="override path to retire anyway")
    ap.add_argument("--orig", help="save each touched override here first (lane orig dir)")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--check", action="store_true",
                    help="gate: exit 1 when a game/ file would change (generated without the stage), "
                         "on any error row, or on an unrouted overlapping pair (ctest protos.interior)")
    ap.add_argument("--propose-extents", action="store_true",
                    help="print candidate interior_extent.tsv rows for every component with a member "
                         "past the root's declared extent (data-layer extents + the file's uses)")
    ap.add_argument("--control", action="store_true",
                    help="the check must see a hazard: synthetic sources (ctest protos.interior_control)")
    a = ap.parse_args()
    if a.control:
        return control()
    if a.propose_extents:
        return propose_extents(Path(a.game))
    if a.port_overrides:
        return 1 if port_overrides(Path(a.root), Path(a.port_overrides), Path(a.game),
                                   Path(a.orig) if a.orig else None, a.retire, a.write) else 0
    if a.file:
        for f in a.file:
            sys.stdout.write(transform(Path(f).read_bytes().decode("utf-8", "surrogateescape"))[0])
        return 0
    g = Path(a.game)
    st = InteriorStage()
    changed = 0
    for p in sorted((g / "src").rglob("*")):
        if p.suffix not in (".c", ".cpp"):
            continue
        rel = p.relative_to(g).as_posix()
        data = p.read_bytes()
        new, n = st.apply(rel, data)
        if new != data:
            changed += 1
    st.finish_errors()
    ext_bad = check_extents(g, st)
    if a.list:
        print("\n".join(st.rows))
    print(st.report())
    for e in ext_bad:
        print("  interior ERROR " + e)
    print(f"files that would change: {changed}")
    c = st.census
    unrouted = c["pairs"] - c["pairs_unused"] - c["pairs_routed"]
    if a.check:
        ok = not st.errors and not ext_bad and unrouted == 0 and changed == 0 and c["beyond"] == 0
        print(f"interior check: {'PASS' if ok else 'FAIL'}")
        return 0 if ok else 1
    return 1 if (st.errors or ext_bad) else 0


BSS_LABEL = re.compile(r'RG_DR_SYM\((D_[0-9A-Fa-f]{8})\) ":\\n"|"\.zero (0x[0-9A-Fa-f]+|\d+)\\n"')


def data_extents(game: Path) -> dict:
    """symbol -> (bytes, what) from MAIN's data layer: a data2c object's size
    (`sizeof(D_x) == N`), or a bss label's span to the next label (data2c_bss.c)."""
    out: dict = {}
    md = game / "src" / "main_data"
    bss = md / "data2c_bss.c"
    if bss.exists():
        cur: list = []
        for m in BSS_LABEL.finditer(bss.read_text(encoding="utf-8", errors="replace")):
            if m.group(1):
                if cur and cur[-1][1] > 0:
                    cur = []
                cur.append([m.group(1), 0])
            elif cur:
                for c in cur:
                    c[1] += int(m.group(2), 0)
                    out[c[0]] = (c[1], "bss label span")
    for f in md.glob("data2c_*.c"):
        if not re.fullmatch(r"data2c_[0-9A-Fa-f]{8}", f.stem):
            continue
        sym = "D_" + f.stem[7:]
        t = f.read_text(encoding="utf-8", errors="replace")
        # the object (D_X, or data2c_fragment_X) and its asm alias names `D_Y = obj + off`
        # (an alias's extent: to the end of the object)
        for m in re.finditer(r"sizeof\((" + sym + r"|data2c_fragment_[0-9A-Fa-f]{8})\) == (\d+)", t):
            obj, n = m.group(1), int(m.group(2))
            if obj == sym:
                out[sym] = (n, "data2c object")
            for a in re.finditer(r"RG_DR_ASYM\((D_[0-9A-Fa-f]{8})\) \" = \" RG_DR_ASYM\(" + obj
                                 + r"\) \" \+ (0x[0-9A-Fa-f]+)", t):
                k = n - int(a.group(2), 16)
                if k > 0 and a.group(1) not in out:
                    out[a.group(1)] = (k, ("data2c object" if a.group(2) == "0x0" else "data2c object tail")
                                       + (" (fragment alias)" if obj != sym else " (alias)"))
    return out


def check_extents(game: Path, st: "InteriorStage") -> list[str]:
    """every interior_extent.tsv row: its true extent fits the data-layer object."""
    if not st.extents or st.off:
        return []
    ext = data_extents(game)
    bad = []
    for f, rows in sorted(st.extents.items()):
        for sym, frm, to in rows:
            have = st.extent_sizes.get((f, sym))
            d = ext.get(sym)
            if d is None:
                bad.append(f"{f}: {sym}: no data-layer extent to check the row against")
            elif have is None or have > d[0]:
                bad.append(f"{f}: {sym}: declared {have} bytes after the row > {d[1]} {d[0]}")
    return bad


def _decl_dims(code: str, sym: str) -> list[str]:
    """the bracket groups of sym's declarator in each extern statement of the file (blanked)."""
    rx = re.compile(r"\b" + sym + r"\s*((?:\[[^\]]*\])+)")
    return [d.group(1) for m in EXTERN.finditer(code) for d in [rx.search(m.group(0))] if d]


def scan_uses(body: str, sym: str, count: int, unit: int) -> tuple[list[str], list[str]]:
    """Every mention of sym in body (extern statements blanked): (problems, notes) for shrinking
    its first dimension to `count` elements of `unit` bytes.  Problems: a constant index >= count,
    a non-constant index, sizeof, pointer arithmetic on the bare name, a constant byte offset
    past count*unit.  Notes: bare-name uses (address passed / stored / dereferenced)."""
    probs, notes = [], []
    for m in re.finditer(r"\b" + sym + r"\b", body):
        pre = body[max(0, m.start() - 40):m.start()]
        if re.search(r"\bsizeof\s*\(?\s*$", pre):
            probs.append("sizeof")
            continue
        k = m.end()
        while k < len(body) and body[k] in " \t":
            k += 1
        if k < len(body) and body[k] == "[":
            e = X.match_close(body, k, "[", "]")
            ix = body[k + 1:e].strip()
            v = _ev(ix)
            if v is None:
                probs.append(f"index [{ix}]")
            elif v >= count and not (v == count and pre.rstrip().endswith("&")):
                probs.append(f"index [{ix}] >= {count}")
            continue
        # deref through a cast at offset 0: `*(T *)D_x` -- a value of T (arithmetic after it is
        # on the value); T must fit the true extent
        dc = re.search(r"(&\s*\(\s*)?\*\s*\(\s*((?:const\s+|volatile\s+|unsigned\s+|signed\s+)*\w+)\s*((?:\*\s*)+)\)\s*$", pre)
        if dc and not dc.group(1):
            stars = dc.group(3).count("*")
            tsz = 4 if stars > 1 else SCALAR.get(dc.group(2).split()[-1])
            if tsz is None:
                probs.append(f"deref ({dc.group(2)} *) of unknown size")
            elif tsz > count * unit:
                probs.append(f"deref ({dc.group(2)} *) {tsz} B > {count * unit} B")
            else:
                notes.append("deref")
            continue
        if pre.rstrip().endswith("*") and not dc:
            notes.append("deref")
            continue
        # address (bare name, a cast of it, or `&(*(T *)D_x)`): + / - after closing parens is
        # pointer arithmetic
        t = k
        while t < len(body) and body[t] in " \t)":
            t += 1
        a = re.match(r"([+-])\s*([^;,)\]]+)", body[t:t + 80])
        if a and body[t:t + 2] not in ("++", "--", "+=", "-=", "->"):
            v = _ev(a.group(2))
            if v is None or v != 0:
                probs.append(f"pointer arithmetic {a.group(1)} {a.group(2).strip()[:30]}")
                continue
        if body[t:t + 2] == "->" or (body[t:t + 1] == "." and not body[t + 1:t + 2].isdigit()):
            probs.append("member access through the address")
            continue
        why = _addr_context(body, m.start())
        if why:
            probs.append(why)
            continue
        notes.append("addr")
    return probs, notes


_KW = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case"}


def _addr_context(body: str, at: int) -> str | None:
    """Where an address use of a symbol goes: None when it leaves the file's view (an argument
    of a function not defined in this file, a store into memory, a return value, a comparison);
    a problem string when the file itself may dereference it past the true extent (assigned to
    a local, or passed to a function defined in this file)."""
    j, depth = at - 1, 0
    while j >= 0:
        c = body[j]
        if c in ")]":
            depth += 1
        elif c in "([":
            if depth == 0:
                if c == "[":
                    return None
                nm = re.search(r"(\w+)\s*$", body[:j])
                if nm and not nm.group(1).isdigit():
                    if nm.group(1) in _KW:
                        return None
                    if re.search(r"(?m)^[ \t]*#[ \t]*define[ \t]+" + nm.group(1) + r"\(", body):
                        return f"address passed to macro {nm.group(1)}(), defined in this file"
                    if re.search(r"(?m)^[A-Za-z_][\w \t*]*?\b" + nm.group(1) + r"\s*\([^;{}]*\)\s*\{", body):
                        return f"address passed to {nm.group(1)}, defined in this file"
                    return None
            else:
                depth -= 1
        elif c in ";{}" and depth == 0:
            break
        j -= 1
    stmt = body[j + 1:at]
    if re.match(r"\s*return\b", stmt):
        return None
    a = re.match(r"\s*([^=;]*?)\s*=(?!=)", stmt)
    if not a:
        return None
    lhs = a.group(1).strip()
    if re.fullmatch(r"\w+", lhs) or re.fullmatch(r"(?:const\s+)?\w+[\w\s]*?\**\s*\w+", lhs):
        return f"address assigned to local `{lhs}`"
    return None


def propose_extents(game: Path) -> int:
    """Candidate true-extent rows: in every file, each USED, array-declared symbol of an interior
    component whose declared extent is larger than its data-layer extent (data2c object size /
    bss label span) AND covers another used symbol past that extent (the over-declaration is what
    put it in the component), shrunk to the data-layer extent; each with a scan of the file's uses
    (scan_uses).  A row with a problem is printed commented (`#FLAG`): keep the declaration, or
    investigate.  Rows already in interior_extent.tsv are applied first (only new rows print)."""
    st = InteriorStage()
    files = []
    for p in sorted((game / "src").rglob("*")):
        if p.suffix in (".c", ".cpp"):
            rel = p.relative_to(game).as_posix()
            if wanted(rel) and b"D_" in p.read_bytes():
                files.append((rel, p))
    ext = data_extents(game)
    print("file\tsymbol\tfrom\tto\tevidence")
    for rel, p in files:
        text = p.read_bytes().decode("utf-8", "surrogateescape")
        text = apply_extents(OLD.sub("", text), st.extents.get(rel, ()))[0]
        _, defs, info = analyse(text)
        if not defs:
            continue
        code = X.blank(text)
        body = list(code)
        for m in EXTERN.finditer(code):
            body[m.start():m.end()] = " " * (m.end() - m.start())
        body = "".join(body)
        size, root, used = info["size"], info["root"], info["used"]
        ovr_body = None
        ovr = PORT / "overrides" / rel
        if ovr.exists():  # the override is what compiles: its uses must fit too
            ot = apply_extents(OLD.sub("", ovr.read_bytes().decode("utf-8", "surrogateescape")),
                               st.extents.get(rel, ()))[0]
            oc = X.blank(ot)
            ob = list(oc)
            for m in EXTERN.finditer(oc):
                ob[m.start():m.end()] = " " * (m.end() - m.start())
            ovr_body = "".join(ob)
        members = set(root) | set(root.values())
        addr = {s: int(s[2:], 16) for s in used}
        for s in sorted(members, key=lambda x: int(x[2:], 16)):
            sz, d = size.get(s), ext.get(s)
            if not sz or not d or d[0] >= sz:
                continue
            a0 = int(s[2:], 16)
            past = [t for t in used if a0 + d[0] <= addr[t] < a0 + sz]
            if not past:
                continue
            dims = _decl_dims(code, s)
            note = f"{d[1]} {d[0]} B; covers {','.join(sorted(past))}"
            if not dims:
                print(f"#NOROW {rel}\t{s}\t-\t-\t{note}; scalar declarator")
                continue
            first = re.match(r"\[([^\]]*)\]", dims[-1]).group(1).strip()
            n = _ev(first)
            if not n or sz % n:
                print(f"#NOROW {rel}\t{s}\t{first}\t-\t{note}; dims {dims[-1]}")
                continue
            unit = sz // n
            new = d[0] // unit
            if new == 0:
                print(f"#NOROW {rel}\t{s}\t{first}\t-\t{note}; element {unit} B > data extent")
                continue
            if d[0] % unit:
                note += f"; floor ({unit} B elements)"
            probs, notes = scan_uses(body, s, new, unit)
            if ovr_body is not None:
                probs += [f"override: {x}" for x in scan_uses(ovr_body, s, new, unit)[0]]
            note += f"; uses: {len(notes)} bare" + (f" ({','.join(sorted(set(notes)))})" if notes else "")
            to = str(new) if new < 10 else hex(new).upper().replace("0X", "0x")
            if len(set(dims)) > 1:
                probs.append(f"declarators differ {sorted(set(dims))}")
            if probs:
                print(f"#FLAG {rel}\t{s}\t{first}\t{to}\t{note}; PROBLEM {'; '.join(probs)}")
            else:
                print(f"{rel}\t{s}\t{first}\t{to}\t{note}")
    # every row (re-scanned with the current scan) and, when an override replaces its game file,
    # the override too (what compiles): #ROWFLAG / #OVRFLAG = drop the row, keep the declaration
    reviewed = {tuple(ln.split("\t")[:2]) for ln in EXTENT_TSV.read_text(encoding="utf-8").splitlines()
                if "reviewed:" in ln and not ln.startswith("#")}
    for rel, rows in sorted(st.extents.items()):
        for tag, ovr in (("ROWFLAG", game / rel), ("OVRFLAG", PORT / "overrides" / rel)):
            if not ovr.exists():
                continue
            text = apply_extents(OLD.sub("", ovr.read_bytes().decode("utf-8", "surrogateescape")), rows)[0]
            code = X.blank(text)
            body = list(code)
            for m in EXTERN.finditer(code):
                body[m.start():m.end()] = " " * (m.end() - m.start())
            body = "".join(body)
            size = analyse(text)[2]["size"]
            for sym, frm, to in rows:
                if tag == "ROWFLAG" and (rel, sym) in reviewed:
                    continue
                n, sz = _ev(to), size.get(sym)
                if not n or not sz:
                    continue
                probs, _ = scan_uses(body, sym, n, sz // n)
                if probs:
                    print(f"#{tag} {ovr.relative_to(PORT).as_posix()}\t{sym}\t{frm}\t{to}\tPROBLEM {'; '.join(probs)}")
    return 0


def control() -> int:
    """Synthetic sources: a store through an interior label + a load through the container must
    get a define; a 3-link chain routes to the lowest; a use before a later redeclaration is an
    error; a file already transformed is a fixed point."""
    src = ("extern u8 D_00400000[0x40];\r\nextern void *D_00400010[4];\r\n"
           "extern u8 D_00400100[0x10], D_00400108[0x10], D_00400110[0x10];\r\n"
           "void f(void) { D_00400010[0] = 0; g(D_00400000[0x10]); "
           "g(D_00400100[0] + D_00400108[0] + D_00400110[0]); }\r\n")
    out, defs, info = transform(src)
    want = {("D_00400010", "D_00400000", 0x10), ("D_00400108", "D_00400100", 8),
            ("D_00400110", "D_00400100", 0x10)}
    ok = ({(b, a_, o) for _, b, a_, o in defs} == want and transform(out)[0] == out
          and "\r\n#define D_00400010 " in out and info["beyond"] == 1)
    bad = ("extern u8 D_00400000[0x40];\nextern u8 D_00400010[4];\nvoid f(void){D_00400010[0]=1;}\n"
           "extern u8 D_00400010[4];\nint h(void){return D_00400000[0x10];}\n")
    ok = ok and transform(bad)[2]["uncovered"] == [("D_00400010", 1)]
    # past-extent member: the stage must ERROR on it (the chain above has one: D_00400110 at
    # D_00400100 + 0x10 = the root's whole declared extent) ...
    st = InteriorStage()
    st.off, st.extents = False, {}
    st.apply("src/x.c", src.encode())
    ok1 = st.census["beyond"] == 1 and any("past the root's declared extent" in e for e in st.errors)
    # ... true-extent rows dissolve it (8-byte objects: no overlap, no define), a stale row errors
    rows = [("D_00400100", "0x10", "8"), ("D_00400108", "0x10", "8")]
    out2, defs2, info2 = transform(src, rows)
    ok2 = ({(b, a_) for _, b, a_, _ in defs2} == {("D_00400010", "D_00400000")} and info2["beyond"] == 0
           and "D_00400100[8], D_00400108[8], D_00400110[0x10]" in out2 and not info2["extent_errors"]
           and transform(out2, rows)[0] == out2)
    ok3 = bool(transform(src, [("D_00400100", "0x20", "8")])[2]["extent_errors"])
    st2 = InteriorStage()
    st2.off, st2.extents = False, {"src/gone.c": rows}
    st2.finish_errors()
    ok3 = ok3 and len(st2.errors) == 1
    # the --propose-extents use scan (shrink D_00400100 to 2 elements of 4 B): each hazard
    # spelling is a problem, each in-extent / opaque use is not
    probe = {
        "D_00400100[1] = 0;": False, "D_00400100[2] = 0;": True, "x = D_00400100[i];": True,
        "x = *(s32 *)D_00400100 - 1;": False, "x = *(u128 *)D_00400100;": True,
        "x = *(s32 *)(D_00400100 + i * 4);": True, "g(&(*(u8 *)D_00400100));": False,
        "o->p = D_00400100;": False, "u8 *q = D_00400100;": True, "((T *)D_00400100)->f();": True,
        "n = sizeof(D_00400100);": True, "M(D_00400100);": True, "h(D_00400100);": True,
    }
    hdr = "#define M(x) (*(s32 *)(x))\nvoid h(u8 *p) { }\n"
    miss = [k for k, want in probe.items() if bool(scan_uses(hdr + k, "D_00400100", 2, 4)[0]) != want]
    ok4 = not miss
    print(f"interior control: past-extent error {'ok' if ok1 else 'MISSED'}, true-extent rows "
          f"{'ok' if ok2 else 'WRONG'}, stale rows {'ok' if ok3 else 'MISSED'}, use scan "
          f"{'ok' if ok4 else 'WRONG ' + str(miss)}")
    ok = ok and ok1 and ok2 and ok3 and ok4
    print(f"interior control: {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())

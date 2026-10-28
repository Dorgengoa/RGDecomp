#!/usr/bin/env python3
"""Ingest stage `spin`: give every busy-wait loop the census found a defined
point where virtual time passes (docs/SPIN.md).

The EE kernel HLE (docs/KERNEL.md) is non-preemptive and its clock moves only
at kernel calls / ps2k_poll / ps2k_charge or when every thread is blocked.  A
loop that waits for an interrupt handler, another thread or the IOP to change
memory therefore never terminates on the host.  This stage is TABLE-DRIVEN:
it instruments exactly the loops listed in census/spin_loops.tsv with a
non-empty `hint` column (classes HANDLER-FLAG / REVIEW -> `hint`, HALT ->
`halt`), nothing else.

Rewrite (in the loop's controlling expression, AFTER the condition, so the
call runs once per iteration that actually continues -- a loop whose flag is
already set costs nothing -- whatever `continue`/`goto` paths the body
takes; no statement parsing needed):

    while (c)            ->  while ((c) && (rg_spin_hint(SITE), 1))
    do {..} while (c);   ->  do {..} while ((c) && (rg_spin_hint(SITE), 1));
    for (i; c; s)        ->  for (i; (c) && (rg_spin_hint(SITE), 1); s)
    for (i;; s)          ->  for (i; (rg_spin_hint(SITE), 1); s)
    label:  (goto loop)  ->  label: rg_spin_hint(SITE);
    HALT loops use rg_spin_halt(SITE) instead: it is reached only when the
    loop really iterates, i.e. when retail would hang for good.

SITE = (image index << 28) | retail loop-head address, so a report names the
retail instruction.  One declaration line is prepended to an instrumented
file (`extern "C"` in C++), so the stage needs no header of its own; when
include/port grows a port/spin.h the declaration can move there.

Loop location is robust to earlier stages moving lines: the table gives
(file, symbol, line, src_loop); the stage finds the function by name, lists
its loops (same parser as the census), and takes the loop whose kind and
normalised header text match, nearest to the table line.  Lines are
PRESUMED lines (`#line` honoured): the protos preamble ends in `#line 1` and
the declaration this stage prepends is followed by `#line 1`, so the table's
2efa6b43 line numbers stay exact and diagnostics keep them.  A row that does
not match exactly one loop is an error (reported in `report()`), never a
guess.  Idempotent: an already-instrumented loop is left alone.

Use from tools/ingest.py (not wired in yet -- ingest.py is owned elsewhere):

    sys.path.insert(0, str(Path(__file__).resolve().parent / "stages"))
    import spin
    SPIN = spin.SpinStage()                    # reads census/spin_loops.tsv
    STAGES.append(Stage("spin", SPIN, ("unit",)))   # after asmexclude
    ... after the loop: print(SPIN.report())

Standalone test on a copy of game/:

    python tools/stages/spin.py --game game --out out/spin-test
"""
from __future__ import annotations

import argparse
import csv
import re
import shutil
import sys
from dataclasses import dataclass, field
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
sys.path.insert(0, str(PORT / "tools" / "census"))
import portxform as X  # noqa: E402  (read-only reuse: blank, find_funcs)
import spin_loops as SL  # noqa: E402  (read-only reuse: src_loops)

TABLE = PORT / "census" / "spin_loops.tsv"
MARK = "/* rgp:spin */"
DECL_C = (MARK + " extern void rg_spin_hint(unsigned int); "
          "extern void rg_spin_halt(unsigned int);\n#line 1\n")
DECL_CXX = (MARK + ' extern "C" void rg_spin_hint(unsigned int); '
            'extern "C" void rg_spin_halt(unsigned int);\n#line 1\n')
HINT_RX = re.compile(r"\brg_spin_(hint|halt)\((0x[0-9A-Fa-f]+)\)")


@dataclass
class Site:
    file: str
    symbol: str
    line: int
    kind: str          # while | for | do | label
    header: str        # normalised condition text from the table
    site: int
    fn: str            # rg_spin_hint | rg_spin_halt
    cls: str


@dataclass
class SpinStage:
    table: Path = TABLE
    sites: dict = field(default_factory=dict)       # file -> [Site]
    done: list = field(default_factory=list)        # (Site, how)
    errors: list = field(default_factory=list)      # (Site, why)

    def __post_init__(self):
        rows = [ln for ln in self.table.read_text(encoding="utf-8").splitlines()
                if not ln.startswith("#")]
        rd = csv.DictReader(rows, delimiter="\t")
        for r in rd:
            if not r.get("hint"):
                continue
            kind, _, hdr = r["src_loop"].partition(":")
            s = Site(r["file"], r["symbol"], int(r["line"] or 0), kind, norm(hdr),
                     int(r["site"], 16),
                     "rg_spin_halt" if r["hint"] == "halt" else "rg_spin_hint", r["cls"])
            self.sites.setdefault(s.file, []).append(s)

    # ingest Stage interface: apply(relpath, data) -> (data, sites)
    def __call__(self, relpath: str, data: bytes) -> tuple[bytes, int]:
        todo = self.sites.get(relpath)
        if not todo:
            return data, 0
        text = data.decode("utf-8", errors="surrogateescape")
        edits = []                       # (offset, insert_text) or (lo, hi, repl)
        n = 0
        code = SL.blank(text)
        funcs = X.find_funcs(code)
        for s in todo:
            fn = [f for f in funcs if f.name.split("::")[-1] == s.symbol]
            if len(fn) != 1:
                self.errors.append((s, f"function found {len(fn)}x"))
                continue
            f = fn[0]
            if f"{s.fn}(0x{s.site:08X})" in text[f.body_open:f.body_close]:
                self.done.append((s, "already"))
                continue
            loops = SL.src_loops(code, f.body_open, f.body_close)
            cands = []
            for lp in loops:
                if lp[0] != s.kind:
                    continue
                hdr = text[lp[2]:lp[3] + 1]
                if not norm(hdr).startswith(s.header):
                    continue
                line = presumed_line(text, lp[1])
                cands.append((abs(line - s.line), lp))
            if not cands:
                # an earlier stage may have respelled the header (protos renames
                # address-style callees to their MAIN symbol and drops extra
                # arguments): accept the ONE loop of this kind on the table's
                # exact line (protos keeps line numbers)
                same = [lp for lp in loops if lp[0] == s.kind
                        and presumed_line(text, lp[1]) == s.line]
                if len(same) == 1:
                    cands = [(0, same[0])]
            if not cands:
                self.errors.append((s, "no loop with that header"))
                continue
            cands.sort(key=lambda c: c[0])
            if len(cands) > 1 and cands[0][0] == cands[1][0]:
                self.errors.append((s, "ambiguous loop"))
                continue
            lp = cands[0][1]
            call = f"{s.fn}(0x{s.site:08X})"
            e = rewrite(text, code, s.kind, lp, call)
            if e is None:
                self.errors.append((s, "cannot rewrite header"))
                continue
            edits.extend(e)
            self.done.append((s, s.kind))
            n += 1
        if not edits and MARK in text:
            return data, 0
        for e in sorted(edits, key=lambda e: e[0], reverse=True):
            lo, hi, rep = e
            text = text[:lo] + rep + text[hi:]
        if n and MARK not in text:
            text = (DECL_CXX if relpath.endswith(".cpp") else DECL_C) + text
        return text.encode("utf-8", errors="surrogateescape"), n

    apply = __call__

    def report(self) -> str:
        out = [f"spin: {sum(1 for _, h in self.done if h != 'already')} loops instrumented, "
               f"{sum(1 for _, h in self.done if h == 'already')} already present "
               f"({sum(1 for s, _ in self.done if s.fn == 'rg_spin_halt')} halt), "
               f"{len(self.errors)} errors"]
        for s, why in self.errors:
            out.append(f"    ERROR {s.file}:{s.line} {s.symbol} 0x{s.site:08X}: {why}")
        return "\n".join(out)


LINE_RX = re.compile(r"^[ \t]*#[ \t]*line[ \t]+(\d+)", re.M)


def presumed_line(text: str, off: int) -> int:
    """The line number a compiler reports for `off`: honours `#line N`
    directives, so a preamble an earlier stage prepends (protos: defines,
    an #include and `#line 1`) does not move the table's line numbers."""
    base, start = 1, 0
    for m in LINE_RX.finditer(text, 0, off):
        nl = text.find("\n", m.end())
        if nl < 0 or nl >= off:
            break
        base, start = int(m.group(1)), nl + 1
    return base + text.count("\n", start, off)


def norm(s: str) -> str:
    return re.sub(r"\s+", "", s)


def split_for(code: str, lo: int, hi: int):
    """Offsets of the two top-level `;` inside a for(...) header [lo, hi]."""
    depth, semis = 0, []
    for k in range(lo + 1, hi):
        ch = code[k]
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == ";" and depth == 0:
            semis.append(k)
    return semis if len(semis) == 2 else None


def rewrite(text: str, code: str, kind: str, lp, call: str):
    kw, kwo, clo, chi, blo, bhi = lp
    if kind == "label":
        # `label:` -> `label: call;` (insert right after the colon)
        return [(chi + 1, chi + 1, " " + call + ";")]
    if kind in ("while", "do"):
        inner = text[clo + 1:chi]
        if re.match(r"\s*(?:const\s+)?[A-Za-z_][\w:<>]*\s*\*?\s+[A-Za-z_]\w*\s*=", inner) \
                and not re.match(r"\s*\w+\s*(==|!=)", inner):
            return None                    # C++ condition declaration
        return [(clo + 1, chi, f"({inner.strip()}) && ({call}, 1)")]
    if kind == "for":
        semis = split_for(code, clo, chi)
        if semis is None:
            return None
        a, b = semis
        cond = text[a + 1:b]
        new = f" ({cond.strip()}) && ({call}, 1)" if cond.strip() else f" ({call}, 1)"
        return [(a + 1, b, new)]
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description="apply stage `spin` to a copy of game/")
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--out", type=Path, default=PORT / "out" / "spin-test")
    ap.add_argument("--table", type=Path, default=TABLE)
    ap.add_argument("--full", action="store_true", help="copy all of game/ (slow)")
    a = ap.parse_args()
    st = SpinStage(a.table)
    if a.out.exists():
        shutil.rmtree(a.out)
    if a.full:
        shutil.copytree(a.game, a.out)
    else:                       # what a syntax check of the changed files needs
        for sub in ("include", "config"):
            shutil.copytree(a.game / sub, a.out / sub)
        for f in ("MANIFEST.tsv", "SNAPSHOT.txt", "EXCLUDED.tsv"):
            shutil.copy2(a.game / f, a.out / f)
        for rel in st.sites:
            (a.out / rel).parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(a.game / rel, a.out / rel)
    changed = 0
    for rel in sorted(st.sites):
        p = a.out / rel
        if not p.exists():
            st.errors.append((st.sites[rel][0], "file missing"))
            continue
        data = p.read_bytes()
        new, n = st(rel, data)
        again, n2 = SpinStage(a.table)(rel, new)    # idempotence check
        if again != new or n2:
            st.errors.append((st.sites[rel][0], "NOT idempotent"))
        if new != data:
            p.write_bytes(new)
            changed += 1
    print(st.report())
    print(f"files changed: {changed}")
    return 1 if st.errors else 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Ingest stage `wideret` (before protos): a MAIN definition typed with a 4-byte integer
return whose retail `$v0` at `jr $31` is a 64-bit value returns `long long`, and the
4-byte locals that carry the value there (accumulators `v |= F(..)`, copies) and the
listing-less static helpers it flows through become 8-byte (docs/PROTOS.md "wideret",
BRINGUP.md "User play-test 2", item 2).

Why: the EE's GPRs are 64 bits and mwcc never narrows a register for a C conversion to a
4-byte integer, so `s32 r = 0; r |= ActTimePrmtGetFlags(..);  return r;` returns all 64
bits (`or $16,$16,$2` ... `daddu $2,$16,$0`).  The decomp spells such functions with s32
(the bytes are the same); the port's s32 cuts the high word.  The protos stage's own
wide-ret rule handles one level (a 4-byte definition returning an 8-byte call result that
a caller reads whole); this stage handles the chains and accumulators it cannot see, and
runs before protos so the unified prototypes (and the callers' header) follow.

Found in play-test 2: the ActCfg PENDING prmt / cmnd mask chain
(CharaTableDataCollectPendingPrmtFlags_2267f0 -> ActCfgTableEvalPendingPrmtFlags_221380 /
..Refs_221040 / ActCfgTableEvalNormalPendingPrmtFlags_2217a0) dropped bits 32-63, so the
battle command bits (SQUARE gun 1<<56, CROSS sword 1<<55, ..) were never kept in Chara +0x568
across an action's recovery: a press during the recovery was lost (retail fires it when the
recovery ends: 16-VBlank gun cadence; the port 18-20 with dropped presses).

Detection (the same as tools/bringup/wideret_census.py): asmflow.wide_flow over each MAIN
listing whose C definition returns s32 / u32 / int (non-static), with `ld`/`lq`/`dsll32` and
calls to 8-byte-returning definitions as sources, iterated to a fixpoint.  Rewrites in the
definition's file: the return type; 4-byte locals assigned or OR/AND/XOR-accumulated from a
wide call or a wide local (fixpoint); a static helper `H` whose value reaches a wide local or
the return gets the same treatment.  RG_PROTOS_NO_WIDERET=1 disables the stage.

Standalone dry run on game/:  python tools/stages/wideret.py --game game
"""
from __future__ import annotations

import argparse
import os
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import portxform as X  # noqa: E402
import asmflow  # noqa: E402

WIDE_T = r"(?:long\s+long|unsigned\s+long\s+long|signed\s+long\s+long|s64|u64)"
INT4_T = r"(?:s32|u32|int|unsigned\s+int|unsigned|signed\s+int|signed)"
_HEAD = re.compile(r"^(?P<pre>[ \t]*(?:extern\s+\"[ C]\"\s+)?(?P<st>(?:(?:static|inline|__inline)\s+)*))"
                   r"(?P<t>" + WIDE_T + "|" + INT4_T + r")(?P<sp>\s+)(?P<n>[A-Za-z_]\w*)\s*\(", re.M)


def _code(text: str) -> str:
    return X.blank_pp(X.blank(text))


def _close(code: str, i: int, o="(", c=")") -> int:
    depth = 0
    for k in range(i, len(code)):
        if code[k] == o:
            depth += 1
        elif code[k] == c:
            depth -= 1
            if depth == 0:
                return k
    return -1


def defs_of(code: str):
    """[(name, type, static, type span, body_open, body_close)]"""
    out = []
    for m in _HEAD.finditer(code):
        lp = m.end() - 1
        rp = _close(code, lp)
        if rp < 0:
            continue
        k = rp + 1
        while k < len(code) and code[k] in " \t\r\n":
            k += 1
        if k < len(code) and code[k] == "{":
            bc = X.match_close(code, k)
            out.append((m.group("n"), re.sub(r"\s+", " ", m.group("t")), "static" in m.group("st"),
                        (m.start("t"), m.end("t")), k, bc))
    return out


def wide_type(t: str) -> str:
    return "unsigned long long" if t.startswith("u") or t.startswith("unsigned") else "long long"


class WideRetStage:
    def __init__(self):
        self.addr_table = None
        self.plan: dict[str, set] = {}     # rel -> names of wide defs in that file
        self.wide_fns: set = set()         # every 8-byte-returning name (C types + found)
        self.found: list = []
        self.errors: list = []
        self.rows: list = []

    # ---- detection over the corpus + listings
    def prepare(self, files: dict) -> None:
        if os.environ.get("RG_PROTOS_NO_WIDERET") or not self.addr_table:
            return
        lst = self.addr_table.get("asm_text") or {}
        rets = {}
        for rel, data in files.items():
            if not rel.endswith((".c", ".cpp")) or not rel.startswith("src/main/"):
                continue
            code = _code(data.decode("utf-8", "replace"))
            for n, t, st, _, _, _ in defs_of(code):
                rets.setdefault(n, (t, st, rel))
        wide = {n for n, (t, _, _) in rets.items() if re.fullmatch(WIDE_T, t)}
        cfgs = {}
        found = {}
        for _ in range(10):
            changed = False
            for fn, (t, st, rel) in rets.items():
                if fn in wide or st or fn not in lst or not re.fullmatch(INT4_T, t):
                    continue
                if fn not in cfgs:
                    try:
                        cfgs[fn] = asmflow.CFG(asmflow.parse_listing(lst[fn])[0])
                    except Exception:   # noqa: BLE001
                        cfgs[fn] = None
                if cfgs[fn] is None:
                    continue
                ev = asmflow.wide_flow(cfgs[fn], {}, gen_ret=lambda tgt: "w" if tgt in wide else None)
                if any(e[0] == "ret" for e in ev):
                    wide.add(fn)
                    found[fn] = rel
                    changed = True
            if not changed:
                break
        self.wide_fns = wide
        for fn, rel in found.items():
            self.plan.setdefault(rel, set()).add(fn)
        self.found = sorted(found)

    # ---- rewrite of one file
    def apply(self, rel: str, data: bytes) -> tuple[bytes, int]:
        names = self.plan.get(rel)
        if not names:
            return data, 0
        text = data.decode("utf-8", "surrogateescape")
        code = _code(text)
        dl = defs_of(code)
        byname = {d[0]: d for d in dl}
        wide_defs = set(n for n in names if n in byname)
        rws = {}          # start -> (end, new)
        wide_all = set(self.wide_fns)
        done_locals = {}
        work = list(wide_defs)
        while work:
            n = work.pop()
            name, t, st, (ta, tb), bo, bc = byname[n]
            if re.fullmatch(INT4_T, t):
                rws[ta] = (tb, wide_type(t))
            wide_all.add(n)
            body = code[bo:bc]
            locs = done_locals.setdefault(n, set())
            # fixpoint over the body's locals
            for _ in range(8):
                grew = False
                srcs = [re.escape(x) for x in wide_all] + [re.escape(x) for x in locs]
                if not srcs:
                    break
                src_re = re.compile(r"\b(?:" + "|".join(sorted(srcs, key=len, reverse=True)) + r")\b")
                for m in re.finditer(r"(?<![\w.>\]])([A-Za-z_]\w*)\s*([|^&]?=)(?!=)([^;]*);", body):
                    v, rhs = m.group(1), m.group(3)
                    if v in locs or not src_re.search(rhs):
                        continue
                    dm = re.search(r"(?<![\w*])(" + INT4_T + r")\s+" + re.escape(v) + r"\s*(?:=[^;,]*)?;", body)
                    if dm is None:
                        continue
                    locs.add(v)
                    grew = True
                    rws[bo + dm.start(1)] = (bo + dm.end(1), wide_type(dm.group(1)))
                # static helpers whose value reaches a wide local or the return
                for h, hd in byname.items():
                    if h in wide_all or not hd[2] or not re.fullmatch(INT4_T, hd[1]):
                        continue
                    pat = re.compile(r"(?:(?:\b(?:" + "|".join(re.escape(x) for x in locs) + r")\b\s*[|^&]?=)|\breturn\b)"
                                     r"[^;]*\b" + re.escape(h) + r"\s*\(") if locs else re.compile(
                                         r"\breturn\b[^;]*\b" + re.escape(h) + r"\s*\(")
                    if pat.search(body):
                        wide_all.add(h)
                        work.append(h)
                        grew = True
                if not grew:
                    break
            self.rows.append((rel, n, sorted(locs)))
        if not rws:
            return data, 0
        out, pos = [], 0
        for a in sorted(rws):
            b, new = rws[a]
            out.append(text[pos:a])
            out.append(new)
            pos = b
        out.append(text[pos:])
        return "".join(out).encode("utf-8", "surrogateescape"), len(wide_defs)

    def report(self) -> str:
        return (f"wideret: {len(self.found)} definitions return a 64-bit $v0: " + ", ".join(self.found)
                + "".join(f"\n  {rel}: {n} locals {','.join(l) or '-'}" for rel, n, l in self.rows))


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--show", help="print the rewrite of one file (relative to --game)")
    a = ap.parse_args(argv)
    sys.path.insert(0, str(PORT / "tools" / "bringup"))
    import listings  # noqa: E402
    root = Path(a.game)
    files = {p.relative_to(root).as_posix(): p.read_bytes()
             for p in root.rglob("*") if p.suffix in (".c", ".cpp")}
    st = WideRetStage()
    st.addr_table = listings.table()
    st.prepare(files)
    for rel in sorted(st.plan):
        new, _ = st.apply(rel, files[rel])
        if a.show == rel:
            print(new.decode("utf-8", "replace"))
    print(st.report())
    return 0


if __name__ == "__main__":
    sys.exit(main())

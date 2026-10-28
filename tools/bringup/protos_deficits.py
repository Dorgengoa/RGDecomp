# SPDX-License-Identifier: CC0-1.0
"""protos_deficits.py: calls that still pass FEWER arguments than the callee's definition.

The protos stage patches a short call only when the callee is in include/port/game_protos.h.
A callee whose definition takes a by-value struct / union (or 128-bit / unknown type) stays
out of the header, so a caller's own short declaration is left as is (`manual-decl` "count N
vs M" + `manual-call` rows in game/PROTOS.tsv).  On i686 the callee then reads a stale stack
word for each missing parameter; retail passed whatever the MIPS register held (often the
caller's own entry argument).  Found 2026-10-25: HandleTableGet_1a1d50 lost its handle in
four effect units -> EffTableDestroyAll_1a0240 spun forever (Insectron return to title) and
EffResGetNameMaybe_1a83d0 faulted under RG_IOP=hle (BRINGUP-HISTORY 2026-10-25 (stream close)).

    python tools/bringup/protos_deficits.py [--game game] [--all] [--ignore-overrides]

Lists every (file, callee) whose declaration is short AND which the file really calls (a
`manual-call` row; address-only uses in data tables are skipped), and whether an override
replaces the file already.  Also the same family through a struct return: a view that
returns a struct BY VALUE (`ret Iter vs int`) against a definition that returns a scalar or
nothing: on the EE that struct came back through a hidden out pointer in $a0 (the
definition's first parameter), i686/MSVC returns a <= 8-byte struct in EAX:EDX, so every
argument lands one slot off (OstreamWriteBool_1b2710 / OstreamWriteFloat_1b25c0, 2026-10-25).
--all: also the address-only rows.  Exit 1 when an un-overridden call site is left (ctest
`protos.deficits`; `--ignore-overrides` is its control, which must fail).

2026-10-25 (protos manual-row close-out, docs/PROTOS.md "Manual rows closed"), two more checks:

  --manual   every manual / unresolved row of PROTOS.tsv (manual-call, manual-decl,
             missing-zero, manual-missing, void-value-zero, vcall, stack-block, ...) has a
             reviewed verdict in census/protos_manual.tsv (tools/bringup/protos_manual.py) and
             none is BUG; a `fixed-override` verdict needs its override (--ignore-overrides:
             counted as open).  ctest `protos.manual` (+ `protos.manual_control`).
  --ir BUILD every manual-call / manual-decl pair compiled to clang IR with the build's own
             commands (tools/bringup/protos_irabi.py): the caller's call vs the definition's
             i686 signature (stack words, over-aligned aggregates passed by address, return
             width / class, sret).  A BUG verdict fails unless the file is overridden or the
             row is hand-reviewed OK in protos_manual.REVIEWED.  ctest `protos.irabi`
             (+ `protos.irabi_control`, --ignore-overrides: the game file's own
             StringReplaceRange_1b3da0 view of NumPutFixedZeroStrMaybe_1b3c90 must fail).
"""
import argparse
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
# the stage's normalised scalar spellings (protos.py `_abi_diff` / T.c)
SCALARS = {"void", "int", "char", "short", "long", "float", "double", "bool", "unsigned",
           "signed", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64"}


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--ignore-overrides", action="store_true",
                    help="control: treat every site as un-overridden")
    ap.add_argument("--overrides", default=str(PORT / "overrides"))
    ap.add_argument("--manual", action="store_true",
                    help="check the reviewed verdict table (census/protos_manual.tsv)")
    ap.add_argument("--table", default=str(PORT / "census" / "protos_manual.tsv"))
    ap.add_argument("--ir", metavar="BUILD", help="IR ABI check of the manual call pairs")
    ap.add_argument("--cache", default=None, help="--ir: IR cache dir (default BUILD/protos/ir)")
    a = ap.parse_args(argv)
    if a.manual:
        return check_manual(a)
    if a.ir:
        return check_ir(a)
    rows = [l.rstrip("\n").split("\t") for l in open(Path(a.game) / "PROTOS.tsv", encoding="utf-8")][1:]
    calls = {(r[0], r[2]) for r in rows if len(r) > 3 and r[3] == "manual-call"}
    open_sites = 0
    for r in rows:
        if len(r) < 5 or r[3] != "manual-decl":
            continue
        m = re.match(r"count (\d+) vs (\d+)", r[4])
        rs = re.search(r"(?:^|, )ret (\w+) vs (\w+)", r[4].split(":", 1)[0])
        short = bool(m) and int(m.group(1)) < int(m.group(2))
        sret = bool(rs) and rs.group(1) not in SCALARS and rs.group(2) in SCALARS
        if not short and not sret:
            continue
        called = (r[0], r[2]) in calls
        if not called and not a.all:
            continue
        ovr = (Path(a.overrides) / r[0]).exists() and not a.ignore_overrides
        state = "override" if ovr else ("OPEN" if called else "address-only")
        if called and not ovr:
            open_sites += 1
        what = []
        if short:
            what.append(f"{m.group(1)} of {m.group(2)} args")
        if sret:
            what.append(f"returns {rs.group(1)} by value, definition {rs.group(2)}: sret")
        print(f"{state:12} {r[0]}:{r[1]}  {r[2]}  ({'; '.join(what)})")
    print(f"protos_deficits: {open_sites} call site(s) without an override")
    return 1 if open_sites else 0


def check_manual(a) -> int:
    sys.path.insert(0, str(PORT / "tools" / "bringup"))
    import protos_manual
    rows = [l.rstrip("\n").split("\t") for l in open(Path(a.game) / "PROTOS.tsv", encoding="utf-8")][1:]
    rows = [r for r in rows if len(r) >= 5 and r[3] in protos_manual.RULES]
    t = {}
    for r in protos_manual.load_tsv(a.table):
        t.setdefault((r["file"], r["callee"], r["rule"]), []).append(r["verdict"])
    bad = 0
    for f, line, callee, rule, _d in (r[:5] for r in rows):
        vs = t.get((f, callee, rule))
        ovr = (Path(a.overrides) / f).exists() and not a.ignore_overrides
        why = None
        if not vs:
            why = "UNREVIEWED (run tools/bringup/protos_manual.py, review, commit the table)"
        elif "BUG" in vs or "needs-retail-check" in vs:
            why = "open verdict " + "/".join(sorted(set(vs)))
        elif "fixed-override" in vs and not ovr:
            why = "fixed-override without its override"
        if why:
            bad += 1
            print(f"OPEN  {rule} {f}:{line} {callee}: {why}")
    print(f"protos_deficits --manual: {len(rows)} manual row(s), {bad} open")
    return 1 if bad else 0


def check_ir(a) -> int:
    sys.path.insert(0, str(PORT / "tools" / "bringup"))
    import protos_irabi
    import protos_manual
    cache = a.cache or str(Path(a.ir) / "protos" / "ir")
    res = protos_irabi.analyse(Path(a.game), a.ir, cache, 2, ("manual-call", "manual-decl"),
                               a.ignore_overrides)
    bad = 0
    for f, callee, v, df, calls, why, shapes in res:
        if not v.startswith("BUG"):
            continue
        rv = [protos_manual.REVIEWED.get((ru, f, callee)) for ru in ("manual-call", "manual-decl")]
        if any(x and x[0] == "OK" for x in rv):
            print(f"ok    {f} {callee}: {v} reviewed OK ({why})")
            continue
        bad += 1
        print(f"BUG   {f} {callee}: {v}: {why} [{shapes}]")
    print(f"protos_deficits --ir: {len(res)} (file, callee) pair(s), {bad} ABI difference(s)")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

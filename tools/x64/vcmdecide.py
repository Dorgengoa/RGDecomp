#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""vcmdecide.py: Win64 verdict for every devirt slot call (docs/X64-PLAN.md 0.4 / 0.11).

i686 cdecl passes argument k in stack word k whatever its class, so a slot call
whose view says `s32` where a target reads `f32` (or the reverse) still hands the
target the same 4 bytes.  Win64 passes argument k < 4 in RCX/RDX/R8/R9 when the
CALLER types it as an integer / pointer and in XMM0-3 when it types it as a float:
the same disagreement makes the target read an unrelated register.  (Arguments 5+
are 8-byte stack slots: a float read from an integer slot is the low 4 bytes, as
on i686.)  winabi_census.py lists the slot calls whose view disagrees with SOME
function found at that table offset in some vtable; the offset alone does not
tell which of those functions the call can reach.

Method (retail is the truth for the target set; f32args.py machinery):
  * port side: every devirt thunk (VCM / VCM0 / VCMQ / VCM_FN) of game/src/**/*.cpp
    and the game/include/*.h thunks a file calls: slot offset S, the vptr offset
    of the thunk's class, the view's parameter types;
  * retail side: the vtable jalr sites of the file's definitions with
    `lw $25, S($25)` and that vptr offset; their targets = slot S of every vtable
    retail code stores at +V of an object (sbresolve.Resolver.vcall_targets: table
    lengths, vptr stores, and a target is PLAUSIBLE only when every argument lane
    it reads is live at the jalr);
  * per plausible target: its C prototype; the positions k (1..3) whose lane the
    target reads (retail listing) and whose Win64 class differs from the view's.

Verdicts per thunk:
  safe        every plausible target agrees with the view at every register
              position it reads (or the view has no float and no target a float)
  cast        some target disagrees, and all plausible targets agree with each
              other: a view typed like the targets would be correct (the caller's
              value is passed with its bits reinterpreted, as on i686)
  poly        plausible targets disagree with each other at a register position:
              no single prototype is right for every target
  unresolved  no retail jalr paired with the thunk (thunk of a header / an
              unpaired call / too many candidate tables) -- judged by the table
              candidates at the offset (winabi_census): `unresolved-agree` when
              every table function at the offset agrees with the view
A `cast` / `poly` / `unresolved` row fails --check (ctest x64.vcmdecide; its control
x64.vcmdecide_control flips each view's first parameter class and must fail).
Result 2026-11-01 (lane x64d): every thunk safe (1,491 by retail targets, 17 by the
vtable the file itself stores, 14 by every table function at the offset); no stage
change needed.  Remedy if a row ever appears: type the view like its targets (cast,
in protos/devirt, both arches) or, for poly, call it with DUAL lanes on x64: every
argument as a 64-bit pattern through `R (*)(void *, ...)` -- Win64 passes a variadic
double in both its XMM and its integer register (clang checked), so each target reads
the 4 / 8 bytes the i686 stack word held, whatever class it gives the position.

    python tools/x64/vcmdecide.py [--game game] [--tsv out/x64d/vcmdecide.tsv] [--check]
                                  [--control]

Original CC0 code.
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "census"))
sys.path.insert(0, str(PORT / "tools" / "x64"))
import f32args as F  # noqa: E402


def wcls(k: str) -> str:
    """Win64 class of an f32args kind: X (f32 / double in XMM) or G."""
    return {"f": "Xf", "d": "Xd"}.get(k, "G")


def target_reads(tp_kinds, rd):
    """{position k: read?} for a target's parameters (k = 0 is this)."""
    out = {}
    for k, (_o, _sz, kk, ln) in enumerate(F.layout(tp_kinds)):
        out[k] = True if rd is None else (F.lane_reg(ln) in rd)
    return out


def x64_mismatch(view_k, tp_k, reads):
    """register positions (1..3) whose Win64 class differs between view and target
    and that the target reads: [(k, view class, target class)]."""
    out = []
    for k in range(1, min(4, len(view_k), len(tp_k))):
        if view_k[k] == "v" or tp_k[k] == "v":
            break
        a, b = wcls(view_k[k]), wcls(tp_k[k])
        if a != b and reads.get(k, True):
            out.append((k, a, b))
    return out


def table_cands(R, soff):
    """functions at byte offset soff of every data2c vtable (header words first)."""
    out = set()
    for sym, (a, n) in R.R.T.items():
        if n <= soff // 4:
            continue
        w = R.R.W.get(a + soff)
        if w and w[0] == "fn":
            out.add(w[1])
    return out


# Reviewed receivers for jalrs the resolver finds no vptr store for: (file stem, soff)
# -> ([vtables], why).  Class "map area model": the vptr sits at model + 0x68 (= map
# data + 0x98), stored through the data pointer, which vcall_targets does not follow.
MAP_AREA = (["D_00470410", "D_00470480"],
            "map area model, vptr at +0x68: MapDataLoadRequest*_1e6* / MapAreaStartLoad_1d8370 store "
            "D_00470410 then D_00470480 at data+0x98 = model+0x68 (sbresolve REVIEWED_VTABLES)")
REVIEWED = {(stem, so): MAP_AREA for stem, so in (
    ("EvCmdMapRaycast_25d2b0", 0x64), ("MapAreaDataReset_1e8fe0", 0x84),
    ("MapAreaModelCollectTrisAllMaybe_187d40", 0x5C), ("MapAreaModelUpdateObjsMaybe_1875e0", 0x34),
    ("MapDataAnimStep_1e6600", 0x7C), ("MapDataAnimStep_1e6600", 0x78),
    ("MapDataCollectCollTrisMaybe_1e6c80", 0x60), ("MapDataQueryCollTrisMaybe_1e6bc0", 0x64),
    ("SceneMapAreasCollectCollTrisMaybe_1c5090", 0x60), ("TaskDrawShadowMap_1f70f0", 0x48),
    ("TaskDrawShadowMap_1f70f0", 0x4C))}


def stored_tables(R, text, soff):
    """vtables (two zero header words, long enough for soff) the file names: a
    constructor stores its own vtable and then calls a slot of it."""
    out = []
    for sym in sorted(set(re.findall(r"\bD_[0-9A-Fa-f]{8}\b", text))):
        tl = R.R.T.get(sym)
        if tl is None or soff // 4 >= tl[1]:
            continue
        a = tl[0]
        if R.R.W.get(a) != ("int", 0) or R.R.W.get(a + 4) != ("int", 0):
            continue
        out.append(sym)
    return out


def control_view(pts):
    """--control: the first non-this parameter's class flipped (f32 <-> s32): every
    resolved thunk with a parameter its target reads at position 1 must turn up."""
    if len(pts) < 2:
        return pts
    k = F.kind(F.ptype_of(pts[1]))
    return [pts[0], "s32" if k in "fd" else "f32"] + list(pts[2:])


def run(game: Path, ovr: Path, control: bool = False):
    P = F.protos_index(game)
    R = F.Retail(game)
    rows = []
    hdr = {}
    for h in (game / "include").glob("*.h"):
        t = h.read_text("latin-1")
        if "VCM" in t:
            hdr[h.name] = F.thunks_of(t)
    tcache = {}

    def proto(n):
        return P.get(n) or F.def_proto(game, n)

    for p in sorted((game / "src").rglob("*.cpp")):
        rel = str(p.relative_to(game)).replace("\\", "/")
        text = p.read_text("latin-1")
        src = "game"
        if (ovr / rel).exists():
            text = (ovr / rel).read_text("latin-1")
            src = "overrides"
        th = [(f"{src}/{rel}",) + x for x in F.thunks_of(text)]
        # hand-written VCALL(obj, voff, soff, ret, (ptypes), args..) in overrides
        for m in re.finditer(r"\bVCALL(?:_THIS)?\s*\(", text):
            rp = F._paren(text, m.end() - 1)
            args = F._split_top(text[m.end():rp])
            try:
                cv, so, ret, pt = int(args[1], 0), int(args[2], 0), args[3], args[4]
            except (IndexError, ValueError):
                continue
            pts = F._split_top(pt.strip()[1:-1])
            th.append((f"{src}/{rel}", text.count("\n", 0, m.start()) + 1, "VCALL", ret, pts, so,
                       "..." in pts, cv))
        for hn, hts in hdr.items():
            if re.search(r'#\s*include\s*"%s"' % re.escape(hn), text):
                for x in hts:
                    if re.search(r"(?:->|\.)\s*%s\s*\(" % re.escape(x[1]), text):
                        th.append((f"game/include/{hn}",) + x)
        if not th:
            continue
        img = F.image_of(rel)
        jal = defaultdict(set)
        for d in F.defs_of(text):
            for j, V, S in R.jalrs(img, d):
                jal[S].add((d, V, j))
        for (where, line, meth, ret, pts, soff, va, cv) in th:
            if control:
                pts = control_view(pts)
            vk = [F.kind(F.ptype_of(x)) for x in pts]
            if va or len(pts) < 2:
                continue
            if len(pts) > 1 and "*" in pts[0] and pts[1].replace(" ", "") == "void*" \
                    and pts[0].replace(" ", "") != "void*":
                continue            # struct return: (R *, void *, ..) -- not a VCM view
            sites = jal.get(soff) or set()
            if cv is not None:
                sites = {x for x in sites if x[1] == cv}
            base = dict(file=rel, where=f"{where}:{line}", method=meth, soff=hex(soff),
                        view="(" + ", ".join(pts) + ")")
            plaus, impl, notes, too_many = {}, set(), [], False
            for d, V, j in sorted(sites):
                el = F.entry_lanes(proto(d))
                tg = R.R.vcall_targets(f"{img}:{d}", j, V, soff, el)
                if len(tg) > F.MAX_CANDS:
                    too_many = True
                    continue
                for lst, rd, ok, why in tg:
                    cn = lst.partition(":")[2].split("@")[0]
                    if ok:
                        # lanes read: None (no listing) wins; else the union over sites
                        if cn in plaus and plaus[cn] is None or rd is None:
                            plaus[cn] = None
                        else:
                            plaus[cn] = set(plaus.get(cn) or ()) | set(rd)
                    else:
                        impl.add(cn)
                notes.append(f"{d}@{j} +0x{V:x}")
            # judge
            mism, unk, sig = {}, [], {}
            for cn, rd in sorted(plaus.items()):
                tp = proto(cn)
                if tp is None:
                    unk.append(cn)
                    continue
                tk = [F.kind(x) for x in tp]
                rdl = None if rd is None else set(rd)
                reads = target_reads(tk, rdl)
                mm = x64_mismatch(vk, tk, reads)
                if mm:
                    mism[cn] = mm
                sig[cn] = tuple(wcls(tk[k]) if (k < len(tk) and reads.get(k, True)) else "-"
                                for k in range(1, min(4, len(vk))))
            if sites and not too_many and plaus:
                if not mism:
                    verdict = "safe" if not unk else "safe-noproto"
                else:
                    # do the targets agree among themselves at each read register position?
                    cols = list(zip(*sig.values())) if sig else []
                    agree = all(len({c for c in col if c != "-"}) <= 1 for col in cols)
                    verdict = "cast" if agree else "poly"
            elif (REVIEWED.get((Path(rel).stem, soff)) or stored_tables(R, text, soff)) and not too_many:
                tabs, why = REVIEWED.get((Path(rel).stem, soff)) or (stored_tables(R, text, soff),
                                                                     "vtables the file stores")
                sig = {}
                for sym in tabs:
                    lst = R.R.slot_target(img, sym, soff)
                    if not lst:
                        continue
                    cn = lst.partition(":")[2].split("@")[0]
                    tp = proto(cn)
                    if tp is None:
                        unk.append(cn)
                        continue
                    plaus[cn] = None
                    tk = [F.kind(x) for x in tp]
                    mm = x64_mismatch(vk, tk, {})
                    if mm:
                        mism[cn] = mm
                    sig[cn] = tuple(wcls(tk[k]) if k < len(tk) else "-" for k in range(1, min(4, len(vk))))
                cols = list(zip(*sig.values())) if sig else []
                agree = all(len({c for c in col if c != "-"}) <= 1 for col in cols)
                verdict = ("safe-store" if not mism else ("cast" if agree else "poly")) if sig                     else "unresolved-agree" if not unk else "unresolved"
                notes.append(f"{why}: {','.join(tabs)}")
            else:
                tc = table_cands(R, soff)
                bad = []
                for cn in sorted(tc):
                    tp = proto(cn)
                    if tp is None:
                        continue
                    mm = x64_mismatch(vk, [F.kind(x) for x in tp], {})
                    if mm:
                        bad.append(cn)
                        mism[cn] = mm
                why = "too many tables" if too_many else ("no plausible target" if sites
                                                         else "no retail jalr paired")
                verdict = "unresolved-agree" if not bad else "unresolved"
                notes.append(why)
            rows.append(dict(base, verdict=verdict, n_plaus=len(plaus), n_impl=len(impl),
                             mismatch=";".join(f"{cn}:" + ",".join(f"{k}{a}>{b}" for k, a, b in mm)
                                               for cn, mm in sorted(mism.items()))[:400],
                             targets=",".join(sorted(plaus))[:300],
                             sites=" ".join(notes)[:200], ret=ret))
    return rows


COLS = ["verdict", "file", "where", "method", "soff", "view", "ret", "n_plaus", "n_impl",
        "mismatch", "targets", "sites"]


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--overrides", default=str(PORT / "overrides"))
    ap.add_argument("--tsv", default=str(PORT / "out" / "x64d" / "vcmdecide.tsv"))
    ap.add_argument("--check", action="store_true",
                    help="exit 1 when a thunk is cast / poly / unresolved (ctest x64.vcmdecide)")
    ap.add_argument("--control", action="store_true",
                    help="flip each view's first parameter class: --check must fail")
    a = ap.parse_args(argv)
    rows = run(Path(a.game), Path(a.overrides), a.control)
    Path(a.tsv).parent.mkdir(parents=True, exist_ok=True)
    with open(a.tsv, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("\t".join(COLS) + "\n")
        for r in sorted(rows, key=lambda r: (r["verdict"], r["where"])):
            fh.write("\t".join(str(r.get(c, "")) for c in COLS) + "\n")
    c = Counter(r["verdict"] for r in rows)
    print("vcmdecide: " + ", ".join(f"{k}={v}" for k, v in sorted(c.items())), file=sys.stderr)
    bad = [r for r in rows if r["verdict"] in ("cast", "poly", "unresolved")]
    for r in bad[:40]:
        print(chr(9).join(str(r.get(c, "")) for c in COLS)[:300])
    return 1 if (a.check and bad) else 0


if __name__ == "__main__":
    sys.exit(main())

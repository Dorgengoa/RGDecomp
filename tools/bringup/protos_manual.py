#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""protos_manual.py: a verdict for every row the protos stage left for a human.

    python tools/bringup/protos_manual.py [--game game] [--out census/protos_manual.tsv]
        [--irabi out/protos2/irabi.tsv] [--vvz out/protos2/abi0/vvz.tsv]
        [--vcall out/protos2/vcall_review/verdicts.tsv] [--check]

Rows (game/PROTOS.tsv): manual-call, manual-decl, manual-missing, missing-zero,
manual-vcall-forward, manual-vcall-v0, manual-stack-block, info-stack-block-unresolved,
ret-class-convert, vararg-missing, void-value-zero, info-bare-return,
addr-alias-unresolved, info-vcall-set-args, info-vcall-unpaired, manual-ret-class,
manual-unproto.  Verdict per row:

    OK                  nothing lost on i686 (evidence column says why)
    fixed-rule          a stage rule handles the site (the row stays as a log)
    fixed-override      an override under overrides/ replaces the file
    BUG                 an open ABI difference (no rule, no override): the check fails
    needs-retail-check  not decidable from the listings / IR (reason given)

Evidence is mechanical where a tool decides it:
  manual-call/-decl   tools/bringup/protos_irabi.py (clang IR of the caller's call vs the
                      callee's definition: stack words, return width/class, sret)
  void-value-zero     tools/bringup/abi_census.py vvz (does retail's caller read $v0?)
  stack-block rows    census/stackblock_sites.tsv (tools/census/stackblock_census.py)
  ret-class-convert,  the callers' listings (asmflow.reg_after_call: is $v0 read after
  info-bare-return    the jal?)
  vcall rows          out/protos2/vcall_review/verdicts.tsv (slot methods vs registers,
                      tools/bringup/vslot_reads.py)
and REVIEWED (below) holds the hand-checked rest, each with its listing evidence.

--check (ctest `protos.manual`): exit 1 when a row has no verdict (a new manual row after a
re-ingest) or a BUG verdict.  Used by tools/bringup/protos_deficits.py --manual.
"""
from __future__ import annotations

import argparse
import collections
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]

RULES = ("manual-call", "manual-decl", "manual-missing", "missing-zero", "manual-vcall-forward",
         "manual-vcall-v0", "manual-stack-block", "info-stack-block-unresolved",
         "ret-class-convert", "vararg-missing", "void-value-zero", "info-bare-return",
         "addr-alias-unresolved", "info-vcall-set-args", "info-vcall-unpaired",
         "manual-ret-class", "manual-unproto")

# Hand-reviewed rows: (rule, file, callee) -> (verdict, evidence).  file may be "*".
REVIEWED = {
    # ---- missing-zero / manual-missing: lanes that only forward registers into virtuals
    ("missing-zero", "src/main/chara/CharaActAppear_21c1f0.cpp", "Notify"): (
        "OK", "Notify(p,0,0,0) -> ActorCastToUnit_3b8770 -> slot 0x34 (UnitBase/Unit/Chara*IsKindOf, "
              "vslot_reads.py: none reads $6/$7); the lanes are vcall-widen forwards of dead registers"),
    ("missing-zero", "src/main/container/PartyDeserialize_3bf4f0.cpp", "InvObjCastToCage_3d3c80"): (
        "OK", "InvObjCastToCage_3d3c80 -> slot 0x20 (Item*/InsectItem IsKindOf: none reads $6/$7)"),
    ("missing-zero", "src/main/map/WorldSubsysLinkIds_40a6a0.cpp", "IterInit_370170"): (
        "OK", "IterInit_370170 forwards $6/$7 only to the container's slot 0x8 (count): no slot-8 "
              "method of any vtable reads $6 (vslot_reads.py, 83 methods)"),
    ("missing-zero", "src/main/sys/AbilityModeRun_2790e0.cpp", "SystemVmCall_250a50"): (
        "OK", "PROTOS-MISSING-ARGS.md: $f12..$f19 reach only Fprintf (varargs save area); the inline "
              "method Wait has 3 jals, all CLOBBER"),
    ("manual-missing", "src/main/chara/CharaUseActionGaugeOnce_214010.cpp", "ActorCastToChara_3b87b0"): (
        "OK", "ActorCastToChara_3b87b0 -> slot 0x34 (Chara*/Unit* IsKindOf): none reads $6/$7"),
    ("manual-missing", "src/main/item/InsectApplyItem_3cf310.cpp", "IterInit_370170"): (
        "OK", "IterInit_370170: $6/$7 reach only slot 0x8 (count) methods, none reads them"),
    ("manual-missing", "src/main/map/WorldSubsysPlanetEntryLink_40ecd0.c", "WorldSubsysLinkIds_40fca0"): (
        "OK", "WorldSubsysLinkIds_40fca0 reads $6 only via IterInit_370170 (slot 0x8: no read)"),
    ("manual-missing", "src/main/map/WorldSubsysPlanetEntryLink_41fd30.c", "WorldSubsysLinkIds_420640"): (
        "OK", "WorldSubsysLinkIds_420640 reads $6 only via IterInit_370170 (slot 0x8: no read)"),
    # Port-arity evidence: the lanes are vcall-widen `rgp_aN` forwards; every port C definition
    # at the end of the chain (the receiver's vtable slot) takes fewer parameters, so the value
    # passed in that lane is never read on i686 (retail: a dead register at a jtbl case).
    ("manual-missing", "src/main/chara/CharaActDispatch_20d190.cpp", "CharaActDamage_218880"): (
        "OK", "rgp_a2/a3 reach only slot 0x20C of the chara vtables = CharaTopPriorityStatusMaybe_3b6a80"
              "(arg0) (sbresolve CHARA_VTABLES): 1 port parameter; retail $6/$7 at this jtbl case are "
              "leftovers"),
    ("manual-missing", "src/main/chara/CharaActDispatch_20d190.cpp", "CharaActBlownAway_217de0"): (
        "OK", "as CharaActDamage_218880: slot 0x20C = CharaTopPriorityStatusMaybe_3b6a80(arg0)"),
    ("manual-missing", "src/main/item/InvMoveItemMaybe_3c5b10.cpp", "ItemConsume_3d41b0"): (
        "OK", "rgp_a2/a3 reach item slots 0x50 (ItemGetCountDefault_2a3b90 / ItemStackGetCount_3d5c80, "
              "1 param) and 0x5C (ItemAddCountDefault_3c6450 1 param; ItemStackAddCount_3d3830 -> slot "
              "0x58 ItemStackSetCount_3d3870 2 params / ItemSetCountNop_3d5a10): no port terminal has lane 2/3"),
    ("manual-missing", "src/main/menu/MenuRevelationConfirmOpenState_3476a0.cpp",
     "RevelationBoardCellGetItemRec_3ead00"): (
        "OK", "rgp_a3 -> RevelationBoardFindById_3eb580 -> slot 0x70 DataTableFindByKey_3680a0 -> slot "
              "0x30/0x38 of the 75 DataTable vtables (<= 2 port params): lane 3 never read"),
    ("manual-missing", "src/main/effect/EffectEntryReleaseNodeById_2da4c0.c", "EffectEntryReleaseNode_2da6c0"): (
        "OK", "rgp_a2/a3 reach only the node's slot 0x18 (v18); every slot-0x18 method with a lane-2/3 "
              "parameter is a save-object Deserialize / filebuf Sync / SpatialMgrListAddRef (other "
              "classes); effect-node methods there take <= 2"),
    ("manual-decl", "src/main/effect/EffectKill_2e06c0.c", "EffInstDestroyByHandle_1a0b00"): (
        "OK", "the C keeps `n = EffInstDestroyByHandle_1a0b00(..)` (void def) but never reads n; retail "
              "2e074c: `b 0x2e077c` then `move v0,zero`: $v0 dead"),
    ("manual-call", "src/main/effect/EffectKill_2e06c0.c", "EffInstDestroyByHandle_1a0b00"): (
        "OK", "value dead in retail and in C (see manual-decl)"),
    # the game file's own view is ABI-wrong; the override passes the definition's shape
    ("manual-decl", "src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c", "StringReplaceRange_1b3da0"): (
        "fixed-override", "game file: u64 size view of an s32 parameter (every later argument one "
                          "slot off, protos_irabi BUG-kind); overrides/src/main/libc/"
                          "NumPutFixedZeroStrMaybe_1b3c90.c passes (s32 size, 0, &c, &c + 1, tag)"),
    ("manual-call", "src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c", "StringReplaceRange_1b3da0"): (
        "fixed-override", "see manual-decl"),
    # void-value-zero whose enclosing function is only called indirectly (0 direct call sites)
    ("void-value-zero", "src/main/event/DrawEventFrameTask_27a870.c", "LetterboxDraw_277ff0"): (
        "OK", "task-table callback (data2c_0044ECF0); LetterboxDraw_277ff0's $v0 is LetterboxIsEnabled's 0 "
              "on the disabled path (= the C's 0), else DrawListEndPrim_141a20 leftovers (no value)"),
    ("void-value-zero", "src/main/event/EvM05ChangeSuspend_350a10.c", "SoundStopEntry_1b8bc0"): (
        "OK", "vtable entry (data2c_00471E20); SoundStopEntry_1b8bc0's exits leave $v0 from its inner "
              "SoundSendCmd/SoundSeqStop calls or scratch: no defined result"),
}


def dead_local(game, f, line, callee):
    """`x = (F(..), (T)0);` where x is never read again in the file (the C use is dead)."""
    p = game / f
    if not p.exists():
        return False
    tx = p.read_text(encoding="utf-8", errors="replace")
    m = re.search(r"\b(\w+)\s*=\s*\(\s*%s\s*\(" % re.escape(callee), tx)
    if not m:
        return False
    v = m.group(1)
    uses = [u for u in re.finditer(r"\b%s\b" % re.escape(v), tx)]
    reads = [u for u in uses if not re.match(r"\s*=[^=]", tx[u.end():u.end() + 3])
             and not re.search(r"\b(s32|u32|int|s16|u16|u8|s8|f32|void\s*\*)\s*$",
                               tx[max(0, u.start() - 12):u.start()])]
    return not reads


def load_tsv(p):
    p = Path(p)
    if not p.exists():
        return []
    ls = p.read_text(encoding="utf-8").splitlines()
    h = ls[0].split("\t")
    return [dict(zip(h, l.split("\t"))) for l in ls[1:] if l.strip()]


class Listings:
    """Retail listings + a reverse jal index (who calls address A, and whether that
    caller reads $v0 after the jal)."""

    def __init__(self):
        sys.path.insert(0, str(PORT / "tools" / "bringup"))
        sys.path.insert(0, str(PORT / "tools" / "stages"))
        import abi_census  # noqa
        import asmflow  # noqa
        self.ac, self.af = abi_census, asmflow
        self.L = abi_census.Listings()
        self._rev = None

    def rev(self):
        if self._rev is None:
            self._rev = collections.defaultdict(list)
            for img, d in self.L.text.items():
                for fn in d:
                    cfg = self.L.cfg(img, fn)
                    if cfg is None:
                        continue
                    for j, op, tgt in cfg.calls():
                        a = self.L.name_addr(tgt, img)
                        if a is not None:
                            self._rev[a].append((img, fn, j, op))
        return self._rev

    def callers_read(self, name, img="main"):
        """[(caller, 'read'|'returned'|'dead')] over every jal/j to name's address."""
        a = self.L.name_addr(name, img)
        out = []
        for ci, cn, j, op in self.rev().get(a, []):
            if op == "j":
                out.append((f"{ci}:{cn}", "returned"))
                continue
            out.append((f"{ci}:{cn}", self.af.reg_after_call(self.L.cfg(ci, cn), j)))
        return out

    def site_use(self, rel, line, callee, files):
        caller = files.encl(rel, line)
        if not caller:
            return None, "no enclosing function"
        cfg, js, img = self.ac.sites(self.L, files, rel, caller, callee)
        if not cfg or not js:
            return caller, "noasm"
        uses = sorted({self.af.reg_after_call(cfg, j) for j in js})
        return caller, ",".join(uses)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--out", default=str(PORT / "census" / "protos_manual.tsv"))
    ap.add_argument("--irabi", default=str(PORT / "out" / "protos2" / "irabi.tsv"))
    ap.add_argument("--vvz", default=str(PORT / "out" / "protos2" / "abi0" / "vvz.tsv"))
    ap.add_argument("--vcall", default=str(PORT / "out" / "protos2" / "vcall_review" / "verdicts.tsv"))
    ap.add_argument("--sblock", default=str(PORT / "census" / "stackblock_sites.tsv"))
    ap.add_argument("--check", action="store_true",
                    help="only compare game/PROTOS.tsv with the committed --out table")
    a = ap.parse_args(argv)
    game = Path(a.game)
    rows = [l.rstrip("\n").split("\t") for l in open(game / "PROTOS.tsv", encoding="utf-8")][1:]
    rows = [r for r in rows if len(r) >= 5 and r[3] in RULES]
    if a.check:
        return check(rows, Path(a.out), game)

    ir = {(r["file"], r["callee"]): r for r in load_tsv(a.irabi)}
    vvz = {(r["file"], r["line"], r["callee"]): r for r in load_tsv(a.vvz)}
    vc = {(r["file"], r["line"], r["callee"], r["rule"]): r for r in load_tsv(a.vcall)}
    sb = collections.defaultdict(list)
    for r in load_tsv(a.sblock):
        sb[r["site"]].append(r["verdict"])
    L = None
    files = None

    def lst():
        nonlocal L, files
        if L is None:
            L = Listings()
            files = L.ac.Files(game)
        return L

    out = []
    for f, line, callee, rule, det in (r[:5] for r in rows):
        ovr = (PORT / "overrides" / f).exists()
        v, ev = None, ""
        rv = REVIEWED.get((rule, f, callee)) or REVIEWED.get((rule, "*", callee))
        if rv:
            v, ev = rv
        elif rule in ("manual-call", "manual-decl"):
            x = ir.get((f, callee))
            if x is None:
                v, ev = None, "no irabi row"
            else:
                iv = x["verdict"]
                if iv == "nocall":
                    v, ev = "OK", "address-only use (no direct call in the IR)"
                elif iv == "nodef" and callee == "new":
                    v, ev = "OK", "C++ `new T(..)` expression, not a call of a function named new"
                elif iv.startswith("OK"):
                    v, ev = "OK", f"irabi {iv}: {x['why'] or x['shapes']}"[:200]
                elif iv == "BUG-retvoid":
                    _c, use = lst().site_use(f, line, callee, files)
                    v = "OK" if use == "dead" else "BUG"
                    ev = f"irabi {iv}; retail caller {_c} $v0 after the jal: {use}"
                else:
                    v = "fixed-override" if ovr else "BUG"
                    ev = f"irabi {iv}: {x['why']}"[:200]
        elif rule == "void-value-zero":
            x = vvz.get((f, line, callee))
            vv = x["verdict"] if x else None
            if ovr:
                v, ev = "fixed-override", f"vvz {vv}"
            elif vv in ("dead",):
                v, ev = "OK", "retail's caller never reads $v0 after the jal"
            elif vv == "undef":
                v, ev = "OK", "callee's $v0 is set by nobody at its exits: retail read garbage"
            elif vv in ("returned", "noasm"):
                # the caller forwards the value (or has no listing): do ITS callers read?
                caller = x["caller"] if x else "?"
                if x and x["callee_exit"] == "undef":
                    v, ev = "OK", f"vvz {vv}; callee {callee} sets no $v0 (exit undef): garbage either way"
                else:
                    uses = lst().callers_read(caller, "main") if caller != "?" else []
                    rd = [c for c, u in uses if u == "read"]
                    if vv == "returned" and not rd and uses:
                        v, ev = "OK", (f"vvz returned; no caller of {caller} reads $v0 "
                                       f"({len(uses)} call sites)")
                    elif dead_local(game, f, line, callee):
                        v, ev = "OK", f"vvz {vv}; the C assigns the zero to a local it never reads"
                    elif vv == "noasm" and x and not re.search(r":(?!void\b)\w", x.get("passed", "")):
                        v, ev = "OK", f"vvz noasm; callee {callee} forwards only void callees ({x['passed'][:80]})"
                    else:
                        v, ev = None, f"vvz {vv}; readers {rd[:3]} passed {x['passed'][:80] if x else ''}"
            elif vv == "BUG-pass":
                v, ev = ("fixed-override" if ovr else "BUG"), "vvz BUG-pass"
            else:
                v, ev = None, f"vvz {vv}"
        elif rule in ("manual-stack-block", "info-stack-block-unresolved"):
            vs = sb.get(f"{f}:{callee}", [])
            if not vs:
                v, ev = "OK", "not a census site (complete inside its local)"
            elif all(x in ("OK", "OK-block") for x in vs):
                v, ev = "OK", f"census/stackblock_sites.tsv: {len(vs)} site(s) OK/OK-block"
            elif all(x.startswith("override:") or x in ("OK", "OK-block") for x in vs):
                v, ev = "fixed-override", "census: override: BUG rows (the override places the block)"
            else:
                v, ev = None, f"census verdicts {sorted(set(vs))}"
        elif rule == "vararg-missing":
            v, ev = "fixed-rule", "vararg-missing passes the format's argument registers (" + det[-12:] + ")"
        elif rule == "addr-alias-unresolved":
            v, ev = "OK", ("link-resolved: " + ("kernel HLE" if "kernel" in det else
                                               "asm unit's own interior label" if "interior" in det else
                                               "a data2c object / data label of that name"))
        elif rule in ("ret-class-convert", "info-bare-return"):
            if rule == "ret-class-convert":
                c, use = lst().site_use(f, line, callee, files)
                if use == "dead":
                    v, ev = "OK", f"retail caller {c} never reads $v0 after the jal"
                elif use and "read" in use:
                    v, ev = "OK", (f"retail caller {c} reads $v0, which the callee never sets "
                                   f"(only $f0): no defined value to match; C conversion stands")
                else:
                    v, ev = None, f"caller {c}: {use}"
            else:
                uses = lst().callers_read(callee, "main")
                rd = [c for c, u in uses if u == "read"]
                if not rd:
                    v, ev = "OK", f"no retail caller reads $v0/$f0 ({len(uses)} call sites)"
                else:
                    v, ev = None, f"read by {rd[:4]}"
        elif rule.startswith(("info-vcall", "manual-vcall")):
            x = vc.get((f, line, callee, rule))
            if x:
                v, ev = x["verdict"], x["evidence"]
                if v == "BUG" and ovr:
                    v = "fixed-override"
        if v is None:
            v, ev = "needs-retail-check", ev or "no mechanical evidence"
        out.append((f, line, callee, rule, v, ev.replace("\t", " ")))
    p = Path(a.out)
    p.parent.mkdir(parents=True, exist_ok=True)
    with open(p, "w", encoding="utf-8", newline="\n") as fo:
        fo.write("file\tline\tcallee\trule\tverdict\tevidence\n")
        for r in out:
            fo.write("\t".join(r) + "\n")
    c = collections.Counter((r[3], r[4]) for r in out)
    for rule in RULES:
        n = {v: k for (ru, v), k in c.items() if ru == rule}
        if n:
            print(f"{rule:30} " + ", ".join(f"{k} {v}" for v, k in sorted(n.items())))
    tot = collections.Counter(r[4] for r in out)
    print("total: " + ", ".join(f"{k} {v}" for v, k in tot.most_common()))
    return 0


def check(rows, table, game):
    """Every manual row of PROTOS.tsv has a verdict row; none is BUG / unreviewed."""
    t = {}
    for r in load_tsv(table):
        t.setdefault((r["file"], r["callee"], r["rule"]), []).append(r["verdict"])
    bad = 0
    for f, line, callee, rule, _d in (r[:5] for r in rows):
        vs = t.get((f, callee, rule))
        if not vs:
            print(f"UNREVIEWED {rule} {f}:{line} {callee}")
            bad += 1
            continue
        if any(v == "BUG" for v in vs):
            ovr = (PORT / "overrides" / f).exists()
            if not ovr:
                print(f"BUG        {rule} {f}:{line} {callee}")
                bad += 1
    print(f"protos_manual --check: {len(rows)} manual row(s), {bad} unreviewed/open")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

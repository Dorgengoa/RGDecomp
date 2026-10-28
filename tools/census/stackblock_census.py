#!/usr/bin/env python3
"""Stack-block census: classify every stack-address call argument the protos
`stack-block` rule could not settle (docs/PROTOS.md "Stack-block census").

The PS2 frame keeps address-taken locals at fixed slots; a callee handed &x
may reach past x (a {lo, hi} pair, a matrix written through &v50 ...).  The
protos stage measures that reach from retail's listings (asmflow
Flow.extent) and builds one block when it crosses locals; this tool reviews
what the stage could not finish:

  * every `info-stack-block-unresolved` site (the extent is a lower bound:
    the pointer reaches a jalr, a callee with no listing, a data-driven
    length), re-measured with a deeper call graph (--depth, default 12) by
    the stage's own function-pointer resolver (tools/stages/sbresolve.py:
    own-local vtables, foreign vtables, stored callbacks, function tables,
    reviewed receivers / sources / bounds, the port's call arity), so a row
    here says why the STAGE left it open; sites the stage resolved carry its
    notes (`resolved` in the census JSON);
  * complete sites whose reach exceeds the C local, or whose local the
    stage cannot size (REVIEWED_TYPE_SIZES sizes the known ones);
  * every manual-stack-block group (the stage declined to build it).
REVIEWED_SITES settles sites whose reach depends on data the resolver cannot
follow (a count argument, a constant the port passes in the lane).

Verdicts: OK (the C local covers the reach), OK-block (the stage built the
block), BUG: under-sized local, BUG: split block, needs-human (+ why).
--compare OLD.tsv prints what became of an earlier census's non-OK rows.

    RG_PROTOS_SB_CENSUS=out/sblock/census.jsonl \\
        python tools/stages/protos_pre.py out/sblock/pre.pkl --out out/sblock/p
    python tools/census/stackblock_census.py out/sblock/census.jsonl \\
        --pkl out/sblock/pre.pkl --out out/sblock/stackblock-census.tsv

(pre.pkl: `RG_INGEST_PRE_PROTOS=out/sblock/pre.pkl python tools/ingest.py
--out <scratch>`, see tools/stages/protos_pre.py.)
"""
from __future__ import annotations

import argparse
import collections
import json
import pickle
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "stages"))
import protos  # noqa: E402
import asmflow  # noqa: E402
import sbresolve  # noqa: E402

OVL_FILES = {"title": "TITLE.BIN", "insmenu": "INSMENU.BIN", "normal": "NORMAL.BIN",
             "factory": "FACTORY.BIN", "insect": "INSECT.BIN"}
OVL_BASE = 0x004E9E80


# Local types the stage's layout reader cannot size, sized by review
# (typedef'd arrays, small C++ classes): {type: (bytes, why)}
REVIEWED_TYPE_SIZES = {
    "MTX": (0x40, "typedef struct { VEC v[4]; } MTX, VEC = f32[4] aligned(16) (DynCloth*)"),
    "VEC": (0x10, "typedef f32 VEC[4] __attribute__((aligned(16)))"),
    "It": (4, "class It { node *p; } (EventObjMgrDrawDoorCursorsMaybe_2e7e10 list iterator)"),
    "WorldPosition": (0x10, "struct WorldPosition : Vec4 {} (NpcObjDrawIcons_2fbb20)"),
}


# Sites settled by review where the reach depends on data the resolver cannot
# follow (a count argument, the port passing a constant in the lane):
# {(definition, local): (verdict, why)}
COLLECT = ("collision-triangle collect: the callee chain writes at most `max` 0x60-byte "
           "hit records (SceneMapAreasCollectCollTrisMaybe_1c5090 advances arg1 by r*0x60 and "
           "lowers arg3 by r); the C buffer is exactly max * 0x60 bytes")
REVIEWED_SITES = {
    ("EvSubNodeMoveByVel_252f40", "hits"): ("OK", COLLECT + " (Hit[0x80], max 0x80)"),
    ("EvSubNodeSplineMove_2531f0", "buf"): ("OK", COLLECT + " (u8[0x3000], max 0x80)"),
    ("EventSysUpdate_26ac10", "list"): ("OK", COLLECT + " (u8[0x6000], max 0x100)"),
    ("MapEntryUpdateMaybe_1e0cd0", "hits"): ("OK", COLLECT + " (Hit[0x100], max 0x100)"),
    ("MapUpdatePlayerLocationMaybe_1ff710", "ids"): (
        "OK", "ids reaches GroupTableFindEntry_415e00's $7 only as retail's leftover register: "
              "the port's WorldDataZoneEntriesUpdateMaybe_3f1660 passes 0 in that lane "
              "(GroupTableFindEntry(.., id2, 0)), so no port callee receives it"),
}


class Census:
    """The protos stage's own resolver (tools/stages/sbresolve.py), deeper."""

    def __init__(self, pkl, depth):
        d = pickle.load(open(pkl, "rb"))
        self.st = protos.ProtoStage()
        self.st.addr_table = d["addr_table"]
        self.flow = self.st._flow()
        self.flow.max_depth = depth
        W, T = sbresolve.data_words({k: v for k, v in d["outputs"].items() if "/data2c_" in k})
        self.R = sbresolve.Resolver(self.st, self.flow, W, T)

    def measure(self, r):
        """(E, complete, notes, resolved targets) for a census site."""
        reg = "$%d" % (4 + r["lane"])
        if not r["listing"]:
            # a MAIN caller of an overlay address: whichever overlay is loaded
            m = re.fullmatch(r"func_([0-9A-Fa-f]{6,8})", r["callee"])
            a = int(m.group(1), 16) if m else None
            cands = [f"{ov}:{self.st._fn_at(a, ov)[1]}" for ov in OVL_FILES
                     if a and a >= OVL_BASE and self.st._fn_at(a, ov)] if a else []
            if not cands:
                return (0, False, [f"? callee {r['callee']} has no listing"], [])
            e, ok, notes = 0, True, []
            for t in cands:
                se, sok, sn, _tg, _w = self.R.extent(t, reg)
                e = max(e, se)
                ok = ok and sok
                notes.append(f"overlay target {t} E 0x{se:x}" + ("" if sok else " (incomplete)"))
                notes += sn
            return (e, ok, notes, [c.split(":")[-1] for c in cands])
        self.R.scan_hi = 0
        e, ok, notes, tg, _w = self.R.extent(
            r["listing"], reg, r.get("kargs") or {},
            ctx={"img": r["img"], "def": r["def"], "off": r["off"], "terms": r.get("terms") or {}})
        opn = [n for n in notes if n.startswith("? ")]
        r["_lenvar_only"] = bool(opn) and all("length from data" in n for n in opn)
        r["_scan_only"] = bool(opn) and all("scanned candidates disagree" in n and
                                            n.count("incomplete:") == 1 and
                                            n.split("incomplete: ", 1)[1].startswith("scanned")
                                            for n in opn)
        r["_scan_hi"] = self.R.scan_hi
        return (e, ok, notes, tg)

    def frame_room(self, r, loc):
        """Bytes from the argument's slot to the next address-taken local or
        the saved-register area of the caller's retail frame (entry-sp
        relative offsets, as the census rows), or None."""
        cfg = self.flow.cfg(f"{r['img']}:{r['def']}")
        if cfg is None:
            return None
        F, saves = None, []
        for op, ops in cfg.ins[:40]:
            if op == "addiu" and ops[:2] == ["$29", "$29"]:
                im = asmflow._imm(ops[2])
                if im and im[0] == "int" and im[1] < 0:
                    F = -im[1]
            elif F and op in ("sd", "sq", "sw", "sdc1", "swc1") and ops[1].endswith("($29)")                     and ops[0] in ("$31", "$30") + tuple("$%d" % i for i in range(16, 24)) +                     tuple("$f%d" % i for i in range(20, 32)):
                try:
                    saves.append(int(ops[1][:-5], 0) - F)
                except ValueError:
                    pass
        tops = [o for v in loc.values() for o in v["offs"] + [mo for _m, mo in v["moffs"]]
                if o > r["off"]]
        if saves:
            tops.append(min(saves))
        if not tops:
            return None
        return min(tops) - r["off"]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("census", type=Path)
    ap.add_argument("--pkl", type=Path, required=True)
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--depth", type=int, default=12)
    ap.add_argument("--all", action="store_true", help="also list complete OK sites")
    ap.add_argument("--compare", type=Path, help="an earlier census TSV: print what became "
                    "of its non-OK rows (verdict transitions)")
    a = ap.parse_args()
    R = [json.loads(ln) for ln in open(a.census, encoding="utf-8")]
    C = Census(a.pkl, a.depth)
    L = {(r["file"], r["def"]): r for r in R if r["kind"] == "locals"}
    built = collections.defaultdict(list)
    for r in R:
        if r["kind"] == "outcome":
            built[(r["file"], r["def"])].append(r)
        if r["kind"] == "group" and r["bad"]:
            built[(r["file"], r["def"])].append({"names": r["names"], "built": False,
                                                 "unk": r["bad"], "holes": [], "bad": True})
    # overrides/: a replaced game file is not built from the stage's output;
    # its rows are verdicts on the snapshot text, the override needs its own look
    ovr = {}
    for f in (PORT / "overrides").rglob("*.c*"):
        m = re.search(r"rg-override: replaces game/(\S+)", f.read_text(encoding="utf-8", errors="replace")[:400])
        if m:
            ovr[m.group(1)] = f.relative_to(PORT).as_posix()
    rows = []
    for r in R:
        if r["kind"] != "site":
            continue
        key = (r["file"], r["def"])
        grp = [g for g in built.get(key, []) if r["local"] in g["names"]]
        loc = L[key]["locals"]
        lo = loc[r["local"]]
        if r["complete"] and not grp and not a.all and not r.get("resolved"):
            # a complete site is listed only when its reach exceeds the C object
            # (the stage would have grouped it: a miss shows up here)
            sz = lo["size"]
            mo = r.get("moff") if r["member"] else 0
            # (a local whose size the stage cannot tell is listed: the stage
            # never groups it, so a reach past it would go unseen)
            if sz is not None and mo is not None and (r["E"] or 0) <= sz - mo:
                continue
            if not r["E"]:
                continue
        if r["complete"]:
            e, ok, tg = r["E"] or 0, True, []
            notes = list(r.get("resolved") or []) or                 [f"str:{x['tgt']}" for x in r.get("escapes", []) if x["kind"] == "str"]
        else:
            e, ok, notes, tg = C.measure(r)
        # where x starts in the frame
        xs = r["off"] - (r.get("moff") or 0) if r["member"] else r["off"]
        if r["member"] and r.get("moff") is None:
            xs = None
        S = lo["size"]
        if S is None and lo["type"] in REVIEWED_TYPE_SIZES:
            n = 1
            for x in re.findall(r"\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]", lo["dims"] or ""):
                n *= int(x, 0)
            S = REVIEWED_TYPE_SIZES[lo["type"]][0] * n
            lo = dict(lo, size=S)
            notes_size = f"size by review: {lo['type']} = 0x{REVIEWED_TYPE_SIZES[lo['type']][0]:x} ({REVIEWED_TYPE_SIZES[lo['type']][1]})"
        else:
            notes_size = None
        space = None if (S is None or xs is None) else S - (r["off"] - xs)
        cov = sorted({n for n, v in loc.items() if n != r["local"]
                      for o in v["offs"] + [mo for _m, mo in v["moffs"]]
                      if r["off"] <= o < r["off"] + e})
        covtxt = ",".join([f"{r['local']}({lo['type']}{lo['dims']}:{S if S is not None else '?'})"]
                          + [f"{n}({loc[n]['type']}{loc[n]['dims']}:{loc[n]['size']})" for n in cov])
        if grp and any(g["built"] for g in grp):
            v = "OK-block"
        elif cov and e > (space or 0):
            v = "BUG: split block"
        elif space is not None and e > space:
            v = "BUG: under-sized local"
        elif not ok and r.get("_lenvar_only") and space is not None and \
                (C.frame_room(r, loc) or 1 << 30) <= space:
            v = "OK"
            notes.append(f"the C object fills its retail frame slot (0x{space:x} bytes): a "
                         "data-length access past it would overrun retail too")
        elif not ok and r.get("_scan_only") and space is not None and                 max(e, r.get("_scan_hi", 0)) <= space:
            v = "OK"
            notes.append(f"every scanned candidate stays inside the C object (largest reach "
                         f"0x{max(e, r.get('_scan_hi', 0)):x} <= 0x{space:x})")
        elif not ok and (r["def"], r["local"]) in REVIEWED_SITES:
            v = REVIEWED_SITES[(r["def"], r["local"])][0]
            notes.append("reviewed: " + REVIEWED_SITES[(r["def"], r["local"])][1])
        elif not ok:
            v = "needs-human"
        elif space is None:
            v = "needs-human (size unknown)"
        else:
            v = "OK"
        if grp and not any(g["built"] for g in grp):
            g = grp[0]
            why = (f"stage declined: holes {','.join(hex(h) for h in g['holes'])}" if g["holes"]
                   else f"stage declined: cannot place/size {g['unk']}")
            notes.append(why)
        if notes_size:
            notes.append(notes_size)
        if r["file"] in ovr:
            notes.append(f"file replaced by {ovr[r['file']]}")
            if not v.startswith("OK"):
                v = "override: " + v
        rows.append([f"{r['file']}:{r['def']}", r["callee"] + (f" -> {' '.join(tg)}" if tg else ""),
                     f"{r['arg']}=sp{r['off']:+#x} lane{r['lane']}",
                     f"0x{e:x}" + ("" if ok else "+?"),
                     covtxt, v, "; ".join(notes)])
    a.out.parent.mkdir(parents=True, exist_ok=True)
    with open(a.out, "w", encoding="utf-8") as fh:
        fh.write("site\tcallee(s)\targ\textent\tlocals covered (type:size)\tverdict\tnotes\n")
        for x in rows:
            fh.write("\t".join(str(c).replace("\t", " ") for c in x) + "\n")
    cnt = collections.Counter(x[5] for x in rows)
    print(f"{len(rows)} rows: " + ", ".join(f"{k} {v}" for k, v in cnt.most_common()))
    if a.compare:
        new = collections.defaultdict(list)
        for x in rows:
            new[(x[0], x[2])].append(x[5])
        trans = collections.Counter()
        for ln in list(open(a.compare, encoding="utf-8"))[1:]:
            c = ln.rstrip("\n").split("\t")
            if len(c) < 6 or c[5] in ("OK", "OK-block"):
                continue
            v = new.get((c[0], c[2]))
            to = v[0] if v else "not listed (complete, inside the C object: OK)"
            trans[(c[5], to)] += 1
            print(f"  {c[5]} -> {to}: {c[0].split(':')[-1]} {c[2]}")
        for (f, t), n in sorted(trans.items()):
            print(f"{n:4d}  {f} -> {t}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

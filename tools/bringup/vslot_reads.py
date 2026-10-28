#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""vslot_reads.py: does any method in vtable slot S read argument register R?

    python tools/bringup/vslot_reads.py PKL SLOT [--vptr V] [--reg $6 --reg $7 ..]

For a virtual call through slot SLOT (byte offset, e.g. 0x34) of an object whose vptr
is at +V (default 0), lists every candidate method (slot SLOT of every vtable that
listing code stores at +V: sbresolve's scan, the same set the protos stage's
stack-block resolver uses) and whether its retail listing reads each register's
incoming value (asmflow.Flow.reads, followed into jal / tail jumps).  PKL is a
protos_pre input dump (RG_INGEST_PRE_PROTOS, e.g. out/sweep/pre_protos.pkl).

Used for the protos `missing-zero` / `manual-missing` / `manual-vcall-forward` close-out
(2026-10-25): a lane passed 0 where retail passed a dead register is exact when no
method of the slot reads it.
"""
import argparse
import pickle
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "stages"))
import protos  # noqa: E402
import sbresolve  # noqa: E402


def resolver(pkl):
    d = pickle.load(open(pkl, "rb"))
    st = protos.ProtoStage()
    st.addr_table = d["addr_table"]
    texts = {p: (b.decode("utf-8", "replace") if isinstance(b, bytes) else b)
             for p, b in d["outputs"].items() if "/data2c_" in p}
    W, T = sbresolve.data_words(texts)
    fl = st._flow()
    return sbresolve.Resolver(st, fl, W, T), fl


_VIA = re.compile(r"maybe:via (\S+)")


def jalr_slots(fl, fn):
    """Slot offsets S of the `lw t9, S(t9)` feeding each jalr of listing fn."""
    cfg = fl.cfg(fn)
    out = set()
    if cfg is None:
        return out
    ins = cfg.ins
    for i, (op, ops) in enumerate(ins):
        if op != "jalr":
            continue
        r = ops[-1]
        for k in range(i - 1, max(-1, i - 8), -1):
            o2, a2 = ins[k]
            if o2 == "lw" and a2 and a2[0] == r:
                m = re.fullmatch(r"(-?\w+)\((\$\w+)\)", a2[1])
                if m:
                    out.add(int(m.group(1), 0))
                break
    return out


def deep_reads(R, fl, fn, reg, depth=0, seen=None):
    """fl.reads(fn, reg) with indirect calls resolved by vtable slot (every method of
    slot S over all vtables stored at +0: an over-approximation, so `no` is sound
    up to vtables the tree does not hold).  Returns (verdict, why)."""
    seen = (seen or set()) | {fn}
    r = fl.reads(fn, reg)
    if not r.startswith("maybe"):
        return ("yes" if r.startswith("yes") else "no" if r == "no" else "unknown"), r
    if depth > 4:
        return "maybe", "depth: " + r
    m = _VIA.match(r)
    tgt = m.group(1) if m else None
    if tgt and tgt != "<indirect>":
        img = fn.split(":")[0]
        sub = tgt if ":" in tgt else f"{img}:{tgt}"
        if sub in seen:
            return "maybe", r
        v, why = deep_reads(R, fl, sub, reg, depth + 1, seen)
        return v, f"via {tgt}: {why}"
    # indirect: every slot this function calls through
    res = []
    for S in sorted(jalr_slots(fl, fn)):
        img, _c, nm = fn.partition(":")
        rv = R.REVIEWED_VTABLES.get((nm, S))
        cands = ({R._slot_fn(img, sym, S) for sym in rv[0]} - {None}) if rv else             R.foreign_virtuals(0, S)
        for t in sorted(cands):
            if t in seen:
                continue
            v, why = deep_reads(R, fl, t, reg, depth + 1, seen)
            res.append((v, f"slot {S:#x} {t}: {why[:80]}"))
    if not res:
        return "maybe", "indirect call with no resolved slot: " + r
    for want in ("yes", "unknown", "maybe"):
        hit = [w for v, w in res if v == want]
        if hit:
            return want, hit[0]
    return "no", f"{len(res)} slot method(s), none reads {reg}"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("pkl")
    ap.add_argument("slot", nargs="*", help="slot byte offsets (0x34 ..)")
    ap.add_argument("--fn", action="append", default=[],
                    help="img:name -- deep reads of its argument registers (indirect calls "
                         "resolved by slot)")
    ap.add_argument("--vptr", default="0")
    ap.add_argument("--reg", action="append", default=None)
    a = ap.parse_args(argv)
    regs = a.reg or ["$6", "$7"]
    R, fl = resolver(a.pkl)
    worst = 0
    for fn in a.fn:
        fn = fn if ":" in fn else "main:" + fn
        for r in regs:
            v, why = deep_reads(R, fl, fn, r)
            worst |= v != "no"
            print(f"{fn} {r}: {v}  ({why})")
    for s in a.slot:
        S = int(s, 0)
        fns = R.foreign_virtuals(int(a.vptr, 0), S)
        print(f"slot {S:#x} (vptr +{a.vptr}): {len(fns)} method(s); unknown vtables {len(R.unknown)}")
        for fn in fns:
            rd = {r: fl.reads(fn, r) for r in regs}
            hit = [r for r, v in rd.items() if v.startswith("yes")]
            worst |= bool(hit)
            print(f"  {'READS ' + ','.join(hit) if hit else 'no-read':16} {fn}  "
                  + "; ".join(f"{r}={v[:60]}" for r, v in rd.items()))
    return 1 if worst else 0


if __name__ == "__main__":
    sys.exit(main())

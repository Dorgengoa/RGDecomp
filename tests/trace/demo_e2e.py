# SPDX-License-Identifier: CC0-1.0
"""End-to-end trace pipeline on rg-runtime-demo (docs/TRACE-PORT.md "Tests").

  demo_e2e.py pipeline --exe rg-runtime-demo --tmp DIR
      port_trace.py run twice (a golden and a run, same input) and compare:
      IDENTICAL; the rows prove the pointer semantics (host-pointer deref,
      slot translation, null marker, RAM-block heap) and the notes.
  demo_e2e.py fault --exe ... --tmp DIR
      a planted fault (RG_TRACE_FAULT) at vbl 150 is reported at exactly that
      vbl and symbol; a different input script diverges in DemoPadWords where
      the scripts differ; a fault in an excluded symbol is not reported.
  demo_e2e.py control --exe ... --tmp DIR
      compare golden vs the faulted run as if they had to match: exits 1
      (ctest WILL_FAIL).
"""
import argparse
import contextlib
import io
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(PORT, "tools", "trace"))

import port_trace  # noqa: E402
import trace  # noqa: E402

DATA = os.path.join(HERE, "data")
REGIONS = os.path.join(DATA, "demo_regions.cfg")
PORTCFG = os.path.join(DATA, "demo_port.cfg")
INPUT = os.path.join(DATA, "demo_input.txt")
OTHER = os.path.join(DATA, "demo_input_other.txt")
STOP = 300
PAD_WORDS = 0x00500000
STABLE = 0x00502008
FAULT_VBL = 150


def record(args, name, inp=INPUT, fault=None):
    out = os.path.join(args.tmp, name + ".tsv")
    if os.path.exists(out):
        os.remove(out)
    argv = ["run", "--exe", args.exe, "--demo", "--out", out, "--regions", REGIONS, "--portcfg", PORTCFG,
            "--input", inp, "--stop-vbl", str(STOP), "--workdir", os.path.join(args.tmp, "work")]
    if fault:
        argv += ["--fault", fault]
    rc = port_trace.main(argv)
    if rc:
        raise SystemExit("port_trace run %s failed (%d)" % (name, rc))
    return out


def compare(a, b, extra=()):
    cap = io.StringIO()
    with contextlib.redirect_stdout(cap):
        rc = port_trace.main(["compare", a, b, "--portcfg", PORTCFG] + list(extra))
    text = cap.getvalue()
    print(text.rstrip())
    return rc, text


def meta(path):
    with open(path, encoding="utf-8") as f:
        return [l.rstrip("\n") for l in f if l.startswith("#")]


def check(cond, what, bad):
    print("%s: %s" % ("ok  " if cond else "FAIL", what))
    if not cond:
        bad.append(what)


def pipeline(args):
    bad = []
    g = record(args, "golden")
    r = record(args, "run")
    rc, text = compare(g, r)
    check(rc == 0 and "IDENTICAL" in text, "two runs of the same input are identical by vbl", bad)
    t = trace.read_trace(g)
    vbls = sorted(int(rows["@vbl"]) for rows in t.values())
    check(vbls and vbls[-1] == STOP, "stop at vbl %d (last %s)" % (STOP, vbls[-1] if vbls else None), bad)
    m = meta(g)
    check(any(l.startswith("# key\t") and "game vbl counter @0x004810C4" in l for l in m),
          "keyed by the game counter", bad)
    check(any(l.startswith("# unmapped\t") and "\tsym:DemoUnmapped\t" in l for l in m), "MAIN text unmapped note", bad)
    check(any(l.startswith("# unmapped\t") and "\tiop\t" in l for l in m), "IOP unmapped note", bad)
    check(any(l.startswith("# stop\tstop-vbl") for l in m), "stop line", bad)
    last = t[max(t)]
    check("sym:DemoUnmapped" not in last and "iop" not in last, "unmapped regions have no rows", bad)
    # pointer semantics, recomputed in Python
    ptrs = (0x00502000).to_bytes(4, "little") + (0x00528200).to_bytes(4, "little") + bytes(4)
    check(last.get("sym:DemoPtrs") == trace.h(ptrs), "host pointer slots -> PS2 addresses (static, heap, null)", bad)
    check(last.get("sym:DemoPadReadsVia") == last.get("sym:DemoPadReads"), "host-pointer deref == the pointee", bad)
    check(last.get("sym:DemoNull") == trace.h(b"ptr:00000000"), "null deref marker", bad)
    heap = bytes((0xA5 ^ (i * 7)) & 0xFF for i in range(64))
    check(last.get("sym:DemoHeap") == trace.h(heap) == last.get("sym:DemoHeapDirect"),
          "deref into the RAM block == the heap by address", bad)
    words = {}
    for fr in sorted(t):
        words.setdefault(t[fr]["sym:DemoPadWords"], fr)
    check(len(words) > 20, "DemoPadWords changes with the frames (%d distinct)" % len(words), bad)
    print("pipeline: %s" % ("PASS" if not bad else "FAIL: " + "; ".join(bad)))
    return 1 if bad else 0


def first_div(text):
    m = re.search(r"FIRST DIVERGENCE at vbl (\d+)", text)
    s = re.search(r"symbols differing: (.*)", text)
    return (int(m.group(1)) if m else None), (s.group(1).split() if s else [])


def fault(args):
    bad = []
    g = record(args, "golden")
    f = record(args, "fault", fault="0x%08X:%d" % (PAD_WORDS + 0x1F00, FAULT_VBL))
    rc, text = compare(g, f)
    v, syms = first_div(text)
    check(rc == 1 and v == FAULT_VBL and syms == ["DemoPadWords"],
          "planted fault reported at vbl %d in DemoPadWords (got %s %s)" % (FAULT_VBL, v, syms), bad)
    check(any(l.startswith("# fault\t") and "0x00501F00" in l for l in meta(f)), "fault line in the trace", bad)
    o = record(args, "other", inp=OTHER)
    rc, text = compare(g, o)
    v, syms = first_div(text)
    # the scripts differ from vbl 71 (CROSS released); the demo's pad thread
    # records the word a field or two after the counter it was keyed by
    check(rc == 1 and v is not None and 71 <= v <= 74 and "DemoPadWords" in syms,
          "different input diverges at vbl 71..74 in DemoPadWords (got %s %s)" % (v, syms), bad)
    x = record(args, "excluded", fault="0x%08X:%d" % (STABLE, FAULT_VBL))
    rc, text = compare(g, x)
    check(rc == 0 and "IDENTICAL" in text, "a fault in an excluded symbol is not judged", bad)
    # ...but the fault is there: without the port config it is reported
    cap = io.StringIO()
    with contextlib.redirect_stdout(cap):
        rc = trace.compare(argparse.Namespace(a=g, b=x, key="vbl", only="^sym:", ignore=None, limit=10))
    v, syms = first_div(cap.getvalue())
    check(rc == 1 and v == FAULT_VBL and syms == ["DemoPadStable"],
          "...which trace.py compare without the exclusions reports (got %s %s)" % (v, syms), bad)
    print("fault: %s" % ("PASS" if not bad else "FAIL: " + "; ".join(bad)))
    return 1 if bad else 0


def control(args):
    g = record(args, "golden")
    f = record(args, "fault", fault="0x%08X:%d" % (PAD_WORDS + 0x1F00, FAULT_VBL))
    rc, _ = compare(g, f)
    return rc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("what", choices=("pipeline", "fault", "control"))
    ap.add_argument("--exe", required=True)
    ap.add_argument("--tmp", required=True)
    args = ap.parse_args()
    os.makedirs(args.tmp, exist_ok=True)
    return {"pipeline": pipeline, "fault": fault, "control": control}[args.what](args)


if __name__ == "__main__":
    sys.exit(main())

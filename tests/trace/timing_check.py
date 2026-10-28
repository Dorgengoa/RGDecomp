# SPDX-License-Identifier: CC0-1.0
"""Timing-record checks (docs/TIMING-LOCKSTEP.md; ctest -L trace).

  unit   rg-timing-tests writes a record over synthetic game memory; every
         source's words are checked, then `timing.py build` and `align` read it
  demo   rg-runtime-demo with RG_TIMING: one VblankStart per field keyed by
         the game counter, CD and pad reads from the SDK HLE, a clean end
  --control (unit): expects one tick too many -> must fail (WILL_FAIL test)
"""
import argparse
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
TT = os.path.join(PORT, "tools", "trace")
sys.path.insert(0, TT)

import timing  # noqa: E402

FAILS = []


def check(cond, what):
    if not cond:
        FAILS.append(what)
        print("FAIL:", what)


def load(path):
    meta, recs, end = None, [], None
    for line in open(path, encoding="utf-8"):
        o = json.loads(line)
        if o["t"] == "meta":
            meta = o
        elif o["t"] == "r":
            recs.append(o)
        elif o["t"] == "end":
            end = o
    return meta, recs, end


def unit(args):
    os.makedirs(args.tmp, exist_ok=True)
    out = os.path.join(args.tmp, "unit.jsonl")
    r = subprocess.run([args.exe, out], capture_output=True, text=True, timeout=120)
    print(r.stdout.strip())
    if r.returncode:
        print(r.stderr)
        sys.exit("rg-timing-tests exit %d" % r.returncode)
    meta, recs, end = load(out)
    check(meta and meta["side"] == "port" and len(meta["sites"]) == 21 and meta["sites"]["4"] == "GfxEndFrame",
          "meta: side port, probe.py's 21 sites")
    check(end is not None and end["reason"] == "test end", "end record")
    check([r["seq"] for r in recs] == list(range(len(recs))), "seq is 0..n-1")
    fn = lambda name: [r for r in recs if r["fn"] == name]  # noqa: E731

    vb = fn("VblankStart")
    check([r["vbl"] for r in vb] == [10, 11, 12, 13, 14, 15, 18], "VblankStart per call, keyed by the game counter")
    check(vb and vb[0]["d"] == [0, 1, 0, 0, 0, 0], "VblankStart words = probe.py's (wait, ready, disk, owner, pause, sysmode)")

    mem = [r for r in fn("GfxEndFrame") if r.get("src") == "mem"]
    check([(r["k"], r["d"][1] if r["k"] == "ret" else None) for r in mem][1::2] ==
          [("ret", 11), ("ret", 13), ("ret", 14), ("ret", 15)], "synthetic ticks at flips 11, 13, 14, 15 only")
    check([r["ra_name"] for r in mem][::2] == ["MainLoop_1c2c10", "MainLoop_1c2c10", "LoadingScreenThread_343510",
                                               "MoviePlayModal_267c60"], "synthetic tick loops")
    check(all(e["pair"] == r["pair"] for e, r in zip(mem[::2], mem[1::2])), "synthetic entry/ret pairs")
    ret11 = mem[1] if len(mem) > 1 else {"d": []}
    check(ret11["d"] == [0x40000000, 11, 0, 2, 1, 0xFFFFFFFF], "synthetic return words (fb, flip, late, interval, depth)")
    check(mem and mem[0]["d"][2] == 262, "synthetic entry divisor")

    wr = [r for r in fn("GfxEndFrame") if "src" not in r]
    check(len(wr) == 2 and wr[0]["k"] == "entry" and wr[1]["k"] == "ret" and wr[0]["pair"] == wr[1]["pair"],
          "wrapped GfxEndFrame: entry + ret, paired")
    if len(wr) == 2:
        check(wr[0]["d"] == [0, 0, 262, 0, 0, 0], "wrapper entry dump (arg chain a0+0x270+0x2C)")
        check(wr[1]["d"] == [0x40000000, 16, 0, 1, 1, 0xFFFFFFFF], "wrapper return dump (saved a0 chains)")
        check(wr[1]["v0"] == 25, "wrapper v0")
    pu = fn("PadUpdate")
    check(len(pu) == 1 and pu[0]["k"] == "ret" and pu[0]["d"][:3] == [0x004B2570, 0xBFFF, 0xFFFF],
          "PadUpdate: return only; pad object reverse-mapped to its PS2 address")
    tl = fn("TaskListChanged")
    check(len(tl) == 1 and tl[0]["a"][0] == 1, "TaskListChanged leaf: a0 == 0 skipped")
    ss = fn("SoundSeqUpdate")
    check(len(ss) == 1 and ss[0]["d"][0] == 0x40000000, "SoundSeqUpdate: W_fpr(12)")

    ol = fn("OverlayLoad")
    check([(r["k"], r["a"][0]) for r in ol] == [("entry", 2), ("ret", 2), ("entry", 3), ("ret", 3)],
          "OverlayLoad entry/ret with the loader index")
    check(ol and ol[0]["d"][0] == 0xFFFFFFFF and ol[0]["pair"] == ol[1]["pair"], "OverlayLoad words + pairing")
    cd = fn("sceCdRead")
    check(len(cd) == 1 and cd[0]["a"][:2] == [1234, 3], "sceCdRead lsn, sectors")
    mo = fn("MovieOpen")
    check(len(mo) == 1 and mo[0]["path"].endswith("NONE.PSS;1"), "MovieOpen with the path")
    check(len(fn("MovieShutdown")) == 1, "MovieShutdown")
    ms = fn("MemState")
    check(ms and ms[0]["d"][:5] == [2, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF], "MemState baseline")
    check(any(r["d"][0] == 1 and r["d"][5] == 1 for r in ms), "MemState sees interval 1 + lock")

    # timing.py reads it like a PCSX2 capture
    syms = timing.Syms(os.path.join(args.tmp, "no-asm"))
    pre = os.path.join(args.tmp, "unit")
    s = timing.build(out, syms, pre)
    ticks = [l.rstrip("\n").split("\t") for l in open(pre + ".ticks.tsv", encoding="utf-8")
             if not l.startswith("#")]
    hdr, rows = ticks[0], ticks[1:]
    col = lambda name: [r[hdr.index(name)] for r in rows]  # noqa: E731
    want = 6 if args.control else 5
    check(len(rows) == want, "timing.py build: %d ticks (got %d)" % (want, len(rows)))
    check(col("loop")[:4] == ["main", "main", "loadscreen", "moviemodal"], "tick loops")
    check(col("vbl") == ["11", "13", "14", "15", "16"][:len(rows)], "tick vbls = flip counters")
    check(col("interval")[:2] == ["2", "1"], "tick interval from the return words")
    # the read came after flip 13 was set: the poll before it closed tick 2 first
    check(col("cd_reads")[:3] == ["0", "0", "1"], "CD read folded into the tick after the flip")
    ev = [l.rstrip("\n").split("\t") for l in open(pre + ".events.tsv", encoding="utf-8")][1:]
    kinds = [e[3] for e in ev]
    for k in ("overlay_load", "overlay_loaded", "cd_read", "movie_open", "movie_shutdown", "mem_interval",
              "mem_locked", "mem_gamemode", "task_list_changed"):
        check(k in kinds, "event %s" % k)
    ms = timing.read_milestones(pre + ".milestones.tsv")
    keys = [(m[2], m[3]) for m in ms]
    check(("overlay_load", "2") in keys and ("overlay_load", "3") in keys and ("mem_gamemode", "11") in keys
          and ("loop", "loadscreen") in keys and ("mem_interval", "1") in keys, "milestones")
    check(timing.align(pre + ".milestones.tsv", pre + ".milestones.tsv") == 0, "align: a run against itself")
    check(timing.align(pre + ".milestones.tsv", pre + ".milestones.tsv", nowrap=True) == 0, "align --nowrap")
    print("unit: %d records, %d ticks, %d milestones" % (len(recs), len(rows), len(ms)))


def demo(args):
    os.makedirs(args.tmp, exist_ok=True)
    out = os.path.join(args.tmp, "demo.jsonl")
    env = dict(os.environ)
    for k in list(env):
        if k.startswith(("RG_TRACE_", "RG_TIMING")) or k in ("RG_DATA",):
            del env[k]
    env["RG_TIMING"] = out
    fields = 300
    r = subprocess.run([args.exe, "--headless", "--fields", str(fields)], env=env, cwd=args.tmp,
                       capture_output=True, text=True, timeout=600)
    if r.returncode:
        print(r.stdout[-2000:], r.stderr[-2000:])
        sys.exit("rg-runtime-demo exit %d" % r.returncode)
    meta, recs, end = load(out)
    check(meta is not None and end is not None, "meta and end records (atexit close)")
    vb = [x for x in recs if x["fn"] == "VblankStart"]
    check(abs(len(vb) - fields) <= 2, "one VblankStart per field (%d for %d fields)" % (len(vb), fields))
    vbls = [x["vbl"] for x in vb]
    check(vbls == sorted(vbls) and len(set(vbls)) >= len(vbls) - 2, "VblankStart keyed by the game counter")
    cnts = [x["cnt"] for x in vb]
    per = [(b - a) & 0xFFFFFFFF for a, b in zip(cnts, cnts[1:])]
    check(per and all(p == per[0] or abs(p - 4920120) <= 1 for p in per), "cnt = EE cycles: 4,920,120 per field")
    check(any(x["fn"] == "sceCdRead" for x in recs), "sceCdRead records from the SDK HLE")
    check(any(x["fn"] == "scePadRead" for x in recs), "scePadRead records from the SDK HLE")
    s = timing.build(out, timing.Syms(os.path.join(args.tmp, "no-asm")), os.path.join(args.tmp, "demo"))
    check(s["vblank"]["median_cycles"] in (4920120, 4920121), "timing.py summary: VBlank period %s" % s["vblank"])
    print("demo: %d records, %d VblankStart" % (len(recs), len(vb)))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", choices=["unit", "demo"])
    ap.add_argument("--exe", required=True)
    ap.add_argument("--tmp", required=True)
    ap.add_argument("--control", action="store_true")
    args = ap.parse_args()
    {"unit": unit, "demo": demo}[args.mode](args)
    if FAILS:
        sys.exit("%d check(s) failed" % len(FAILS))
    print("ok")


if __name__ == "__main__":
    main()

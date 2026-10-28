#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Thread / interrupt / timing census for the native-threads lane (docs/NATIVE-THREADS.md).

  python tools/native/thread_census.py static
      Scans the compiled game sources (game/ with overrides/ substituted,
      PORT_PROVIDED files skipped) for every EE-kernel call, thread creation,
      handler installation and timer access.  Writes census/native_threads_static.tsv
      and prints the thread-entry / handler tables.  No build needed.

  python tools/native/thread_census.py dynamic RUN.kcensus.tsv --map build/.../rg-game.map
                                       [--out census/native_threads_dynamic.tsv] [--label NAME]
      Summarises a run recorded with RG_KCENSUS=<path> (src/sce/kernel/kcensus.c):
      threads (entry, priority, switches, blocking calls by site), semaphores
      (creator, waiters, signallers and their contexts), handlers (cause, function,
      deliveries), DelayThread / SleepThread / WakeupThread / Rotate sites, VBlank
      waits and timer reads.  Writes a TSV and prints a readable report.

  Recording a run (one rg-game at a time on the shared PC):
      set RG_KCENSUS=out\\nthreads\\title.kcensus.tsv
      python tools/fixtures/run_from.py title --run 600 --exe build/nthreads-i686/rg-game.exe
"""
import argparse
import bisect
import collections
import csv
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

# ---------------------------------------------------------------- static
KAPI = [
    "CreateThread", "DeleteThread", "StartThread", "StartThread_1176e0", "ExitThread", "ExitDeleteThread",
    "TerminateThread", "iTerminateThread", "ChangeThreadPriority", "iChangeThreadPriority",
    "RotateThreadReadyQueue", "iRotateThreadReadyQueue", "ReleaseWaitThread", "iReleaseWaitThread",
    "GetThreadId", "ReferThreadStatus", "iReferThreadStatus", "SleepThread", "WakeupThread", "iWakeupThread",
    "CancelWakeupThread", "iCancelWakeupThread", "SuspendThread", "iSuspendThread", "ResumeThread",
    "iResumeThread", "DelayThread", "DelayThread_117618",
    "CreateSema", "DeleteSema", "iDeleteSema", "SignalSema", "iSignalSema", "WaitSema", "PollSema", "iPollSema",
    "ReferSemaStatus", "iReferSemaStatus",
    "AddIntcHandler", "AddIntcHandler2", "RemoveIntcHandler", "AddDmacHandler", "AddDmacHandler2",
    "RemoveDmacHandler", "EnableIntc", "DisableIntc", "iEnableIntc", "iDisableIntc", "EnableDmac", "DisableDmac",
    "iEnableDmac", "iDisableDmac", "EnableIntc_1170e8", "DisableIntc_117080", "EnableDmac_1171b8",
    "DisableDmac_117150", "DIntr", "EIntr", "DisableIntr_120660", "EnableIntr_1206b0", "CpuIntrDisabled_117070",
    "SetAlarm", "iSetAlarm", "ReleaseAlarm", "iReleaseAlarm",
    "sceGsSyncV", "sceGsSyncVCallback", "sceGsSyncVCallback_109b18", "WaitVsyncCount_15de90",
    "SetVblankCallback_15df10", "ThreadYield_1d2b70", "GetVsyncCount_15df00",
]
CALL_RX = re.compile(r"\b(" + "|".join(sorted(KAPI, key=len, reverse=True)) + r")\s*\(")
DECL_RX = re.compile(r"^\s*(extern\b|static\b|typedef\b|#)")
ENTRY_RX = re.compile(r"=\s*\(\s*void\s*\*\s*\)\s*&?\s*(\w+_[0-9a-f]{5,6})\b|=\s*&?(\w+_[0-9a-f]{5,6})\s*;")
TIMER_LO, TIMER_HI = 0x10000000, 0x10001840


def compiled_sources():
    """game/src files the build compiles, with overrides substituted (gamesrcs.py rules,
    simplified: every override replaces its target; PORT_PROVIDED rows are skipped)."""
    provided = set()
    pp = os.path.join(ROOT, "overrides", "PORT_PROVIDED.tsv")
    if os.path.exists(pp):
        for line in open(pp, encoding="utf-8"):
            if line.startswith("#") or not line.strip():
                continue
            provided.add(line.split("\t")[0].strip())
    out = []
    gsrc = os.path.join(ROOT, "game")
    for dp, _, fs in os.walk(os.path.join(gsrc, "src")):
        for f in fs:
            if not f.endswith((".c", ".cpp")):
                continue
            rel = os.path.relpath(os.path.join(dp, f), gsrc).replace("\\", "/")
            if rel in provided:
                continue
            ov = os.path.join(ROOT, "overrides", rel)
            out.append((rel, ov if os.path.exists(ov) else os.path.join(gsrc, rel), os.path.exists(ov)))
    return sorted(out)


def cmd_static(args):
    rows = []
    entries = []
    for rel, path, is_ov in compiled_sources():
        try:
            text = open(path, encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        if not CALL_RX.search(text):
            continue
        func = os.path.splitext(os.path.basename(rel))[0]
        lines = text.split("\n")
        has_ct = False
        for i, ln in enumerate(lines, 1):
            if DECL_RX.match(ln) or ln.strip().startswith(("/*", "*", "//")):
                continue
            for m in CALL_RX.finditer(ln):
                api = m.group(1)
                if re.search(r"\b(s32|int|void|u32)\s+" + api + r"\s*\(", ln):
                    continue  # a definition / prototype
                rows.append((func, rel, i, api, "override" if is_ov else "game", ln.strip()[:140]))
                if api == "CreateThread":
                    has_ct = True
        if has_ct:
            for i, ln in enumerate(lines, 1):
                for m in ENTRY_RX.finditer(ln):
                    name = m.group(1) or m.group(2)
                    if name and name != func and ("Thread" in name or "Main" in name or "Def" in name):
                        entries.append((func, name, i))
    # timer accesses (HWACCESS.tsv, the address-literal transform's log)
    hw = os.path.join(ROOT, "game", "HWACCESS.tsv")
    timers = []
    if os.path.exists(hw):
        for r in csv.DictReader(open(hw, encoding="utf-8"), delimiter="\t"):
            try:
                a = int(r["addr"], 16)
            except (ValueError, KeyError):
                continue
            if TIMER_LO <= a < TIMER_HI or a in (0x1000F000, 0x1000F010):
                timers.append((r["symbol"], r["file"], r["line"], r["rule"], "%08X" % a, r["before"]))
                rows.append((r["symbol"], r["file"], int(r["line"]), "HW:%08X:%s" % (a, r["rule"]), "hwaccess",
                             r["before"][:140]))
    out = args.out or os.path.join(ROOT, "census", "native_threads_static.tsv")
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write("# tools/native/thread_census.py static: EE-kernel calls in the compiled game sources\n")
        f.write("func\trelpath\tline\tapi\tsource\ttext\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")
    by_api = collections.Counter(r[3] for r in rows)
    funcs = collections.defaultdict(set)
    for r in rows:
        funcs[r[3]].add(r[0])
    print("static census: %d call sites in %d functions -> %s" % (len(rows), len({r[0] for r in rows}), out))
    print("\n## thread creators -> entries")
    for func, name, i in entries:
        print("  %-36s -> %s (line %d)" % (func, name, i))
    print("\n## handler installs")
    for r in rows:
        if r[3] in ("AddIntcHandler", "AddIntcHandler2", "AddDmacHandler", "AddDmacHandler2",
                    "sceGsSyncVCallback", "sceGsSyncVCallback_109b18", "SetVblankCallback_15df10"):
            print("  %-36s %s" % (r[0], r[5]))
    print("\n## timer / INTC register accesses")
    for t in timers:
        print("  %-36s %s %-12s %s" % (t[0], t[4], t[3], t[5]))
    print("\n## calls per API (sites / functions)")
    for api, n in sorted(by_api.items(), key=lambda x: -x[1]):
        if not api.startswith("HW:"):
            print("  %-28s %4d %4d" % (api, n, len(funcs[api])))
    return 0


# ---------------------------------------------------------------- dynamic
class HostMap:
    """lld-link /MAP: `0001:off  name  rva+base  object` rows (code section)."""
    RX = re.compile(r"^\s*0001:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)?")

    def __init__(self, path):
        base = 0x400000
        rows = []
        for line in open(path, encoding="utf-8", errors="replace"):
            m = re.search(r"Preferred load address is ([0-9a-fA-F]+)", line)
            if m:
                base = int(m.group(1), 16)
                continue
            m = self.RX.match(line)
            if m:
                n = m.group(1)
                if n.startswith("_") and "@" not in n:
                    n = n[1:]
                rows.append((int(m.group(2), 16) - base, n))
        rows.sort()
        self.rows = rows
        self.keys = [a for a, _ in rows]

    def name(self, rva):
        if not rva:
            return "-"
        i = bisect.bisect_right(self.keys, rva) - 1
        return self.rows[i][1] if i >= 0 else "rva_%x" % rva


INTC = ["GS", "SBUS", "VBLANK_START", "VBLANK_END", "VIF0", "VIF1", "VU0", "VU1", "IPU", "TIMER0", "TIMER1",
        "TIMER2", "TIMER3", "SFIFO", "VU0WD"]
DMAC = ["VIF0", "VIF1", "GIF", "fromIPU", "toIPU", "SIF0", "SIF1", "SIF2", "fromSPR", "toSPR"]


def cause_name(a):
    a = int(a)
    if a >= 0x100:
        return "DMAC:" + (DMAC[a - 0x100] if a - 0x100 < len(DMAC) else str(a - 0x100))
    return "INTC:" + (INTC[a] if a < len(INTC) else str(a))


def cmd_dynamic(args):
    hm = HostMap(args.map)
    nm = hm.name
    threads = {}          # tid -> dict
    thr_entry = {}        # tid -> entry name
    cur_sema = {}         # id -> instance key
    semas = collections.OrderedDict()
    handlers = collections.Counter()   # (cause, fn) -> calls
    installs = []
    calls = collections.Counter()      # (ctx, kind, caller, extra) -> n
    kw = collections.Counter()         # (ctx, kind) -> n
    t0 = collections.Counter()
    switches = collections.Counter()
    first_vbl = None
    last_vbl = 0
    nrows = 0

    def ctx(tid, isr, entry_fn=None):
        if int(isr):
            return "handler"
        tid = int(tid)
        if tid == 0:
            return "kernel"
        return "T%d:%s" % (tid, thr_entry.get(tid, "?"))

    def sema_inst(sid):
        sid = int(sid)
        k = cur_sema.get(sid)
        if k is None:
            k = "S%d(port/pre-load)" % sid
            cur_sema[sid] = k
            semas[k] = {"id": sid, "creator": "-", "init": "?", "max": "?", "ops": collections.Counter(),
                        "blocked": 0}
        return k

    cur_handler = None  # (cause, fn name) while delivering: attributes isr rows
    for line in open(args.log, encoding="utf-8", errors="replace"):
        if line.startswith("#"):
            continue
        p = line.rstrip("\n").split("\t")
        if len(p) < 10:
            continue
        vbl, tid, prio, isr, kind, a, b, c, fn, ra = p[:10]
        nrows += 1
        vbl = int(vbl)
        first_vbl = vbl if first_vbl is None else first_vbl
        last_vbl = vbl
        fnn = nm(int(fn, 16))
        ran = nm(int(ra, 16))
        if kind == "SW":
            t = int(a)
            if t not in thr_entry:
                thr_entry[t] = fnn
                threads.setdefault(t, {"entry": fnn, "prio": int(b), "creator": "-", "stack": "?",
                                       "first": vbl})
            threads[t]["last"] = vbl
            threads[t].setdefault("prios", set()).add(int(b))
            switches[t] += 1
            cur_handler = None
            continue
        if kind == "HC":
            handlers[(cause_name(a), fnn)] += 1
            cur_handler = "H:%s:%s" % (cause_name(a), fnn)
            continue
        if kind == "AC":
            handlers[("ALARM", fnn)] += 1
            cur_handler = "H:ALARM:%s" % fnn
            continue
        if kind == "VB":
            continue
        cx = ctx(tid, isr)
        if cx == "handler" and cur_handler:
            cx = cur_handler
        if kind == "KW":
            kw[(cx, "vblank" if a == "1" else "until")] += 1
            continue
        if kind == "T0":
            t0[(cx, "%08X" % (int(a) & 0xFFFFFFFF))] += 1
            continue
        if kind == "CT":
            t = int(a)
            thr_entry[t] = fnn
            threads[t] = {"entry": fnn, "prio": int(b), "creator": ran, "stack": "0x%X" % int(c), "first": vbl,
                          "last": vbl, "prios": {int(b)}}
            calls[(cx, kind, ran, "%s prio=%s" % (fnn, b))] += 1
            continue
        if kind == "CS":
            sid = int(a)
            k = "S%d@%s#%d" % (sid, ran, sum(1 for x in semas if x.startswith("S%d@" % sid)))
            cur_sema[sid] = k
            semas[k] = {"id": sid, "creator": ran, "creator_ctx": cx, "init": b, "max": c,
                        "ops": collections.Counter(), "blocked": 0, "first": vbl}
            continue
        if kind in ("WS", "SS", "iSS", "PS", "iPS", "DS", "iDS", "RS?", "iRS?"):
            k = sema_inst(a)
            s = semas[k]
            s["ops"][(kind, cx, ran)] += 1
            if kind == "WS" and int(b) <= 0:
                s["blocked"] += 1
            if kind in ("DS", "iDS"):
                cur_sema.pop(int(a), None)
            continue
        if kind in ("AI", "AD"):
            installs.append((vbl, cx, ran, cause_name(int(a) + (0x100 if kind == "AD" else 0)), fnn, b, c))
            continue
        extra = ""
        if kind in ("WK", "iWK", "ST", "TT", "iTT", "DT", "CW", "iCW", "SU", "RS", "RT", "iRT"):
            extra = "T%s:%s" % (a, thr_entry.get(int(a), "?"))
        elif kind in ("DL",):
            extra = "%sus" % a
        elif kind in ("CP", "iCP"):
            extra = "T%s:%s->%s" % (a, thr_entry.get(int(a), "?"), b)
        elif kind in ("RQ", "iRQ", "EI", "DI", "iEI", "iDI"):
            extra = cause_name(a) if kind.endswith(("EI", "DI")) else "prio=%s" % a
        elif kind in ("ED", "DD", "iED", "iDD"):
            extra = cause_name(int(a) + 0x100)
        elif kind in ("SA", "iSA"):
            extra = "%s hsync %s" % (fnn, a)
        calls[(cx, kind, ran, extra)] += 1

    # merge the instances one creator made (per-call semas: DelayThread-style, Vif1DmaStart's
    # per-frame sema) into one row "S<ids>@creator xN"
    merged = collections.OrderedDict()
    for k, s in semas.items():
        key = (s["creator"], s["init"], s["max"]) if s["creator"] != "-" else k
        m = merged.get(key)
        if m is None:
            m = merged[key] = {"ids": [], "creator": s["creator"], "init": s["init"], "max": s["max"],
                               "ops": collections.Counter(), "blocked": 0, "n": 0}
        if s["id"] not in m["ids"]:
            m["ids"].append(s["id"])
        m["ops"].update(s["ops"])
        m["blocked"] += s["blocked"]
        m["n"] += 1
    semas = collections.OrderedDict()
    for key, m in merged.items():
        name = "S%s@%s" % ("/".join(str(i) for i in m["ids"][:4]) + ("/.." if len(m["ids"]) > 4 else ""),
                           m["creator"]) + (" x%d" % m["n"] if m["n"] > 1 else "")
        semas[name] = m

    fields = (last_vbl - (first_vbl or 0)) or 1
    label = args.label or os.path.basename(args.log)
    out = args.out or os.path.join(ROOT, "census", "native_threads_dynamic.tsv")
    rows = []
    for t, d in sorted(threads.items()):
        rows.append(("thread", label, "T%d" % t, d["entry"], "prio=%s" % "/".join(str(x) for x in sorted(d.get("prios", {d["prio"]}))),
                     "creator=%s stack=%s" % (d["creator"], d["stack"]), switches[t],
                     "%.2f/field" % (switches[t] / fields), "vbl %s..%s" % (d.get("first"), d.get("last"))))
    for k, s in semas.items():
        total = sum(s["ops"].values())
        rows.append(("sema", label, k, "init=%s max=%s" % (s["init"], s["max"]), "creator=%s" % s["creator"],
                     "blocked_waits=%d" % s["blocked"], total, "", ""))
        for (kind, cx, ran), n in sorted(s["ops"].items(), key=lambda x: -x[1]):
            rows.append(("sema_op", label, k, kind, cx, ran, n, "%.2f/field" % (n / fields), ""))
    for (cause, fnn), n in sorted(handlers.items(), key=lambda x: (-x[1], x[0])):
        rows.append(("handler", label, cause, fnn, "", "", n, "%.2f/field" % (n / fields), ""))
    inst = collections.OrderedDict()
    for vbl, cx, ran, cause, fnn, nxt, hid in installs:
        inst.setdefault((cause, fnn, cx, ran, nxt), [0, vbl])[0] += 1
    for (cause, fnn, cx, ran, nxt), (n, vbl) in inst.items():
        rows.append(("install", label, cause, fnn, cx, ran, n, "next=%s" % nxt, "first vbl %d" % vbl))
    for (cx, kind, ran, extra), n in sorted(calls.items(), key=lambda x: (x[0][1], -x[1])):
        rows.append(("call", label, kind, extra, cx, ran, n, "%.2f/field" % (n / fields), ""))
    for (cx, k), n in sorted(kw.items(), key=lambda x: -x[1]):
        rows.append(("kwait", label, k, "", cx, "", n, "%.2f/field" % (n / fields), ""))
    for (cx, reg), n in sorted(t0.items(), key=lambda x: -x[1]):
        rows.append(("timer_read", label, reg, "", cx, "", n, "%.2f/field" % (n / fields), ""))
    mode = "a" if args.append and os.path.exists(out) else "w"
    with open(out, mode, encoding="utf-8", newline="\n") as f:
        if mode == "w":
            f.write("# tools/native/thread_census.py dynamic: RG_KCENSUS runs summarised (docs/NATIVE-THREADS.md)\n")
            f.write("kind\trun\tkey\twhat\tctx\tsite\tcount\trate\tnote\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")

    # readable report
    print("run %s: %d rows, vbl %s..%s (%d fields) -> %s" % (label, nrows, first_vbl, last_vbl, fields, out))
    print("\n## threads")
    for t, d in sorted(threads.items()):
        print("  T%-3d %-34s prio %-8s switches %7d (%.2f/field)  creator %s" % (
            t, d["entry"], "/".join(str(x) for x in sorted(d.get("prios", {d["prio"]}))), switches[t],
            switches[t] / fields, d["creator"]))
    print("\n## handlers delivered")
    for (cause, fnn), n in sorted(handlers.items(), key=lambda x: -x[1]):
        print("  %-18s %-40s %8d (%.2f/field)" % (cause, fnn, n, n / fields))
    if installs:
        print("\n## handler installs (count, first vbl)")
        agg = collections.OrderedDict()
        for vbl, cx, ran, cause, fnn, nxt, hid in installs:
            k = (cause, fnn, ran, cx)
            agg.setdefault(k, [0, vbl])[0] += 1
        for (cause, fnn, ran, cx), (n, v) in agg.items():
            print("  %-18s %-36s by %-32s %-28s x%d from vbl %d" % (cause, fnn, ran, cx, n, v))
    print("\n## semaphores (instances with traffic)")
    for k, s in semas.items():
        total = sum(s["ops"].values())
        if total < args.min_ops:
            continue
        print("  %s init=%s max=%s blocked_waits=%d ops=%d" % (k, s["init"], s["max"], s["blocked"], total))
        for (kind, cx, ran), n in sorted(s["ops"].items(), key=lambda x: -x[1])[:8]:
            print("      %-5s %-44s %-40s %d" % (kind, cx, ran, n))
    print("\n## other kernel calls (by kind, context, site)")
    for (cx, kind, ran, extra), n in sorted(calls.items(), key=lambda x: (x[0][1], -x[1])):
        if n >= args.min_ops or kind in ("CT", "ST", "SA", "iSA", "CP", "RQ", "WK", "iWK", "SL", "DL"):
            print("  %-4s %-40s %-44s %-30s %d" % (kind, cx, ran, extra, n))
    print("\n## kernel-private waits (sceGsSyncV, timed waits)")
    for (cx, k), n in sorted(kw.items(), key=lambda x: -x[1]):
        print("  %-8s %-44s %d" % (k, cx, n))
    print("\n## timer reads")
    for (cx, reg), n in sorted(t0.items(), key=lambda x: -x[1]):
        print("  %s %-44s %d (%.2f/field)" % (reg, cx, n, n / fields))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    s = sp.add_parser("static")
    s.add_argument("--out")
    d = sp.add_parser("dynamic")
    d.add_argument("log")
    d.add_argument("--map", required=True)
    d.add_argument("--out")
    d.add_argument("--label")
    d.add_argument("--append", action="store_true", help="append to --out instead of rewriting it")
    d.add_argument("--min-ops", type=int, default=2, help="report threshold for semaphores / calls")
    a = ap.parse_args()
    return cmd_static(a) if a.cmd == "static" else cmd_dynamic(a)


if __name__ == "__main__":
    sys.exit(main())

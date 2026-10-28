#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Driven-thread busy-wait census (docs/SPIN.md "Driven threads") -> census/driven_wait.tsv.

The bug class (BRINGUP-HISTORY 2026-10-25 (stream close)): a loop on a game flow (main or
the loading screen) signals the semaphore of a thread that is now a *driven native step*
(docs/NATIVE-THREADS.md "Driven threads") and then polls state that step would write.  On
the EE the signal switched at once to the higher-priority waiter; natively a non-`sync`
conversion runs only at a driver point, so the loop spins forever unless it passes one.
The spin census (spin_loops.py) classed such loops SAFE whenever a WaitSema (BLOCK) ran in
them, although a WaitSema on a free mutex is no driver point.

Ground truth is the retail code (tools/census/platform, the same loader and loop finder as
spin_loops.py), with the port's driver points laid over it:

  driven      every `rg_thread_conv` in overrides/ (entry, sync flag, parsed from source).
              A thread's wake semaphores = the semaphores its entry (and direct callees)
              WaitSema on and that the thread itself never signals (a mutex it also
              releases is not a wake).
  signals     every jal to SignalSema / iSignalSema / WakeupThread / iWakeupThread /
              ResumeThread; the sema id ($a0) from a straight-line register simulation
              (a word loaded from a constant address = a global id) or, failing that, the
              field offset it was loaded from.  A signal of a driven thread's wake sema is
              propagated up the call graph (function -> threads it may wake, with a chain).
  driver pt   functions that are a native driver point: WaitVsyncCount, DelayThread,
              sceGsSyncV / VSync, RotateThreadReadyQueue / ThreadYield, plus every
              function whose OVERRIDE calls rg_frame_point / rg_frame_delay /
              rg_frame_wait_cond / rg_frame_yield / rg_frame_frame_wait (so a fix by
              override is seen), plus every loop the spin stage instruments with a hint
              (census/spin_loops.tsv hint=hint: rg_spin_hint is a driver point).
              Propagated up the call graph as "may reach".

Per retail loop (every back-edge head in the six images):

  A. the body (directly or through callees) signals a driven thread's wake sema:
     WAKE-SYNC      the thread is a `sync` conversion: its step runs at the signal (safe)
     WAKE-DP        a call on EVERY iteration reaches a driver point (or the loop has a
                    spin hint): the woken step runs inside the loop (safe / fixed)
     WAKE-DP-SOME   a driver point is reached on some iterations only: review
     BUSY-WAIT      no driver point, and an exit of the loop depends on memory / a call
                    result (not only an induction variable): THE BUG CLASS
     WAKE-ONCE      no driver point, every exit is an induction / walk exit (a loop that
                    signals per element and ends by itself: the step runs later, at the
                    caller's next driver point; documented placement difference)
     IN-STEP        the loop runs only inside a driven thread's own step (no flow waits)
  B. no wake, but the loop was SAFE for the spin census only through a WaitSema / BLOCK
     call that is no native driver point, and it polls memory written from a driven
     thread or an interrupt handler (natively those run only at driver points):
     SAFE-NONDP     (same hazard without the signal)

Rows for replaced code (EXCLUDED / no source: src/sce re-implementations) are kept with
compiled=excluded and never count as open.

    python tools/census/driven_wait.py            # writes the TSV
    python tools/census/driven_wait.py --check    # exit 1 on an open row
    ... --no-overrides   ignore the overrides' driver points (control: must find the
                         SoundStreamSlotShutdown_1bdfd0 busy-wait the 2026-10-25 fix closed)

Exit 77 (ctest skip) when the platform cache / retail images are not available.
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
GAME = PORT / "game"
OVR = PORT / "overrides"

# Reviewed rows (classes the census cannot decide: WAKE-DP-SOME, SAFE-NONDP*): (symbol,
# loop head) -> why the loop cannot spin natively.  Add a row only with the evidence.
REVIEWED: dict = {
    ("SoundStreamSlotShutdown_1bdfd0", "0x1BDFE8"):
        "outer `while (!(idle && state 0))`: every iteration pushes a command (or finds the "
        "ring full), so the inner `while (busy) kick();` kicks at least once, and the kick "
        "override ends in rg_frame_point (its guard D_00481504 is 0 outside the kick); "
        "insectrun --title reaches TITLE (BRINGUP-HISTORY 2026-10-25 (stream close))",
    ("SoundStreamSlotShutdown_1bdfd0", "0x1BE198"):
        "outer `while (!(idle && state 7))`: as 0x1BDFE8 (close command 0xA)",
    ("GameFrameUpdate_27c4c0", "0x27C630"):
        "`do {} while (GameModeDispatch())`: re-dispatch while a mode update reports a mode "
        "change in this frame; no mode update returns non-zero on slot / stream state (phase "
        "machines, LoadingModeUpdate_285450 returns 0 while it waits); the slot-queue signal "
        "(EventPlayerAbort -> StreamMgrUpdate -> SoundStreamSlotQueueStop) runs the step at the "
        "frame's next driver point, as documented for SoundStreamSlotQueueStop",
    ("GameModeDispatch_27c670", "0x27C6BC"):
        "the mode loop `do { r = mode update } while (r)`: as GameFrameUpdate_27c4c0 0x27C630",
}

SIGNAL_STUBS = {"SignalSema": "SignalSema", "iSignalSema": "iSignalSema",
                "WakeupThread": "WakeupThread", "_iWakeupThread": "iWakeupThread",
                "iWakeupThread_117468": "iWakeupThread", "ResumeThread_116530": "ResumeThread",
                "iResumeThread_116540": "iResumeThread"}
WAIT_STUBS = {"WaitSema"}
# native driver points by retail name (docs/NATIVE-THREADS.md "Driver points")
DP_NAMES = {"WaitVsyncCount_15de90", "DelayThread_117618", "sceGsSyncV", "VSync_116a30",
            "VSync2_116ac0", "RotateThreadReadyQueue", "ThreadYield_1d2b70"}
FLOW_PRIO = 20               # main and the loading screen (docs/NATIVE-THREADS.md)
SHALLOW = 2                  # call depth under which a reached driver point counts
DP_CALL = re.compile(r"\brg_frame_(point|delay|wait_cond|yield|frame_wait)\s*\(")
CONV_RX = re.compile(r"rg_thread_conv\s+\w+\s*=\s*\{(.*?)\};", re.S)


def strip_comments(s: str) -> str:
    s = re.sub(r"/\*.*?\*/", " ", s, flags=re.S)
    return re.sub(r"//[^\n]*", " ", s)


def driven_convs():
    """[(entry name, sync, anywhere, override rel, old priority)] from the overrides'
    conversions."""
    out = []
    for f in sorted(OVR.rglob("*.c*")):
        t = f.read_text(encoding="utf-8", errors="replace")
        for m in CONV_RX.finditer(t):
            body = strip_comments(m.group(1))
            parts = [p.strip() for p in body.split(",")]
            ent = re.sub(r"\(\s*void\s*\*\s*\)", "", parts[0]).strip()
            num = lambda i: (int(parts[i], 0) if i < len(parts) and re.fullmatch(r"-?\d+|0x[0-9a-fA-F]+", parts[i]) else 0)
            out.append((ent, num(8), num(12), f.relative_to(OVR).as_posix(), num(7)))
    return out


def func_spans(code: str):
    """(name, open, close) of top-level function bodies in C/C++ text (comments blanked)."""
    out = []
    depth = 0
    i = 0
    n = len(code)
    start = None
    while i < n:
        c = code[i]
        if c == "{":
            if depth == 0:
                head = code[max(0, i - 400):i]
                m = re.search(r"(\w+)\s*\([^;{}]*\)\s*(const\s*)?$", head)
                start = (m.group(1) if m else None, i)
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0 and start is not None:
                out.append((start[0], start[1], i))
                start = None
        i += 1
    return out


def override_dps():
    """{function name defined in an override whose body calls a driver point}."""
    out = {}
    for f in sorted(OVR.rglob("*.c*")):
        t = strip_comments(f.read_text(encoding="utf-8", errors="replace"))
        if not DP_CALL.search(t):
            continue
        for name, a, b in func_spans(t):
            if name and DP_CALL.search(t, a, b):
                out[name] = f.relative_to(OVR).as_posix()
    return out


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--out", type=Path, default=PORT / "census" / "driven_wait.tsv")
    ap.add_argument("--check", action="store_true", help="exit 1 when a row is open")
    ap.add_argument("--no-overrides", action="store_true",
                    help="control: ignore the overrides' driver points")
    ap.add_argument("--no-write", action="store_true")
    a = ap.parse_args(argv)
    try:
        sys.path.insert(0, str(HERE / "platform"))
        sys.path.insert(0, str(HERE))
        import common as C  # noqa: E402
        import spin_loops as SL  # noqa: E402
        if not C.CACHE.exists() and not (C.WORK / "SCUS_974.90").exists():
            print("driven_wait: no platform cache and no retail images: skipped")
            return 77
        facts, imgs, edges, files = C.cached(False)
    except (OSError, ImportError) as e:
        print(f"driven_wait: platform data unavailable ({e}): skipped")
        return 77
    A = SL.Analysis(imgs, edges)
    main_im = imgs["main"]

    # ---- compiled source per symbol (unit / excluded) + overrides present
    manifest = {}
    for ln in (GAME / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split("\t")
        if len(f) >= 5:
            for s in f[4].split(","):
                manifest[(f[2], s)] = (f[0], f[3])

    def compiled(fn):
        hit = manifest.get((fn.image, fn.name))
        if hit is None:
            return "-", "no-source", False
        return hit[0], hit[1], (OVR / hit[0]).exists()

    # ---- driven threads
    convs = driven_convs()
    driven = {}
    for ent, sync, anyw, rel, order in convs:
        f = main_im.by_name.get(ent)
        if f is not None:
            driven[f.key] = dict(name=ent, sync=bool(sync), anywhere=bool(anyw), rel=rel, order=order)
    stub_addr = {main_im.by_name[n].addr: kind for n, kind in SIGNAL_STUBS.items()
                 if n in main_im.by_name}
    wait_addr = {main_im.by_name[n].addr for n in WAIT_STUBS if n in main_im.by_name}

    def sema_label(fn, site, regs):
        v = regs.get(4)
        if isinstance(v, tuple) and v[0] == "load":
            return ("glob", v[1])
        # field offset: the last straight-line definition of $a0 before the jal (+ slot)
        im = imgs[fn.image]
        seq = list(C.insns(im, fn))
        idx = next((i for i, (pc, _) in enumerate(seq) if pc == site), None)
        if idx is None:
            return ("?",)
        want = 4
        for j in [idx + 1] + list(range(idx - 1, max(-1, idx - 40), -1)):
            if j >= len(seq):
                continue
            w = seq[j][1]
            op = w >> 26
            rt, rs, rd = (w >> 16) & 31, (w >> 21) & 31, (w >> 11) & 31
            if op in (0x23, 0x37) and rt == want:
                return ("field", C.sx16(w & 0xFFFF))
            if op == 0 and (w & 63) in (0x21, 0x25, 0x2D) and rd == want:
                if rt == 0:
                    want = rs
                    continue
                if rs == 0:
                    want = rt
                    continue
                return ("?",)
            if op == 3 and j < idx:
                return ("?",)
            d = SL.regs(w)[0]
            if want in d:
                return ("?",)
        return ("?",)

    # direct sema waits / signals per function
    waits = defaultdict(set)     # fn key -> {label}
    sigs = defaultdict(set)      # fn key -> {(label, stub kind)}
    targets = set(stub_addr) | wait_addr
    for k, fi in A.info.items():
        fn = fi.fn
        if not any(d.addr in targets and d.image == "main" for _, d in fi.callees):
            continue
        for site, tgt, (regs, _, _) in C.callsites(imgs[fn.image], fn, targets, imgs):
            lab = sema_label(fn, site, regs)
            if tgt in wait_addr:
                waits[k].add(lab)
            else:
                sigs[k].add((lab, stub_addr[tgt]))

    # wake semas per driven thread: waited in the entry or a direct callee, never
    # signalled by the thread's own code (entry + direct callees)
    wake = {}                    # label -> [thread names]
    for dk, d in driven.items():
        fi = A.info.get(dk)
        if fi is None:
            continue
        scope = [dk] + [c.key for _, c in fi.callees]
        w = set().union(*(waits.get(x, set()) for x in scope))
        s = set().union(*({l for l, _ in sigs.get(x, set())} for x in scope))
        d["wake"] = sorted(l for l in w - s if l[0] != "?")
        for l in d["wake"]:
            wake.setdefault(l, []).append(d["name"])

    def lab_str(l):
        if l[0] == "glob":
            return "D_%08X" % l[1]
        if l[0] == "field":
            return "*(p+0x%X)" % (l[1] & 0xFFFF)
        return "?"

    # functions -> driven threads they may wake: {fn key: {thread: chain}}
    reach = defaultdict(dict)
    for k, ss in sigs.items():
        for lab, kind in ss:
            for t in wake.get(lab, ()):
                reach[k].setdefault(t, f"{kind}({lab_str(lab)})")
    changed = True
    while changed:
        changed = False
        for k, fi in A.info.items():
            if k in driven:
                continue          # a thread entry is not called by the flows
            for _, d in fi.callees:
                for t, ch in list(reach.get(d.key, {}).items()):
                    if t not in reach[k]:
                        reach[k][t] = f"{d.name} > {ch}"
                        changed = True

    # driver points
    ovr_dp = {} if a.no_overrides else override_dps()
    dp = {}                      # fn key -> (depth, chain)
    for k, fi in A.info.items():
        nm = fi.fn.name
        if nm in DP_NAMES:
            dp[k] = (0, nm)
        elif nm in ovr_dp:
            dp[k] = (0, f"{nm} (override)")
    changed = True
    while changed:
        changed = False
        for k, fi in A.info.items():
            if k in driven:
                continue
            best = dp.get(k)
            if best is not None and best[0] == 0:
                continue
            for _, d in fi.callees:
                if d.key in dp:
                    dd, ch = dp[d.key]
                    cand = (dd + 1, d.name if dd == 0 and ch.startswith(d.name) else f"{d.name} > {ch}")
                    if best is None or cand[0] < best[0]:
                        best = cand
            if best is not None and dp.get(k) != best:
                dp[k] = best
                changed = True
    hinted = set()
    for ln in (PORT / "census" / "spin_loops.tsv").read_text(encoding="utf-8").splitlines():
        f = ln.split("\t")
        if ln.startswith("#") or len(f) < 19 or f[0] == "file":
            continue
        if f[18] == "hint":
            hinted.add((f[3], int(f[6], 16)))

    # thread contexts (A.ctx_of: isr:/thread: roots that reach a function)
    driven_names = {d["name"] for d in driven.values()}
    order_of = {d["name"]: d["order"] for d in driven.values()}
    # functions a game flow reaches (main from Main_15e700, the loading screen), not
    # through thread entries; overlay code runs on main
    flow = {k for k in A.info if k[0] != "main"}
    todo = [main_im.by_name[n].key for n in ("Main_15e700", "LoadingScreenThread_343510")
            if n in main_im.by_name]
    flow.update(todo)
    while todo:
        k = todo.pop()
        for _, d in (A.info[k].callees if k in A.info else ()):
            if d.key not in flow and d.key not in driven:
                flow.add(d.key)
                todo.append(d.key)
    nonsync_names = {d["name"] for d in driven.values() if not d["sync"]}

    def every_fn(body, head, end, backs):
        brs = [(pc, SL.branch_info(pc, w)) for pc, w in body]
        brs = [(pc, b) for pc, b in brs if b]

        def every(at):
            for pc, b in brs:
                if pc >= at:
                    break
                tgt = b[0]
                if head <= tgt <= end and (tgt > at or tgt == head) and pc not in backs:
                    return False
                if pc in backs and pc < at:
                    return False
            return True
        return every

    rows = []
    stats = defaultdict(int)
    for key, fi in sorted(A.info.items(), key=lambda kv: (kv[0][0] != "main", kv[0])):
        fn = fi.fn
        for head, end, backs in A.loops(fi):
            stats["loops"] += 1
            if key in dp and dp[key][0] == 0:
                continue          # the driver point itself (its own wait loop)
            if key in driven:
                continue          # a driven thread's own loop: natively its wait/step split
            L = A.analyse_loop(fi, head, end, backs)
            every = every_fn(L["body"], head, end, backs)
            woke = {}
            for pc, d in L["calls"]:
                if d is None:
                    continue
                for t, ch in reach.get(d.key, {}).items():
                    woke.setdefault(t, (pc, f"{d.name} > {ch}"))
            dp_every, dp_some = [], []
            for pc, d in L["calls"]:
                if d is not None and d.key in dp:
                    dd, ch = dp[d.key]
                    txt = ch if dd == 0 else f"{d.name} > {ch}"
                    # a driver point the callee reaches within SHALLOW calls counts as
                    # reached; deeper chains are "may" (a retry / error path, usually)
                    (dp_every if every(pc) and dd <= SHALLOW else dp_some).append(txt)
            if (fn.image, head) in hinted:
                dp_every.append("rg_spin_hint (spin stage)")
            # exits
            # an exit that is not purely an induction / walk test is a poll; an exit
            # whose condition the taint pass lost (no label) counts as a poll too
            # (SoundStreamSlotShutdown_1bdfd0's inner `while (busy) kick();`), and so
            # does a loop with no conditional exit at all (it leaves by return / goto)
            poll_exit = not L["exits"]
            for pc, lab in L["exits"]:
                kinds = {l[0] for l in lab}
                if lab and kinds <= {"ind", "walk", "stack"} and kinds & {"ind", "walk"}:
                    continue
                poll_exit = True
            ctx = A.ctx_of.get(key, set())
            ctx_thr = {c.split(":", 1)[1] for c in ctx if c.startswith("thread:")}
            in_step = key not in flow and bool(ctx_thr) and ctx_thr <= driven_names
            rel, kind, has_ovr = compiled(fn)
            base = dict(file=rel, symbol=fn.image + ":" + fn.name if fn.image != "main" else fn.name,
                        image=fn.image, addr="0x%06X" % head, back="0x%06X" % (end - 4),
                        compiled=kind, override="yes" if has_ovr else "",
                        ctx=",".join(sorted(ctx | ({"flow"} if key in flow else set()))) or "?")
            if woke:
                stats["wake_loops"] += 1
                # a sync step runs at the signal only when its old priority is higher
                # than the signaller's: a flow (20), or the step the loop runs in
                sprio = min((order_of[t] for t in ctx_thr if t in order_of), default=FLOW_PRIO)                     if in_step else FLOW_PRIO
                nonsync = {t: v for t, v in woke.items()
                           if t in nonsync_names or order_of.get(t, 0) >= sprio}
                if not nonsync:
                    cls = "WAKE-SYNC"
                elif in_step and not poll_exit:
                    cls = "IN-STEP"
                elif not poll_exit:
                    cls = "WAKE-ONCE"
                elif dp_every:
                    cls = "WAKE-DP"
                elif dp_some:
                    cls = "WAKE-DP-SOME"
                else:
                    cls = "BUSY-WAIT"
                shown = nonsync or woke
                rows.append(dict(base, cls=cls,
                                 wakes=", ".join(sorted(shown)),
                                 via="; ".join(f"{v[1]}" for _, v in sorted(shown.items()))[:300],
                                 driver=", ".join(dp_every) or ("some: " + ", ".join(dp_some) if dp_some else "-"),
                                 exits="poll" if poll_exit else "induction",
                                 polled="-", setters="-"))
                continue
            # B: SAFE only through a non-driver-point BLOCK call
            if L["lvl_every"] < 3 or dp_every or not poll_exit or in_step:
                continue
            labels = set()
            for pc, lab in L["exits"]:
                labels |= set(lab)
            setters, hazard, ptrs = set(), False, []
            for l in labels:
                if l[0] == "ptr" and ("ptr", l[1], l[2]) not in L["own_st"] and                         not any(d is None or A.writes_memory(d.key)
                                for _, d in L["calls"]) and not L["jalr"]:
                    ptrs.append(l)      # nothing in the loop writes memory: a pointer poll
                m = l if l[0] == "mem" else (l[1:] if l[0] == "via" and l[1] == "mem" else
                                             (l[2:] if l[0] == "from" and len(l) > 2 and l[2] == "mem" else None))
                if not m or m[1] != "glob":
                    continue
                w = SL.phys(m[3]) & ~3
                for k2 in A.store_map.get(w, set()):
                    if k2 == key:
                        continue
                    for c in A.ctx_of.get(k2, set()):
                        nm = c.split(":", 1)[1]
                        # natively an ISR runs in the kernel pass and a driven step at a
                        # driver point (or at its own signal): neither inside this loop
                        if c.startswith("isr:") or nm in driven_names:
                            setters.add(f"{A.info[k2].fn.name}[{nm}]")
                            hazard = True
            if hazard:
                cls = "SAFE-NONDP"
            elif ptrs and not any(l[0] in ("mem", "via", "from", "ind", "walk") for l in labels):
                cls = "SAFE-NONDP-PTR"     # a field of a pointer: setter unknown (review)
                setters.add("? (pointer field)")
            else:
                continue
            stats["safe_nondp"] += 1
            rows.append(dict(base, cls=cls, wakes="-", via="-",
                             driver=("some: " + ", ".join(dp_some)) if dp_some else "-",
                             exits="poll",
                             polled=" | ".join(sorted(SL.fmt_label(l) for l in labels))[:200],
                             setters="; ".join(sorted(setters))[:300]))

    OPEN = {"BUSY-WAIT", "SAFE-NONDP", "SAFE-NONDP-PTR", "WAKE-DP-SOME"}
    for r in rows:
        r["open"] = ""
        if r["cls"] in OPEN:
            if r["compiled"] != "unit":
                r["open"] = "replaced"
            elif (r["symbol"], r["addr"]) in REVIEWED:
                r["open"] = "reviewed: " + REVIEWED[(r["symbol"], r["addr"])]
            else:
                r["open"] = "OPEN"
    cols = ["file", "symbol", "image", "addr", "back", "compiled", "override", "ctx", "cls",
            "open", "wakes", "via", "driver", "exits", "polled", "setters"]
    cnt = defaultdict(int)
    for r in rows:
        cnt[r["cls"]] += 1
    thr = "; ".join(f"{d['name']}({'sync' if d['sync'] else 'driver-point'}"
                    f"{', anywhere' if d['anywhere'] else ''}: wake "
                    f"{','.join(lab_str(l) for l in d.get('wake', [])) or '-'})"
                    for d in driven.values())
    if not a.no_write:
        meta = C.meta("driven_wait", {
            "generator": "tools/census/driven_wait.py" + (" --no-overrides" if a.no_overrides else ""),
            "loops": f"{stats['loops']} retail loops, {stats['wake_loops']} wake a driven thread, "
                     f"{stats['safe_nondp']} SAFE only through a non-driver-point wait",
            "driven": thr,
            "override_driver_points": ", ".join(sorted(ovr_dp)) or "-",
            "classes": ", ".join(f"{k}={v}" for k, v in sorted(cnt.items())),
            "doc": "docs/SPIN.md \"Driven threads\""})
        C.write_tsv(a.out, cols, rows, meta)
        print(f"{len(rows)} rows -> {a.out}")
    print(f"driven threads: {thr}")
    print(f"loops {stats['loops']}, waking a driven thread {stats['wake_loops']}")
    for k, v in sorted(cnt.items()):
        print(f"  {k:13s} {v}")
    nopen = 0
    for r in rows:
        if r["open"] == "OPEN":
            nopen += 1
            print(f"OPEN {r['cls']:12s} {r['symbol']} @{r['addr']} ({r['file']}) wakes {r['wakes']} "
                  f"via {r['via'][:120]} polled {r['polled'][:80]}")
    print(f"driven_wait: {nopen} open row(s)")
    return 1 if (a.check and nopen) else 0


if __name__ == "__main__":
    sys.exit(main())

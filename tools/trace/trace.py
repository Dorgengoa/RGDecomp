# SPDX-License-Identifier: CC0-1.0
"""PCSX2 reference state trace: hash EE memory regions per sampled VBlank.

  python tools/trace/trace.py run --frames 600 --out a.tsv [--mode live|state]
                                  [--speed S] [--input script.txt] [--regions regions.cfg]
  python tools/trace/trace.py compare a.tsv b.tsv

Output TSV, one row per (sample, region):  frame <TAB> region <TAB> hash
  frame  = EE VBlank index since power-on, from the EE cycle counter
           (emu.FrameClock). Same emulated instant in every deterministic run,
           independent of host speed.
  region = name from regions.cfg (chunked ones as name@start), plus
           pseudo-regions '@cycle' (EE cycle of the vsync, u32 hex) and
           '@vbl' (the game's own VBlank counter [0x004810C4]).
  hash   = first 16 hex digits of BLAKE2b over the region's bytes.
Lines starting with '#' are metadata.

Sampling (see README): every sample is taken with PCSX2's CPU thread stopped
at a vsync boundary, either by a savestate (--mode state) or by freezing the
thread while it sleeps in the frame limiter (--mode live, default). compare
judges only frames present in both traces.
"""
import argparse
import hashlib
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import emu  # noqa: E402

GAME_VBL = 0x004810C4


def load_regions(path):
    """Region lines: space name start end [chunk]
                     space name *PTR[+OFF] size      (follow a u32 pointer)
                     include <file>                  (relative to this file)
    Returns (space, name, start, end, deref) tuples; deref = (ptr, off) or None."""
    regs = []
    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.split("#", 1)[0].split()
            if not line:
                continue
            if line[0] == "include":
                regs += load_regions(os.path.join(os.path.dirname(os.path.abspath(path)), line[1]))
                continue
            space, name = line[0], line[1]
            if line[2].startswith("*"):
                ptr, _, off = line[2][1:].partition("+")
                regs.append((space, name, 0, int(line[3], 0), (int(ptr, 0), int(off, 0) if off else 0)))
                continue
            start, end = int(line[2], 0), int(line[3], 0)
            chunk = int(line[4], 0) if len(line) > 4 else 0
            if chunk:
                for a in range(start, end, chunk):
                    regs.append((space, "%s@%08X" % (name, a), a, min(a + chunk, end), None))
            else:
                regs.append((space, name, start, end, None))
    return regs


def region_bytes(snap, reg):
    """Bytes of one region in a snapshot (or a 'ptr:' marker for a bad pointer)."""
    space, name, a, b, deref = reg
    data = snap.space(space)
    if not data:
        return None
    if deref:
        ptr = int.from_bytes(data[deref[0]:deref[0] + 4], "little") & 0x1FFFFFFF
        a = ptr + deref[1]
        if ptr == 0 or a + b > len(data):
            return ("ptr:%08x" % ptr).encode()
        return data[a:a + b]
    return data[a:b]


OVERLAY_ID = 0x0047E254      # LoadedOverlayId (OverlayLoad_1c3210)
OVERLAY_LANG = 0x0048155C    # row of the overlay name table
OVERLAY_TABLE = 0x0044AF90   # char *D_0044AF90[lang][7]


def _u32(ee, a):
    return int.from_bytes(ee[a:a + 4], "little")


def _cstr(ee, a, n=48):
    a &= 0x1FFFFFFF
    if not 0 < a < len(ee):
        return ""
    return ee[a:a + n].split(b"\0", 1)[0].decode("latin-1")


def overlay_of(s):
    """'<id> <file>' of the loaded overlay, from the game's own variables."""
    i, lang = _u32(s.ee, OVERLAY_ID), _u32(s.ee, OVERLAY_LANG)
    name = ""
    if i < 7 and lang < 4:
        name = _cstr(s.ee, _u32(s.ee, OVERLAY_TABLE + 4 * (7 * lang + i)))
    return "%d %s" % (i, name)


def status_line(s):
    ee = s.ee
    mode = int.from_bytes(ee[0x4B51A0:0x4B51A4], "little", signed=True)
    return "vbl=%d sys=%d ovl=%s mode=%d titleOpened=%d titleSel=%d pad0=%04x" % (
        _u32(ee, GAME_VBL), _u32(ee, 0x47E224), _u32(ee, OVERLAY_ID), mode,
        int.from_bytes(ee[0x48416C:0x48416E], "little"),
        int.from_bytes(ee[0x4803AC:0x4803AE], "little"), _u32(ee, 0x4B2574) & 0xFFFF)


def h(b):
    return hashlib.blake2b(b, digest_size=8).hexdigest()


def run(args):
    regions = load_regions(args.regions)
    words = None
    if not args.no_hook:
        # The input hook is installed in every run, with an empty table when
        # there is no script: it costs a few EE cycles per pad read, which
        # changes timing-sensitive state, so hooked and unhooked runs are not
        # comparable. With it always present, runs differ only by input.
        import input as inp
        words = inp.build_table(inp.parse_script(args.input) if args.input else [])
    elif args.input:
        raise SystemExit("--input needs the hook")
    tag = os.path.splitext(os.path.basename(args.out))[0]
    speed = args.speed if args.speed is not None else (0.1 if args.mode == "live" else 0.02)
    e = emu.Emu(iso=args.iso, speed=speed, slot=args.slot, renderer=args.renderer, tag=tag,
                state_slot=args.state_slot, overrides=args.set,
                memcard=args.memcard)
    out = open(args.out, "w", encoding="utf-8", newline="\n")
    samples = rejected = 0
    try:
        pine = e.connect()
        out.write("# pcsx2\t%s\n# game\t%s %s\n" % (pine.version(), pine.game_id(), pine.title()))
        for spec in args.set:
            out.write("# ini\t%s\n" % spec)
        out.write("# mode\t%s\n# speed\t%s\n# renderer\t%s\n# regions\t%s\n"
                  % (args.mode, speed, args.renderer, args.regions))
        if args.mode == "live":
            import live
            sampler = live.LiveSampler(e.proc.pid, e.log, idle_ms=args.idle_ms)
            if not sampler.find_cpuregs():
                raise RuntimeError("cpuRegs not found in PCSX2 memory")
            sampler.find_cpu_thread()
        if words is not None:
            vbl = inp.install(pine, words, sampler=sampler if args.mode == "live" else None)
            out.write("# input\t%s\t%d vblanks\thook installed at game vbl %d\n"
                      % (args.input, len(words), vbl))
            print("input hook installed at game vbl", vbl, flush=True)
        out.write("# every\t%d\n# memcard\t%s\n" % (args.every, "fresh" if args.memcard else "none"))
        clock = emu.FrameClock()
        frame0 = None
        due = 0              # next frame worth sampling (--every)
        ovl = None
        next_shot = args.shot_from
        stop_at = None
        gmode = None
        next_emit = 0
        vbl_off = None
        t0 = time.time()

        def wanted(c):
            if not clock.wanted(c):
                return False
            if clock.last is None or args.every <= 1:
                return True
            d = emu._delta(c, clock.last)
            return clock.frame + d / emu.EE_CYCLES_PER_VSYNC >= due - 0.5

        while True:
            if args.mode == "live":
                r = sampler.wait_vsync_and_read(wanted, pine=pine, timeout=args.idle_timeout)
                if r is None:
                    raise RuntimeError("no vsync idle within %d s (speed too high?)" % args.idle_timeout)
                s = emu.LiveSnapshot(*r)
            else:
                s = e.snapshot(timeout=args.state_timeout)
            ready = clock.offer(s.ee_cycle32, s, _u32(s.ee, GAME_VBL))
            rejected = clock.dropped
            done = False
            for frame, s in ready:
                if frame0 is None:
                    frame0 = frame
                due = (frame // args.every + 1) * args.every   # aim at multiples of N
                if words is not None and not inp.verify(s, words):
                    out.write("# WARNING\thook/table corrupted at frame %d\n" % frame)
                o = overlay_of(s)
                if o != ovl:
                    out.write("# overlay\t%d\t%s\n" % (frame, o))
                    print("frame %d: overlay %s" % (frame, o), flush=True)
                    ovl = o
                vb = _u32(s.ee, GAME_VBL)
                if vb:
                    off = frame - vb
                    if vbl_off is not None and off != vbl_off:
                        out.write("# note\tframe-vbl offset %d -> %d at frame %d\n" % (vbl_off, off, frame))
                    vbl_off = off
                gm = int.from_bytes(s.ee[0x4B51A0:0x4B51A4], "little", signed=True)
                if gm != gmode:
                    out.write("# gamemode-change\t%d\t%d\tvbl %d\n" % (frame, gm, _u32(s.ee, GAME_VBL)))
                    gmode = gm
                if args.shot_every and args.mode == "live" and frame >= next_shot:
                    next_shot = frame + args.shot_every
                    shots = os.path.join(emu.RUN_DIR, "shots", tag)
                    os.makedirs(shots, exist_ok=True)
                    live.window_shot(e.proc.pid, os.path.join(
                        shots, "f%06d_v%05d.png" % (frame, _u32(s.ee, GAME_VBL))))
                if frame % args.emit_every == 0:
                    # --emit-every thins the OUTPUT only (rows for frames that
                    # are multiples of N, so two runs emit the same frames);
                    # sampling stays at --every to keep FrameClock dense.
                    rows = ["%d\t@cycle\t%08x" % (frame, s.ee_cycle32 & 0xFFFFFFFF),
                            "%d\t@vbl\t%d" % (frame, int.from_bytes(s.ee[GAME_VBL:GAME_VBL + 4], "little"))]
                    for reg in regions:
                        data = region_bytes(s, reg)
                        if data is not None:
                            rows.append("%d\t%s\t%s" % (frame, reg[1], h(data)))
                    out.write("\n".join(rows) + "\n")
                    out.flush()
                samples += 1
                if samples % args.status_every == 0:
                    print("frame %d samples %d %.1fs %s" % (frame, samples, time.time() - t0,
                                                         status_line(s)), flush=True)
                if frame - frame0 >= args.frames:
                    done = "frames: frame %d" % frame
                if args.stop_vbl and _u32(s.ee, GAME_VBL) >= args.stop_vbl:
                    done = "stop-vbl: frame %d vbl %d" % (frame, _u32(s.ee, GAME_VBL))
                if args.stop_mode is not None:
                    mode = int.from_bytes(s.ee[0x4B51A0:0x4B51A4], "little", signed=True)
                    if mode == args.stop_mode and stop_at is None:
                        stop_at = frame + args.stop_after
                        out.write("# gamemode\t%d\treached at frame %d (vbl %d)\n"
                                  % (mode, frame, _u32(s.ee, GAME_VBL)))
                        print("game mode %d reached at frame %d" % (mode, frame), flush=True)
                    if stop_at is not None and frame >= stop_at:
                        done = "stop-mode: frame %d" % frame
            if done:
                out.write("# stop\t%s\n" % done)
                break
        out.write("# samples\t%d\trejected\t%d\n" % (samples, rejected))
    finally:
        out.close()
        e.stop()
    print("wrote", args.out, "samples", samples, "rejected", rejected)


def read_trace(path):
    t = {}
    with open(path, encoding="utf-8") as f:
        for line in f:
            if line.startswith("#") or not line.strip():
                continue
            fr, reg, hv = line.rstrip("\n").split("\t")
            t.setdefault(int(fr), {})[reg] = hv
    return t


def compare(args):
    """First divergent frame, with the named symbols (sym:*) that differ there.
    Only regions present in both traces are judged; --only / --ignore take
    regexes over region names (e.g. --only '^sym:' for symbol-level lockstep)."""
    import re
    a, b = read_trace(args.a), read_trace(args.b)
    if args.key == "vbl":
        # Key by the game's own VBlank counter: what the port can reproduce
        # (it has no BIOS boot, so no power-on frame index). vbl 0 (before the
        # game starts) is dropped; a repeated vbl keeps its first sample.
        def by_vbl(t):
            out = {}
            for fr in sorted(t):
                v = int(t[fr].get("@vbl", "0"))
                if v and v not in out:
                    rows = dict(t[fr])
                    rows.pop("@cycle", None)
                    out[v] = rows
            return out
        a, b = by_vbl(a), by_vbl(b)
    only = re.compile(args.only) if args.only else None
    ignore = re.compile(args.ignore) if args.ignore else None

    def judged(r):
        if only and not only.search(r) and not r.startswith("@"):
            return False
        return not (ignore and ignore.search(r))

    common = sorted(set(a) & set(b))
    span = lambda t: "%d..%d" % (min(t), max(t)) if t else "-"
    print(args.key + "s: A %d (%s), B %d (%s), common %d (%s)" % (
        len(a), span(a), len(b), span(b), len(common), span(common)))
    if common:
        ra, rb = set(a[common[0]]), set(b[common[0]])
        if ra != rb:
            print("regions only in A: %d, only in B: %d (not judged)" % (len(ra - rb), len(rb - ra)))
    first = None
    diverged = {}
    nbad = 0
    for fr in common:
        bad = sorted(r for r in set(a[fr]) & set(b[fr]) if judged(r) and a[fr][r] != b[fr][r])
        if bad:
            nbad += 1
            if first is None:
                first = fr
            for r in bad:
                diverged.setdefault(r, fr)
    if first is None:
        print("IDENTICAL on all %d common frames" % len(common))
        return 0
    prev = [fr for fr in common if fr < first]
    print("FIRST DIVERGENCE at " + args.key + " %d, game vbl A=%s B=%s (last matching: %s; "
          "%d of %d common frames differ)" % (first, a[first].get("@vbl"), b[first].get("@vbl"),
                                             prev[-1] if prev else "-", nbad, len(common)))
    bad_first = [r for r in diverged if diverged[r] == first]
    syms = sorted(r[4:] for r in bad_first if r.startswith("sym:"))
    other = sorted(r for r in bad_first if not r.startswith("sym:"))
    print("  symbols differing: %s" % (" ".join(syms) if syms else "(none)"))
    print("  other regions differing: %s" % (" ".join(other[:40]) if other else "(none)"))
    print("first divergence per region (" + args.key + " region):")
    for r, fr in sorted(diverged.items(), key=lambda kv: (kv[1], kv[0]))[:args.limit]:
        print("  %8d  %s" % (fr, r))
    return 1


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run")
    r.add_argument("--frames", type=int, default=600, help="VBlanks to trace after the first sample")
    r.add_argument("--out", required=True)
    r.add_argument("--regions", default=os.path.join(HERE, "regions.cfg"))
    r.add_argument("--mode", choices=("live", "state"), default="live",
                   help="live: freeze PCSX2's CPU thread at a vsync and read RAM in-process "
                        "(fast, Windows); state: one savestate per sample (slow, disk-bound)")
    r.add_argument("--speed", type=float, default=None,
                   help="PCSX2 NominalScalar (1.0 = realtime; default 0.1 live, 0.02 state)")
    r.add_argument("--state-timeout", type=float, default=120.0)
    r.add_argument("--emit-every", type=int, default=1,
                   help="write rows only for frames that are multiples of N (sampling stays at --every)")
    r.add_argument("--every", type=int, default=1,
                   help="live: sample only VBlanks that are multiples of N (lets PCSX2 run faster)")
    r.add_argument("--idle-ms", type=float, default=15.0,
                   help="live: CPU-thread idle time that counts as 'asleep at vsync' "
                        "(use ~3 at speed >= 0.5)")
    r.add_argument("--idle-timeout", type=float, default=60.0)
    r.add_argument("--shot-every", type=int, default=0,
                   help="live: save a window screenshot every N frames to .tools/run/shots/<tag>/ "
                        "(debug aid for writing input scripts; needs a real renderer, e.g. --renderer 13)")
    r.add_argument("--shot-from", type=int, default=0, help="first frame to screenshot")
    r.add_argument("--status-every", type=int, default=50, help="print a status line every N samples")
    r.add_argument("--renderer", type=int, default=11, help="GS renderer id (11 = Null, 13 = SW)")
    r.add_argument("--input", help="input script (see input.py)")
    r.add_argument("--stop-mode", type=int, default=None,
                   help="stop --stop-after frames after GameModeStack[0] first equals this (6 = field explore)")
    r.add_argument("--stop-after", type=int, default=600)
    r.add_argument("--stop-vbl", type=int, default=0, help="stop once the game VBlank counter reaches this")
    r.add_argument("--memcard", action="store_true",
                   help="insert a freshly created 8 MB card in slot 1 (deleted and recreated per run)")
    r.add_argument("--no-hook", action="store_true",
                   help="do not install the input hook (pure retail code; not comparable "
                        "with hooked runs)")
    r.add_argument("--set", action="append", default=[], metavar="Section/Key=Value",
                   help="override a PCSX2.ini setting for this run (repeatable)")
    r.add_argument("--iso", default=emu.DEFAULT_ISO)
    r.add_argument("--slot", type=int, default=emu.DEFAULT_SLOT, help="PINE slot (TCP port)")
    r.add_argument("--state-slot", type=int, default=emu.STATE_SLOT,
                   help="savestate slot used for snapshots (give parallel runs different ones)")
    c = sub.add_parser("compare")
    c.add_argument("a")
    c.add_argument("b")
    c.add_argument("--limit", type=int, default=60)
    c.add_argument("--key", choices=("frame", "vbl"), default="frame",
                   help="match samples by power-on frame index (PCSX2 vs PCSX2) or by the game's "
                        "VBlank counter (PCSX2 vs port)")
    c.add_argument("--only", help="regex: judge only matching regions (e.g. '^sym:')")
    c.add_argument("--ignore", help="regex: skip matching regions (e.g. '^iop$')")
    args = ap.parse_args()
    if args.cmd == "run":
        run(args)
    else:
        sys.exit(compare(args))


if __name__ == "__main__":
    main()

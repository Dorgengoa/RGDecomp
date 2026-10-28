# SPDX-License-Identifier: CC0-1.0
"""PCSX2 WIDE reference (docs/WIDESCREEN.md "Stage 1", the audit's ground-truth check).

Runs retail in PCSX2 with the golden input (tools/trace input hook), writes the
game's WIDE flag D_00481638 = 1 at every sampled vsync from --wide-from on (the
port's stage 0/1 policy writes it before every field outside the title and
movies), and saves window screenshots at the given game vbls.  Uses the
tools/trace modules unchanged (emu, input, live, pine).

Window shots need the software renderer (--renderer 13, tools/trace/README.md).
One PCSX2 at a time (the portable install's ini is shared).

  python pcsx2_wide.py --renderer 13 --speed 0.5 --out DIR --shots 8000,8290,12000,23000,23600,24500 [--wide-from 7400] [--no-wide]
"""
import argparse, os, sys, time, struct

sys.path.insert(0, 'tools/trace')
import emu            # noqa: E402
import input as inp   # noqa: E402
import live           # noqa: E402

FLAG = 0x00481638
VBL = 0x004810C4


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--out', required=True)
    ap.add_argument('--shots', required=True)
    ap.add_argument('--wide-from', type=int, default=7400)
    ap.add_argument('--no-wide', action='store_true')
    ap.add_argument('--speed', type=float, default=1.0)
    ap.add_argument('--renderer', type=int, default=11)
    ap.add_argument('--input', default='tools/trace/goldens/newgame_battle.input.txt')
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    shots = sorted(int(x) for x in a.shots.split(','))
    words = inp.build_table(inp.parse_script(a.input))
    e = emu.Emu(speed=a.speed, renderer=a.renderer, tag='wide-ref', memcard=True)
    log = open(os.path.join(a.out, 'log.txt'), 'w')
    try:
        pine = e.connect()
        s = live.LiveSampler(e.proc.pid, e.log, idle_ms=3.0)
        if not s.find_cpuregs():
            raise RuntimeError('cpuRegs not found')
        s.find_cpu_thread()
        v0 = inp.install(pine, words, sampler=s)
        print('input hook at vbl', v0, flush=True)
        base = s.addr['ee']
        clock = emu.FrameClock()
        t0 = time.time()
        while shots:
            def rd():
                vbl = struct.unpack('<I', s.p.read(base + VBL, 4))[0]
                flag = struct.unpack('<i', s.p.read(base + FLAG, 4))[0]
                if not a.no_wide and vbl >= a.wide_from and flag != 1:
                    pine.write32(FLAG, 1)
                return vbl, flag
            r = s.frozen_call(clock.wanted, rd, timeout=120)
            if r is None:
                raise RuntimeError('no vsync idle')
            cyc, (vbl, flag) = r
            for _ in clock.offer(cyc, None, vbl):
                pass
            if vbl >= shots[0]:
                p = os.path.join(a.out, 'v%05d.png' % vbl)
                ok = live.window_shot(e.proc.pid, p)
                log.write('shot vbl=%d flag=%d ok=%s %s t=%.0f\n' % (vbl, flag, ok, p, time.time() - t0))
                log.flush()
                print('shot', vbl, flag, ok, flush=True)
                while shots and shots[0] <= vbl:
                    shots.pop(0)
    finally:
        log.close()
        e.stop()


if __name__ == '__main__':
    main()

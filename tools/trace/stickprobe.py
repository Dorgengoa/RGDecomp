# SPDX-License-Identifier: CC0-1.0
"""Retail stick probe from a PCSX2 save state (docs/INPUT.md "Retail stick probe").

    python tools/trace/stickprobe.py --state out/captures/states/v24790_0_cb80c10a5.p2s \\
        --input out/play/r1.txt --watch lead:0xa397f0:0xa40 --watch pad:0x4b2570:0x20 \\
        --shot 24830 --shot 24900 --stop-vbl 25000 --out out/play/r1.jsonl

Loads the state (a probe.py --state-at state of a golden run: the input hook is
already patched in), then, with the EE frozen at a vsync, rewrites the input
tables and the trampoline from --input (buttons AND `#!stick` lines, input.py;
lines are keyed on the game VBlank counter like every retail script) so the
golden presses stop and the scripted sticks start. Then it polls the game
VBlank over PINE and writes one JSONL row per new VBlank with the --watch
ranges (hex; PINE reads, not atomic with the EE) and takes window screenshots
at --shot VBlanks (<out>.vNNNNN.png). PCSX2 is started and stopped by PID
(emu.Emu); one instance at a time.
"""
import argparse
import json
import os
import struct
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import emu  # noqa: E402
import input as inp  # noqa: E402
import live  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--state", required=True)
    ap.add_argument("--input", required=True)
    ap.add_argument("--watch", action="append", default=[], metavar="NAME:ADDR:SIZE")
    ap.add_argument("--shot", type=int, action="append", default=[])
    ap.add_argument("--stop-vbl", type=int, required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--speed", type=float, default=1.0)
    ap.add_argument("--slot", type=int, default=28021)
    ap.add_argument("--renderer", type=int, default=11, help="PCSX2 renderer (11 = null: no picture; 13 = software, for --shot)")
    ap.add_argument("--rel", action="store_true",
                    help="script keys, --shot and --stop-vbl are offsets from the VBlank the tables are patched at")
    a = ap.parse_args()
    a.state = os.path.abspath(a.state)
    ev = inp.parse_script(a.input)
    sev = inp.parse_sticks(a.input)
    watches = []
    for w in a.watch:
        n, ad, sz = w.split(":")
        ad, sz = int(ad, 0), int(sz, 0)
        watches.append((n, ad & ~7, (sz + (ad & 7) + 7) & ~7, ad & 7, sz))
    code = inp.trampoline(sticks=bool(sev))
    code += [0] * (-len(code) % 2)

    def tables(base):
        words = inp.build_table([(x + base, y + base, m) for x, y, m in ev])
        sticks = inp.build_stick_table([(x + base, y + base, w) for x, y, w in sev])
        blob = struct.pack("<I%dH" % len(words), len(words), *words)
        blob += bytes(-len(blob) % 8)
        sblob = struct.pack("<%dI" % len(sticks), *sticks) if sticks else b""
        sblob += bytes(-len(sblob) % 8)
        return blob, sblob

    e = emu.Emu(speed=a.speed, slot=a.slot, tag="stickprobe", statefile=a.state, renderer=a.renderer)
    out = open(a.out, "w", encoding="utf-8", newline="\n")
    try:
        pine = e.connect()
        sampler = live.LiveSampler(e.proc.pid, e.log, idle_ms=3.0)
        if not sampler.find_cpuregs():
            raise RuntimeError("cpuRegs not found")
        sampler.find_cpu_thread()
        # wait until the state is running (VBL counter moving)
        v0 = pine.read32(inp.VBL)
        t_end = time.time() + 120
        while pine.read32(inp.VBL) == v0:
            if time.time() > t_end:
                raise RuntimeError("game VBlank never moved after the state load")
            time.sleep(0.01)

        base = [0]

        def write():
            if a.rel:
                base[0] = pine.read32(inp.VBL)
            blob, sblob = tables(base[0])
            if sblob:
                pine.write_block(inp.STICK_TABLE, sblob)
            pine.write_block(inp.TABLE, blob)
            pine.write_block(inp.TRAMP, struct.pack("<%dI" % len(code), *code))
            pine.write64(inp.HOOK, inp._j(inp.TRAMP) | (inp.HOOK_ORIG[0] << 32))
        # any idle point (the EE waits for the vsync there); the BIOS-grid test
        # input.install uses does not hold this late in a run
        if sampler.frozen_call(lambda c: True, write, timeout=60) is None:
            raise RuntimeError("no vsync idle to patch the input tables")
        vbl = pine.read32(inp.VBL)
        print("stickprobe: tables patched at game vbl", vbl, flush=True)
        out.write(json.dumps({"t": "patched", "vbl": vbl}) + "\n")
        shots = sorted(set(x + base[0] for x in a.shot))
        a.stop_vbl += base[0]
        last = None
        while True:
            v = pine.read32(inp.VBL)
            if v == last:
                time.sleep(0.002)
                continue
            last = v
            row = {"t": "v", "vbl": v}
            for n, ad, sz, off, want in watches:
                row[n] = pine.read_block(ad, sz)[off:off + want].hex()
            out.write(json.dumps(row, separators=(",", ":")) + "\n")
            while shots and v >= shots[0]:
                live.window_shot(e.proc.pid, "%s.v%05d.png" % (os.path.splitext(a.out)[0], shots.pop(0)))
            if v >= a.stop_vbl:
                break
    finally:
        out.close()
        e.stop()
    return 0


if __name__ == "__main__":
    sys.exit(main())

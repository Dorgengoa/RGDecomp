# SPDX-License-Identifier: CC0-1.0
"""Reference audio capture from the portable PCSX2 (docs/SOUND.md "Validation").

PCSX2 2.6.3's release build has no SPU2 WAV dump (the `SPU2/Debug`
`Log_WAVE_Output` key is read but writes nothing) and its media capture needs
FFmpeg DLLs the portable copy does not ship. So the reference audio is taken
at the host audio sink instead: the SDL audio backend (`SPU2/Output/Backend =
SDL`) with SDL3's own `disk` driver, which writes the device stream (s16
stereo, 48000 Hz, PCSX2's SPU2 rate) to a raw file. Time stretching is off
(`SyncMode = Disabled`), so samples are never time-scaled; the disk driver
paces itself with sleeps, so the device consumes at roughly wall-clock rate.
If PCSX2 produces faster than the device consumes, its buffer overflows and
drops samples; if slower, the device underruns and gets filled. Both are
measured afterwards (tools/sound/audiocmp.py) against the movie WAVs, which
the SPU2 plays sample for sample.

Alignment to VBlank: while the run goes, PINE polls the game's VBlank counter
[0x004810C4] and the movie audio decoder's "bytes sent to the IOP" (+0x54 of
D_004B32D0, docs/VALIDATION.md section 6) together with the raw file size and
a host timestamp, and writes them to <out>.poll.tsv. The first poll where the
decoder count leaves 0 gives the VBlank the movie audio started in; the
analysis anchors the capture's movie onset to it.

PCSX2 is used as an external program only; nothing here comes from its
source. The run uses the isolated copy in .tools/pcsx2 (emu.py), never the
user's install, and stops the process by PID.

usage:
  python tools/trace/audiocap.py --out out/audio/pcsx2_title --stop-vbl 2400
"""
import argparse
import os
import struct
import sys
import time
import wave

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import emu  # noqa: E402

VBL_ADDR = 0x004810C4
MOVIE_AUDIO_BYTES = 0x004B32D0 + 0x54


def raw_to_wav(raw, path, rate=48000):
    with open(raw, "rb") as f:
        data = f.read()
    data = data[:len(data) // 4 * 4]
    with wave.open(path, "wb") as w:
        w.setnchannels(2)
        w.setsampwidth(2)
        w.setframerate(rate)
        w.writeframes(data)
    return len(data) // 4


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--out", required=True, help="output prefix (.raw, .wav, .poll.tsv)")
    ap.add_argument("--stop-vbl", type=int, default=2400, help="stop at this game VBlank")
    ap.add_argument("--timeout", type=float, default=600.0, help="wall-clock limit, seconds")
    ap.add_argument("--speed", type=float, default=1.0, help="PCSX2 NominalScalar")
    ap.add_argument("--timescale", default="1.0", help="SDL_AUDIO_DISK_TIMESCALE")
    ap.add_argument("--frames", default="4795",
                    help="SDL_AUDIO_DEVICE_SAMPLE_FRAMES (4795 -> 99 ms sleeps, about 48.2k frames/s)")
    ap.add_argument("--buffer-ms", type=int, default=200, help="SPU2/Output/BufferMS")
    ap.add_argument("--latency-ms", type=int, default=100, help="SPU2/Output/OutputLatencyMS")
    ap.add_argument("--input", help="tools/trace input script (needs --speed 0.5 or less: the "
                    "hook is installed at a frozen vsync, as trace.py does)")
    ap.add_argument("--idle-ms", type=float, default=3.0)
    ap.add_argument("--no-memcard", action="store_true", help="no card (default: fresh card)")
    ap.add_argument("--set", action="append", default=[], metavar="Section/Key=Value")
    ap.add_argument("--slot", type=int, default=emu.DEFAULT_SLOT)
    ap.add_argument("--iso", default=emu.DEFAULT_ISO)
    ap.add_argument("--poll-ms", type=float, default=2.0)
    ap.add_argument("--raw-dir", help="write the raw stream here (a fast local disk; the "
                    "disk driver blocks on slow writes), then move it next to --out")
    a = ap.parse_args()

    out = os.path.abspath(a.out)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    raw = out + ".raw"
    if a.raw_dir:
        os.makedirs(a.raw_dir, exist_ok=True)
        raw = os.path.join(os.path.abspath(a.raw_dir), os.path.basename(out) + ".raw")
    if os.path.exists(raw):
        os.remove(raw)
    os.environ["SDL_AUDIO_DRIVER"] = "disk"
    os.environ["SDL_AUDIO_DISK_OUTPUT_FILE"] = raw
    os.environ["SDL_AUDIO_DISK_TIMESCALE"] = str(a.timescale)
    os.environ["SDL_AUDIO_DEVICE_SAMPLE_FRAMES"] = str(a.frames)
    overrides = ["SPU2/Output/Backend=SDL", "SPU2/Output/SyncMode=Disabled",
                 "SPU2/Output/ExpansionMode=Disabled", "SPU2/Output/OutputMuted=false",
                 "SPU2/Output/StandardVolume=100", "SPU2/Output/BufferMS=%d" % a.buffer_ms,
                 "SPU2/Output/OutputLatencyMS=%d" % a.latency_ms,
                 "SPU2/Output/OutputLatencyMinimal=false"] + a.set
    tag = "audiocap_" + os.path.basename(out)
    e = emu.Emu(iso=a.iso, speed=a.speed, slot=a.slot, tag=tag, overrides=overrides,
                memcard=not a.no_memcard)
    rows = []
    try:
        pine = e.connect()
        if a.input:
            import input as inp
            import live
            words = inp.build_table(inp.parse_script(a.input))
            sampler = live.LiveSampler(e.proc.pid, e.log, idle_ms=a.idle_ms)
            if not sampler.find_cpuregs():
                raise RuntimeError("cpuRegs not found in PCSX2 memory")
            sampler.find_cpu_thread()
            v = inp.install(pine, words, sampler=sampler)
            print("audiocap: input hook installed at game vbl", v, flush=True)
        t0 = time.perf_counter()
        last = None
        while time.perf_counter() - t0 < a.timeout:
            try:
                vbl = pine.read32(VBL_ADDR)
                mab = pine.read32(MOVIE_AUDIO_BYTES)
            except Exception:
                break
            t = time.perf_counter() - t0
            try:
                size = os.path.getsize(raw)
            except OSError:
                size = 0
            key = (vbl, mab, size)
            if key != last:
                rows.append((t, vbl, mab, size // 4))
                last = key
            if vbl >= a.stop_vbl and vbl < 0x10000000:
                break
            time.sleep(a.poll_ms / 1000.0)
    finally:
        e.stop()
    with open(out + ".poll.tsv", "w") as f:
        f.write("# audiocap: speed %s timescale %s frames %s buffer_ms %d latency_ms %d input %s\n"
                % (a.speed, a.timescale, a.frames, a.buffer_ms, a.latency_ms, a.input))
        f.write("# t_s\tgame_vbl\tmovie_audio_bytes\traw_frames\n")
        for r in rows:
            f.write("%.4f\t%d\t%d\t%d\n" % r)
    n = raw_to_wav(raw, out + ".wav")
    os.remove(raw)
    print("audiocap: %d frames (%.2f s) -> %s.wav, %d poll rows, last vbl %d"
          % (n, n / 48000.0, out, len(rows), rows[-1][1] if rows else -1))


if __name__ == "__main__":
    main()

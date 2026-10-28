#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare the native audio engine's output with the HLE oracle (docs/NATIVE-AUDIO.md).

    python tools/native/audio_compare.py HLE.wav NATIVE.wav [--align end|start|N]
                                         [--min-snr 30] [--min-window 15] [--table]

A compare-mode run (RG_AUDIO=compare) writes the HLE's output (what is heard) to
$RG_AUDIO_WAV and the engine's to $RG_AUDIO_NATIVE_WAV, frame-aligned (both 48 kHz
s16 stereo, the same frames per field).  Metric, over the frames both files hold:

  snr    10 log10(sum ref^2 / sum (ref - native)^2), whole signal, both channels
  window the same per 50 ms window, for windows whose reference RMS is above
         -60 dBFS; the worst window and the 1st percentile are reported
  lag    the offset in -8..8 frames with the least error (0 = sample aligned)
  level  RMS of both in dBFS, and per second with --table

Exit 0 when snr >= --min-snr, the 1st-percentile window >= --min-window and lag = 0;
1 otherwise (2 = bad input).

--envelope compares two runs whose events may sit a few ms apart (e.g. RG_AUDIO=native
against a compare run's engine output: native mode applies commands on the caller's
frame and ticks from its own origin, so sequenced notes can move by up to one 240 Hz
tick).  Instead of samples it compares, over windows above -60 dBFS, the 50 ms RMS level
(|delta dB| median and 95th percentile) and per second the log spectrum in semitone-wide
bands from 100 Hz to 12 kHz (correlation; a pitch error decorrelates tonal content).
Pass: p95 |delta dB| <= --max-db (3) and the 5th-percentile spectral correlation >=
--min-corr (0.9).  A deliberately broken engine (RG_AUDIO_BREAK=pitch|volume|
reverb) must fail: that is the control that shows the metric is armed.
"""
from __future__ import annotations

import argparse
import sys
import wave

import numpy as np


def load(path: str) -> np.ndarray:
    with wave.open(path, "rb") as w:
        if w.getnchannels() != 2 or w.getsampwidth() != 2 or w.getframerate() != 48000:
            raise SystemExit(f"{path}: need 48 kHz s16 stereo")
        n = w.getnframes()
        raw = w.readframes(n)
    a = np.frombuffer(raw, dtype="<i2")
    a = a[: (len(a) // 2) * 2]
    return a.reshape(-1, 2).astype(np.float64)


def db(x: float) -> float:
    return 10.0 * np.log10(x) if x > 0 else -999.0


def envelope(ref: np.ndarray, nat: np.ndarray, a) -> int:
    n = len(ref)
    w = 2400
    nw = n // w
    pr = (ref[: nw * w].reshape(nw, w, 2) ** 2).mean(axis=(1, 2))
    pn = (nat[: nw * w].reshape(nw, w, 2) ** 2).mean(axis=(1, 2))
    floor = (32768.0 ** 2) * 1e-6
    loud = (pr > floor) | (pn > floor)
    ddb = np.abs(10 * np.log10(np.maximum(pr, 1e-3)) - 10 * np.log10(np.maximum(pn, 1e-3)))[loud]
    # semitone bands 100 Hz .. 12 kHz on 1 s FFTs of the mono mix
    edges = 100.0 * 2 ** (np.arange(0, 12 * np.log2(12000 / 100) + 1) / 12.0)
    f = np.fft.rfftfreq(48000, 1 / 48000)
    band = np.digitize(f, edges)
    corrs = []
    secs = []
    for s in range(n // 48000):
        r = ref[s * 48000:(s + 1) * 48000].mean(axis=1)
        x = nat[s * 48000:(s + 1) * 48000].mean(axis=1)
        if (r ** 2).mean() < floor and (x ** 2).mean() < floor:
            continue
        win = np.hanning(48000)
        R = np.abs(np.fft.rfft(r * win)) ** 2
        X = np.abs(np.fft.rfft(x * win)) ** 2
        br = np.bincount(band, R, minlength=len(edges) + 1)[1:len(edges)]
        bx = np.bincount(band, X, minlength=len(edges) + 1)[1:len(edges)]
        lr, lx = 10 * np.log10(br + 1e-3), 10 * np.log10(bx + 1e-3)
        c = float(np.corrcoef(lr, lx)[0, 1])
        corrs.append(c)
        secs.append(s)
    corrs = np.array(corrs)
    p95 = float(np.percentile(ddb, 95)) if ddb.size else 0.0
    c05 = float(np.percentile(corrs, 5)) if corrs.size else 1.0
    print(f"frames {n} ({n / 48000:.1f} s), {ddb.size} loud 50 ms windows, {corrs.size} loud seconds")
    print(f"level |delta dB|: median {float(np.median(ddb)) if ddb.size else 0:.2f}, p95 {p95:.2f}, max {float(ddb.max()) if ddb.size else 0:.2f}")
    print(f"semitone-band spectrum correlation: median {float(np.median(corrs)) if corrs.size else 1:.4f}, "
          f"p5 {c05:.4f}, min {float(corrs.min()) if corrs.size else 1:.4f}")
    if corrs.size:
        order = np.argsort(corrs)[:5]
        print("lowest seconds: " + ", ".join(f"{secs[i] + a.from_sec:.0f}s {corrs[i]:.3f}" for i in order))
    ok = p95 <= a.max_db and c05 >= a.min_corr
    print("PASS" if ok else "FAIL")
    return 0 if ok else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("hle")
    ap.add_argument("native")
    ap.add_argument("--align", default="end", help="end (default), start, or a frame offset of NATIVE")
    ap.add_argument("--min-snr", type=float, default=30.0)
    ap.add_argument("--min-window", type=float, default=15.0)
    ap.add_argument("--from-sec", type=float, default=0.0)
    ap.add_argument("--table", action="store_true", help="per-second levels and SNR")
    ap.add_argument("--envelope", action="store_true", help="level/spectrum comparison (timing-tolerant)")
    ap.add_argument("--max-db", type=float, default=3.0)
    ap.add_argument("--min-corr", type=float, default=0.9)
    a = ap.parse_args(argv)
    ref, nat = load(a.hle), load(a.native)
    if a.align == "end":
        n = min(len(ref), len(nat))
        ref, nat = ref[len(ref) - n:], nat[len(nat) - n:]
    elif a.align == "start":
        n = min(len(ref), len(nat))
        ref, nat = ref[:n], nat[:n]
    else:
        off = int(a.align)
        if off >= 0:
            nat = nat[off:]
        else:
            ref = ref[-off:]
        n = min(len(ref), len(nat))
        ref, nat = ref[:n], nat[:n]
    s0 = int(a.from_sec * 48000)
    ref, nat = ref[s0:], nat[s0:]
    n = len(ref)
    if n < 4800:
        print("too short")
        return 2
    if a.envelope:
        return envelope(ref, nat, a)
    d = ref - nat
    p, e = float((ref ** 2).sum()), float((d ** 2).sum())
    snr = db(p / e) if e > 0 else 200.0
    best = None
    for lag in range(-8, 9):
        r = ref[16:-16]
        x = nat[16 + lag: len(nat) - 16 + lag]
        el = float(((r - x) ** 2).sum())
        if best is None or el < best[1]:
            best = (lag, el)
    w = 2400
    nw = n // w
    rw = ref[: nw * w].reshape(nw, w, 2)
    dw = d[: nw * w].reshape(nw, w, 2)
    pw = (rw ** 2).sum(axis=(1, 2))
    ew = (dw ** 2).sum(axis=(1, 2))
    loud = pw / (w * 2.0) > (32768.0 ** 2) * 1e-6
    wsnr = np.where(ew > 0, 10 * np.log10(np.maximum(pw, 1e-9) / np.maximum(ew, 1e-9)), 200.0)[loud]
    worst = float(wsnr.min()) if wsnr.size else 200.0
    p01 = float(np.percentile(wsnr, 1)) if wsnr.size else 200.0
    rms_r = db(p / (n * 2) / 32768.0 ** 2)
    rms_n = db(float((nat ** 2).sum()) / (n * 2) / 32768.0 ** 2)
    print(f"frames {n} ({n / 48000:.1f} s), reference {rms_r:.1f} dBFS rms, native {rms_n:.1f} dBFS rms")
    print(f"snr {snr:.1f} dB, best lag {best[0]}, windows (50 ms, > -60 dBFS): {wsnr.size}, "
          f"worst {worst:.1f} dB, 1st percentile {p01:.1f} dB, median {float(np.median(wsnr)) if wsnr.size else 0:.1f} dB")
    print(f"peak |diff| {int(np.abs(d).max())}, peak ref {int(np.abs(ref).max())}, peak native {int(np.abs(nat).max())}")
    if wsnr.size:
        idx = np.nonzero(loud)[0]
        order = np.argsort(wsnr)[:5]
        print("worst windows: " + ", ".join(f"{(idx[i] * w + s0) / 48000:.2f}s {wsnr[i]:.1f} dB" for i in order))
    if a.table:
        print("sec\tref_db\tnat_db\tsnr_db")
        for s in range(n // 48000):
            r = ref[s * 48000:(s + 1) * 48000]
            x = nat[s * 48000:(s + 1) * 48000]
            pr, pe = float((r ** 2).sum()), float(((r - x) ** 2).sum())
            print(f"{s + a.from_sec:.0f}\t{db(pr / 96000 / 32768.0 ** 2):.1f}\t{db(float((x ** 2).sum()) / 96000 / 32768.0 ** 2):.1f}\t"
                  f"{db(pr / pe) if pe > 0 else 200.0:.1f}")
    ok = snr >= a.min_snr and p01 >= a.min_window and best[0] == 0
    print("PASS" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())

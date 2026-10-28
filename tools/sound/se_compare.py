# SPDX-License-Identifier: CC0-1.0
"""Measure the sound effects that play over a movie in a capture (own code, CC0).

For each approximate SE time: locate the movie in the capture around it (sample
exact, so PCSX2 captures with drops/inserts work), remove the movie with
se_extract's least-squares FIR, find the SE onset, and report its fundamental
(FFT peak with parabolic interpolation) and its level (peak, RMS over the first
0.1 s, per channel).  A plain SE render (no movie, e.g. rg-sound-play) is
measured with --no-movie.

usage: se_compare.py CAP.wav --movie 00/TITLE02 --at 45.3,48.6 [--off N] [--f0 1500,3000]
       se_compare.py SE.wav --no-movie --at 0
  --off: capture frame of movie sample 0 near the first SE (default: searched)
"""
import argparse
import os
import sys

import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from audiocmp import RATE, dbfs, load, movie_wav  # noqa: E402
from se_extract import extract  # noqa: E402


def local_offset(cap, mv, at, guess, search):
    """Offset (capture frame - movie frame) for the 0.25 s of capture that ends
    50 ms before `at`, by normalised correlation over guess +- search (step 1).
    Short, because PCSX2 captures drop or insert blocks every few seconds."""
    n = RATE // 4
    s = max(0, at - n - RATE // 20)
    a = cap[s:s + n, 0].astype(np.float64)
    best = (None, -1.0)
    for off in range(guess - search, guess + search + 1):
        k = s - off
        if k < 0 or k + n > len(mv):
            continue
        b = mv[k:k + n, 0].astype(np.float64)
        v = float(a @ b) / (np.sqrt(float(a @ a) * float(b @ b)) + 1e-9)
        if v > best[1]:
            best = (off, v)
    return best


def coarse_offset(cap, mv, at, step=256):
    """Coarse offset by FFT cross-correlation of 2 s of capture against the movie."""
    from scipy.signal import fftconvolve
    n = 2 * RATE
    s = max(0, at - n - RATE // 4)
    a = cap[s:s + n, 0].astype(np.float64)
    b = mv[:, 0].astype(np.float64)
    c = fftconvolve(b, a[::-1], mode="valid")
    k = int(np.argmax(c))
    return s - k


def onset(se, floor_frac=0.4):
    e = np.abs(se).max(1)
    pk = e.max()
    i = int(np.argmax(e > floor_frac * pk))
    return i, pk


def f0(x, lo, hi, nfft=16384):
    w = np.hanning(len(x))
    sp = np.abs(np.fft.rfft(x * w, nfft))
    f = np.fft.rfftfreq(nfft, 1.0 / RATE)
    m = (f >= lo) & (f <= hi)
    i = int(np.argmax(np.where(m, sp, 0)))
    a, b, c = np.log(sp[i - 1] + 1e-12), np.log(sp[i] + 1e-12), np.log(sp[i + 1] + 1e-12)
    d = 0.5 * (a - c) / (a - 2 * b + c)
    return (i + d) * RATE / nfft


def measure(se, lo, hi):
    i, pk = onset(se)
    seg = se[i:i + int(0.1 * RATE)]
    x = se[i + int(0.01 * RATE):i + int(0.01 * RATE) + 4096].mean(1)
    rms = np.sqrt((seg ** 2).mean(0))
    return dict(onset=i, freq=f0(x, lo, hi), peak=np.abs(seg).max(0), rms=rms)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cap")
    ap.add_argument("--movie", default="00/TITLE02")
    ap.add_argument("--no-movie", action="store_true")
    ap.add_argument("--at", required=True, help="approximate SE times in seconds, comma separated")
    ap.add_argument("--off", type=int, default=None)
    ap.add_argument("--search", type=int, default=1500)
    ap.add_argument("--f0", default="1500,3000", help="fundamental search band in Hz")
    ap.add_argument("--len", type=float, default=0.4)
    a = ap.parse_args()
    cap, _ = load(a.cap)
    lo, hi = (float(v) for v in a.f0.split(","))
    mv = None if a.no_movie else load(movie_wav(a.movie))[0]
    for t in (float(v) for v in a.at.split(",")):
        at = int(t * RATE)
        if mv is None:
            s, se = at, cap[at:at + int(a.len * RATE)].astype(np.float64)
            tag = ""
        else:
            guess = a.off if a.off is not None else coarse_offset(cap, mv, at)
            off, ncc = local_offset(cap, mv, at, guess, a.search if a.off is None else 64)
            s, se = extract(cap, mv, off, at, int(a.len * RATE), int(0.25 * RATE))
            tag = " movie off %+d (ncc %.4f)" % (off, ncc)
        m = measure(se, lo, hi)
        print("SE near %7.3fs: onset %8.4fs%s  f0 %7.1f Hz  peak L/R %5.0f/%5.0f (%.1f/%.1f dBFS)"
              "  RMS 0.1s L/R %6.1f/%6.1f (%.1f/%.1f dBFS)"
              % (t, (s + m["onset"]) / RATE, tag, m["freq"], m["peak"][0], m["peak"][1], dbfs(m["peak"][0]),
                 dbfs(m["peak"][1]), m["rms"][0], m["rms"][1], dbfs(m["rms"][0]), dbfs(m["rms"][1])))


if __name__ == "__main__":
    main()

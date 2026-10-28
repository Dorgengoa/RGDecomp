# SPDX-License-Identifier: CC0-1.0
"""Isolate a sound effect that plays over a movie (own code, CC0).

The movie part of a capture is predicted from the movie WAV by a least-squares
FIR (taps -8..+56 per channel, plus DC), fitted on the window around the SE, so
whatever the emulator's or the port's filtering of the movie path is, it is
removed; what is left is the SE (and noise).

usage: se_extract.py CAP.wav MOVIE CAP_OFF AT_S [--len 1.0] [--pre 0.25] -o SE.wav
  CAP_OFF = capture frame of movie sample 0 (audiocmp.py movie / report)
  AT_S    = capture time near the SE onset
"""
import argparse
import os
import sys
import wave

import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from audiocmp import RATE, load, movie_wav  # noqa: E402


def extract(cap, mv, off, at, n, pre, taps=(-8, 56)):
    s = max(0, at - pre)
    lo, hi = taps
    out = np.zeros((n, 2))
    best_shift = 0
    for ch in (0, 1):
        y = cap[s:s + n, ch].astype(np.float64)
        k0 = s - off
        cols = [mv[k0 - j:k0 - j + n, ch].astype(np.float64) for j in range(lo, hi + 1)]
        X = np.column_stack(cols + [np.ones(n)])
        c, *_ = np.linalg.lstsq(X, y, rcond=None)
        out[:, ch] = y - X @ c
    return s, out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cap")
    ap.add_argument("movie")
    ap.add_argument("off", type=int)
    ap.add_argument("at", type=float)
    ap.add_argument("--len", type=float, default=1.0)
    ap.add_argument("--pre", type=float, default=0.25)
    ap.add_argument("-o", "--out")
    a = ap.parse_args()
    cap, _ = load(a.cap)
    mv, _ = load(movie_wav(a.movie))
    s, se = extract(cap, mv, a.off, int(a.at * RATE), int(a.len * RATE), int(a.pre * RATE))
    e = np.sqrt((se ** 2).mean(1))
    print("from %.4f s: residual peak %.0f, RMS %.1f" % (s / RATE, np.abs(se).max(), np.sqrt((se ** 2).mean())))
    if a.out:
        with wave.open(a.out, "wb") as w:
            w.setnchannels(2)
            w.setsampwidth(2)
            w.setframerate(RATE)
            w.writeframes(np.clip(np.round(se), -32768, 32767).astype("<i2").tobytes())


if __name__ == "__main__":
    main()

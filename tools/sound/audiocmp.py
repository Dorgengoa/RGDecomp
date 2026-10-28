# SPDX-License-Identifier: CC0-1.0
"""Compare the port's audio with a PCSX2 reference capture (own code, CC0).

Inputs are 48 kHz s16 stereo WAVs: the port's `RG_AUDIO_WAV` dump (sample 0 =
virtual time 0, <wav>.fields.tsv maps fields to frames) and a PCSX2 capture from
tools/trace/audiocap.py (<prefix>.poll.tsv maps host time, game VBlank and
capture frames). The movie WAVs that rg-extract wrote (`data/converted/MOVIE`)
are the ground truth for movie audio: the SPU2 plays them sample for sample.

usage:
  audiocmp.py movie  CAP.wav [--movies 00/TITLE01,00/TITLE02]   sliding match vs the movie WAVs
  audiocmp.py stats  CAP.wav [--from S --to S]                   per-second RMS/peak/clip/gaps
  audiocmp.py compare PORT.wav PCSX2.wav --port-at S --ref-at S --len S [--name N]
  audiocmp.py report PORT.wav PCSX2.wav                         everything above for the title run
"""
import argparse
import os
import sys
import wave

import numpy as np
from scipy.signal import fftconvolve

RATE = 48000
DATA = os.environ.get("RG_DATA", os.path.join(os.path.dirname(os.path.dirname(
    os.path.dirname(os.path.abspath(__file__)))), "data"))


def load(path):
    with wave.open(path) as w:
        if w.getsampwidth() != 2 or w.getnchannels() != 2:
            raise SystemExit("%s: need s16 stereo" % path)
        rate = w.getframerate()
        d = np.frombuffer(w.readframes(w.getnframes()), np.int16).reshape(-1, 2)
    return d, rate


def movie_wav(name):
    return os.path.join(DATA, "converted", "MOVIE", name.replace("\\", "/") + ".wav")


def dbfs(x):
    return 20 * np.log10(max(float(x), 1e-3) / 32768.0)


# ---------------------------------------------------------------- movie match
def match_windows(cap, refs, win=24000, hop=24000, floor=30.0, ch=0, lo=0, hi=None):
    """For each window of the capture, the best normalised cross-correlation
    against every reference (left channel). Returns rows
    (cap_pos, ref_name, ref_pos, ncc, gainL, gainR)."""
    hi = len(cap) if hi is None else min(hi, len(cap))
    out = []
    pre = {}
    for n, r in refs.items():
        x = r[:, ch].astype(np.float64)
        cs = np.concatenate([[0.0], np.cumsum(x * x)])
        pre[n] = (x, cs)
    for s in range(lo, hi - win, hop):
        seg = cap[s:s + win].astype(np.float64)
        sl = seg[:, ch]
        es = float(sl @ sl)
        if np.sqrt(es / win) < floor:
            continue
        best = None
        for n, (x, cs) in pre.items():
            if len(x) < win:
                continue
            c = fftconvolve(x, sl[::-1], "valid")
            er = cs[win:] - cs[:-win]
            e = np.sqrt(np.maximum(er, 0.01 * es) * es)
            k = int(np.argmax(c / e))
            v = float(c[k] / e[k])
            if best is None or v > best[1]:
                best = (n, v, k)
        n, v, k = best
        r = refs[n][k:k + win].astype(np.float64)
        g = [float(seg[:, i] @ r[:, i]) / max(float(r[:, i] @ r[:, i]), 1e-9) for i in (0, 1)]
        out.append((s, n, k, v, g[0], g[1]))
    return out


def movie_segments(rows, ncc_min=0.9):
    """Group good window matches into runs with a constant (cap - ref) offset;
    a change of offset inside one movie is a drop (offset falls) or an
    insertion (offset grows) in the capture."""
    segs = []
    for s, n, k, v, gl, gr in rows:
        if v < ncc_min:
            continue
        off = s - k
        if segs and segs[-1]["movie"] == n and abs(off - segs[-1]["off"]) <= 2 and k >= segs[-1]["ref_end"] - 1:
            g = segs[-1]
            g["ref_end"] = k + 24000
            g["cap_end"] = s + 24000
            g["n"] += 1
            g["gl"].append(gl)
            g["gr"].append(gr)
            g["ncc"].append(v)
        else:
            segs.append(dict(movie=n, off=off, ref_start=k, ref_end=k + 24000, cap_start=s,
                             cap_end=s + 24000, n=1, gl=[gl], gr=[gr], ncc=[v]))
    return segs


def refine_offset(cap, ref, cap_pos, ref_pos, n=48000, search=64):
    """Sample-exact offset near a coarse match: max correlation over +-search."""
    a = cap[cap_pos:cap_pos + n, 0].astype(np.float64)
    best = (None, -1e30)
    for d in range(-search, search + 1):
        p = ref_pos + d
        if p < 0 or p + n > len(ref):
            continue
        b = ref[p:p + n, 0].astype(np.float64)
        v = float(a @ b) / (np.sqrt(float(a @ a) * float(b @ b)) + 1e-9)
        if v > best[1]:
            best = (d, v)
    return best


def residual(cap, ref, cap_pos, ref_pos, n):
    """Least-squares gain per channel and the residual after it, in dB below
    the signal (how sample-exact the capture is)."""
    a = cap[cap_pos:cap_pos + n].astype(np.float64)
    b = ref[ref_pos:ref_pos + n].astype(np.float64)
    res = []
    for i in (0, 1):
        g = float(a[:, i] @ b[:, i]) / max(float(b[:, i] @ b[:, i]), 1e-9)
        e = a[:, i] - g * b[:, i]
        snr = 10 * np.log10(max(float(a[:, i] @ a[:, i]), 1e-9) / max(float(e @ e), 1e-9))
        res.append((g, snr, float(np.abs(e).max())))
    return res


# ---------------------------------------------------------------- stats
def per_second(d, lo_s=0, hi_s=None):
    n = len(d) // RATE
    hi_s = n if hi_s is None else min(hi_s, n)
    rows = []
    for s in range(lo_s, hi_s):
        seg = d[s * RATE:(s + 1) * RATE].astype(np.float64)
        rl, rr = np.sqrt((seg ** 2).mean(0))
        pk = int(np.abs(d[s * RATE:(s + 1) * RATE].astype(np.int32)).max())
        clip = int((np.abs(d[s * RATE:(s + 1) * RATE].astype(np.int32)) >= 32767).sum())
        rows.append((s, rl, rr, pk, clip))
    return rows


def gaps(d, min_len=96, floor=200.0):
    """Runs of exact digital zero (both channels) or of a held frame that
    start and end next to non-quiet audio: candidate dropouts."""
    z = (d == 0).all(1)
    held = np.concatenate([[False], (np.diff(d.astype(np.int32), axis=0) == 0).all(1)])
    out = []
    for kind, m in (("zero", z), ("held", held & ~z)):
        dz = np.diff(np.concatenate([[0], m.astype(np.int8), [0]]))
        st = np.where(dz == 1)[0]
        en = np.where(dz == -1)[0]
        for a, b in zip(st, en):
            if b - a < min_len:
                continue
            pre = d[max(0, a - 480):a].astype(np.float64)
            post = d[b:b + 480].astype(np.float64)
            if len(pre) and len(post) and np.sqrt((pre ** 2).mean()) > floor and np.sqrt((post ** 2).mean()) > floor:
                out.append((kind, int(a), int(b - a)))
    return out


def spectrum(d, lo, n, nfft=4096):
    """Mean power spectrum (dB) of L+R over [lo, lo+n), Hann windows, 50% hop."""
    x = d[lo:lo + n].astype(np.float64).mean(1)
    w = np.hanning(nfft)
    acc = np.zeros(nfft // 2 + 1)
    k = 0
    for s in range(0, len(x) - nfft, nfft // 2):
        acc += np.abs(np.fft.rfft(x[s:s + nfft] * w)) ** 2
        k += 1
    return 10 * np.log10(acc / max(k, 1) + 1e-6)


def band_compare(sa, sb, nfft=4096):
    """Spectral similarity: correlation of the dB spectra 50 Hz..16 kHz and the
    mean level difference per octave band (b - a)."""
    f = np.fft.rfftfreq(nfft, 1.0 / RATE)
    m = (f >= 50) & (f <= 16000)
    corr = float(np.corrcoef(sa[m], sb[m])[0, 1])
    bands = []
    lo = 62.5
    while lo < 16000:
        hi = lo * 2
        mm = (f >= lo) & (f < hi)
        pa = 10 * np.log10(np.mean(10 ** (sa[mm] / 10)))
        pb = 10 * np.log10(np.mean(10 ** (sb[mm] / 10)))
        bands.append((lo, hi, pb - pa))
        lo = hi
    return corr, bands


def xcorr_offset(a, b, max_lag):
    """Lag (in frames) of b relative to a that maximises the normalised
    correlation of their (L+R) signals; positive = b is later."""
    x = a.astype(np.float64).mean(1)
    y = b.astype(np.float64).mean(1)
    n = min(len(x), len(y))
    x, y = x[:n], y[:n]
    c = fftconvolve(y, x[::-1], "full")
    mid = n - 1
    lo, hi = mid - max_lag, mid + max_lag + 1
    k = int(np.argmax(c[lo:hi])) + lo
    v = float(c[k]) / (np.sqrt(float(x @ x) * float(y @ y)) + 1e-9)
    return k - mid, v


# ---------------------------------------------------------------- commands
def cmd_movie(a):
    cap, rate = load(a.cap)
    refs = {m: load(movie_wav(m))[0] for m in a.movies.split(",")}
    rows = match_windows(cap, refs, lo=int(a.from_s * RATE), hi=int(a.to_s * RATE) if a.to_s else None)
    if a.verbose:
        for s, n, k, v, gl, gr in rows:
            print("%8.3fs %-12s ref %8.3fs off %+9d ncc %.4f gain L %.4f R %.4f"
                  % (s / RATE, n, k / RATE, s - k, v, gl, gr))
    segs = movie_segments(rows)
    for g in segs:
        d, v = refine_offset(cap, refs[g["movie"]], g["cap_start"], g["ref_start"])
        print("%-12s capture %8.3f-%8.3fs = movie %7.3f-%7.3fs  off %+d (refined %+d, ncc %.5f)  windows %d  gain L %.4f R %.4f"
              % (g["movie"], g["cap_start"] / RATE, g["cap_end"] / RATE, g["ref_start"] / RATE,
                 g["ref_end"] / RATE, g["off"], g["off"] - (d or 0), v, g["n"],
                 np.median(g["gl"]), np.median(g["gr"])))
    return segs


def cmd_stats(a):
    d, rate = load(a.cap)
    print("%s: %d frames, %.3f s, rate %d" % (a.cap, len(d), len(d) / rate, rate))
    for s, rl, rr, pk, clip in per_second(d, int(a.from_s), int(a.to_s) if a.to_s else None):
        print("%5d s  RMS L %6.1f dBFS  R %6.1f dBFS  peak %5d  clipped %d" % (s, dbfs(rl), dbfs(rr), pk, clip))
    g = gaps(d)
    print("gaps (zero/held runs >= 2 ms between non-quiet audio): %d" % len(g))
    for kind, at, n in g[:40]:
        print("  %s at %.4f s, %d frames" % (kind, at / RATE, n))


# ---------------------------------------------------------------- time maps
def port_fields(wav):
    """<wav>.fields.tsv -> (field, kernel_vblank, game_vblank, frames_end, cycle) rows."""
    p = wav + ".fields.tsv"
    if not os.path.exists(p):
        return None
    return np.loadtxt(p, comments="#", ndmin=2)


def port_frame_to_field(ft, frame):
    """Field (count of completed fields) whose host half delivered `frame`."""
    if ft is None:
        return float("nan")
    i = int(np.searchsorted(ft[:, 3], frame, side="right"))
    return float(ft[min(i, len(ft) - 1), 0])


def pcsx2_poll(wav):
    p = os.path.splitext(wav)[0] + ".poll.tsv"
    if not os.path.exists(p):
        return None
    return np.loadtxt(p, comments="#", ndmin=2)


def pcsx2_frame_to_vbl(poll, frame, latency_frames=0):
    """Game VBlank at the host time the device wrote `frame`, minus the output
    latency (frames that sat in PCSX2's buffer); +-1 device chunk."""
    if poll is None:
        return float("nan")
    t = np.interp(frame + latency_frames, poll[:, 3], poll[:, 0])
    return float(np.interp(t, poll[:, 0], poll[:, 1]))


def first_audible(d, floor=64):
    a = (np.abs(d.astype(np.int32)) > floor).any(1)
    idx = np.where(a)[0]
    return int(idx[0]) if len(idx) else -1


# ---------------------------------------------------------------- report
def movie_map(cap, refs):
    rows = match_windows(cap, refs)
    segs = movie_segments(rows)
    for g in segs:
        d, v = refine_offset(cap, refs[g["movie"]], g["cap_start"], g["ref_start"])
        g["off"] -= (d or 0)
        g["ncc_fine"] = v
    return segs


def seg_blocks(segs, n=RATE):
    """(capture frame, movie frame) of every whole n-frame block inside the segments."""
    for g in segs:
        for s in range(g["cap_start"], g["cap_end"] - n + 1, n):
            yield s, s - g["off"]


def cmd_report(a):
    port, _ = load(a.port)
    ref, _ = load(a.pcsx2)
    movies = a.movies.split(",")
    refs = {m: load(movie_wav(m))[0] for m in movies}
    ft = port_fields(a.port)
    poll = pcsx2_poll(a.pcsx2)
    print("== inputs")
    for name, d in (("port", port), ("pcsx2", ref)):
        x = np.abs(d.astype(np.int32))
        print("%-6s %9d frames %7.2f s  peak %5d  clipped(|x|>=32767) %d  first audible %.3f s"
              % (name, len(d), len(d) / RATE, x.max(), int((x >= 32767).sum()), first_audible(d) / RATE))
    print("== movie segments (sample-exact runs; a change of offset = capture drop/insert)")
    maps = {}
    for name, d in (("port", port), ("pcsx2", ref)):
        segs = movie_map(d, refs)
        maps[name] = segs
        for g in segs:
            start = g["off"]  # capture frame of movie sample 0
            if name == "port":
                where = " field %.0f" % port_frame_to_field(ft, start)
            else:
                where = " vbl ~%.0f" % pcsx2_frame_to_vbl(poll, start, a.latency)
            print("%-6s %-12s cap %8.3f-%8.3fs movie %7.3f-%7.3fs  movie@0 = cap %9d (%.3f s%s)  ncc %.5f  gain L %.4f R %.4f"
                  % (name, g["movie"], g["cap_start"] / RATE, g["cap_end"] / RATE, g["ref_start"] / RATE,
                     g["ref_end"] / RATE, start, start / RATE, where, g["ncc_fine"],
                     np.median(g["gl"]), np.median(g["gr"])))
    print("== per movie: level, residual (non-movie content), port vs pcsx2")
    for m in movies:
        ps = [g for g in maps["port"] if g["movie"] == m]
        rs = [g for g in maps["pcsx2"] if g["movie"] == m]
        if not ps or not rs:
            print("%s: not in both captures" % m)
            continue
        gp = float(np.median(np.concatenate([g["gl"] + g["gr"] for g in ps])))
        gr = float(np.median(np.concatenate([g["gl"] + g["gr"] for g in rs])))
        print("%s: movie gain port %.4f pcsx2 %.4f -> port %+.2f dB" % (m, gp, gr, 20 * np.log10(gp / gr)))
        po = ps[0]["off"]
        snrs, lags = [], []
        for s, k in seg_blocks(rs):
            p = k + po
            if p < 0 or p + RATE > len(port):
                continue
            A = ref[s:s + RATE].astype(np.float64)
            B = port[p:p + RATE].astype(np.float64)
            lag, v = xcorr_offset(A, B, 256)
            e = A - B
            snrs.append(10 * np.log10(max(float((A ** 2).sum()), 1e-9) / max(float((e ** 2).sum()), 1e-9)))
            lags.append(lag)
        if snrs:
            print("   port vs pcsx2, %d aligned 1 s blocks: SNR median %.1f dB (min %.1f, max %.1f), lag median %+d frames"
                  % (len(snrs), np.median(snrs), np.min(snrs), np.max(snrs), int(np.median(lags))))
        mv = refs[m].astype(np.float64)
        for name, d, segs, g0 in (("port", port, ps, gp), ("pcsx2", ref, rs, gr)):
            res = []
            for s, k in seg_blocks(segs):
                if k + RATE > len(mv):
                    continue
                x = d[s:s + RATE].astype(np.float64) - g0 * mv[k:k + RATE]
                res.append(np.sqrt((x ** 2).mean()))
            if res:
                print("   %-6s residual after removing gain x movie: RMS median %.1f dBFS, max %.1f dBFS (%d blocks)"
                      % (name, dbfs(np.median(res)), dbfs(np.max(res)), len(res)))
        g = max(rs, key=lambda g: g["cap_end"] - g["cap_start"])
        n = g["cap_end"] - g["cap_start"]
        p = g["ref_start"] + po
        if n >= 2 * RATE and p >= 0 and p + n <= len(port):
            sp_p = spectrum(port, p, n)
            sp_r = spectrum(ref, g["cap_start"], n)
            corr, bands = band_compare(sp_r, sp_p)
            print("   spectrum (%.1f s, movie %.1f-%.1f s): dB-spectrum correlation %.4f; port-pcsx2 dB per octave from Hz: %s"
                  % (n / RATE, g["ref_start"] / RATE, g["ref_end"] / RATE, corr,
                     " ".join("%g:%+.1f" % (b[0], b[2]) for b in bands)))
    if len([g for g in maps["port"]]) and len(maps["pcsx2"]):
        print("== movie timing")
        for name, segs in (("port", maps["port"]), ("pcsx2", maps["pcsx2"])):
            st = {}
            for g in segs:
                st.setdefault(g["movie"], g["off"])
            if len(st) >= 2:
                a0, b0 = st[movies[0]], st[movies[1]]
                print("   %-6s %s@0 -> %s@0: %d frames = %.2f fields%s"
                      % (name, movies[0], movies[1], b0 - a0, (b0 - a0) / 800.8,
                         "" if name == "port" else " (PCSX2 capture drops shorten this; see segments)"))
    print("== channel order (correlation of capture L/R with movie L/R, longest segment)")
    for name, d, segs in (("port", port, maps["port"]), ("pcsx2", ref, maps["pcsx2"])):
        if not segs:
            continue
        g = max(segs, key=lambda g: g["cap_end"] - g["cap_start"])
        r = refs[g["movie"]]
        s, k, n = g["cap_start"], g["ref_start"], g["cap_end"] - g["cap_start"]
        A = d[s:s + n].astype(np.float64)
        B = r[k:k + n].astype(np.float64)
        m = [[float(np.corrcoef(A[:, i], B[:, j])[0, 1]) for j in (0, 1)] for i in (0, 1)]
        print("   %-6s L~L %.4f L~R %.4f R~L %.4f R~R %.4f" % (name, m[0][0], m[0][1], m[1][0], m[1][1]))
    print("== loudness per second (dBFS RMS of L and R)")
    for name, d in (("port", port), ("pcsx2", ref)):
        r = per_second(d)
        print("   %-6s %s" % (name, " ".join("%.0f" % dbfs(np.sqrt((x[1] ** 2 + x[2] ** 2) / 2)) for x in r)))
    print("== gaps (zero/held runs >= 2 ms between non-quiet audio)")
    for name, d in (("port", port), ("pcsx2", ref)):
        g = gaps(d)
        print("   %-6s %d%s" % (name, len(g), ("  first: " + ", ".join("%s@%.3fs/%d" % (k, at / RATE, n) for k, at, n in g[:8])) if g else ""))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    m = sub.add_parser("movie")
    m.add_argument("cap")
    m.add_argument("--movies", default="00/TITLE01,00/TITLE02")
    m.add_argument("--from-s", type=float, default=0.0)
    m.add_argument("--to-s", type=float, default=0.0)
    m.add_argument("-v", "--verbose", action="store_true")
    s = sub.add_parser("stats")
    s.add_argument("cap")
    s.add_argument("--from-s", type=float, default=0.0)
    s.add_argument("--to-s", type=float, default=0.0)
    r = sub.add_parser("report")
    r.add_argument("port")
    r.add_argument("pcsx2")
    r.add_argument("--movies", default="00/TITLE01,00/TITLE02")
    r.add_argument("--latency", type=int, default=0,
                   help="PCSX2 output latency in frames (buffered before the device wrote them)")
    a = ap.parse_args()
    {"movie": cmd_movie, "stats": cmd_stats, "report": cmd_report}[a.cmd](a)


if __name__ == "__main__":
    main()

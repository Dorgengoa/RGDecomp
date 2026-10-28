#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Check src/crt/crt_eelibm.c (the retail fdlibm float libm in C) against retail.

    python tools/parity/eelibm_check.py interp [--n 3000]   # interpreter vs PCSX2 pairs
    python tools/parity/eelibm_check.py vectors [--n 4000]  # expected results for new inputs
    python tools/parity/eelibm_check.py c                   # build + compare the C (plain / exact)
    python tools/parity/eelibm_check.py all

Retail references:
  * out/parity/libm/pairs.txt: 113,903 Sinf / Cosf / IeeeAtan2f calls probed on PCSX2 during a
    juraika walk (2026-10-19, out/parity/libmprobe.py);
  * for tanf / asinf / acosf / powf and large-argument sinf / cosf (KernelRemPio2f): the retail
    machine code itself, run by tools/parity/eediv/ee_interp.py with the EE float model the
    pairs verified (`interp` re-checks the interpreter on a sample of the pairs first).
The C is built twice: plain (the shipping build: native SSE under the game's MXCSR, round
toward zero + FTZ + DAZ) and exact (through tools/parity/eediv/eediv_cc.py: the EE add/sub
and the round-to-nearest division, RG_EE_FPU_EXACT).  The exact build must match every
reference; the plain build's agreement is reported (close, not bit-exact).
Work dir: out/eefpu/eelibm.
"""
import argparse
import os
import random
import struct
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.normpath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(HERE, "eediv"))
import ee_interp  # noqa: E402

WORK = os.path.join(PORT, "out", "eefpu", "eelibm")
PAIRS = os.path.join(PORT, "out", "parity", "libm", "pairs.txt")
VECS = os.path.join(WORK, "vectors.txt")
CLANG = os.environ.get("CLANG", r"../tools/llvm/bin/clang.exe")
TARGET = "--target=i686-pc-windows-msvc"
FLAGS = [TARGET, "-m32", "-msse2", "-mfpmath=sse", "-O2", "-ffp-contract=off", "-w"]

# retail entry points (MAIN): name -> (address, float args)
RETAIL = {"sinf": (0x128FD0, 1), "cosf": (0x128D30, 1), "tanf": (0x1290B8, 1), "asinf": (0x124878, 1),
          "acosf": (0x124450, 1), "atan2f": (0x124C18, 2), "powf": (0x124DF8, 2)}


def fb(x):
    return struct.unpack("<I", struct.pack("<f", x))[0]


def bf(b):
    return struct.unpack("<f", struct.pack("<I", b))[0]


def read_pairs(path):
    out = []
    with open(path) as fp:
        for line in fp:
            p = line.split()
            if len(p) == 4:
                out.append((p[0], int(p[1], 16), int(p[2], 16), int(p[3], 16)))
    return out


def run_retail(ee, fn, a, b):
    addr, nargs = RETAIL[fn]
    return ee.call_f(addr, [a, b][:nargs])


def cmd_interp(args):
    pairs = read_pairs(PAIRS)
    rnd = random.Random(1)
    by = {}
    for p in pairs:
        by.setdefault(p[0], []).append(p)
    ee = ee_interp.EE()
    tot = ok = 0
    t0 = time.time()
    for fn, lst in sorted(by.items()):
        sample = rnd.sample(lst, min(len(lst), args.n))
        good = sum(run_retail(ee, fn, a, b) == r for _, a, b, r in sample)
        print("interp vs PCSX2 %-7s %d / %d" % (fn, good, len(sample)))
        tot += len(sample)
        ok += good
    print("interp vs PCSX2: %d / %d (%.0fs)" % (ok, tot, time.time() - t0))
    return ok == tot


def gen_inputs(n, rnd):
    """(fn, a_bits, b_bits) inputs over the ranges the game uses plus the edges."""
    out = []
    u = rnd.uniform

    def add(fn, a, b=0.0):
        out.append((fn, fb(a) if isinstance(a, float) else a, fb(b) if isinstance(b, float) else b))
    for _ in range(n):
        add("tanf", u(-3.2, 3.2))
        add("tanf", u(-0.8, 0.8))
        add("asinf", u(-1, 1))
        add("acosf", u(-1, 1))
        add("asinf", u(-0.5, 0.5))
        add("acosf", u(0.97, 1.0))
        add("acosf", u(-1.0, -0.97))
        add("asinf", u(0.97, 1.0))
        add("powf", u(0, 4), u(-3, 3))
        add("powf", u(0, 1), u(0, 8))
        add("powf", u(0.5, 2), float(rnd.randint(-6, 6)))
        add("powf", -u(0.1, 4), float(rnd.randint(-5, 5)))
        add("powf", u(0.999, 1.001), u(-1e9, 1e9))
        add("powf", u(1, 100), u(-20, 20))
        add("sinf", u(-1e4, 1e4))        # medium + large reduction
        add("cosf", u(-1e4, 1e4))
        add("sinf", u(-1e8, 1e8))        # KernelRemPio2f
        add("cosf", u(-1e8, 1e8))
        add("tanf", u(-1e6, 1e6))
        add("sinf", rnd.choice([1, -1]) * 2.0 ** u(8, 60))
    for e in (0.0, 1.0, -1.0, 0.5, -0.5, 0.975, 2.0 ** -30, 1e-20):
        add("asinf", e)
        add("acosf", e)
    for x, y in ((2.0, 0.5), (0.0, 2.0), (0.0, -1.0), (-8.0, 1.0 / 3), (-2.0, 3.0), (1.0, 1e10), (3.0, 1.0),
                 (3.0, -1.0), (3.0, 2.0), (-1.0, 1e10), (10.0, 38.0), (10.0, -38.0), (2.0, 127.9), (2.0, -126.5)):
        add("powf", x, y)
    return out


def cmd_vectors(args):
    os.makedirs(WORK, exist_ok=True)
    rnd = random.Random(2)
    ins = gen_inputs(args.n, rnd)
    ee = ee_interp.EE()
    t0 = time.time()
    with open(VECS, "w", newline="\n") as fp:
        for fn, a, b in ins:
            fp.write("%s %08x %08x %08x\n" % (fn, a, b, run_retail(ee, fn, a, b)))
    print("vectors: %d (retail code, interpreter) -> %s (%.0fs)" % (len(ins), VECS, time.time() - t0))
    return True


DRIVER = r"""
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <xmmintrin.h>
float rg_ee_sinf(float), rg_ee_cosf(float), rg_ee_tanf(float), rg_ee_asinf(float), rg_ee_acosf(float);
float rg_ee_atan2f(float, float), rg_ee_powf(float, float);
static float F(uint32_t u){float f;memcpy(&f,&u,4);return f;}
static uint32_t U(float f){uint32_t u;memcpy(&u,&f,4);return u;}
int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    char k[16]; unsigned a, b, r;
    _mm_setcsr(0x1F80 | 0x6000 | 0x8040);       /* the game's EE MXCSR */
    while (fscanf(fp, "%15s %x %x %x", k, &a, &b, &r) == 4) {
        volatile float x = F(a), y = F(b); float e;
        if (!strcmp(k, "sinf")) e = rg_ee_sinf(x);
        else if (!strcmp(k, "cosf")) e = rg_ee_cosf(x);
        else if (!strcmp(k, "tanf")) e = rg_ee_tanf(x);
        else if (!strcmp(k, "asinf")) e = rg_ee_asinf(x);
        else if (!strcmp(k, "acosf")) e = rg_ee_acosf(x);
        else if (!strcmp(k, "atan2f")) e = rg_ee_atan2f(x, y);
        else e = rg_ee_powf(x, y);
        printf("%s %08x %08x %08x %08x\n", k, a, b, r, U(e));
    }
    return 0;
}
"""


def build(variant):
    os.makedirs(WORK, exist_ok=True)
    drv = os.path.join(WORK, "drv.c")
    with open(drv, "w", newline="\n") as fp:
        fp.write(DRIVER)
    src = os.path.join(PORT, "src", "crt", "crt_eelibm.c")
    inc = ["-I" + os.path.join(PORT, "src", "crt")]
    obj = os.path.join(WORK, "eelibm_%s.obj" % variant)
    cc = [CLANG] + FLAGS + inc + ["-c", src, "-o", obj]
    if variant == "exact":
        cc = [sys.executable, os.path.join(HERE, "eediv", "eediv_cc.py")] + cc
    subprocess.check_call(cc)
    exe = os.path.join(WORK, "drv_%s.exe" % variant)
    subprocess.check_call([CLANG] + FLAGS + [drv, obj, "-o", exe])
    return exe


def compare(exe, path, label):
    out = subprocess.run([exe, path], capture_output=True, text=True, check=True).stdout.split("\n")
    stats = {}
    bad = []
    for line in out:
        p = line.split()
        if len(p) != 5:
            continue
        s = stats.setdefault(p[0], [0, 0, 0])
        s[0] += 1
        if p[3] == p[4]:
            s[1] += 1
        else:
            d = abs(int(p[3], 16) - int(p[4], 16))
            if d <= 1:
                s[2] += 1
            bad.append(line)
    for fn, (n, ok, one) in sorted(stats.items()):
        print("  %-6s %-7s exact %6d / %6d  (1-ulp off %d)" % (label, fn, ok, n, one))
    return bad


def cmd_c(args):
    ok = True
    if not os.path.exists(VECS):
        cmd_vectors(args)
    for variant in ("exact", "plain"):
        exe = build(variant)
        print("C build %s:" % variant)
        for path, label in ((PAIRS, "pcsx2"), (VECS, "interp")):
            bad = compare(exe, path, label)
            with open(os.path.join(WORK, "mism_%s_%s.txt" % (variant, label)), "w", newline="\n") as fp:
                fp.write("\n".join(bad) + ("\n" if bad else ""))
            if variant == "exact" and bad:
                ok = False
                print("  EXACT MISMATCHES (%s): %d, first: %s" % (label, len(bad), bad[0]))
    print("exact build matches every reference" if ok else "exact build: MISMATCHES")
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["interp", "vectors", "c", "all"])
    ap.add_argument("--n", type=int, default=3000)
    a = ap.parse_args()
    if a.cmd == "interp":
        r = cmd_interp(a)
    elif a.cmd == "vectors":
        r = cmd_vectors(a)
    elif a.cmd == "c":
        r = cmd_c(a)
    else:
        r = cmd_interp(a) and cmd_vectors(a) and cmd_c(a)
    sys.exit(0 if r else 1)


if __name__ == "__main__":
    main()

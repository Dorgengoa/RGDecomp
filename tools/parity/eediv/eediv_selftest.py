#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Self-test of the exact EE float launcher (tools/parity/eediv/eediv_cc.py; RG_EE_FPU_EXACT,
docs/TEST-FIXTURES.md "Exact EE float build").  ctest `eefloat.launcher` (label eefloat).

    eediv_selftest.py CLANG [--target=TRIPLE] [--work DIR] [-n N]

1. rewrite(): float fadd / fsub / fdiv of a game function become rg_ee_* calls; VU0 model
   functions (rg_vu*, rg_vb*, rg_vbi*, vu0_*) and fmul / double ops stay as they are.
2. A small C driver compiled through eediv_cc.py runs N random add / sub / div pairs under the
   game's MXCSR (round toward zero + FTZ + DAZ) and the results are compared bit for bit with a
   Python model of the EE FPU (exact rationals): add / sub = operands aligned with one guard
   bit, then rounded toward zero; div = rounded to nearest (PCSX2 DIV.S).  The same driver
   compiled plainly must differ (arming control: the plain build is not the EE model).
Exit 0 pass, 1 fail, 77 skip (no compiler / not an i686 target).
"""
from __future__ import annotations

import argparse
import os
import random
import struct
import subprocess
import sys
import tempfile
from fractions import Fraction

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import eediv_cc  # noqa: E402

IR = """define dso_local float @Game_100(float %a, float %b) {
  %1 = fadd float %a, %b
  %2 = fsub float %1, %b
  %3 = fdiv float %2, %a
  %4 = fmul float %3, %a
  %5 = fadd <4 x float> zeroinitializer, zeroinitializer
  ret float %4
}
define internal i32 @rg_vu_addf(float %a, float %b) {
  %1 = fadd float %a, %b
  ret i32 0
}
define internal void @rg_vbi_vadd(float %a, float %b) {
  %1 = fsub float %a, %b
  ret void
}
define internal double @Game_200(double %a) {
  %1 = fadd double %a, %a
  ret double %1
}
"""

DRIVER = r"""
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <xmmintrin.h>
static float f(uint32_t u) { float x; memcpy(&x, &u, 4); return x; }
static uint32_t u(float x) { uint32_t v; memcpy(&v, &x, 4); return v; }
__attribute__((noinline)) float op_add(float a, float b) { return a + b; }
__attribute__((noinline)) float op_sub(float a, float b) { return a - b; }
__attribute__((noinline)) float op_div(float a, float b) { return a / b; }
int main(int argc, char **argv)
{
    unsigned k, a, b;
    FILE *fp = fopen(argv[1], "r");
    if (!fp) return 2;
    _mm_setcsr((_mm_getcsr() & ~0x6000u) | 0x6000u | 0x8000u | 0x0040u);  /* RTZ + FTZ + DAZ */
    while (fscanf(fp, "%u %x %x", &k, &a, &b) == 3) {
        float r = k == 0 ? op_add(f(a), f(b)) : k == 1 ? op_sub(f(a), f(b)) : op_div(f(a), f(b));
        printf("%08x\n", (unsigned)u(r));
    }
    return 0;
}
"""


def fval(u: int) -> Fraction:
    s = -1 if u >> 31 else 1
    e = (u >> 23) & 0xFF
    m = u & 0x7FFFFF
    if e == 0:
        return Fraction(0)          # DAZ
    return s * Fraction((m | 0x800000) * 2 ** 0) * Fraction(2) ** (e - 150)


def to_f32(x: Fraction, nearest: bool) -> int:
    """x rounded to a float32 (toward zero or to nearest even); FTZ; no overflow in the test."""
    if x == 0:
        return 0
    s = 0x80000000 if x < 0 else 0
    a = abs(x)
    e = a.numerator.bit_length() - a.denominator.bit_length()
    if Fraction(2) ** e > a:
        e -= 1
    # a in [2^e, 2^(e+1))
    if e < -126:
        return s                    # FTZ
    scaled = a / Fraction(2) ** (e - 23)   # in [2^23, 2^24)
    m = scaled.numerator // scaled.denominator
    rem = scaled - m
    if nearest and (rem > Fraction(1, 2) or (rem == Fraction(1, 2) and (m & 1))):
        m += 1
        if m == 1 << 24:
            m >>= 1
            e += 1
    return s | ((e + 127) << 23) | (m & 0x7FFFFF)


def ee_align(ua: int, ub: int) -> tuple[int, int]:
    d = ((ua >> 23) & 0xFF) - ((ub >> 23) & 0xFF)
    if d < 0:
        ua, ub = ub, ua
        d = -d
        swap = True
    else:
        swap = False
    if d >= 25:
        ub &= 0x80000000
    elif d > 0:
        ub &= (0xFFFFFFFF << (d - 1)) & 0xFFFFFFFF
    return (ub, ua) if swap else (ua, ub)


def model(k: int, a: int, b: int) -> int:
    if k == 2:
        return to_f32(fval(a) / fval(b), nearest=True)
    if k == 1:
        b ^= 0x80000000
    a2, b2 = ee_align(a, b)
    return to_f32(fval(a2) + fval(b2), nearest=False)


def rnd_float(r: random.Random) -> int:
    e = r.randint(100, 150)
    return (r.getrandbits(1) << 31) | (e << 23) | r.getrandbits(23)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("clang")
    ap.add_argument("--target", default="")
    ap.add_argument("--work", default="")
    ap.add_argument("-n", type=int, default=3000)
    a = ap.parse_args(argv)

    ir2, n = eediv_cc.rewrite(IR)
    body = {}
    cur = None
    for line in ir2.splitlines():
        if line.startswith("define"):
            cur = line.split("@")[1].split("(")[0]
            body[cur] = []
        elif cur:
            body[cur].append(line)
    g = "\n".join(body["Game_100"])
    vu = "\n".join(body["rg_vu_addf"] + body["rg_vbi_vadd"])
    ok = (n == 4 and g.count("@rg_ee_addf") == 5 and "@rg_ee_subf" in g and "@rg_ee_divf" in g
          and "fmul float" in g and "fadd float" in vu and "fsub float" in vu and "rg_ee_" not in vu
          and "fadd double" in "\n".join(body["Game_200"]))
    print(f"rewrite: {n} ops rewritten, VU0 / double untouched: {'ok' if ok else 'FAIL'}")
    if not ok:
        print(ir2)
        return 1

    if not os.path.exists(a.clang):
        print("skip: no compiler")
        return 77
    tgt = ["--target=" + a.target] if a.target else []
    if a.target and not a.target.startswith(("i686", "i386")):
        print("skip: not an i686 target")
        return 77
    work = a.work or tempfile.mkdtemp(prefix="eediv_selftest_")
    os.makedirs(work, exist_ok=True)
    src = os.path.join(work, "drv.c")
    with open(src, "w", newline="\n") as fp:
        fp.write(DRIVER)
    r = random.Random(1024)
    rows = []
    for i in range(a.n):
        k = i % 3
        x, y = rnd_float(r), rnd_float(r)
        if k < 2 and i % 7 == 0:        # close exponents: the guard-bit cases
            y = (y & 0x807FFFFF) | (x & 0x7F800000)
        rows.append((k, x, y))
    vec = os.path.join(work, "vec.txt")
    with open(vec, "w", newline="\n") as fp:
        fp.writelines(f"{k} {x:08x} {y:08x}\n" for k, x, y in rows)
    want = [model(*row) for row in rows]
    exe_ext = ".exe" if os.name == "nt" else ""
    results = {}
    for variant in ("exact", "plain"):
        obj = os.path.join(work, f"drv_{variant}.o")
        exe = os.path.join(work, f"drv_{variant}{exe_ext}")
        cc = [a.clang] + tgt + ["-m32", "-msse2", "-mfpmath=sse", "-O2", "-w", "-o", obj, "-c", src]
        if variant == "exact":
            cc = [sys.executable, os.path.join(HERE, "eediv_cc.py"), f"--cache={work}"] + cc
        subprocess.check_call(cc)
        subprocess.check_call([a.clang] + tgt + ["-m32", obj, "-o", exe])
        out = subprocess.run([exe, vec], capture_output=True, text=True, check=True).stdout.split()
        results[variant] = [int(v, 16) for v in out]
    bad = [i for i, (g, w) in enumerate(zip(results["exact"], want)) if g != w]
    ctl = sum(1 for g, w in zip(results["plain"], want) if g != w)
    for i in bad[:10]:
        k, x, y = rows[i]
        print(f"  MISS op {k} {x:08x} {y:08x}: got {results['exact'][i]:08x} model {want[i]:08x}")
    print(f"exact build: {len(rows) - len(bad)}/{len(rows)} equal to the EE model; "
          f"plain build (control): {ctl} differ")
    if bad or len(results["exact"]) != len(rows):
        return 1
    if ctl == 0:
        print("FAIL: the control (plain build) matches the model: the test is not armed")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

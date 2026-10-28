/* SPDX-License-Identifier: CC0-1.0
 * libmcheck (docs/X64-PLAN.md section 0.7): the host CRT's double libm under the game's
 * MXCSR (round toward zero + FTZ + DAZ) vs under round to nearest, on THIS arch, plus a
 * hash of each function's chop results to compare across archs.  Build and run both:
 *   clang --target=i686-pc-windows-msvc   -O1 -msse2 -mfpmath=sse tools/x64/libmcheck.c -o lm86.exe
 *   clang --target=x86_64-pc-windows-msvc -O1 tools/x64/libmcheck.c -o lm64.exe
 * 2026-10-26: i686 UCRT within 3 ulp of nearest; x64 UCRT sin/cos/tan off by up to 2^32
 * ulp under chop (hence HOST_RN in src/crt/crt_math.c on x64). */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <xmmintrin.h>
#pragma STDC FENV_ACCESS ON
typedef double (*f1)(double);
static double at2(double x) { return atan2(x, x * 0.37 + 1.0); }
static double ac(double x) { return acos(x / 4.0); }
static volatile f1 fs[] = {sin, cos, tan, atan, ac, sqrt, at2};
static const char *nm[] = {"sin", "cos", "tan", "atan", "acos", "sqrt", "atan2"};
int main(void)
{
    const unsigned chop = 0x1F80u | 0x6000u | 0x8040u, rn = 0x1F80u;
    for (int k = 0; k < 7; k++) {
        unsigned long long s = 88172645463325252ull, h = 14695981039346656037ull, mx = 0;
        unsigned diff = 0, n = 200000;
        for (unsigned i = 0; i < n; i++) {
            s ^= s << 13; s ^= s >> 7; s ^= s << 17;
            double x = ((double)(s >> 11) / 9007199254740992.0) * 8.0 - 4.0, a, b;
            long long ia, ib;
            _mm_setcsr(chop); a = fs[k](x);
            _mm_setcsr(rn);   b = fs[k](x);
            memcpy(&ia, &a, 8); memcpy(&ib, &b, 8);
            unsigned long long d = (unsigned long long)(ia > ib ? ia - ib : ib - ia);
            if (d) diff++;
            if (d > mx) mx = d;
            h = (h ^ (unsigned long long)ia) * 1099511628211ull;
        }
        printf("%-6s chop-vs-nearest: %6u of %u differ, max %llu ulp; chop hash %016llx\n", nm[k], diff, n, mx, h);
    }
    return 0;
}

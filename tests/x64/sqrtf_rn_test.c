/* SPDX-License-Identifier: CC0-1.0
 * x64.sqrtf_rn (docs/X64-PLAN.md section 0.7): port/sqrtf_rn.h under the guest MXCSR
 * (round toward zero + FTZ + DAZ) must give the round-to-nearest sqrt of every
 * non-negative float (the i686 build's CRT sqrtf: x87 fsqrt, nearest, no DAZ), the
 * reference being sqrtss under a round-to-nearest MXCSR without DAZ.  --control: a raw
 * sqrtss under the guest MXCSR must DIFFER (the bug the helper fixes).
 *   rg-x64-sqrtf-rn [--control] [--step N]   (every N-th float bit pattern, default 1)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include "port/sqrtf_rn.h"

/* the MXCSR changes below must not be moved across the float ops */
#pragma STDC FENV_ACCESS ON

static float raw_sqrtss(float x)
{
    __asm__ volatile("sqrtss %0, %0" : "+x"(x));
    return x;
}

int main(int argc, char **argv)
{
    int control = 0;
    unsigned step = 1, i, bad = 0, n = 0;
    for (int k = 1; k < argc; k++) {
        if (!strcmp(argv[k], "--control")) control = 1;
        else if (!strcmp(argv[k], "--step") && k + 1 < argc) step = (unsigned)strtoul(argv[++k], NULL, 0);
    }
    const unsigned guest = 0x1F80u | 0x6000u | 0x8040u, nearest = 0x1F80u;
    for (i = 0; i < 0x7F800000u; i += step) {   /* +0 .. largest finite, denormals included */
        float x, r, ref;
        unsigned rb, fb;
        memcpy(&x, &i, 4);
        _mm_setcsr(nearest);
        ref = raw_sqrtss(x);
        _mm_setcsr(guest);
        r = control ? raw_sqrtss(x) : rg_sqrtf_rn(x);
        _mm_setcsr(nearest);
        memcpy(&rb, &r, 4);
        memcpy(&fb, &ref, 4);
        n++;
        if (rb != fb && bad++ < 5)
            printf("x=%08x got %08x want %08x\n", i, rb, fb);
        if (i > 0xFFFFFFFFu - step) break;
    }
    printf("sqrtf_rn: %u inputs, %u differ (%s)\n", n, bad, control ? "control: raw sqrtss under the guest MXCSR" : "rg_sqrtf_rn");
    if (control)
        return bad ? 0 : 1;
    if (!bad) printf("sqrtf_rn: ok\n");
    return bad ? 1 : 0;
}

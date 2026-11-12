/* SPDX-License-Identifier: CC0-1.0 */
/* Float sine / cosine / arc cosine of the native renderer (nr_vux.c particle quads, nr_interp.c
 * slerp and rotation angle), the same on i686 and x64 (gfxperf6, docs/NATIVE-RENDER.md "GPU
 * throughput 5", docs/X64-PLAN.md section 0.7).
 *
 * The i686 CRT headers turn sinf / cosf / acosf into (float)sin((double)x) etc. (corecrt_math.h,
 * _M_IX86); x64 links the UCRT's float versions, which differ from those in 0.15 % (sinf, cosf)
 * and 1.9 % (acosf) of single inputs under round to nearest (tools/x64/dlibmx.c), while the double
 * routines through a single agree in all of them.  So on x64 these spell out the i686 form (default);
 * RG_NR_DTRIG=0 = the float versions as before.  Checked equal to i686 (and to =0) on boot:insectron x3
 * (22k particle batches), boot:save2 x3, town x3 and the 74 interpolated pass images, every field's display.  On i686 the macros are the plain calls: the
 * objects are byte-identical (tools/native/objsame.py).  These callers run under round to nearest
 * (sceDmaSend's PS2K_FPU_HOST_SCOPE; the interpolation on the GS worker), where the x64 double
 * routines are right (unlike under the game's round toward zero: src/crt/crt_math.c HOST_RN). */
#ifndef NR_TRIG_H
#define NR_TRIG_H
#include <math.h>
#if defined(__x86_64__) || defined(_M_X64)
#include <stdlib.h>
static inline int nr_dtrig_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_DTRIG"); on = e ? e[0] != '0' : 1; }
    return on;
}
static inline float nr_sinf(float x) { return nr_dtrig_on() ? (float)sin((double)x) : sinf(x); }
static inline float nr_cosf(float x) { return nr_dtrig_on() ? (float)cos((double)x) : cosf(x); }
static inline float nr_acosf(float x) { return nr_dtrig_on() ? (float)acos((double)x) : acosf(x); }
#define NR_SINF(x) nr_sinf(x)
#define NR_COSF(x) nr_cosf(x)
#define NR_ACOSF(x) nr_acosf(x)
#else
#define NR_SINF(x) sinf(x)
#define NR_COSF(x) cosf(x)
#define NR_ACOSF(x) acosf(x)
#endif
#endif

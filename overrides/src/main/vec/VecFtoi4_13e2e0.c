/* rg-override: replaces game/src/main/vec/VecFtoi4_13e2e0.c sha256 88482cf85cf7675df420d016162f92a4011026f930cff08596ddffa7e803ad5f
 * why: asm body (asmexclude, L5 library); C port from the retail listing
 * (docs/UNBOUND-TRIAGE.md P1: an overridden sibling exists) */
#include "types.h"

/* lqc2 / vftoi4.xyzw / sqc2: each lane to 28.4 fixed point (x * 16 truncated toward
   zero, saturated to the s32 range as the VU does). */
static s32 rg_ftoi4_13e2e0(f32 f)
{
    f32 x = f * 16.0f;
    if (x != x) return 0;
    if (x >= 2147483520.0f) return 0x7FFFFFFF;
    if (x <= -2147483648.0f) return (s32)0x80000000;
    return (s32)x;
}

void VecFtoi4_13e2e0(s32 *dst, const f32 *src)
{
    s32 r0 = rg_ftoi4_13e2e0(src[0]), r1 = rg_ftoi4_13e2e0(src[1]);
    s32 r2 = rg_ftoi4_13e2e0(src[2]), r3 = rg_ftoi4_13e2e0(src[3]);
    dst[0] = r0; dst[1] = r1; dst[2] = r2; dst[3] = r3;
}

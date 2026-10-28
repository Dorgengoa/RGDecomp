#include "vec.h"

/* Sony ships libvu0 as documented inline assembly -- hard-coded registers,
   per the judgement written into sceVu0CopyMatrix.c. Componentwise clamp
   against a broadcast min/max pair. */

void sceVu0ClampVector(Vec4 *dst, const Vec4 *src, f32 min, f32 max)
{
    asm volatile {
        mfc1        $8, min
        mfc1        $9, max
        lqc2        vf6, 0x0($5)
        qmtc2.ni    $8, vf4
        qmtc2.ni    $9, vf5
        vmaxx.xyzw  vf6, vf6, vf4x
        vminix.xyzw vf6, vf6, vf5x
        sqc2        vf6, 0x0($4)
    }
}

#include "vec.h"

/* Sony ships libvu0 as documented inline assembly -- hard-coded registers,
   per the judgement written into sceVu0CopyMatrix.c: transcription is earned
   only where the CONTENT proves a human wrote it (fixed vf4/vf5/vf6 roles,
   COP2 that C cannot express).  asm volatile; mwcc sinks the last
   instruction into the jr delay slot. */

void sceVu0SubVector(Vec4 *dst, const Vec4 *lhs, const Vec4 *rhs)
{
    asm volatile {
        lqc2      vf4, 0x0($5)
        lqc2      vf5, 0x0($6)
        vsub.xyzw  vf6, vf4, vf5
        sqc2      vf6, 0x0($4)
    }
}

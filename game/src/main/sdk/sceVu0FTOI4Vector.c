#include "vec.h"

/* Sony libvu0-style leaf: lqc2/vftoi4.xyzw/sqc2, ending without an explicit
   jr -- mwcc sinks the last instruction (sqc2) into the jr $31 delay slot,
   same pattern as the already-merged sceVu0MulVector/sceVu0ScaleVector. */

void sceVu0FTOI4Vector(Vec4 *dst, const Vec4 *src)
{
    asm volatile {
        lqc2        vf4, 0x0($5)
        vftoi4.xyzw vf5, vf4
        sqc2        vf5, 0x0($4)
    }
}

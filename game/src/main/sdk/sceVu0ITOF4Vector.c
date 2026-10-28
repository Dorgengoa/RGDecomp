#include "vec.h"

/* Sibling of sceVu0FTOI4Vector -- vitof4.xyzw instead of vftoi4.xyzw. */

void sceVu0ITOF4Vector(Vec4 *dst, const Vec4 *src)
{
    asm volatile {
        lqc2        vf4, 0x0($5)
        vitof4.xyzw vf5, vf4
        sqc2        vf5, 0x0($4)
    }
}

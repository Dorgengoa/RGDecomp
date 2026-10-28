#include "vec.h"

/* Sony ships libvu0 as documented inline assembly -- hard-coded registers,
   per the judgement written into sceVu0CopyMatrix.c.  The dot product comes
   back through $2 -> $f0, the float return register, written by hand the way
   QuatSlerp_13c270's recipe says: the mfc1/mtc1 staging is part of the listing. */

f32 sceVu0InnerProduct(const Vec4 *a, const Vec4 *b)
{
    asm volatile {
        lqc2      vf4, 0x0($4)
        lqc2      vf5, 0x0($5)
        vmul.xyz  vf5, vf4, vf5
        vaddy.x   vf5, vf5, vf5y
        vaddz.x   vf5, vf5, vf5z
        qmfc2.ni  $2, vf5
        mtc1      $2, $f0
    }
}

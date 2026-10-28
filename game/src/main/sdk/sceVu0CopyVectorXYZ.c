#include "vec.h"

/* Three floats only -- w is deliberately left alone, which is the whole point
   of the XYZ variant. Inline assembly with hard-coded registers, like the rest
   of libvu0: the $f0 / $f1 / $f0 alternation is a human writing it, not an
   allocator. Compiled C reuses $f0 for all three and no spelling changes that
   (member assignment, `f32[4]` parameters, one named temp, three named temps
   -- all four measured, all byte-identical). */

void sceVu0CopyVectorXYZ(Vec4 *dst, const Vec4 *src)
{
    asm volatile {
        lwc1  $f0, 0x0($5)
        swc1  $f0, 0x0($4)
        lwc1  $f1, 0x4($5)
        swc1  $f1, 0x4($4)
        lwc1  $f0, 0x8($5)
        swc1  $f0, 0x8($4)
    }
}

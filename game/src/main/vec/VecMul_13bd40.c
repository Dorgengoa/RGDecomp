#include "types.h"
#include "vec.h"

void VecMul_13bd40(Vec4 *pd, const Vec4 *pa, const Vec4 *pb)
{
    asm volatile {
        lqc2      vf4, 0x0($5)
        lqc2      vf5, 0x0($6)
        vmul.xyzw vf6, vf4, vf5
        sqc2      vf6, 0x0($4)
    }
}

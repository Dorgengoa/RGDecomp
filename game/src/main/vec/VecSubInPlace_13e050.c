#include "types.h"
#include "vec.h"

void VecSubInPlace_13e050(Vec4 *pd, const Vec4 *pb)
{
    asm volatile {
        lqc2      vf15, 0x0($4)
        lqc2      vf16, 0x0($5)
        vsub.xyzw vf15, vf15, vf16
        sqc2      vf15, 0x0($4)
    }
}

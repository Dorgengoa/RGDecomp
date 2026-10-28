#include "types.h"
/* soft-double compare wrapper: the decomp typed the passed-through GPRs s32 */
extern s32 DoubleCmp_13b948(s32, s32);

u8 DoubleLess_1002b0(s32 p0, s32 p1)
{
    s32 r;

    r = DoubleCmp_13b948(p0, p1);
    return (r < 0);
}

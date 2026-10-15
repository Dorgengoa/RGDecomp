#include "types.h"

extern f32 D_0047D404;
extern f32 func_1CBF30(f32 a);

f32 factory_FactoryGridDirToAngle_4ff990(s32 i)
{
    return func_1CBF30(D_0047D404 * (i & 3));
}

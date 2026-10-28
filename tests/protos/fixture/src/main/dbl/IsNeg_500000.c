#include "types.h"
extern u8 DoubleLess_1002b0(f64, f64);

s32 IsNeg_500000(f64 d)
{
    return DoubleLess_1002b0(d, 0.0);
}

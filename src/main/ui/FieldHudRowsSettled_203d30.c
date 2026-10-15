#include "types.h"

extern const u8 D_00527020[];
extern s32 func_4F53D0(const u8 *);

s32 FieldHudRowsSettled_203d30(void)
{
    return func_4F53D0(D_00527020) != 0;
}

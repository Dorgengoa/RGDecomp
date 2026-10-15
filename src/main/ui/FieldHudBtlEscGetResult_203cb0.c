#include "types.h"

extern u8 D_00527020[];

extern s32 func_4F0A20(void *);

s16 FieldHudBtlEscGetResult_203cb0(void)
{
    s16 v;

    s16 r;
    v = (s16)func_4F0A20(D_00527020);
    if (v != 2) {
        if (v != 1) {
            return 0;
        }
        r = 1;
    } else {
        r = 2;
    }
    return r;
}

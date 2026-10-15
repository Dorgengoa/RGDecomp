#include "types.h"

extern s16 func_4F9D40(void);

s32 BtlChgMenuIsMemberPageUp_204e20(void)
{
    s32 r;

    r = 1;
    if (func_4F9D40() != 2) {
        r = 0;
    }
    return r;
}

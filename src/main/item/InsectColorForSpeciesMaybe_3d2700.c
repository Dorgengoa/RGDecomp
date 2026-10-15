#include "types.h"

s32 InsectColorForSpeciesMaybe_3d2700(s32 a, s32 b)
{
    s32 r;

    if (a == 0x7DD) {
        r = 0;
    } else {
        r = b;
    }
    return r;
}

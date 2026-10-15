#include "types.h"

extern s32 InsectCageSetType_3910d0(s32);

s32 InsectCageSetTypeFromItem_391090(s32 k)
{
    s32 t;

    t = 0;
    if (k == 0x4169) {
        t = 1;
    } else if (k == 0x416A) {
        t = 2;
    }
    return InsectCageSetType_3910d0(t);
}

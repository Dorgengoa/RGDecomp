#include "types.h"

extern s8 D_00455220[];

s32 Base58CharIndex_42f380(s32 arg0)
{
    s32 i;
    s8 val;

    val = (s8)arg0;
    i = 0;
    while (i < 0x3A) {
        if (val == D_00455220[i]) {
            return i;
        }
        i++;
    }
    return -1;
}

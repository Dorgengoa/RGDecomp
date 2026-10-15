#include "types.h"

s32 MesWinGetPageMaxLineWidth_273a80(void *arg0, s32 arg1) {
    s32 sum;
    s32 j;
    s32 i;
    s32 maxVal;
    s16 cur;

    sum = 0;
    for (i = 0; i < arg1; i++) {
        sum += *(s16 *)((u8 *)arg0 + i * 2 + 0x5C);
    }
    maxVal = 0;
    for (j = 0; j < *(s16 *)((u8 *)arg0 + arg1 * 2 + 0x5C); j++) {
        cur = *(s16 *)((u8 *)arg0 + sum * 2 + j * 2 + 0x1D74);
        if (maxVal < cur) {
            maxVal = cur;
        }
    }
    return maxVal;
}

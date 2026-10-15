#include "types.h"

extern u8 D_00449F90[];

s32 TexSwizzleBlock_157c20(u8 *arg0, u8 *arg1) {
    u8 *dst;
    u32 k;
    u32 j;
    u32 i;
    s32 idxBase;
    s32 srcIdx;
    u8 idx;
    u8 val;

    dst = arg1;
    srcIdx = 0;
    i = 0;
    do {
        idxBase = (i & 1) << 6;
        k = 0;
        do {
            j = 0;
            do {
                idx = D_00449F90[idxBase];
                idxBase += 1;
                val = arg0[srcIdx];
                srcIdx += 1;
                dst[idx] = val;
                j += 1;
            } while (j < 4);
            k += 1;
        } while (k < 0x10);
        i += 1;
        dst += 0x40;
    } while (i < 4);
    return 0;
}

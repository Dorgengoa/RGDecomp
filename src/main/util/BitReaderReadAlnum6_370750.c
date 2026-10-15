#pragma optimization_level 3
#include "types.h"
typedef struct S00370750 {
    s16 unk0;
    u8 pad2[6];
    u8 *unk8;
} S00370750;

static inline s32 getbit(S00370750 *p, s32 one)
{
    s16 pos = p->unk0++;
    if (p->unk8[pos >> 3] & (u8)(one << (pos & 7))) return 1;
    return 0;
}

s32 BitReaderReadAlnum6_370750(S00370750 *arg0, s8 *arg1, s32 arg2)
{
s32 count;
s32 i;
s8 c;
s8 acc;
s32 bit;
s32 j;
s16 pos;
s32 one = 1;

    if (arg1 == NULL) {
        return 0;
    }
    count = 0;
    for (i = 0; i < arg2; i++) {
        acc = 0;
        bit = 1;
        j = 0;
        do {
            if (getbit(arg0, one)) {
                acc |= (s8)bit;
            }
            j++;
            count++;
            bit <<= 1;
        } while (j < 6);
        if (acc == 0) {
            c = 0;
        } else if (acc == 1) {
            c = 0x20;
        } else if (acc >= 2 && acc < 0x1C) {
            c = acc + 0x3F;
        } else if (acc >= 0x1C && acc < 0x36) {
            c = acc + 0x45;
        } else if (acc >= 0x36 && acc < 0x40) {
            c = acc - 6;
        } else {
            c = 0;
        }
        *arg1 = c;
        arg1++;
    }
    *arg1 = 0;
    return count;
}

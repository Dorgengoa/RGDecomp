#include "types.h"

typedef struct S0042ccd0 {
    u32 *unk0;
    u8 pad4[4];
    u32 unk8;
} S0042ccd0;

static inline u8 bit_0042ccd0(S0042ccd0 *s, s32 i)
{
    if (i >= s->unk8) {
        return 0;
    }
    return ((1 << (i & 0x1F)) & s->unk0[i >> 5]) != 0;
}

u32 BitArrayFindValue_42ccd0(S0042ccd0 *arg0, u32 arg1, u32 arg2)
{
    s32 i;
    u8 c;

    if (arg0->unk0 == NULL) {
        return -1;
    }
    if (arg2 > arg0->unk8) {
        arg2 = arg0->unk8;
    }
    c = arg1;
    for (i = arg2; i < arg0->unk8; i++) {
        if (c == bit_0042ccd0(arg0, i)) {
            return i;
        }
    }
    for (i = 0; i < arg2; i++) {
        if (c == bit_0042ccd0(arg0, i)) {
            return i;
        }
    }
    return -1;
}

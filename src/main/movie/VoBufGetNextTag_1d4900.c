#pragma divbyzerocheck on
#include "types.h"

typedef struct Obj001d4900 {
    u8 pad0[0x8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Obj001d4900;

s32 VoBufGetNextTag_1d4900(Obj001d4900 *self)
{
    s32 count;
    s32 idx;

    count = self->unk14;
    idx = (self->unkC - self->unk10 + 1 + count) % count;
    return self->unk8 + idx * 0x48;
}

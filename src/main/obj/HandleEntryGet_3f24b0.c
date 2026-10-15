#include "types.h"

typedef struct Obj003f24b0 {
    u8 pad0[0x18];
    s32 unk18;
} Obj003f24b0;

extern u8 D_004644A0[0x400];

s32 HandleEntryGet_3f24b0(Obj003f24b0 *self, s32 idx)
{
    s32 base;
    s32 r;

    base = self->unk18;
    if (base == 0) {
        return 0;
    }
    if (idx >= 0 && idx < (*(s32 *)D_004644A0)) {
        return base + idx * 0x28;
    }
    return 0;
}

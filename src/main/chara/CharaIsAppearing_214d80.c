#include "types.h"

struct T214D80 { u8 pad000[0xA32]; s16 fA32; u8 pad0A34[0x4]; s16 fA38; };

s32 CharaIsAppearing_214d80(struct T214D80 *p)
{
    s32 r;

    r = !p->fA38;
    if (r != 0) {
        r = p->fA32 == 0x12;
    }
    return r;
}

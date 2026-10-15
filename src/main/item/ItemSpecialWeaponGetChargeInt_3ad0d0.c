#include "types.h"

struct T3AD0D0 { u8 pad000[0x20]; f32 f20; };

extern f32 D_0047D258;

s32 ItemSpecialWeaponGetChargeInt_3ad0d0(struct T3AD0D0 *p)
{
    return (s32)(D_0047D258 + p->f20);
}

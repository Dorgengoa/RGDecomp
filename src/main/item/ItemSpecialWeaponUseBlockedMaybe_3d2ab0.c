#include "types.h"

typedef struct G_003d2ab0 {
    u8 pad20[0x20];
    s32 f20;
} G_003d2ab0;

typedef struct S_003d2ab0 {
    u8 padC[0xC];
    s16 fC;
} S_003d2ab0;

extern G_003d2ab0 *D_004838E8;
extern s32 CharaSysStateFlag24Bit0Related_3a38c0(s32);

s32 ItemSpecialWeaponUseBlockedMaybe_3d2ab0(S_003d2ab0 *self, s32 code)
{
    s16 t;
    if (code == 0x2AFC) goto zero;
    if (code == 0x2AFE) goto zero;
    t = *(volatile s16 *)&self->fC;
    if (t == 0x3F03) goto zero;
    if (t == 0x3F07) goto zero;
    if (t != 0x3F0B) goto ok;
zero:
    return 0;
ok:
    return !(CharaSysStateFlag24Bit0Related_3a38c0(D_004838E8->f20) != 0);
}

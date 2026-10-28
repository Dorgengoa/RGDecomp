/* rgp:protos */
#define RGP_SELF_FUN_0040e370_e1 1
#define RGP_SELF_ItemDefIsSpecialWeapon_40e370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P40E370 {
    u8  pad000[0x2];
    s8  m2;
    u8  pad003[0x1];
    s16 m4;
} P40E370;

u8 FUN_0040e370_e1(s32 a, s32 b);

u8 ItemDefIsSpecialWeapon_40e370(P40E370 *p)
{
    return FUN_0040e370_e1(p->m2, p->m4);
}

u8 FUN_0040e370_e1(s32 a, s32 b)
{
    u8 r;

    r = 0;
    if ((u32)a >= 2) goto out;
    if (b == 0xCF) goto ok;
    if (b == 0xCE) goto ok;
    if (b == 0xCC) goto ok;
    if (b == 0xCB) goto ok;
    if (b == 0xCA) goto ok;
    if (b == 0xC9) goto ok;
    if (b == 0xC8) goto ok;
    if (b == 0x69) goto ok;
    return r;
ok:
    r = 1;
out:
    return r;
}

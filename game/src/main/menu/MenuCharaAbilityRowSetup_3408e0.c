/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityRowSetup_3408e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 a;
    s16 b;
} P3408E0;

/*rgp*/
/*rgp*/
/*rgp*/
extern P3408E0 D_00453810[9];

void MenuCharaAbilityRowSetup_3408e0(s32 pd0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5)
{
    P3408E0 tbl[9] __attribute__((aligned(16)));
    P3408E0 *s;
    P3408E0 *d;
    s32 k;
    s32 t;
    s32 v;
    s32 r;
    s32 i;

    t = *(s32 *)(arg1 + 0x8);
    *(s32 *)(arg4 + 0x4) = t;
    *(s32 *)(arg4 + 0xC) = 0xFF303030;
    *(s16 *)(arg5 + 0xC) = 0x18;
    *(s16 *)(arg5 + 0x4) = 0x18;
    *(s16 *)(arg5 + 0xE) = 0x16;
    *(s16 *)(arg5 + 0x6) = 0x16;
    if (arg1[2] == 0) {
        *(s16 *)(arg2 + 0xC) = 0x14;
        *(s16 *)(arg2 + 0x4) = 0x14;
        *(s16 *)(arg2 + 0xE) = 0x10;
        *(s16 *)(arg2 + 0x6) = 0x10;
        v = ((s32)CharaFindSlotByRecId_3ad390(pd0, *(s16 *)arg1));
        if (v != 0) {
            *(s64 *)(arg3 + 0x8) = EquipSlotGetScaledCost_3a05c0(v);
        } else {
            *(s64 *)(arg3 + 0x8) = AbilityDataGetCost_3f5ca0(arg1);
        }
        *(s16 *)(arg3 + 0x16) = 0xC;
        *(s16 *)(arg3 + 0x18) = 0x10;
    } else {
        *(s16 *)(arg2 + 0xE) = 0;
        *(s16 *)(arg2 + 0xC) = 0;
        *(s16 *)(arg2 + 0x6) = 0;
        *(s16 *)(arg2 + 0x4) = 0;
        *(s16 *)(arg3 + 0x18) = 0;
        *(s16 *)(arg3 + 0x16) = 0;
    }
    d = tbl;
    s = D_00453810;
    k = 9;
    do {
        k -= 1;
        d->a = s->a;
        d->b = s->b;
        s += 1;
        d += 1;
    } while (k > 0);
    *(s16 *)(arg5 + 0x8) = 0;
    for (i = 0; i < 9; i++) {
        if (arg1[3] == tbl[i].a) {
            *(s16 *)(arg5 + 0x8) = tbl[i].b;
        }
    }
}

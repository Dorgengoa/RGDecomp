/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelHealGlowStart_4f2f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F2F40 -- writes one 8-byte slot of p->f33C, then pushes the
 * matching 784-byte record at the gp pointer 0x00484414. */
typedef struct A {
    u8    pad000[0x18];
    void *f18;
} A;

typedef struct Slot {
    s32 f00;
    s16 f04;
    s16 f06;
} Slot;

typedef struct N {
    u8   pad000[0x33C];
    Slot f33C[3];
} N;

typedef struct Big {
    u8 pad000[784];
} Big;

extern void *D_00484414;          /* gp - 0xD5C */
extern u8    normal_D_00526380[];

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudPanelHealGlowStart_4f2f40(N *p, s16 key, s16 v)
{
    A  *a;
    s32 i;

    a = ((A *)GetGameData_1fede0());
    if (a == NULL) {
        return;
    }
    i = PartyFindSlotOfId_3c3070(a->f18, key);
    if (i < 0 || i > 2) {
        return;
    }
    {
        p->f33C[i].f04 = v;
        p->f33C[i].f00 = 0;
        p->f33C[i].f06 = key;
        if (D_00484414 != NULL) {
            UiGlowSpriteListInit_33bf40(&((Big *)D_00484414)[i], normal_D_00526380, 0x32B);
        }
    }
}

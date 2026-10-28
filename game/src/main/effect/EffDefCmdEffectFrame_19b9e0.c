/* rgp:protos */
#define RGP_SELF_EffDefCmdEffectFrame_19b9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004709A8[];

s32 EffDefCmdEffectFrame_19b9e0(s32 arg0, s32 arg1, u8 **arg2)
{
    u8 *x;
    u8 *list;
    u8 *p;
    s32 v;
    u8 **q;
    u8 **n;
    u8 *r;

    x = *arg2;
    v = SlotGetInt_15f720((void *)arg0);
    if (v == 0) {
        return 0;
    }
    list = *(u8 **)(x + 0x24);
    p = ((u8 *)MemStackNew_14e230(0x4C, *(s32 *)(x + 0x20)));
    if (p != 0) {
        EffObjBaseCtor_1a9ed0(p + 4);
        *(u8 **)(p + 0x44) = D_004709A8;
        *(s32 *)(p + 0x48) = 0;
        *(s32 *)(p + 0x0) = 0;
    }
    if (p == 0) {
        r = 0;
    } else {
        *(s32 *)(list + 0x80) = 0;
        q = *(u8 ***)(list + 0x7C);
        if (q != 0) {
            while (q != 0) {
                n = (u8 **)*q;
                if (n == 0) {
                    break;
                }
                q = n;
            }
            *q = p;
        } else {
            *(u8 **)(list + 0x7C) = p;
        }
        r = p + 4;
    }
    *(u8 **)(x + 0x30) = r;
    *(u8 **)(x + 0x28) = r;
    if (*(u8 **)(x + 0x30) == 0) {
        return 0;
    }
    SetDupString_1a9ea0(*(u8 **)(x + 0x30), *(s32 *)(x + 0x20), v);
    return 1;
}

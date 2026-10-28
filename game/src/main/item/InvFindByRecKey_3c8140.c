/* rgp:protos */
#define RGP_SELF_InvFindByRecKey_3c8140 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: m2c fails outright (jump table not provided). Not attempted. */
/* s49m: MATCH jtbl rodata_check */
#pragma opt_propagation off
#include "types.h"

extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern s32 D_00465A38[];
extern s32 D_00465A40[];
extern s32 D_00465A60[];
extern s32 D_00465A68[];
extern s32 D_00465A78[];
extern s32 D_00465A80[];
extern s32 D_00465A90[];
extern s32 D_00465A98[];
extern s32 D_00465AA8[];
extern s32 D_00465AB0[];
extern s32 D_00465AD0[];
extern s32 D_00465AD8[];
extern s32 D_00465AE8[];
extern s32 D_00465AF0[];
extern s32 D_00465B00[];
extern s32 D_00465B08[];
extern s32 D_00465B30[];
extern s32 D_00465B38[];
extern s32 D_00465B40[];
extern s32 D_00465B48[];
extern s32 D_00465B50[];
/*rgp*/

typedef struct {
    u8 b0:1;
    u8 bit:1;
    u8 pad:6;
} Flags;

u8 *InvFindByRecKey_3c8140(u8 *self, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 lo;
    s32 hi;
    u8 *res;
    s32 i;
    s32 count;
    u8 *p;
    u8 *q;
    s32 c2;
    s32 c4;
    s32 c3;

    if (*(s32 *)(self + 0x168) == 0) {
        return 0;
    }
    switch (arg4) {
    case 0:
        lo = D_00465A08[0];
        hi = D_00465A10[0];
        break;
    case 1:
        lo = D_00465A38[0];
        hi = D_00465A40[0];
        break;
    case 10:
        lo = D_00465B40[0];
        hi = D_00465B48[0];
        break;
    case 2:
        lo = D_00465A60[0];
        hi = D_00465A68[0];
        break;
    case 3:
        lo = D_00465A78[0];
        hi = D_00465A80[0];
        break;
    case 4:
        lo = D_00465A90[0];
        hi = D_00465A98[0];
        break;
    case 5:
        lo = D_00465AA8[0];
        hi = D_00465AB0[0];
        break;
    case 6:
        lo = D_00465AD0[0];
        hi = D_00465AD8[0];
        break;
    case 7:
        lo = D_00465AE8[0];
        hi = D_00465AF0[0];
        break;
    case 8:
        lo = D_00465B00[0];
        hi = D_00465B08[0];
        break;
    case 9:
        lo = D_00465B30[0];
        hi = D_00465B38[0];
        break;
    case -1:
    default:
        lo = 0;
        hi = D_00465AD8[0];
        break;
    }
    res = 0;
    count = D_00465B50[0];
    for (i = 0; i < count; i++) {
        p = ((u8 *)PoolGetUsedElem_36acb0(*(s32 *)(self + 0x168), i));
        if (p == 0) {
            continue;
        }
        if (*(s16 *)(p + 6) < lo) {
            continue;
        }
        if (*(s16 *)(p + 6) > hi) {
            continue;
        }
        if (((Flags *)(p + 0xA))->bit) {
            continue;
        }
        q = *(u8 **)(p + 0x10);
        c2 = *(s8 *)(q + 2);
        c4 = *(s16 *)(q + 4);
        c3 = *(s8 *)(q + 3);
        if (c2 == arg1 && c4 == arg2 && c3 == arg3) {
            res = p;
            break;
        }
    }
    return res;
}

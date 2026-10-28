/* rgp:protos */
#define RGP_SELF_InvCollectInsects_3c4d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2];
    u8 b0:1;
    u8 b1:1;
    u8 b2:6;
} Elem;

typedef struct {
    u8 pad0[0x168];
    s32 unk168;
} Obj;

/*rgp*/
/*rgp*/
extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern s32 D_00465AE8[];
extern s32 D_00465AF0[];
extern s32 D_00465B50[];

s32 InvCollectInsects_3c4d90(Obj *arg0, s32 *arg1, s32 arg2)
{
    s32 count;
    s32 pass;
    s32 lo;
    s32 hi;
    s32 i;
    s32 lo1;
    s32 hi1;
    s32 lo2;
    s32 hi2;
    s32 n;
    Elem *e;
    s32 r;

    if (arg1 == 0) {
        return 0;
    }
    if (arg2 <= 0) {
        return 0;
    }
    lo1 = D_00465A08[0];
    hi1 = D_00465A10[0];
    lo2 = D_00465AE8[0];
    hi2 = D_00465AF0[0];
    n = D_00465B50[0];
    count = 0;
    for (pass = 1; pass <= 2; pass++) {
        hi = hi1;
        lo = lo1;
        if (pass == 2) {
            lo = lo2;
            hi = hi2;
        }
        for (i = 0; i < n; i++) {
            e = ((Elem *)PoolGetUsedElem_36acb0(arg0->unk168, i));
            if (e == 0) {
                continue;
            }
            if (e->b1) {
                continue;
            }
            if (e->unk6 < lo || e->unk6 > hi) {
                continue;
            }
            r = ((s32)InvObjCastToInsect_3d3d10(e, 0, 0, 0));
            if (r == 0) {
                continue;
            }
            arg1[count++] = r;
            if (count >= arg2) {
                break;
            }
        }
        if (count >= arg2) {
            break;
        }
    }
    return count;
}

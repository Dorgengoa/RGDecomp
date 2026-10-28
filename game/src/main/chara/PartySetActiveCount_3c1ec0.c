/* rgp:protos */
#define RGP_SELF_FindFree 1
#define RGP_SELF_PartySetActiveCount_3c1ec0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct {
    u8 pad0[0x18C];
    s16 cur;
    s16 f18E;
    s16 f190[3];
    s16 f196[7];
} Obj;

/*rgp*/
/*rgp*/

static inline s32 FindFree(Obj *a) {
    s32 k;
    for (k = 0; k < 7; k++) {
        if (a->f196[k] < 0) {
            return k;
        }
    }
    return -1;
}

s32 PartySetActiveCount_3c1ec0(Obj *arg0, s32 arg1)
{
    s32 old;
    s32 j;
    s32 k;
    s16 x;
    s16 *e;
    s32 r;

    old = arg0->cur;
    arg0->cur = arg1;
    if ((s16)arg1 <= 0) {
        arg0->cur = 1;
    } else if ((s16)arg1 > 3) {
        arg0->cur = 3;
    }
    if (arg0->cur == old) {
        return 0;
    }
    if (old < arg0->cur) {
        return 1;
    }
    if (PartyCountMembers_3c2010(arg0, 1, 1) > arg0->cur) {
        for (j = 2; j >= 0; j--) {
            e = &arg0->f190[j];
            x = *e;
            if (x >= 0 && x != arg0->f18E) {
                k = FindFree(arg0);
                if (k >= 0) {
                    *e = -1;
                    arg0->f196[k] = x;
                }
            }
        }
        r = PartyCountMembers_3c2010(arg0, 1, 1);
        if (arg0->cur < r) {
            arg0->cur = r;
        }
        PartyCompactSlots_3c2c50(arg0);
    }
    return arg0->cur != 0;
}

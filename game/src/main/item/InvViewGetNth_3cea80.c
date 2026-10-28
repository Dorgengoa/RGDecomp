/* rgp:protos */
#define RGP_SELF_InvViewGetNth_3cea80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E3cea80 {
    u8 pad0[6];
    s16 m6;
    u8 pad8[8];
    u8 *m10;
} E3cea80;

typedef struct Q3cea80 {
    u8 pad0[4];
    s32 m4;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 mE;
    s16 m10;
    s16 m12;
} Q3cea80;

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00465B50[0x100];

E3cea80 *InvViewGetNth_3cea80(Q3cea80 *arg0, s32 arg1)
{
    s32 cnt;
    s32 i;
    s32 n;
    E3cea80 *e;
    s32 t;

    if (arg0->m4 == 0) {
        return NULL;
    }
    cnt = 0;
    i = 0;
    if (arg0->m12 >= 0 && arg0->m10 >= 0 && arg0->m10 + 1 == arg1) {
        cnt = arg0->m10 + 1;
        i = arg0->m12 + 1;
    }
    n = D_00465B50[0];
    for (; i < n; i++) {
        e = ((E3cea80 *)InvFindByInvId_3c87d0(arg0->m4, i, 0));
        if (e == NULL) {
            continue;
        }
        t = InvGetCategoryOfId_3d56f0(e->m6);
        if (arg0->m8 >= 0) {
            if (arg0->m8 == 10) {
                if (t != 0 && t != 1) {
                    continue;
                }
            } else if (arg0->m8 != t) {
                continue;
            }
        }
        if (arg0->mA >= 0) {
            t = InvIdGetMajorIndex_3d55f0(e->m6);
            if (arg0->mA != t) {
                continue;
            }
        }
        if (arg0->mC >= 0 && arg0->mC != *(s8 *)(e->m10 + 2)) {
            continue;
        }
        if (arg0->mE >= 0 && arg0->mE != *(s16 *)(e->m10 + 4)) {
            continue;
        }
        if (cnt == arg1) {
            arg0->m10 = cnt;
            arg0->m12 = i;
            return e;
        }
        cnt++;
    }
    return NULL;
}

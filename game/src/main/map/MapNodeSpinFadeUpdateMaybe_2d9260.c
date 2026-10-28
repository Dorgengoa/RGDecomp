/* rgp:protos */
#define RGP_SELF_MapNodeSpinFadeUpdateMaybe_2d9260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A2d9260 {
    u8 m0;
    u8 pad1[3];
    s32 m4;
    f32 m8;
    f32 mC;
} A2d9260;

typedef struct R2d9260 {
    u8 pad0[0x32];
    s16 m32;
    u8 pad34[0x30];
    f32 m64;
} R2d9260;

typedef struct Q2d9260 {
    u8 pad0[0x34];
    s32 m34;
    s32 m38;
} Q2d9260;

typedef struct P2d9260 {
    s32 m0;
    f32 m4;
    s32 m8;
    s32 mC;
} P2d9260;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047DAE0;
extern f32 D_0047DC8C;

void MapNodeSpinFadeUpdateMaybe_2d9260(A2d9260 *arg0, s32 arg1, Q2d9260 *arg2, s32 arg3)
{
    R2d9260 *r;
    P2d9260 p __attribute__((aligned(16)));
    u8 *q;
    u32 n;
    f32 v;

    if (arg0->m0 == 0) {
        if (arg2 == NULL) {
            return;
        }
        r = ((R2d9260 *)NodeObjFindChildByName_195040(arg2, arg3));
        if (r == NULL) {
            return;
        }
        r->m64 = 0.0f;
        r->m32 = 0;
        return;
    }
    switch (arg0->m4) {
    case 0:
        arg0->mC = arg0->mC + D_0047DAE0;
        break;
    case 1:
        arg0->mC = arg0->mC - D_0047DAE0;
        break;
    }
    arg0->m8 = WrapAngle_13c050(D_0047DC8C + arg0->m8);
    if (arg0->mC < 0.0f) {
        arg0->mC = 0.0f;
    }
    if (!(arg0->mC <= 1.0f)) {
        arg0->mC = 1.0f;
    }
    if (arg2 == NULL) {
        return;
    }
    arg2->m34 = 0;
    arg2->m38 = 0;
    NodeSetTranslation_1866b0(arg2, arg1);
    v = arg0->m8;
    q = (u8 *)&p;
    n = 16;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--n != 0);
    }
    p.m4 = v;
    p.m0 = 0;
    p.m8 = 0;
    NodeSetRotation_186620(arg2, &p);
    r = ((R2d9260 *)NodeObjFindChildByName_195040(arg2, arg3));
    if (r == NULL) {
        return;
    }
    r->m64 = arg0->mC;
    r->m32 = 1;
}

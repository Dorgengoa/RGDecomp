/* rgp:protos */
#define RGP_SELF_XformRecUpdateMaybe_1c5ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef union Vec4 {
    struct {
        f32 x, y, z, w;
    } v;
    u128 q;
} __attribute__((aligned(16))) Vec4;

typedef struct Mtx4 {
    Vec4 r[4];
} Mtx4;

typedef struct Mdl {
    u8 pad0[0x60];
    Mtx4 m60;
} Mdl;

typedef struct Chr {
    u8 pad0[0x180];
    Vec4 v180;
    Vec4 v190;
    u8 pad1A0[0x4CC - 0x1A0];
    f32 f4CC;
} Chr;

typedef struct Node {
    s32 w0;
    u8 pad4[0xC];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
} Node;

typedef struct Look {
    u8 pad0[4];
    f32 f04;
    f32 f08;
    u8 padC[8];
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    Vec4 v20;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    Vec4 v40;
    s16 h50;
    u8 pad52[6];
    s16 h58;
    s16 h5A;
    s16 h5C;
    s16 h5E;
} Look;

typedef struct World {
    u8 pad0[0x4340];
    s32 w4340;
} World;

extern s16 D_0047E278;
extern s16 D_0047E27A;
extern f32 D_0047D1FC;
extern f32 D_0047D288;
extern f32 D_0047D310;
extern f32 D_0047D1F4;
extern f32 D_0047D240;
extern f32 D_0047D2E8;
extern f32 D_0047D2EC;
extern f32 D_0047D324;
extern f32 D_0047D328;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

#pragma opt_unpromotetypes on
void XformRecUpdateMaybe_1c5ee0(Look *__restrict lk, World *g)
{
    volatile s16 ax[2];
    Vec4 d __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 hp __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    Vec4 tgt __attribute__((aligned(16)));
    Mtx4 unit __attribute__((aligned(16)));
    Mtx4 m __attribute__((aligned(16)));
    Mtx4 ma __attribute__((aligned(16)));
    Mtx4 mb __attribute__((aligned(16)));
    Chr *ch;
    s32 cnt;
    Mdl *m5;
    Mdl *m6;
    Chr *c2;
    Mdl *mdl;
    s32 id;
    s32 idx;
    f32 yaw;
    f32 pitch;
    f32 len;
    f32 a;
    Node *n6;
    f32 t;
    Node *n5;

    XformRecProximityUpdateMaybe_1c6690(lk, (void *)g);
    if (lk->h58 == 0) {
        return;
    }
    ch = ((Chr *)ObjRecGetLiveObject_1c4a90(g, lk->h5A));
    if (ch == 0) {
        return;
    }
    n5 = ((Node *)ObjFindNthAttachPoint_1addc0(ch, 5, 0));
    n6 = ((Node *)ObjFindNthAttachPoint_1addc0(ch, 6, 0));
    if (n5 == 0 || n6 == 0) {
        return;
    }
    m5 = ((Mdl *)ModelGetFrame_1511f0(ch, n5->w0));
    m6 = ((Mdl *)ModelGetFrame_1511f0(ch, n6->w0));
    if (m5 == 0 || m6 == 0) {
        return;
    }
    ax[0] = D_0047E278;
    ax[1] = D_0047E27A;
    if (!(n5->f18 <= 0.0f)) {
        ax[0] = (s16)(s32)n5->f18 - 1;
    }
    if (!(n5->f1C <= 0.0f)) {
        ax[1] = (s16)(s32)n5->f1C - 1;
    }
    pos.q = ch->v180.q;
    *(u128 *)rot = ch->v190.q;
    FrameGetWorldPos_148f30((s32)m5, &hp);
    if (lk->h58 == 3) {
        yaw = rot[1];
        pitch = 0.0f;
    }
    if (lk->h58 == 1) {
        goto calc;
    }
    if (lk->h58 == 2) {
    calc:
        id = lk->h5C;
        if (id == 0) {
            id = g->w4340;
        }
        if (lk->h50 == 4) {
            tgt.q = lk->v20.q;
        } else {
            idx = lk->h5E;
            if (idx >= 0) {
                id = idx;
            }
            c2 = ((Chr *)ObjRecGetLiveObject_1c4a90(g, id));
            if (c2 == 0) {
                return;
            }
            mdl = ((Mdl *)ModelGetFrame_1511f0(c2, ModelFindFrameIndexByName_151220(c2, &lk->v40)));
            if (mdl != 0) {
                FrameGetWorldPos_148f30((s32)mdl, &tgt);
            } else {
                FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(c2), &tgt);
                tgt.v.y = tgt.v.y + D_0047D240 * (c2->f4CC - 25.0f);
            }
        }
        VecSub_13be40(&d, &tgt, &pos);
        yaw = Atan2f_1291a8(d.v.x, d.v.z);
        VecSub_13be40(&d, &tgt, &hp);
        d.v.y = 0.0f;
        len = VecLength_13d4a0(&d);
        VecSub_13be40(&d, &tgt, &hp);
        pitch = -Atan2f_1291a8(d.v.y, len);
    }
    if (lk->h50 == 2) {
        a = yaw - rot[1];
if (a > D_0047D1FC) {
            a -= 6.2831855f;
        }
        if (a < -3.1415927f) {
            a += 6.2831855f;
        }
        a=(a<0.0f)?-a:a;
        if (!(a <= D_0047D1F4)) {
            pitch = 0.0f;
            yaw = rot[1];
        }
    } else {
        a = WrapAngle_13c050(yaw - rot[1]);
        if (!((a < 0.0f ? -a : a) <= D_0047D1F4)) {
            yaw = rot[1] + *(volatile f32 *)&D_0047D1F4 * (a / (a < 0.0f ? -a : a));
        }
    }
    cnt = 0;
    t = n5->f10 * (D_0047D288 * WrapAngle_13c050(yaw - rot[1]));
    if (t < D_0047D2E8) {
        t = D_0047D2E8;
    }
    if (!(t <= D_0047D2EC)) {
        t = D_0047D2EC;
    }
    lk->f04 = AngleStepToward_13c150(lk->f04, t, lk->f30, 1);
    if (AngleDiffSign_13c0d0(lk->f04, rot[1], D_0047D310) == 0) {
        cnt++;
    }
    t = n6->f10 * WrapAngle_13c050(yaw - (t + rot[1]));
    if (t < D_0047D2E8) {
        t = D_0047D2E8;
    }
    if (!(t <= D_0047D2EC)) {
        t = D_0047D2EC;
    }
    lk->f14 = AngleStepToward_13c150(lk->f14, t, lk->f38, 1);
    if (AngleDiffSign_13c0d0(lk->f14, rot[1], D_0047D310) == 0) {
        cnt++;
    }
    t = D_0047D288 * pitch;
    t = t * n5->f14;
    if (t < D_0047D2E8) {
        t = D_0047D2E8;
    }
    if (!(t <= D_0047D2EC)) {
        t = D_0047D2EC;
    }
    lk->f08 = AngleStepToward_13c150(lk->f08, t, lk->f34, 1);
    if (AngleDiffSign_13c0d0(lk->f08, t, D_0047D310) == 0) {
        cnt++;
    }
    pitch = n6->f14 * WrapAngle_13c050(pitch - t);
    if (pitch < D_0047D324) {
        pitch = D_0047D324;
    }
    if (!(pitch <= D_0047D328)) {
        pitch = D_0047D328;
    }
    lk->f18 = AngleStepToward_13c150(lk->f18, pitch, lk->f3C, 1);
    if (AngleDiffSign_13c0d0(lk->f18, pitch, D_0047D310) == 0) {
        cnt++;
    }
    if (lk->h58 == 1 && cnt == 4) {
        lk->h58 = 2;
    }
    if (lk->h58 == 3 && cnt == 4) {
        lk->h58 = 0;
    }
    sceVu0UnitMatrix(&unit);
    switch (ax[0]) {
    case 0:
        sceVu0RotMatrixX(&ma, &unit, lk->f04);
        break;
    case 1:
        sceVu0RotMatrixY(&ma, &unit, lk->f04);
        break;
    case 2:
        sceVu0RotMatrixZ(&ma, &unit, lk->f04);
        break;
    }
    sceVu0UnitMatrix(&unit);
    switch (ax[1]) {
    case 0:
        sceVu0RotMatrixX(&mb, &unit, lk->f08);
        break;
    case 1:
        sceVu0RotMatrixY(&mb, &unit, lk->f08);
        break;
    case 2:
        sceVu0RotMatrixZ(&mb, &unit, lk->f08);
        break;
    }
    m.r[0].q = m5->m60.r[0].q;
    m.r[1].q = m5->m60.r[1].q;
    m.r[2].q = m5->m60.r[2].q;
    m.r[3].q = m5->m60.r[3].q;
    sceVu0MulMatrix(&m, &m, &ma);
    sceVu0MulMatrix(&m, &m, &mb);
    ModelFrameSetMatrix_14a190(m5, &m);
    sceVu0UnitMatrix(&unit);
    sceVu0RotMatrixX(&ma, &unit, lk->f14);
    sceVu0UnitMatrix(&unit);
    sceVu0RotMatrixZ(&mb, &unit, lk->f18);
    m.r[0].q = m6->m60.r[0].q;
    m.r[1].q = m6->m60.r[1].q;
    m.r[2].q = m6->m60.r[2].q;
    m.r[3].q = m6->m60.r[3].q;
    sceVu0MulMatrix(&m, &m, &ma);
    sceVu0MulMatrix(&m, &m, &mb);
    ModelFrameSetMatrix_14a190(m6, &m);
}

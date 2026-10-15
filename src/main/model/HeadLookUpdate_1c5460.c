#include "types.h"

typedef unsigned __int128 u128;

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
    u8 pad190[0x4CC - 0x190];
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
    Mdl *p20;
    Mdl *p24;
    s32 p28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    s16 h3C;
    u8 pad3E[6];
    s16 h44;
    s16 h46;
    u8 pad48[8];
    Vec4 v50;
} Look;

extern s16 D_0047E27C;
extern s16 D_0047E27E;
extern f32 D_0047D1FC;
extern f32 D_0047D288;
extern const f32 D_0047D310 __attribute__((section(".sdata")));
extern f32 D_0047D404;
extern f32 D_0047D5D0;
extern f32 D_0047DB04;
extern f32 D_0047DB08;
extern f32 D_0047DB0C;
extern f32 D_0047DB10;

extern f32 Atan2f_1291a8(f32, f32);
extern f32 WrapAngle_13c050(f32);
extern s32 AngleDiffSign_13c0d0(f32, f32, f32);
extern f32 AngleStepToward_13c150(s32, f32, f32, f32);
extern f32 VecLength_13d4a0(Vec4 *);
extern void FrameGetWorldPos_148f30(s32, Vec4 *);
extern void FrameCalcWorldMatrix_148ff0(s32, Mtx4 *);
extern void ModelFrameSetMatrix_14a190(Mdl *, Mtx4 *);
extern s32 ModelGetRootFrame_1511a0(Chr *);
extern Mdl *ModelGetFrame_1511f0(Chr *, s32);
extern Node *ObjFindNthAttachPoint_1addc0(Chr *, s32, s32);
extern Chr *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void HeadLookProximityUpdate_1c5ce0(Look *);
extern void MatToRotPos_1cade0(Vec4 *, Vec4 *, Mtx4 *);
extern void sceVu0MulMatrix(Mtx4 *, Mtx4 *, Mtx4 *);
extern void sceVu0RotMatrixX(Mtx4 *, Mtx4 *, f32);
extern void sceVu0RotMatrixY(Mtx4 *, Mtx4 *, f32);
extern void sceVu0RotMatrixZ(Mtx4 *, Mtx4 *, f32);
extern void sceVu0SubVector(Vec4 *, Vec4 *, Vec4 *);
extern void sceVu0UnitMatrix(Mtx4 *);

#pragma opt_unpromotetypes on
void HeadLookUpdate_1c5460(Look *lk, s32 g)
{
    volatile s16 ax[2];
    Vec4 d;
    Vec4 pos;
    Vec4 sc;
    Vec4 rot;
    Mtx4 wm;
    Mtx4 unit;
    Mtx4 m;
    Mtx4 ma;
    Mtx4 mb;
    Chr *ch;
    Node *n5;
    Node *n6;
    f32 yaw;
    f32 pitch;
    f32 len;
    f32 a;
    f32 t;
    s32 cnt;

    HeadLookProximityUpdate_1c5ce0(lk);
    if (lk->h44 == 0) {
        return;
    }
    ch = ObjRecGetLiveObject_1c4a90(g, lk->h46);
    if (ch == 0) {
        return;
    }
    n5 = ObjFindNthAttachPoint_1addc0(ch, 5, 0);
    n6 = ObjFindNthAttachPoint_1addc0(ch, 6, 0);
    if (n5 == 0 || n6 == 0) {
        return;
    }
    lk->p20 = ModelGetFrame_1511f0(ch, n5->w0);
    lk->p24 = ModelGetFrame_1511f0(ch, n6->w0);
    if (lk->p20 == 0) {
        return;
    }
    if (lk->p24 == 0) {
        return;
    }
    ax[0] = D_0047E27C;
    ax[1] = D_0047E27E;
    if (!(n5->f18 <= 0.0f)) {
        ax[0] = (s16)(s32)n5->f18 - 1;
    }
    if (!(n5->f1C <= 0.0f)) {
        ax[1] = (s16)(s32)n5->f1C - 1;
    }
    FrameCalcWorldMatrix_148ff0(ModelGetRootFrame_1511a0(ch), &wm);
    MatToRotPos_1cade0(&rot, &sc, &wm);
    if (lk->p28 != 0) {
        FrameGetWorldPos_148f30(lk->p28, &pos);
    } else {
        pos.q = ch->v180.q;
        pos.v.y = pos.v.y + D_0047D5D0 * ch->f4CC;
    }
    if (lk->h44 == 3) {
        yaw = rot.v.y;
        pitch = 0.0f;
    }
    if (lk->h44 == 1) {
        goto calc;
    }
    if (lk->h44 == 2) {
    calc:
        sceVu0SubVector(&d, &lk->v50, &pos);
        yaw = Atan2f_1291a8(d.v.x, d.v.z);
        d.v.y = 0.0f;
        len = VecLength_13d4a0(&d);
        sceVu0SubVector(&d, &lk->v50, &pos);
        pitch = -Atan2f_1291a8(d.v.y, len);
    }
    if (lk->h3C == 2) {
        a = yaw - rot.v.y;
        if (a > D_0047D1FC) {
            a -= 6.2831855f;
        }
        if (a < -3.1415927f) {
            a += 6.2831855f;
        }
        a=(a<0.0f)?-a:a;
        if (!(a <= D_0047D404)) {
            pitch = 0.0f;
            yaw = rot.v.y;
        }
    } else {
        a = WrapAngle_13c050(yaw - rot.v.y);
        if (!((a < 0.0f ? -a : a) <= D_0047D404)) {
            yaw = rot.v.y + *(volatile f32 *)&D_0047D404 * (a / (a < 0.0f ? -a : a));
        }
    }
    cnt = 0;
    t = n5->f10 * (D_0047D288 * WrapAngle_13c050(yaw - rot.v.y));
    if (t < D_0047DB04) {
        t = D_0047DB04;
    }
    if (!(t <= D_0047DB08)) {
        t = D_0047DB08;
    }
    lk->f04 = AngleStepToward_13c150(1, lk->f04, t, lk->f2C);
    if (AngleDiffSign_13c0d0(lk->f04, rot.v.y, *(f32 *)&D_0047D310) == 0) {
        cnt++;
    }
    t = n6->f10 * WrapAngle_13c050(yaw - (t + rot.v.y));
    if (t < D_0047DB04) {
        t = D_0047DB04;
    }
    if (!(t <= D_0047DB08)) {
        t = D_0047DB08;
    }
    lk->f14 = AngleStepToward_13c150(1, lk->f14, t, lk->f34);
    if (AngleDiffSign_13c0d0(lk->f14, rot.v.y, *(f32 *)&D_0047D310) == 0) {
        cnt++;
    }
    t = D_0047D288 * pitch;
    t = t * n5->f14;
    if (t < D_0047DB04) {
        t = D_0047DB04;
    }
    if (!(t <= D_0047DB08)) {
        t = D_0047DB08;
    }
    lk->f08 = AngleStepToward_13c150(1, lk->f08, t, lk->f30);
    if (AngleDiffSign_13c0d0(lk->f08, t, *(f32 *)&D_0047D310) == 0) {
        cnt++;
    }
    pitch = n6->f14 * WrapAngle_13c050(pitch - t);
    if (pitch < D_0047DB0C) {
        pitch = D_0047DB0C;
    }
    if (!(pitch <= D_0047DB10)) {
        pitch = D_0047DB10;
    }
    lk->f18 = AngleStepToward_13c150(1, lk->f18, pitch, lk->f38);
    if (AngleDiffSign_13c0d0(lk->f18, pitch, D_0047D310) == 0) {
        cnt++;
    }
    if (lk->h44 == 1 && cnt == 4) {
        lk->h44 = 2;
    }
    if (lk->h44 == 3 && cnt == 4) {
        lk->h44 = 0;
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
    m.r[0].q = lk->p20->m60.r[0].q;
    m.r[1].q = lk->p20->m60.r[1].q;
    m.r[2].q = lk->p20->m60.r[2].q;
    m.r[3].q = lk->p20->m60.r[3].q;
    sceVu0MulMatrix(&m, &m, &ma);
    sceVu0MulMatrix(&m, &m, &mb);
    ModelFrameSetMatrix_14a190(lk->p20, &m);
    sceVu0UnitMatrix(&unit);
    sceVu0RotMatrixX(&ma, &unit, lk->f14);
    sceVu0UnitMatrix(&unit);
    sceVu0RotMatrixZ(&mb, &unit, lk->f18);
    m.r[0].q = lk->p24->m60.r[0].q;
    m.r[1].q = lk->p24->m60.r[1].q;
    m.r[2].q = lk->p24->m60.r[2].q;
    m.r[3].q = lk->p24->m60.r[3].q;
    sceVu0MulMatrix(&m, &m, &ma);
    sceVu0MulMatrix(&m, &m, &mb);
    ModelFrameSetMatrix_14a190(lk->p24, &m);
}

#include "types.h"
#pragma divbyzerocheck on
#pragma opt_loop_invariants off
#pragma opt_propagation off
#pragma opt_pulloutconstants off

typedef unsigned __int128 u128;

typedef struct Vec {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec;

struct Sub {
    u8 pad0[1];
};

struct Map {
    Vec f0;
    Vec f10;
    Vec f20;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[0x40];
    s32 fC4;
    s32 fC8;
    u8 padCC[0x10];
    f32 fDC;
    u8 padE0[4];
    f32 fE4;
    u8 padE8[0x14];
    s16 fFC;
    s16 fFE;
    s16 f100;
    s16 f102;
    u8 pad104[4];
    s16 f108;
    s16 f10A;
    u8 pad10C[0xA];
    u8 f116;
    u8 f117;
    u8 f118;
    u8 f119;
    u8 pad11A[2];
    s8 f11C;
    u8 pad11D[3];
    Sub f120;
    u8 pad121[0x43];
    f32 f164;
    f32 f168;
};

struct Ctx {
    u8 pad0[0x10];
    s32 f10;
    u8 pad14[4];
    s32 f18;
};

struct Obj {
    u8 pad0[0x18];
    s16 f18;
    u8 f1A;
    u8 pad1B[5];
    Vec f20;
    u8 pad30[0x10];
    s32 f40;
};

struct Chr {
    u8 pad0[8];
    s16 f8;
    u8 padA[0xA];
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 pad20[6];
    s16 f26;
    u8 pad28[0x14];
    struct {
        u8 pad0[0xA];
        u8 fA;
    } *f3C;
    s32 f40;
};

struct Pt {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x2E];
    f32 f38;
    f32 f3C;
    f32 f40;
    u8 pad44[4];
    s32 f48;
    u8 pad4C[0xA];
    u8 f56;
};

struct Ent {
    u8 pad0[0x18];
    struct {
        u8 pad0[8];
        s16 f8;
    } *f18;
};

struct Mark {
    f32 x, y, z, w;
};

struct Iter {
    u8 pad0[8];
};

struct Buf12 {
    u8 pad0[0xC];
};

struct Buf16 {
    u8 pad0[0x10];
};

struct Buf20 {
    u8 pad0[0x20];
};

struct Buf70 {
    u8 pad0[0x70];
};


extern "C" {
f64 FabsDouble_1283a0(f64);
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 Atan2f_1291a8(f32, f32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetAntialias_13e390(s32, s32);
void GsPktSetGouraud_13e3b0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetUseUV_13e3e0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetFrameMask_13e420(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktSetZTest_13e450(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktSetDestAlphaTest_13e4a0(s32, s32);
void GsPktSetDestAlphaMode_13e4b0(s32, s32);
void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetXYZf_13f060(s32, f32, f32, f32);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetDefaultState_13fa80(s32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void DrawListEndPrim_141a20(s32);
s32 DrawListBeginPrim_141b00(s32);
void DrawListAddEnv_1421d0(s32);
void DrawEnvGetVsyncInterval_144130(s32);
void DrawEnvPop_144800(s32);
void DrawEnvPush_144830(s32);
void DrawEnvSetFrameFromDesc_144fe0(s32, s32, s32);
s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetWidth_1451e0(s32);
void NameTableNodeCtor_15ae50(Buf70 *);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
s32 MapFindBlockIdAtPos_1e39d0(s32, void *, f32);
Ctx *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
s32 EntryGetTileSize_323ad0(s32);
void EntryGetRange_323af0(s32, f32 *, f32 *);
void EntryGetOrigin_323b10(s32, s32 *, s32 *);
f32 EntryGetScale_323b30(s32);
void EntryGetGridSize_323bb0(s32, s32 *, s32 *);
f32 MinimapEaseFactorMaybe_323dd0(Map *);
void MinimapGetEntryGridOrigin_323e40(Map *, s32, f32 *, f32 *);
s32 AngleToQuadrant_323fd0(Map *);
f32 GetQuadrantAngle_324120(Map *);
void MinimapGetScaledXZMaybe_3242b0(Map *, f32 *, f32 *, s32);
void MinimapGetWinSize_324c30(Map *, s32 *, s32 *);
void MinimapGetAspectScale_324c70(Map *);
void MinimapGetScreenAnchorPos_324c80(Map *, s32 *, s32 *);
void MinimapEmitSprite_324d30(Map *, s32, Buf16 *, Buf16 *, s32, s32, s32, s32, s32, s32);
void MinimapEmitQuadTris_324e20(Map *, s32, Buf16 *, Buf16 *, Buf16 *, Buf16 *, s32, s32, s32, s32, s32, s32);
s32 MinimapCheckBlockNameMaybe_325030(Map *, s32, s32, f32 *);
void MinimapCalcQuadCornersMaybe_325150(Map *, Buf16 *, Buf16 *, s32, s32, f32, f32, f32 *, s32, s32, s64);
void MinimapBuildRectCornersMaybe_3252b0(Map *, Buf16 *, Buf16 *, Buf16 *, Buf16 *, s32, s32, f32, f32, f32 *, s64, s64, s64);
s32 MinimapIsCellExplored_325550(Map *, Vec *, s32, s32);
void MinimapDrawTiles_328c50(Map *, s32, Vec *, s32, s32, s32, f32, f32);
f32 MinimapGetDrawAlpha_32a180(Map *);
s32 MinimapGetTexGroup_32a1e0(Map *);
s32 MinimapGetPendingOrCurEntry_32a8f0(Map *);
s32 MinimapGetCurOrPendingEntry_32a920(Map *);
s32 MinimapSubGetArray_32ae80(Sub *);
s32 MinimapSubGetCapacity_32ae90(Sub *);
s32 EntryPosRecIsOnEntry_32b030(s32, s32);
void Vec3Unpack_32b080(s32, f32 *, f32 *, f32 *);
void MinimapWorldToMapXZ_32c280(Vec *, f32, f32, f32, f32);
void *IterNext_370040(Iter *);
void IterReset_3700f0(Iter *);
void IterInit_370170(Iter *, void *);
s32 InvCollectPlacedCagesInCurLocation_3c4be0(s32, Ent **, s32);
s32 PartyLocationGroupIdIsOneMaybe_3cb120(s32);
s32 StateBlockCollectMapMarkers_3cc390(s32, Mark *, s16 *);
s32 StateFlag2Test_3cc860(s32, s32);
void CageRecGetPos_3d0b40(Ent *, Vec *);
u8 SavePointAreaCompleteTestMaybe_3ec7a0(Ctx *);
void NpcViewCtor_41c210(Buf20 *, Ctx *, s32, s32, s32);
void GroupViewCtor_425440(Buf16 *, Ctx *, s32, s32);
s32 SavePointIsActivated_426510(Obj *);
void TreasureBoxViewCtor_426d70(void *, Ctx *, s32);
void *memcpy(void *, const void *, u32);

extern f32 D_0047D1FC;
extern f32 D_0047D5D0;
extern f32 D_0047D7E0;
extern f32 D_0047D818;
}

#define ZERON(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = n; if (p_) do { *p_ = 0; n_--; p_++; } while (n_); }
#define ZERO16(d) ZERON(d, 16)

static inline s32 Shown3(s32 k) {
    switch (k) {
    case 0: case 2: case 1: return 1;
    }
    return 0;
}

static inline s32 Shown(s32 k) {
    switch (k) {
    case 0:
    case 2:
        return 1;
    case 1:
        return 1;
    }
    return 0;
}

static inline s32 Shown2(s32 k) {
    switch (k) {
    case 0:
    case 2:
        return 1;
    case 1:
        return 0;
    }
    return 0;
}

static inline s32 Shown6(s32 k) {
    switch (k) {
    case 1:
        return 0;
    case 0:
    case 2:
        return 1;
    }
    return 0;
}

static inline s32 Shown7(s32 k) {
    switch (k) {
    case 0:
        return 1;
    case 1:
        return 0;
    case 2:
        return 1;
    }
    return 0;
}

static inline u8 ScaleA(u8 a, f32 k) {
    return (u8)((f32)(u32)a * k);
}

extern "C" s32 MinimapDrawEntry_325720(Map *m, s32 who, Vec *at, s32 mode, f32 ang) {
    f32 alpha;
    s32 sz0;
    s32 sz1;
    f32 lo;
    f32 hi;
    s32 cnt0;
    s32 cnt1;
    f32 orgx;
    f32 orgz;
    f32 rx;
    f32 rz;
    f32 fx;
    f32 fz;
    f32 hh;
    f32 lim0;
    f32 lim1;
    f32 scl;
    f32 cz;
    f32 cx;
    f32 sx;
    f32 sz;
    f32 dz;
    f32 ey;
    f32 x1;
    f32 z1;
    f32 zc;
    f32 tx;
    f32 ty;
    f32 f;
    f32 hhE;
    f32 g;
    f32 mw;
    f32 mh;
    f32 cell;
    f32 unit;
    f32 offx;
    f32 offz;
    f32 bxw;
    f32 by;
    f32 bx;
    f32 x0;
    f32 fC;
    f32 hwM;
    f32 hhM;
    f32 pr;
    f32 mw0;
    f32 mh0;
    f32 ty2;
    f32 hw;
    s32 tw;
    s32 th;
    s32 bw;
    s32 bh;
    f32 a790;
    f32 a78C;
    f32 a788;
    u8 bg[4];
    Iter it770;
    Buf12 it760;
    Iter it758;
    Iter it750;
    Ent *ents[3];
    s16 ids[4];
    s16 ids2[4];
    Buf16 b720;
    Buf16 b710;
    Buf16 b700;
    Buf16 b6F0;
    Buf70 b680;
    f32 pos[4] __attribute__((aligned(16)));
    f32 org[4] __attribute__((aligned(16)));
    s32 ex2;
    s32 a610;
    s32 tex5;
    s32 tag;
    s32 tex;
    Ctx *ctx;
    s32 tex2;
    s32 ix;
    s32 iz;
    s32 flg;
    s32 area;
    s32 jx;
    s32 jz;
    s32 hx;
    s32 hz;
    s32 kx;
    s32 kz;
    s32 tex3;
    s32 lx;
    s32 lz;
    s32 tex4;
    s32 mx;
    s32 mz;
    s32 icon;
    s32 ey2;
    s32 ecnt;
    s32 mcnt;
    s32 a2D0;
    s32 g2C0;
    s32 b2B0;
    s32 g2A0;
    s32 b290;
    s32 g280;
    s32 b270;
    s32 g260;
    s32 b250;
    s32 g240;
    s32 b230;
    s32 g220;
    s32 b210;
    s32 y200;
    s32 y1F0;
    s32 x1E0;
    s32 y1D0;
    s32 x1C0;
    s32 x1B0;
    s32 y1A0;
    s32 x190;
    s32 pcnt;
    s32 parr;
    Ent **pent;
    s32 a150;
    Mark *pm;
    f32 *pmz;
    s32 gs;
    s32 c;
    s32 c0;
    s32 w;
    s32 h;
    s32 n;
    s32 i;
    s32 k;
    s32 passes;
    s32 pss;
    s32 km;
    s32 a;
    Obj *o;
    Chr *ch;
    Pt *pt;
    Ent *en;
    f32 bz;
    s32 t8;
    s32 area0;
    s32 fl;
    s32 nm;
    s32 ne;

    gs = GetDrawCtx_15de80();
    DrawEnvGetVsyncInterval_144130(gs);
    alpha = 1.0f;
    tag = MinimapGetPendingOrCurEntry_32a8f0(m);
    switch (mode) {
    case 0:
        memcpy(&m->f20, &m->f0, 0x10);
        alpha = m->fDC;
        tag = MinimapGetCurOrPendingEntry_32a920(m);
        break;
    case 1:
        memcpy(&m->f20, &m->f10, 0x10);
        alpha = m->fE4;
        tag = MinimapGetPendingOrCurEntry_32a8f0(m);
        break;
    }
    if (alpha <= 0.0f) return 0;
    f = D_0047D1FC * GetQuadrantAngle_324120(m) / 180.0f;
    pr = D_0047D818 * m->f168;
    { f32 t_ = pr + f; f = t_; }
    fx = Sinf_128fd0(f);
    fz = -Cosf_128d30(f);
    if (who == 0) return 0;
    c0 = GetDrawCtxNameTable_15de40();
    NameTableNodeCtor_15ae50(&b680);
    if (gs == 0) return 0;
    if (c0 == 0) return 0;
    tex = m->fC8;
    if (tex == 0) return 0;
    w = DrawEnvGetWidth_1451e0(gs);
    h = DrawEnvGetHeight_1451d0(gs);
    scl = MinimapGetDrawAlpha_32a180(m);
    DrawListAddTexLoad_1418c0(gs, MinimapGetTexGroup_32a1e0(m), 1.0f);
    DrawEnvPush_144830(gs);
    DrawEnvSetFrameFromDesc_144fe0(gs, tex, 0);
    DrawListAddEnv_1421d0(gs);
    c = DrawListBeginPrim_141b00(gs);
    GsPktSetDefaultState_13fa80(c);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetZTest_13e450(c, 0);
    GsPktSetTextured_13e400(c, 0);
    GsPktSetAlphaBlend_13e500(c, 0);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetRGBAQ_13ee40(c, 0, 0, 0, 0);
    GsPktSetXYZPixel_13f110(c, 0, 0, 0);
    GsPktSetXYZPixel_13f110(c, w, h, 0);
    GsPktClose_13f5b0(c);
    GsPktSetDefaultState_13fa80(c);
    GsPktSetAlphaBlend_13e500(c, 0);
    GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetGouraud_13e3b0(c, 1);
    GsPktSetOriginMode_13e2f0(c, 0);
    GsPktSetTextured_13e400(c, 1);
    GsPktSetUseUV_13e3e0(c, 1);
    GsPktSetTexFilter_13e3d0(c, 0);
    GsPktSetAntialias_13e390(c, 0);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetDestAlphaTest_13e4a0(c, 0);
    GsPktSetFrameMask_13e420(c, 0);
    MinimapGetAspectScale_324c70(m);
    lo = 0.0f;
    hi = 0.0f;
    unit = (f32)EntryGetTileSize_323ad0(who);
    EntryGetGridSize_323bb0(who, &sz0, &sz1);
    EntryGetOrigin_323b10(who, &cnt0, &cnt1);
    EntryGetRange_323af0(who, &lo, &hi);
    f = EntryGetScale_323b30(who);
    f = f * unit;
    ZERO16(pos);
    pos[0] = at->x;
    pos[1] = at->y;
    pos[2] = at->z;
    ZERO16(org);
    org[0] = m->f20.x;
    org[1] = m->f20.y;
    org[2] = m->f20.z;
    MinimapGetEntryGridOrigin_323e40(m, who, &orgx, &orgz);
    orgx = orgx + org[0];
    orgz = orgz + org[2];
    x1 = (pos[0] - orgx) / f;
    z1 = (pos[2] - orgz) / f;
    tx = (f32)m->f108;
    ty = (f32)m->f10A;
    n = (s32)(tx / unit);
    k = (s32)(ty / unit);
    if (n % 2 == 0) n++;
    if (k % 2 == 0) k++;
    if (n < 0) n = 5;
    if (k < 0) k = 5;
    x1 = x1 - (f32)(n / 2);
    z1 = z1 - (f32)(k / 2);
    MinimapDrawTiles_328c50(m, who, (Vec *)pos, n, k, c, x1, z1);
    mw0 = (f32)n * unit;
    mh0 = (f32)k * unit;
    cell = EntryGetScale_323b30(who);
    n = (s32)x1;
    k = (s32)z1;
    MinimapGetScaledXZMaybe_3242b0(m, &rx, &rz, 1);
    a = (s32)unit;
    offx = (f32)((s32)((pos[0] - orgx - (f32)n * (unit * cell)) / cell) % a);
    offz = (f32)((s32)((pos[2] - orgz - (f32)k * (unit * cell)) / cell) % a);
    MinimapGetScreenAnchorPos_324c80(m, &tw, &th);
    MinimapGetWinSize_324c30(m, &bw, &bh);
    bxw = (f32)bw;
    by = (f32)bh;
    hw = unit / 2.0f;
    tx = (f32)tw;
    ty2 = (f32)th;
    hh = unit / 4.0f;
    cz = by / 2.0f;
    cx = bxw / 2.0f;
    sx = (mw0 - bxw) / 2.0f;
    sz = (mh0 - by) / 2.0f;
    switch (AngleToQuadrant_323fd0(m)) {
    case 1:
        { f32 t_ = unit + hh; hh = t_; }
        break;
    case 2:
        { f32 t_ = unit + hw; hw = t_; }
        { f32 t_ = unit + hh; hh = t_; }
        break;
    case 3:
        { f32 u_ = unit; hh = u_ / 2.0f; }
        hw = unit + hh;
        break;
    }
    bx = tx + hw;
    dz = (tx + cx) - rx;
    ey = (ty2 + cz) - rz;
    mw = mw0 / 2.0f;
    mh = mh0 / 2.0f - hh;
    mw = mw - hw;
    x0 = ty2 + hh;
    lim0 = D_0047D5D0 * by;
    lim1 = D_0047D5D0 * bxw;
    if (Shown2(m->f11C)) {

        a790 = 1.0f;
        s32 col650[4] __attribute__((aligned(16))) = {128, 128, 128, 128};
        passes = 1;
        if ((t8 = m->f11C) == 2 || t8 == 1) {
            passes = 2;
            a2D0 = (s32)(128.0f * MinimapEaseFactorMaybe_323dd0(m));
        } else {
            a2D0 = 0x80;
        }
        ctx = GetGameData_1fede0();
        Buf16 b640;
        GroupViewCtor_425440(&b640, ctx, -1, 0);
        IterInit_370170(&it770, &b640);
        tex2 = m->fC4;
        if (tex2 != 0) {
            g220 = col650[2];
            b210 = col650[1];
            for (k = 0; k < passes; k++) {
                GsPktSetDefaultState_13fa80(c);
                GsPktEnableAlphaTest_13e4d0(c, 1);
                GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
                GsPktEnableZTest_13e460(c, 0);
                GsPktSetTextured_13e400(c, 1);
                GsPktSetOriginMode_13e2f0(c, 0);
                GsPktSetGouraud_13e3b0(c, 1);
                GsPktSetUseUV_13e3e0(c, 1);
                GsPktSetTexFilter_13e3d0(c, 0);
                GsPktSetAntialias_13e390(c, 0);
                GsPktSetZWriteMask_13e430(c, 1);
                if (passes == 2) {
                    GsPktSetAlphaBlend_13e500(c, 1);
                    GsPktSetBlendMode_13e4f0(c, 1);
                    if (k == 0) {
                        GsPktSetDestAlphaTest_13e4a0(c, 1);
                        GsPktSetDestAlphaMode_13e4b0(c, 1);
                        GsPktSetFrameMask_13e420(c, 2);
                    } else {
                        GsPktSetDestAlphaTest_13e4a0(c, 0);
                        GsPktSetFrameMask_13e420(c, 1);
                    }
                } else {
                    GsPktSetAlphaBlend_13e500(c, 0);
                    GsPktSetDestAlphaTest_13e4a0(c, 0);
                    GsPktSetFrameMask_13e420(c, 0);
                }
                GsPktOpenPrim_13f730(c, 3);
                GsPktSetTexture_13ec00(c, tex2);
                MinimapBuildRectCornersMaybe_3252b0(m, &b720, &b710, &b700, &b6F0, 9, 9, fx, fz, (f32[4]){1.0f, 0.7f, 1.0f, 0.0f}, 1, 0, 0);
                IterReset_3700f0(&it770);
                while (o = (Obj *)IterNext_370040(&it770), o != 0) {
                    if (o == 0) continue;
                    if (PartyLocationGroupIdIsOneMaybe_3cb120(ctx->f18) != 0 && !(o->f1A & 1)) continue;
                    if (!(o->f40 & 1)) continue;
                    if (!o->f20.x && !o->f20.y && !o->f20.z) continue;
                    if (MinimapCheckBlockNameMaybe_325030(m, o->f18, mode, &a790) == 0) continue;
                    if (!(lo < o->f20.y)) continue;
                    if (!(o->f20.y < hi)) continue;
                    f32 d630[4] __attribute__((aligned(16)));
                    ZERO16(d630);
                    fl = 0;
                    flg = 0;
                    d630[0] = o->f20.x - pos[0];
                    d630[1] = o->f20.y - pos[1];
                    d630[2] = o->f20.z - pos[2];
                    d630[0] = d630[0] / cell;
                    d630[2] = d630[2] / cell;
                    ix = (s32)(offx + (d630[0] + mw));
                    iz = (s32)(offz + (d630[2] + mh));
                    if (SavePointIsActivated_426510(o) == 0) fl += 0x12;
                    f32 w620[4] __attribute__((aligned(16)));
                    ZERO16(w620);
                    w620[0] = o->f20.x;
                    w620[1] = o->f20.y;
                    w620[2] = o->f20.z;
                    MinimapWorldToMapXZ_32c280((Vec *)w620, cell, orgx, orgz, unit);
                    if (MinimapIsCellExplored_325550(m, (Vec *)w620, who, AngleToQuadrant_323fd0(m)) != 0) {
                        GsPktSetRGBAQ_13ee40(c, col650[0], b210, g220, (s32)((f32)a2D0 * a790));
                        MinimapEmitQuadTris_324e20(m, c, &b720, &b710, &b700, &b6F0, ix, iz, fl, flg, 0x12, 0x12);
                    }
                }
                GsPktClose_13f5b0(c);
            }
        }
    }
    if (Shown(m->f11C)) {

        tex2 = m->fC4;
        s32 col610[4] __attribute__((aligned(16))) = {128, 128, 128, 128};
        { s32 *p_ = &col610[3]; *p_ = (s32)((f32)*p_ * alpha); }
        if (tex2 != 0) {
            GsPktSetDefaultState_13fa80(c);
            GsPktSetAlphaBlend_13e500(c, 0);
            GsPktEnableAlphaTest_13e4d0(c, 1);
            GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
            GsPktEnableZTest_13e460(c, 0);
            GsPktSetTextured_13e400(c, 1);
            GsPktSetOriginMode_13e2f0(c, 0);
            GsPktSetGouraud_13e3b0(c, 1);
            GsPktSetUseUV_13e3e0(c, 1);
            GsPktSetTexFilter_13e3d0(c, 0);
            GsPktSetAntialias_13e390(c, 0);
            GsPktSetZWriteMask_13e430(c, 1);
            GsPktSetDestAlphaTest_13e4a0(c, 0);
            GsPktSetFrameMask_13e420(c, 0);
            GsPktOpenPrim_13f730(c, 6);
            GsPktSetTexture_13ec00(c, tex2);
            MinimapCalcQuadCornersMaybe_325150(m, &b720, &b6F0, 8, 8, 0.0f, 0.0f, (f32[4]){0.8f, 0.8f, 1.0f, 0.0f}, 0, 0, 0);
            pcnt = MinimapSubGetCapacity_32ae90(&m->f120);
            parr = MinimapSubGetArray_32ae80(&m->f120);
            g240 = col610[2];
            a610 = col610[3];
            b230 = col610[1];
            for (i = 0; i < pcnt; i++) {
                s32 e = parr + i * 0x10;

                if (e == 0) continue;
                if (EntryPosRecIsOnEntry_32b030(e, tag) == 0) continue;
                f32 p600[4] __attribute__((aligned(16)));
                Vec3Unpack_32b080(e, &p600[0], &p600[1], &p600[2]);
                f32 d5F0[4] __attribute__((aligned(16)));
                ZERO16(d5F0);
                d5F0[0] = p600[0] - pos[0];
                d5F0[1] = p600[1] - pos[1];
                d5F0[2] = p600[2] - pos[2];
                d5F0[0] = d5F0[0] / cell;
                d5F0[2] = d5F0[2] / cell;
                jx = (s32)(offx + (d5F0[0] + mw));
                jz = (s32)(offz + (d5F0[2] + mh));
                f32 w5E0[4] __attribute__((aligned(16)));
                ZERO16(w5E0);
                w5E0[0] = p600[0];
                w5E0[1] = p600[1];
                w5E0[2] = p600[2];
                MinimapWorldToMapXZ_32c280((Vec *)w5E0, cell, orgx, orgz, unit);
                if (MinimapIsCellExplored_325550(m, (Vec *)w5E0, who, AngleToQuadrant_323fd0(m)) != 0) {
                    GsPktSetRGBAQ_13ee40(c, col610[0], b230, g240, a610);
                    MinimapEmitSprite_324d30(m, c, &b720, &b6F0, jx, jz, 0x24, 0, 0x10, 0x10);
                }
            }
            GsPktClose_13f5b0(c);
        }
    }
    a = Shown3(m->f11C);
    if (a != 0) a = SavePointAreaCompleteTestMaybe_3ec7a0(GetGameData_1fede0());
    if (a != 0) {
        tex2 = m->fC4;
        if (tex2 != 0) {
            area0 = GetMapMgr_201a90();
            GsPktSetDefaultState_13fa80(c);
            GsPktSetAlphaBlend_13e500(c, 0);
            GsPktEnableAlphaTest_13e4d0(c, 1);
            GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
            GsPktEnableZTest_13e460(c, 0);
            GsPktSetTextured_13e400(c, 1);
            GsPktSetOriginMode_13e2f0(c, 0);
            GsPktSetGouraud_13e3b0(c, 1);
            GsPktSetUseUV_13e3e0(c, 1);
            GsPktSetTexFilter_13e3d0(c, 0);
            GsPktSetAntialias_13e390(c, 0);
            GsPktSetZWriteMask_13e430(c, 1);
            GsPktSetDestAlphaTest_13e4a0(c, 0);
            GsPktSetFrameMask_13e420(c, 0);
            GsPktOpenPrim_13f730(c, 6);
            GsPktSetTexture_13ec00(c, tex2);
            MinimapCalcQuadCornersMaybe_325150(m, &b720, &b6F0, 4, 4, 0.0f, 0.0f, (f32[4]){1.0f, 1.0f, 1.0f, 0.0f}, 0, 0, 0);
            ctx = GetGameData_1fede0();
            TreasureBoxViewCtor_426d70(&it760, ctx, -1);
            IterInit_370170(&it758, &it760);
            while ((ch = (Chr *)IterNext_370040(&it758)) != 0) {
                if (StateFlag2Test_3cc860(ctx->f10, ch->f8) != 0) continue;
                if (ch->f3C == 0 || (ch->f3C->fA & 1) || !(ch->f40 & 2)) continue;
                f32 q5D0[4] __attribute__((aligned(16)));
                ZERO16(q5D0);
                q5D0[0] = ch->f14;
                q5D0[1] = ch->f18;
                q5D0[2] = ch->f1C;
                if (ch->f26 == -1) ch->f26 = MapFindBlockIdAtPos_1e39d0(area0, q5D0, 0.0f);
                if (MinimapCheckBlockNameMaybe_325030(m, ch->f26, mode, &alpha) == 0) continue;
                if (!(lo < q5D0[1]) || !(q5D0[1] <= hi)) continue;
                s32 col5C0[4] __attribute__((aligned(16))) = {128, 128, 128, 128};
                { s32 *p_ = &col5C0[3]; *p_ = (s32)((f32)*p_ * alpha); }
                f32 d5B0[4] __attribute__((aligned(16))) = {0};
                d5B0[0] = q5D0[0] - pos[0];
                d5B0[1] = q5D0[1] - pos[1];
                d5B0[2] = q5D0[2] - pos[2];
                d5B0[0] = d5B0[0] / cell;
                d5B0[2] = d5B0[2] / cell;
                hx = (s32)(offx + (d5B0[0] + mw));
                hz = (s32)(offz + (d5B0[2] + mh));
                f32 w5A0[4] __attribute__((aligned(16)));
                ZERO16(w5A0);
                w5A0[0] = q5D0[0];
                w5A0[1] = q5D0[1];
                w5A0[2] = q5D0[2];
                MinimapWorldToMapXZ_32c280((Vec *)w5A0, cell, orgx, orgz, unit);
                if (MinimapIsCellExplored_325550(m, (Vec *)w5A0, who, AngleToQuadrant_323fd0(m)) != 0) {
                    GsPktSetRGBAQ_13ee40(c, col5C0[0], col5C0[1], col5C0[2], col5C0[3]);
                    MinimapEmitSprite_324d30(m, c, &b720, &b6F0, hx, hz, 0x34, 0, 8, 8);
                }
            }
            GsPktClose_13f5b0(c);
        }
    }
    if (Shown(m->f11C)) {
        tex3 = m->fC4;
        if (tex3 != 0) {

            area = GetMapMgr_201a90();
            s32 col590[4] __attribute__((aligned(16))) = {128, 128, 128, 128};
            passes = 1;
            { s32 *p_ = &col590[3]; *p_ = (s32)((f32)*p_ * alpha); }
            if ((t8 = m->f11C) == 2 || t8 == 1) {
                passes = 2;
                a = (s32)(128.0f * MinimapEaseFactorMaybe_323dd0(m));
            } else {
                a = 0x80;
            }
            Buf20 b570;
            NpcViewCtor_41c210(&b570, GetGameData_1fede0(), -1, 1, 0);
            IterInit_370170(&it750, &b570);
            g260 = col590[2];
            b250 = col590[1];
            for (i = 0; i < passes; i++) {
                GsPktSetDefaultState_13fa80(c);
                GsPktSetAlphaBlend_13e500(c, 0);
                GsPktEnableAlphaTest_13e4d0(c, 1);
                GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
                GsPktEnableZTest_13e460(c, 0);
                GsPktSetTextured_13e400(c, 1);
                GsPktSetOriginMode_13e2f0(c, 0);
                GsPktSetGouraud_13e3b0(c, 1);
                GsPktSetUseUV_13e3e0(c, 1);
                GsPktSetTexFilter_13e3d0(c, 0);
                GsPktSetAntialias_13e390(c, 0);
                GsPktSetZWriteMask_13e430(c, 1);
                if (passes == 2) {
                    GsPktSetAlphaBlend_13e500(c, 1);
                    GsPktSetBlendMode_13e4f0(c, 1);
                    if (i == 0) {
                        GsPktSetDestAlphaTest_13e4a0(c, 1);
                        GsPktSetDestAlphaMode_13e4b0(c, 1);
                        GsPktSetFrameMask_13e420(c, 2);
                    } else {
                        GsPktSetDestAlphaTest_13e4a0(c, 0);
                        GsPktSetFrameMask_13e420(c, 1);
                    }
                } else {
                    GsPktSetAlphaBlend_13e500(c, 0);
                    GsPktSetDestAlphaTest_13e4a0(c, 0);
                    GsPktSetFrameMask_13e420(c, 0);
                }
                GsPktOpenPrim_13f730(c, 6);
                GsPktSetTexture_13ec00(c, tex3);
                MinimapCalcQuadCornersMaybe_325150(m, &b720, &b6F0, 7, 7, 0.0f, 0.0f, (f32[4]){1.0f, 1.0f, 1.0f, 0.0f}, 0, 0, 0);
                IterReset_3700f0(&it750);
                while ((pt = (Pt *)IterNext_370040(&it750)) != 0) {
                    if (!(pt->f56 & 1) || !(pt->f48 & 1) || !(pt->f8 & 6)) continue;
                    f32 q560[4] __attribute__((aligned(16)));
                    ZERO16(q560);
                    q560[0] = pt->f38;
                    q560[1] = pt->f3C;
                    q560[2] = pt->f40;
                    if (MinimapCheckBlockNameMaybe_325030(m, MapFindBlockIdAtPos_1e39d0(area, q560, 0.0f), mode, &alpha) == 0) continue;
                    if (!(lo < q560[1]) || !(q560[1] <= hi)) continue;
                    f32 d550[4] __attribute__((aligned(16)));
                    ZERO16(d550);
                    d550[0] = q560[0] - pos[0];
                    d550[1] = q560[1] - pos[1];
                    d550[2] = q560[2] - pos[2];
                    d550[0] = d550[0] / cell;
                    d550[2] = d550[2] / cell;
                    kx = (s32)(offx + (d550[0] + mw));
                    kz = (s32)(offz + (d550[2] + mh));
                    f32 w540[4] __attribute__((aligned(16)));
                    ZERO16(w540);
                    w540[0] = q560[0];
                    w540[1] = q560[1];
                    w540[2] = q560[2];
                    MinimapWorldToMapXZ_32c280((Vec *)w540, cell, orgx, orgz, unit);
                    if (MinimapIsCellExplored_325550(m, (Vec *)w540, who, AngleToQuadrant_323fd0(m)) != 0) {
                        GsPktSetRGBAQ_13ee40(c, col590[0], b250, g260, a);
                        MinimapEmitSprite_324d30(m, c, &b720, &b6F0, kx, kz, 0, 0x32, 0xE, 0xE);
                    }
                }
                GsPktClose_13f5b0(c);
            }
        }
    }
    if (Shown(m->f11C)) {
        s32 al;
        s32 md;

        s32 col530[4] __attribute__((aligned(16))) = {128, 128, 128, 0};
        { f32 q = m->f164; al = (s32)(128.0f * q); }
        if ((md = m->f11C) == 2 || md == 1) {
            al = (s32)al;
        } else {
            col530[0] = al;
            col530[1] = al;
            col530[2] = al;
        }
        a78C = 1.0f;
        ecnt = InvCollectPlacedCagesInCurLocation_3c4be0(GetGameData_1fede0()->f18, ents, 3);
        ne = ecnt;
        tex5 = m->fC4;
        if (tex5 != 0 && ne > 0) {
            k = 0;
            g280 = col530[2];
            b270 = col530[1];
            do {
                GsPktSetDefaultState_13fa80(c);
                GsPktSetAlphaBlend_13e500(c, 1);
                GsPktSetBlendMode_13e4f0(c, 1);
                GsPktEnableAlphaTest_13e4d0(c, 1);
                GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
                GsPktEnableZTest_13e460(c, 0);
                GsPktSetTextured_13e400(c, 1);
                GsPktSetOriginMode_13e2f0(c, 0);
                GsPktSetGouraud_13e3b0(c, 1);
                GsPktSetUseUV_13e3e0(c, 1);
                GsPktSetTexFilter_13e3d0(c, 0);
                GsPktSetAntialias_13e390(c, 0);
                GsPktSetZWriteMask_13e430(c, 1);
                GsPktSetAlphaBlend_13e500(c, 1);
                GsPktSetBlendMode_13e4f0(c, 1);
                if (k == 0) {
                    GsPktSetDestAlphaTest_13e4a0(c, 1);
                    GsPktSetDestAlphaMode_13e4b0(c, 1);
                    GsPktSetFrameMask_13e420(c, 2);
                } else {
                    GsPktSetDestAlphaTest_13e4a0(c, 0);
                    GsPktSetFrameMask_13e420(c, 1);
                }
                GsPktOpenPrim_13f730(c, 6);
                GsPktSetTexture_13ec00(c, tex5);
                for (i = 0; i < ecnt; i++) {
                    pent = &ents[i];
                    en = *pent;
                    if (en == 0) continue;
                    if (MinimapCheckBlockNameMaybe_325030(m, en->f18->f8, mode, &a78C) == 0) continue;
                    MinimapCalcQuadCornersMaybe_325150(m, &b720, &b6F0, 9, 9, 0.0f, 0.0f, (f32 *)0, 0, 0, 0);
                    Vec v520;
                    CageRecGetPos_3d0b40(*pent, &v520);
                    if (!(lo < v520.y) || !(v520.y <= hi)) continue;
                    f32 d510[4] __attribute__((aligned(16)));
                    ZERO16(d510);
                    d510[0] = v520.x - pos[0];
                    d510[1] = v520.y - pos[1];
                    d510[2] = v520.z - pos[2];
                    d510[0] = d510[0] / cell;
                    d510[2] = d510[2] / cell;
                    lx = (s32)(offx + (d510[0] + mw));
                    lz = (s32)(offz + (d510[2] + mh));
                    f32 w500[4] __attribute__((aligned(16)));
                    ZERO16(w500);
                    w500[0] = v520.x;
                    w500[1] = v520.y;
                    w500[2] = v520.z;
                    MinimapWorldToMapXZ_32c280((Vec *)w500, cell, orgx, orgz, unit);
                    if (MinimapIsCellExplored_325550(m, (Vec *)w500, who, AngleToQuadrant_323fd0(m)) != 0) {
                        GsPktSetRGBAQ_13ee40(c, col530[0], b270, g280, (s32)((f32)al * a78C));
                        MinimapEmitSprite_324d30(m, c, &b720, &b6F0, lx, lz, 0x20, 0x12, 0x12, 0x12);
                    }
                }
                GsPktClose_13f5b0(c);
                k++;
            } while (k < 2);
        }
    }
    a = Shown3(m->f11C);
    if (a != 0) {
        s32 md;

        pss = 1;
        s32 col4F0[4] __attribute__((aligned(16))) = {128, 128, 128, 128};
        if ((md = m->f11C) == 2 || md == 1) {
            pss = 2;
            col4F0[3] = (s32)(128.0f * m->f164);
        } else {
            f32 q = m->f164; s32 v_ = (s32)(128.0f * q);
            col4F0[0] = v_;
            col4F0[1] = v_;
        }
        a788 = 1.0f;
        Mark marks[4];
        mcnt = StateBlockCollectMapMarkers_3cc390(GetGameData_1fede0()->f10, marks, ids);
        nm = mcnt;
        tex4 = m->fC4;
        if (tex4 != 0 && mcnt > 0) {
            km = 0;
            hwM = 0.5f * bxw;
            a150 = col4F0[3];
            g2A0 = col4F0[2];
            b290 = col4F0[1];
            hhM = 0.5f * by;
            for (; km < pss; km++) {
                GsPktSetDefaultState_13fa80(c);
                GsPktEnableAlphaTest_13e4d0(c, 1);
                GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
                GsPktEnableZTest_13e460(c, 0);
                GsPktSetTextured_13e400(c, 1);
                GsPktSetOriginMode_13e2f0(c, 0);
                GsPktSetGouraud_13e3b0(c, 1);
                GsPktSetUseUV_13e3e0(c, 1);
                GsPktSetTexFilter_13e3d0(c, 0);
                GsPktSetAntialias_13e390(c, 0);
                GsPktSetZWriteMask_13e430(c, 1);
                if (pss == 2) {
                    GsPktSetAlphaBlend_13e500(c, 1);
                    GsPktSetBlendMode_13e4f0(c, 1);
                    if (km == 0) {
                        GsPktSetDestAlphaTest_13e4a0(c, 1);
                        GsPktSetDestAlphaMode_13e4b0(c, 1);
                        GsPktSetFrameMask_13e420(c, 2);
                    } else {
                        GsPktSetDestAlphaTest_13e4a0(c, 0);
                        GsPktSetFrameMask_13e420(c, 1);
                    }
                } else {
                    GsPktSetAlphaBlend_13e500(c, 0);
                    GsPktSetDestAlphaTest_13e4a0(c, 0);
                    GsPktSetFrameMask_13e420(c, 0);
                }
                GsPktOpenPrim_13f730(c, 6);
                GsPktSetTexture_13ec00(c, tex4);
                i = 0;
                if (mcnt > 0) {
                    for (; i < nm; i++) {
                        s32 vis;

                        pm = &marks[i];
                        pmz = &pm->z;
                        g = (pm->x - pos[0]) / cell;
                        fC = (pm->z - pos[2]) / cell;
                        vis = (s8)MinimapCheckBlockNameMaybe_325030(m, ids[i], mode, &a788);
                        if (vis != 0) {
                            if (lo < pm->y && pm->y <= hi) vis = 1;
                            else vis = 0;
                        }
                        if ((f32)FabsDouble_1283a0(g) < hwM && (f32)FabsDouble_1283a0(fC) < hhM) {
                            MinimapCalcQuadCornersMaybe_325150(m, &b720, &b6F0, 8, 8, 0.0f, 0.0f, (f32 *)0, 0, 0, 0);
                            f32 d4A0[4] __attribute__((aligned(16)));
                            ZERO16(d4A0);
                            { s32 i_ = i; Mark *q_ = &marks[i_];
                            d4A0[0] = q_->x - pos[0];
                            d4A0[1] = q_->y - pos[1];
                            d4A0[2] = *pmz - pos[2];
                            icon = 0x12;
                            d4A0[0] = d4A0[0] / cell;
                            d4A0[2] = d4A0[2] / cell;
                            mx = (s32)(offx + (d4A0[0] + mw));
                            mz = (s32)(offz + (d4A0[2] + mh));
                            }
                            if (vis == 0) icon += 0x10;
                            GsPktSetRGBAQ_13ee40(c, col4F0[0], b290, g2A0, (s32)((f32)a150 * a788));
                            MinimapEmitSprite_324d30(m, c, &b720, &b6F0, mx, mz, 0, icon, 0x10, 0x10);
                        }
                    }
                }
                GsPktClose_13f5b0(c);
            }
        }
    }
    DrawListEndPrim_141a20(gs);
    DrawEnvPop_144800(gs);
    DrawListAddEnv_1421d0(gs);
    c = DrawListBeginPrim_141b00(gs);
    switch (m->f11C) {
    case 2:
        a = 1;
        break;
    case 0:
    case 1:
        a = 0;
        break;
    }
    if (mode == 1) a = 0;
    if (a != 0) {
        u8 t;

        ZERON(bg, 4);
        bg[0] = m->f116;
        bg[1] = m->f117;
        bg[2] = m->f118;
        bg[3] = m->f119;
        switch (mode) {
        case 0:
            bg[3] = (u8)((f32)(u32)bg[3] * m->fDC);
            break;
        case 1:
            bg[3] = (u8)((f32)(u32)bg[3] * m->fE4);
            break;
        }
        GsPktSetDefaultState_13fa80(c);
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktEnableZTest_13e460(c, 0);
        GsPktSetTextured_13e400(c, 0);
        GsPktSetOriginMode_13e2f0(c, 0);
        GsPktSetGouraud_13e3b0(c, 1);
        GsPktSetTextured_13e400(c, 0);
        GsPktOpenPrim_13f730(c, 6);
        GsPktSetRGBAQ_13ee40(c, bg[0], bg[1], bg[2], bg[3]);
        GsPktSetXYZPixel_13f110(c, m->fFC, m->fFE, 0);
        GsPktSetXYZPixel_13f110(c, m->fFC + m->f100, m->fFE + m->f102, 0);
        GsPktClose_13f5b0(c);
    }
    if (tex != 0) {
        GsPktSetDefaultState_13fa80(c);
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktEnableZTest_13e460(c, 0);
        GsPktSetTextured_13e400(c, 1);
        GsPktSetOriginMode_13e2f0(c, 0);
        GsPktSetGouraud_13e3b0(c, 1);
        GsPktSetTextured_13e400(c, 1);
        GsPktSetUseUV_13e3e0(c, 1);
        GsPktSetTexFilter_13e3d0(c, 0);
        GsPktSetFrameMask_13e420(c, 1);
        GsPktSetZWriteMask_13e430(c, 1);
        u8 fg0[4] = {0x80, 0x80, 0x80, 0x40};
        u8 fg1[4] = {0x80, 0x80, 0x80, 0x00};

        if ((t8 = m->f11C) == 2 || t8 == 1) fg0[3] = 0x50;
        switch (mode) {
        case 0:
            f = m->fDC * scl;
            fg0[3] = ScaleA(fg0[3], f);
            fg1[3] = ScaleA(fg1[3], f);
            break;
        case 1:
            f = m->fE4 * scl;
            fg0[3] = ScaleA(fg0[3], f);
            fg1[3] = ScaleA(fg1[3], f);
            break;
        }
        GsPktOpenPrim_13f730(c, 4);
        GsPktSetTexture_13ec00(c, tex);
        GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
        {
            f32 xc;
            f32 xb;
            f32 y0;
            f32 yc;
            f32 xa;
            f32 zb;
            f32 za;
            y0 = sz + offz;
            xa = sx + offx;

            y200 = (s32)y0;
            x1B0 = (s32)xa;
            GsPktSetUV_13ed60(c, x1B0, y200);
            GsPktSetXYZf_13f060(c, bx, x0, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            xb = bxw + xa;
            x190 = (s32)xb;
            GsPktSetUV_13ed60(c, x190, y200);
            za = bx + bxw;
            GsPktSetXYZf_13f060(c, za, x0, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            x1E0 = (s32)(lim1 + xa);
            y1F0 = (s32)(lim0 + y0);
            GsPktSetUV_13ed60(c, x1E0, y1F0);
            zb = x0 + lim0;
            zc = bx + lim1;
            GsPktSetXYZf_13f060(c, zc, zb, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            x1C0 = (s32)(xb - lim1);
            GsPktSetUV_13ed60(c, x1C0, y1F0);
            xc = za - lim1;
            GsPktSetXYZf_13f060(c, xc, zb, 0.0f);
            GsPktClose_13f5b0(c);
            GsPktOpenPrim_13f730(c, 4);
            GsPktSetTexture_13ec00(c, tex);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            yc = by + y0;
            y1D0 = (s32)(yc - lim0);
            GsPktSetUV_13ed60(c, x1E0, y1D0);
            y0 = x0 + by;
            xa = y0 - lim0;
            GsPktSetXYZf_13f060(c, zc, xa, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1C0, y1D0);
            GsPktSetXYZf_13f060(c, xc, xa, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            y1A0 = (s32)yc;
            GsPktSetUV_13ed60(c, x1B0, y1A0);
            GsPktSetXYZf_13f060(c, bx, y0, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            GsPktSetUV_13ed60(c, x190, y1A0);
            GsPktSetXYZf_13f060(c, za, y0, 0.0f);
            GsPktClose_13f5b0(c);
            GsPktOpenPrim_13f730(c, 4);
            GsPktSetTexture_13ec00(c, tex);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            GsPktSetUV_13ed60(c, x1B0, y200);
            GsPktSetXYZf_13f060(c, bx, x0, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1E0, y1F0);
            GsPktSetXYZf_13f060(c, zc, zb, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            GsPktSetUV_13ed60(c, x1B0, y1A0);
            GsPktSetXYZf_13f060(c, bx, y0, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1E0, y1D0);
            GsPktSetXYZf_13f060(c, zc, xa, 0.0f);
            GsPktClose_13f5b0(c);
            GsPktOpenPrim_13f730(c, 4);
            GsPktSetTexture_13ec00(c, tex);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1C0, y1F0);
            GsPktSetXYZf_13f060(c, xc, zb, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            GsPktSetUV_13ed60(c, x190, y200);
            GsPktSetXYZf_13f060(c, za, x0, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1C0, y1D0);
            GsPktSetXYZf_13f060(c, xc, xa, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg1[3]);
            GsPktSetUV_13ed60(c, x190, y1A0);
            GsPktSetXYZf_13f060(c, za, y0, 0.0f);
            GsPktClose_13f5b0(c);
            GsPktOpenPrim_13f730(c, 4);
            GsPktSetTexture_13ec00(c, tex);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1E0, y1F0);
            GsPktSetXYZf_13f060(c, zc, zb, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1C0, y1F0);
            GsPktSetXYZf_13f060(c, xc, zb, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1E0, y1D0);
            GsPktSetXYZf_13f060(c, zc, xa, 0.0f);
            GsPktSetRGBAQ_13ee40(c, fg0[0], fg0[1], fg0[2], fg0[3]);
            GsPktSetUV_13ed60(c, x1C0, y1D0);
            GsPktSetXYZf_13f060(c, xc, xa, 0.0f);
            GsPktClose_13f5b0(c);
        }
    }
    a = Shown3(m->f11C);
    if (mode == 1) a = 0;
    if (a != 0) {
        s32 md;
        s32 al;

        s32 col490[4] __attribute__((aligned(16))) = {128, 128, 128, 0};
        if ((md = m->f11C) == 2 || md == 1) {
            al = (s32)(128.0f * scl * m->f164);
        } else {
            f32 q_ = m->f164;
            s32 v_ = (s32)(128.0f * q_);
            col490[0] = v_;
            col490[1] = v_;
            col490[2] = v_;
            al = (s32)(96.0f * scl);
        }
        Mark marks2[4];
        n = StateBlockCollectMapMarkers_3cc390(GetGameData_1fede0()->f10, marks2, ids2);
        tex2 = m->fC4;
        if (tex2 != 0 && n > 0) {
            GsPktSetDefaultState_13fa80(c);
            GsPktSetAlphaBlend_13e500(c, 1);
            GsPktSetBlendMode_13e4f0(c, 1);
            GsPktEnableAlphaTest_13e4d0(c, 1);
            GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
            GsPktEnableZTest_13e460(c, 0);
            GsPktSetTextured_13e400(c, 1);
            GsPktSetOriginMode_13e2f0(c, 0);
            GsPktSetGouraud_13e3b0(c, 1);
            GsPktSetUseUV_13e3e0(c, 1);
            GsPktSetAntialias_13e390(c, 0);
            GsPktSetZWriteMask_13e430(c, 1);
            GsPktOpenPrim_13f730(c, 3);
            GsPktSetTexture_13ec00(c, tex2);
            i = 0;
            if (n > 0) {
                hhE = 0.5f * by;
                g2C0 = col490[2];
                hw = 0.5f * bxw;
                b2B0 = col490[1];
                g = D_0047D7E0 * bxw;
                for (; i < n; i++) {
                    Mark *p2 = &marks2[i];
                    f32 px = (p2->x - pos[0]) / cell;
                    f32 pz = (p2->z - pos[2]) / cell;

                    if (!((f32)FabsDouble_1283a0(px) < hw) || !((f32)FabsDouble_1283a0(pz) < hhE)) {
                        f32 r = Atan2f_1291a8(px, pz);
                        f32 s = Sinf_128fd0(r);
                        f32 co = -Cosf_128d30(r);

                        MinimapBuildRectCornersMaybe_3252b0(m, &b720, &b710, &b700, &b6F0, 8, 8, s, co, (f32 *)0, 1, 0, 0);
                        f32 d440[4] __attribute__((aligned(16)));
                        ZERO16(d440);
                        d440[1] = g;
                        f32 ex = (dz + rx) - (d440[0] * co - d440[1] * s);
                        ex2 = (s32)ex;
                        ey2 = (s32)((ey + rz) - by / bxw * (d440[0] * s + d440[1] * co));
                        GsPktSetRGBAQ_13ee40(c, col490[0], b2B0, g2C0, al);
                        MinimapEmitQuadTris_324e20(m, c, &b720, &b710, &b700, &b6F0, ex2, ey2, 0x10, 0x12, 0x10, 0x10);
                    }
                }
            }
            GsPktClose_13f5b0(c);
        }
    }
    DrawListEndPrim_141a20(gs);
    switch (m->f11C) {
    case 0:
    case 2:
        a = 1;
        break;
    case 1:
        a = 0;
        break;
    }
    if (mode == 1) a = 0;
    if (a != 0) {
        s32 t;

        s32 col430[4] __attribute__((aligned(16))) = {128, 128, 128, 128};
        { s32 *p_ = &col430[3]; *p_ = (s32)((f32)*p_ * MinimapGetDrawAlpha_32a180(m)); }
        f = Sinf_128fd0(ang);
        MinimapBuildRectCornersMaybe_3252b0(m, &b720, &b710, &b700, &b6F0, 8, 8, f, -Cosf_128d30(ang), (f32 *)0, 1, 0, -4);
        DrawListAddTexLoad_1418c0(gs, 0x32B, 1.0f);
        t = m->f80;
        if (t != 0) {
            c = DrawListBeginPrim_141b00(gs);
            GsPktSetDefaultState_13fa80(c);
            GsPktSetAlphaBlend_13e500(c, 1);
            GsPktSetBlendMode_13e4f0(c, 1);
            GsPktEnableAlphaTest_13e4d0(c, 1);
            GsPktEnableZTest_13e460(c, 0);
            GsPktSetTextured_13e400(c, 1);
            GsPktSetOriginMode_13e2f0(c, 0);
            GsPktSetGouraud_13e3b0(c, 1);
            GsPktSetUseUV_13e3e0(c, 1);
            GsPktSetZWriteMask_13e430(c, 1);
            GsPktOpenPrim_13f730(c, 3);
            GsPktSetTexture_13ec00(c, t);
            GsPktSetRGBAQ_13ee40(c, col430[0], col430[1], col430[2], col430[3]);
            MinimapEmitQuadTris_324e20(m, c, &b720, &b710, &b700, &b6F0, (s32)dz, (s32)ey, 0x72, 0, 0xE, 0x10);
            GsPktClose_13f5b0(c);
            DrawListEndPrim_141a20(gs);
        }
    }
    return 1;
}

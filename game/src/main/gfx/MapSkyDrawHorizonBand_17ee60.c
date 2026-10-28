/* rgp:protos */
#define RGP_SELF_MapSkyDrawHorizonBand_17ee60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

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
extern f32 D_0047D53C;
extern f32 D_0047D870;
extern u8 D_0047E008;

void MapSkyDrawHorizonBand_17ee60(u8 *o, u8 *m, f32 *a2, f32 *a3) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 n1[4] __attribute__((aligned(16)));
    f32 s1b0[4] __attribute__((aligned(16)));
    f32 c1a0[4] __attribute__((aligned(16)));
    f32 p[4][4] __attribute__((aligned(16)));
    f32 quad[4][4] __attribute__((aligned(16)));
    f32 v110[4] __attribute__((aligned(16)));
    f32 v100[4] __attribute__((aligned(16)));
    f32 pos2[4] __attribute__((aligned(16)));
    f32 nE0[4] __attribute__((aligned(16)));
    f32 cD0[4] __attribute__((aligned(16)));
    f32 hC0[4] __attribute__((aligned(16)));
    f32 lB0[4] __attribute__((aligned(16)));
    s32 sA0[4] __attribute__((aligned(16)));
    s32 s90[4] __attribute__((aligned(16)));
    s32 s80[4] __attribute__((aligned(16)));
    f32 v70[4] __attribute__((aligned(16)));
    f32 v60[4] __attribute__((aligned(16)));
    f32 y;
    s32 mgr;
    s32 W;
    s32 H;
    s32 c;
    s32 lo;

    if (D_0047E008 != 0) {
        *(u128 *)pos = *(u128 *)(m + 0x30);
        VecScale_13be00(v100, a3, 128.0f);
        VecScale_13be00(v110, a2, 128.0f);
        v100[3] = 128.0f;
        v110[3] = 128.0f;
        VecSetLength_13e000(n1, (f32 *)(m + 0x20), -1.0f);
        if (!(n1[1] <= D_0047D870)) {
            return;
        }
        n1[1] = 0.0f;
        VecSetLength_13e000(n1, n1, (f32)0x3390);
        s1b0[1] = 0.0f;
        s1b0[3] = 0.0f;
        s1b0[0] = n1[2];
        s1b0[2] = -n1[0];
        VecSetLength_13e000(s1b0, s1b0, (f32)0x203A0);
        *(u128 *)quad[0] = *(u128 *)v110;
        *(u128 *)quad[1] = *(u128 *)v110;
        *(u128 *)quad[2] = *(u128 *)v100;
        *(u128 *)quad[3] = *(u128 *)v100;
        VecAdd_13be20(c1a0, pos, n1);
        c1a0[3] = 1.0f;
        VecSub_13be40(p[0], c1a0, s1b0);
        VecAdd_13be20(p[1], c1a0, s1b0);
        VecAdd_13be20(p[2], c1a0, s1b0);
        VecSub_13be40(p[3], c1a0, s1b0);
        y = *(f32 *)(o + 0x1724);
        p[0][1] = p[0][1] + y;
        p[1][1] = p[1][1] + y;
        DrawClippedGouraudQuad_17f3b0(p[0], quad[0]);
        *(u128 *)quad[0] = *(u128 *)v100;
        *(u128 *)quad[1] = *(u128 *)v100;
        *(u128 *)quad[2] = *(u128 *)v110;
        *(u128 *)quad[3] = *(u128 *)v110;
        VecAdd_13be20(c1a0, pos, n1);
        c1a0[3] = 1.0f;
        VecSub_13be40(p[0], c1a0, s1b0);
        VecAdd_13be20(p[1], c1a0, s1b0);
        VecAdd_13be20(p[2], c1a0, s1b0);
        VecSub_13be40(p[3], c1a0, s1b0);
        p[0][1] = p[0][1] + 10.0f;
        p[1][1] = p[1][1] + 10.0f;
        y = *(f32 *)(o + 0x1724);
        p[2][1] = p[2][1] - y;
        p[3][1] = p[3][1] - y;
        DrawClippedGouraudQuad_17f3b0(p[0], quad[0]);
        return;
    }
    *(u128 *)pos2 = *(u128 *)(m + 0x30);
    VecScale_13be00(v70, a3, 128.0f);
    VecScale_13be00(v60, a2, 128.0f);
    v60[3] = 128.0f;
    v70[3] = 128.0f;
    VecSetLength_13e000(nE0, (f32 *)(m + 0x20), -1.0f);
    if (!(nE0[1] <= D_0047D53C)) {
        return;
    }
    nE0[1] = 0.0f;
    VecSetLength_13e000(nE0, nE0, (f32)0x3390);
    VecAdd_13be20(cD0, pos2, nE0);
    cD0[3] = 1.0f;
    *(u128 *)hC0 = *(u128 *)cD0;
    *(u128 *)lB0 = *(u128 *)cD0;
    y = *(f32 *)(o + 0x1724);
    hC0[1] = hC0[1] + y;
    lB0[1] = lB0[1] - y;
    ProjectToScreenOffset_15d160(sA0, cD0);
    ProjectToScreenOffset_15d160(s90, hC0);
    ProjectToScreenOffset_15d160(s80, lB0);
    mgr = GetDrawCtx_15de80();
    W = DrawEnvGetWidth_1451e0(mgr) << 4;
    H = DrawEnvGetHeight_1451d0(mgr) << 4;
    c = ((s32)DrawListBeginPrim_141b00(mgr));
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetGouraud_13e3b0(c, 1);
    GsPktSetZTest_13e450(c, 0);
    GsPktSetTextured_13e400(c, 0);
    GsPktSetAlphaBlend_13e500(c, 0);
    GsPktEnableAlphaTest_13e4d0(c, 0);
    lo = -H / 2;
    if (sA0[1] >= lo && s90[0] <= H * 3 / 2) {
        GsPktOpenPrim_13f730(c, 4);
        GsPktSetRGBAQVec_13edd0(c, v60);
        GsPktSetXYZ_13ef10(c, 0, s90[1], 0);
        GsPktSetXYZ_13ef10(c, W, s90[1], 0);
        GsPktSetRGBAQVec_13edd0(c, v70);
        GsPktSetXYZ_13ef10(c, 0, sA0[1], 0);
        GsPktSetXYZ_13ef10(c, W, sA0[1], 0);
        GsPktClose_13f5b0(c);
    }
    if (sA0[1] <= H * 3 / 2 && s80[0] >= lo) {
        GsPktOpenPrim_13f730(c, 4);
        GsPktSetRGBAQVec_13edd0(c, v70);
        GsPktSetXYZ_13ef10(c, 0, sA0[1], 0);
        GsPktSetXYZ_13ef10(c, W, sA0[1], 0);
        GsPktSetRGBAQVec_13edd0(c, v60);
        GsPktSetXYZ_13ef10(c, 0, s80[1], 0);
        GsPktSetXYZ_13ef10(c, W, s80[1], 0);
        GsPktClose_13f5b0(c);
    }
    DrawListEndPrim_141a20(mgr);
}

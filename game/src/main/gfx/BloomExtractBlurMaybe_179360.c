/* rgp:protos */
#define RGP_SELF_BloomExtractBlurMaybe_179360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Alpha {
    u8 a : 2;
    u8 b : 2;
    u8 c : 2;
    u8 d : 2;
    u8 pad1[3];
    u8 fix;
} Alpha;

typedef struct Tex {
    u8 pad0[0x70];
} Tex;

typedef struct Rect {
    s32 a, b, c, d;
} Rect;

typedef struct Reg {
    __extension__ unsigned int lo : 32;
    unsigned int  : 0, hi : 32;
} __attribute__((aligned(8))) Reg;

typedef struct Frm {
    u8 pad0[0x80];
    Reg f80;
} Frm;

typedef struct Ctx {
    u8 pad0[0x270];
    Frm *f270;
} Ctx;

typedef struct Obj {
    s32 x0;
    s32 x4;
    u8 pad8[8];
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
} Obj;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

void BloomExtractBlurMaybe_179360(Obj *a) {
    s32 pair[2];
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Alpha)]; char m1[0x8]; })];
    Tex tex __attribute__((aligned(16)));
    Rect rc0 __attribute__((aligned(16)));
    Rect rc1 __attribute__((aligned(16)));
    Ctx *r;
    s32 d;
    s32 v;
    s32 j;
    s32 k;

    if (a->x0 == 0 || a->x4 == 0) {
        return;
    }
    ZERO(pair, 8);
    pair[0] = a->x0;
    pair[1] = a->x4;
    r = ((Ctx *)GetDrawCtx_15de80());
    r->f270->f80.hi = 0;
    NameTableNodeCtor_15ae50(&tex);
    DrawEnvGetFrameTexDesc_144cc0(r, &tex);
    DrawEnvGetFrameRect_145040(r, &rc0);
    DrawEnvPush_144830(r);
    DrawEnvSetFrameFromDesc_144fe0(r, pair[0], 0);
    DrawListAddEnv_1421d0(r);
    DrawEnvGetFrameRect_145040(r, &rc1);
    d = ((s32)DrawListBeginPrim_141b00(r));
    GsPktSetOriginMode_13e2f0(d, 0);
    GsPktEnableZTest_13e460(d, 0);
    GsPktSetZWriteMask_13e430(d, 1);
    GsPktSetZTest_13e450(d, 0);
    GsPktSetAlphaBlend_13e500(d, 0);
    GsPktEnableAlphaTest_13e4d0(d, 0);
    GsPktSetTextured_13e400(d, 0);
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetRGBAQ_13ee40(d, 0, 0, 0, 0);
    GsPktSetXYZPixel_13f110(d, rc1.b, rc1.a, 0);
    GsPktSetXYZPixel_13f110(d, rc1.d, rc1.c, 0);
    GsPktClose_13f5b0(d);
    GsPktSetTextured_13e400(d, 1);
    GsPktEnableAlphaTest_13e4d0(d, 1);
    GsPktSetAlphaTestFunc_13e4c0(d, 2, 0x80);
    GsPktSetTexFilter_13e3d0(d, 0);
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetRGBAQ_13ee40(d, 0, 0, 0, 0x80);
    GsPktSetTexture_13ec00(d, &tex);
    GsPktSetUV_13ed60(d, rc0.b, rc0.a);
    GsPktSetXYZ_13ef10(d, rc1.b * 16 - 8, rc1.a * 16 - 8, 0);
    GsPktSetUV_13ed60(d, rc0.d, rc0.c);
    GsPktSetXYZ_13ef10(d, rc1.d * 16 - 8, rc1.c * 16 - 8, 0);
    GsPktClose_13f5b0(d);
    GsPktSetTextured_13e400(d, 0);
    GsPktEnableAlphaTest_13e4d0(d, 0);
    GsPktSetAlphaBlend_13e500(d, 1);
    (*(Alpha *)(rgp_blk1 + 0x0)).a = 0;
    (*(Alpha *)(rgp_blk1 + 0x0)).fix = 0;
    (*(Alpha *)(rgp_blk1 + 0x0)).b = 2;
    (*(Alpha *)(rgp_blk1 + 0x0)).c = 1;
    (*(Alpha *)(rgp_blk1 + 0x0)).d = 2;
    GsPktSetAlphaReg_13e4e0(d, &(*(Alpha *)(rgp_blk1 + 0x0)));
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0x80);
    GsPktSetXYZPixel_13f110(d, rc1.b, rc1.a, 0);
    GsPktSetXYZPixel_13f110(d, rc1.d, rc1.c, 0);
    GsPktClose_13f5b0(d);
    DrawListEndPrim_141a20(r);
    v = 16.0f * a->x20;
    {
    s32 ox[4] __attribute__((aligned(16))) = {0};
    ox[0] = v;
    ox[1] = v;
    ox[2] = -v;
    ox[3] = -v;
    {
    s32 oy[4] __attribute__((aligned(16))) = {0};
    oy[0] = v;
    oy[2] = v;
    oy[1] = -v;
    oy[3] = -v;
    for (j = 0; j < 2; j++) {
        DrawEnvSetFrameFromDesc_144fe0(r, pair[1 - j], 0);
        DrawListAddEnv_1421d0(r);
        DrawEnvGetFrameRect_145040(r, &rc1);
        d = ((s32)DrawListBeginPrim_141b00(r));
        GsPktSetOriginMode_13e2f0(d, 0);
        GsPktEnableZTest_13e460(d, 0);
        GsPktSetZWriteMask_13e430(d, 1);
        GsPktSetZTest_13e450(d, 0);
        GsPktSetAlphaBlend_13e500(d, 0);
        GsPktEnableAlphaTest_13e4d0(d, 0);
        GsPktSetTextured_13e400(d, 0);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetRGBAQ_13ee40(d, 0, 0, 0, 0);
        GsPktSetXYZPixel_13f110(d, rc1.b, rc1.a, 0);
        GsPktSetXYZPixel_13f110(d, rc1.d, rc1.c, 0);
        GsPktClose_13f5b0(d);
        GsPktSetTextured_13e400(d, 1);
        GsPktSetAlphaBlend_13e500(d, 1);
        GsPktSetBlendMode_13e4f0(d, 9);
        for (k = 0; k < 4; k++) {
            GsPktOpenPrim_13f730(d, 6);
            GsPktSetRGBAQ_13ee40(d, 0x40, 0x40, 0x40, 0x80);
            GsPktSetTexture_13ec00(d, (void *)pair[j]);
            GsPktSetUV_13ed60(d, rc1.b, rc1.a);
            GsPktSetXYZ_13ef10(d, rc1.b * 16 - 12 + ox[k], rc1.a * 16 - 12 + oy[k], 0);
            GsPktSetUV_13ed60(d, rc1.d, rc1.c);
            GsPktSetXYZ_13ef10(d, rc1.d * 16 - 12 + ox[k], rc1.c * 16 - 12 + oy[k], 0);
            GsPktClose_13f5b0(d);
        }
        DrawListEndPrim_141a20(r);
    }
    DrawEnvPop_144800(r);
    DrawListAddEnv_1421d0(r);
    d = ((s32)DrawListBeginPrim_141b00(r));
    GsPktSetOriginMode_13e2f0(d, 0);
    GsPktEnableZTest_13e460(d, 0);
    GsPktSetZWriteMask_13e430(d, 1);
    GsPktSetZTest_13e450(d, 0);
    GsPktSetAlphaBlend_13e500(d, 0);
    GsPktEnableAlphaTest_13e4d0(d, 0);
    GsPktSetTextured_13e400(d, 0);
    GsPktSetTextured_13e400(d, 1);
    GsPktSetAlphaBlend_13e500(d, 1);
    GsPktSetBlendMode_13e4f0(d, 9);
    GsPktSetFrameMask_13e420(d, 1);
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetTexture_13ec00(d, (void *)pair[0]);
    GsPktSetRGBAQ_13ee40(d, (s32)(64.0f * a->x10), (s32)(64.0f * a->x14), (s32)(64.0f * a->x18), (s32)(128.0f * a->x1C));
    GsPktSetUV_13ed60(d, rc1.b, rc1.a);
    GsPktSetXYZPixel_13f110(d, rc0.b, rc0.a, 0);
    GsPktSetUV_13ed60(d, rc1.d, rc1.c);
    GsPktSetXYZPixel_13f110(d, rc0.d, rc0.c, 0);
    GsPktClose_13f5b0(d);
    DrawListEndPrim_141a20(r);
    }
    }
}

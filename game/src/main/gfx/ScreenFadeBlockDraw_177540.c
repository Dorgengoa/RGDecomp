/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockDraw_177540 1
#define RGP_SELF_lerp 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    s16 id;
    s16 w;
    s16 h;
    u8 pad[0x36];
    u8 lo : 2;
    u8 f : 1;
    u8 hi : 5;
    u8 pad2[0x33];
} Tex;

typedef struct {
    f32 r, g, b, a;
    s32 m10;
    s32 pad14[3];
    s32 m20;
    s32 m24;
    f32 m28;
    Tex *tex;
    s32 m30;
    s32 m34;
    s32 m38;
    f32 m3C;
    f32 m40;
    f32 m44;
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

static inline f32 lerp(f32 a, f32 b, f32 t)
{
    return a + t * (b - a);
}

void ScreenFadeBlockDraw_177540(Obj *arg0)
{
    Tex tex __attribute__((aligned(16)));
    s32 ctx;
    s32 pk;
    s32 n;
    f32 w;
    f32 h;
    f32 c;
    f32 t;
    f32 x1;
    f32 x2;
    f32 y1;
    f32 y2;
    f32 b;
    Tex *tp;

    ctx = GetDrawCtx_15de80();
    if (!(arg0->a <= 0.0f)) {
        pk = ((s32)DrawListBeginPrim_141b00(ctx));
        GsPktEnableZTest_13e460(pk, 0);
        GsPktEnableAlphaTest_13e4d0(pk, 0);
        GsPktSetAlphaBlend_13e500(pk, 1);
        GsPktSetBlendMode_13e4f0(pk, 1);
        GsPktSetZWriteMask_13e430(pk, 1);
        if (arg0->m24 != 0) {
            tp = arg0->tex;
            if (tp != 0) {
                tp->f = 0;
                GetDrawCtxNameTable_15de40();
                DrawListAddTexLoad_1418c0(ctx, arg0->tex->id, 1.0f);
                GsPktSetTextured_13e400(pk, 1);
                if (arg0->m20 == 1) {
                    GsPktOpen_13f4a0(pk);
                    GsPktSetPrimType_13f470(pk, 6);
                    GsPktSetTexture_13ec00(pk, arg0->tex);
                    GsPktWriteAD_13ec80(pk, 0x3B, 0x8080 | ((u64)0x80 << 32));
                    GsPktSetRGBAQ_13ee40(pk, 0x80, 0x80, 0x80, 0x80);
                    GsPktFinalizeTags_13f260(pk);
                    DrawEnvGetWidth_1451e0(ctx);
                    if (arg0->m10 > 0) {
                        ScreenFadeBlockDrawWipeStrips_177a70(pk, 0, (s32)((arg0->a / 128.0f) * (f32)DrawEnvGetWidth_1451e0(ctx)), 0);
                    } else {
                        n = (s32)((arg0->a / 128.0f) * (f32)DrawEnvGetWidth_1451e0(ctx));
                        ScreenFadeBlockDrawWipeStrips_177a70(pk, n, DrawEnvGetWidth_1451e0(ctx), 1);
                    }
                    GsPktCommit_13f190(pk);
                } else {
                    GsPktOpen_13f4a0(pk);
                    GsPktSetPrimType_13f470(pk, 6);
                    GsPktSetTexture_13ec00(pk, arg0->tex);
                    GsPktWriteAD_13ec80(pk, 0x3B, 0x8080 | ((u64)0x80 << 32));
                    GsPktSetRGBAQ_13ee40(pk, (s32)arg0->r, (s32)arg0->g, (s32)arg0->b, (s32)(arg0->a * arg0->m28));
                    GsPktFinalizeTags_13f260(pk);
                    GsPktTileScreenSprites_177cf0(pk);
                    GsPktCommit_13f190(pk);
                }
            }
        } else {
            GsPktSetTextured_13e400(pk, 0);
            GsPktOpen_13f4a0(pk);
            GsPktSetPrimType_13f470(pk, 6);
            GsPktSetRGBAQ_13ee40(pk, (s32)arg0->r, (s32)arg0->g, (s32)arg0->b, (s32)arg0->a);
            GsPktFinalizeTags_13f260(pk);
            GsPktTileScreenSprites_177cf0(pk);
            GsPktCommit_13f190(pk);
            if (!(arg0->a < 128.0f)) {
                DrawEnvSetClearColorRgba_15ca10(arg0->r, arg0->g, arg0->b, 128.0f);
            }
        }
        DrawListEndPrim_141a20(ctx);
    }
    if (arg0->m30 != 0) {
        pk = ((s32)DrawListBeginPrim_141b00(ctx));
        NameTableNodeCtor_15ae50(&tex);
        DrawEnvGetDispFbTexDesc_144a00(ctx, &tex);
        tex.f = 0;
        GsPktSetTextured_13e400(pk, 1);
        GsPktSetAlphaBlend_13e500(pk, 1);
        GsPktSetBlendMode_13e4f0(pk, 1);
        GsPktEnableZTest_13e460(pk, 0);
        GsPktSetZWriteMask_13e430(pk, 1);
        GsPktOpenPrim_13f730(pk, 6);
        GsPktWriteAD_13ec80(pk, 0x3B, 0x80 | ((u64)0x80 << 32));
        GsPktSetTexture_13ec00(pk, &tex);
        GsPktSetRGBAQ_13ee40(pk, 0x80, 0x80, 0x80, arg0->m30);
        w = (f32)DrawEnvGetWidth_1451e0(ctx);
        h = (f32)DrawEnvGetHeight_1451d0(ctx);
        t = arg0->m3C;
        c = arg0->m40;
        x1 = (f32)arg0->m34 + lerp(c, 0.0f, t);
        x2 = (f32)arg0->m34 + lerp(c, w, t);
        c = arg0->m44;
        y1 = (f32)arg0->m38 + lerp(c, 0.0f, t);
        y2 = (f32)arg0->m38 + lerp(c, h, t);
        GsPktSetUV_13ed60(pk, 0, 0);
        GsPktSetXYZf_13f060(pk, x1, y1, 0.0f);
        GsPktSetUV_13ed60(pk, tex.w, tex.h);
        GsPktSetXYZf_13f060(pk, x2, y2, 0.0f);
        GsPktClose_13f5b0(pk);
        DrawListEndPrim_141a20(ctx);
    }
}

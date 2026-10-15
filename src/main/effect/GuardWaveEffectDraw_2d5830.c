#include "types.h"

extern f32 D_0047D354;

extern void *GetDrawCtx_15de80(void);
extern void *DrawListBeginPrim_141b00(void *ctx);
extern void DrawListAddTexLoad_1418c0(void *ctx, s32 id, f32 t);
extern void GsPktSetOriginMode_13e2f0(void *dl, s32 v);
extern void GsPktSetTextured_13e400(void *dl, s32 v);
extern void GsPktSetAlphaBlend_13e500(void *dl, s32 v);
extern void GsPktSetBlendMode_13e4f0(void *dl, s32 v);
extern void GsPktEnableAlphaTest_13e4d0(void *dl, s32 v);
extern void GsPktSetGouraud_13e3b0(void *dl, s32 v);
extern void GsPktSetTexFilter_13e3d0(void *dl, s32 v);
extern void GsPktSetZWriteMask_13e430(void *dl, s32 v);
extern void GsPktEnableZTest_13e460(void *dl, s32 v);
extern void GsPktSetUseUV_13e3e0(void *dl, s32 v);
extern s32 CameraProjectBillboardRect_15cde0(s32 *a, s32 *b, void *c, s32 d, f32 e, f32 f);
extern void GsPktOpenPrim_13f730(void *dl, s32 v);
extern void GsPktSetTexture_13ec00(void *dl, void *h);
extern void GsPktSetUV_13ed60(void *dl, s32 u, s32 v);
extern void GsPktSetRGBAQ_13ee40(void *dl, s32 r, s32 g, s32 b, s32 a);
extern void GsPktSetXYZ_13ef10(void *dl, s32 x, s32 y, s32 z);
extern void GsPktClose_13f5b0(void *dl);
extern void DrawListEndPrim_141a20(void *ctx);

void GuardWaveEffectDraw_2d5830(void *p)
{
    s32 a[4];
    s32 b[4];
    u8 *q;
    void *ctx;
    void *dl;
    s32 i;
    u8 *r;
    u8 *s;
    f32 t;
    f32 u;
    s32 c;

    q = (u8 *)p;
    if (*(s32 *)q == 0) {
        return;
    }
    ctx = GetDrawCtx_15de80();
    dl = DrawListBeginPrim_141b00(ctx);
    DrawListAddTexLoad_1418c0(ctx, *(s32 *)(q + 0x3C), 1.0f);
    GsPktSetOriginMode_13e2f0(dl, 1);
    GsPktSetTextured_13e400(dl, 1);
    GsPktSetAlphaBlend_13e500(dl, 1);
    GsPktSetBlendMode_13e4f0(dl, 2);
    GsPktEnableAlphaTest_13e4d0(dl, 1);
    GsPktSetGouraud_13e3b0(dl, 0);
    GsPktSetTexFilter_13e3d0(dl, 1);
    GsPktSetZWriteMask_13e430(dl, 1);
    GsPktEnableZTest_13e460(dl, 1);
    GsPktSetUseUV_13e3e0(dl, 1);
    for (i = 0; i < 2; i++) {
        r = q + i * 2;
        if (*(s16 *)(r + 0x34) == 0) {
            continue;
        }
        if (*(s16 *)(r + 0x30) > 0) {
            continue;
        }
        s = q + i * 4;
        t = D_0047D354 * (128.0f * *(f32 *)(s + 0x28));
        u = *(f32 *)(q + 0x38) * *(f32 *)(s + 0x20);
        if (CameraProjectBillboardRect_15cde0(a, b, q + 0x10, 0, u, u) == 0) {
            continue;
        }
        GsPktOpenPrim_13f730(dl, 4);
        GsPktSetTexture_13ec00(dl, *(void **)(q + 0x44));
        GsPktSetUV_13ed60(dl, 0, 0);
        c = (s32)t;
        GsPktSetRGBAQ_13ee40(dl, 0x48, 0x48, 0xA0, c);
        GsPktSetXYZ_13ef10(dl, a[0], a[1], a[2]);
        GsPktSetUV_13ed60(dl, 0x7F, 0);
        GsPktSetRGBAQ_13ee40(dl, 0x48, 0x48, 0xA0, c);
        GsPktSetXYZ_13ef10(dl, b[0], a[1], a[2]);
        GsPktSetUV_13ed60(dl, 0, 0x7F);
        GsPktSetRGBAQ_13ee40(dl, 0x48, 0x48, 0xA0, c);
        GsPktSetXYZ_13ef10(dl, a[0], b[1], a[2]);
        GsPktSetUV_13ed60(dl, 0x7F, 0x7F);
        GsPktSetRGBAQ_13ee40(dl, 0x48, 0x48, 0xA0, c);
        GsPktSetXYZ_13ef10(dl, b[0], b[1], a[2]);
        GsPktClose_13f5b0(dl);
    }
    DrawListEndPrim_141a20(ctx);
}

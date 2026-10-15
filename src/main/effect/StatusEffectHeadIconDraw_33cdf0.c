#include "types.h"

typedef unsigned __int128 u128;

typedef struct V33cdf0 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V33cdf0;

extern f64 D_0047D190;
extern u8 D_00462628[];

extern void *GetStaticScene_1c6c70(void *p);
extern void *ObjRecGetLiveObject_1c4a90(void *t, s32 id);
extern f64 dpmul(f64 a, f64 b);
extern void *GetDrawCtx_15de80(void);
extern void *DrawListBeginPrim_141b00(void *ctx);
extern void GsPktSetOriginMode_13e2f0(void *dl, s32 v);
extern void GsPktSetTextured_13e400(void *dl, s32 v);
extern void GsPktSetAlphaBlend_13e500(void *dl, s32 v);
extern void GsPktSetBlendMode_13e4f0(void *dl, s32 v);
extern void GsPktEnableAlphaTest_13e4d0(void *dl, s32 v);
extern void GsPktSetGouraud_13e3b0(void *dl, s32 v);
extern void GsPktSetTexFilter_13e3d0(void *dl, s32 v);
extern void GsPktSetZWriteMask_13e430(void *dl, s32 v);
extern void GsPktEnableZTest_13e460(void *dl, s32 v);
extern s32 CameraProjectBillboardRect_15cde0(V33cdf0 *a, V33cdf0 *b, V33cdf0 *c, s32 d, f32 e, f32 f);
extern void *GetDrawCtxNameTable_15de40(void);
extern void *NameTableFindByName_159fb0(void *s, void *name, s32 id);
extern void GsPktOpenPrim_13f730(void *dl, s32 v);
extern void GsPktSetTexture_13ec00(void *dl, void *h);
extern void GsPktSetUV_13ed60(void *dl, s32 u, s32 v);
extern void GsPktSetRGBAQ_13ee40(void *dl, s32 r, s32 g, s32 b, s32 a);
extern void GsPktSetXYZVecI_13eeb0(void *dl, V33cdf0 *v);
extern void GsPktClose_13f5b0(void *dl);
extern void DrawListEndPrim_141a20(void *ctx);

void StatusEffectHeadIconDraw_33cdf0(void *p)
{
    V33cdf0 c;
    V33cdf0 b;
    V33cdf0 a;
    u8 *q;
    u8 *r;
    void *ctx;
    void *dl;
    void *h;

    q = (u8 *)p;
    r = (u8 *)ObjRecGetLiveObject_1c4a90(GetStaticScene_1c6c70(q), *(s16 *)(q + 0x14));
    if (r == 0) {
        return;
    }
    *(u128 *)&c = *(u128 *)(r + 0x180);
    c.y += (f32)(5.0 + dpmul(D_0047D190, *(f32 *)(r + 0x4CC)));
    ctx = GetDrawCtx_15de80();
    dl = DrawListBeginPrim_141b00(ctx);
    GsPktSetOriginMode_13e2f0(dl, 1);
    GsPktSetTextured_13e400(dl, 1);
    GsPktSetAlphaBlend_13e500(dl, 1);
    GsPktSetBlendMode_13e4f0(dl, 1);
    GsPktEnableAlphaTest_13e4d0(dl, 1);
    GsPktSetGouraud_13e3b0(dl, 0);
    GsPktSetTexFilter_13e3d0(dl, 1);
    GsPktSetZWriteMask_13e430(dl, 1);
    GsPktEnableZTest_13e460(dl, 1);
    if (CameraProjectBillboardRect_15cde0(&b, &a, &c, 0, 6.0f, 6.0f) != 0) {
        h = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00462628, 0x2A6);
        GsPktOpenPrim_13f730(dl, 6);
        GsPktSetTexture_13ec00(dl, h);
        GsPktSetUV_13ed60(dl, 0x20, 0x40);
        GsPktSetRGBAQ_13ee40(dl, 0x80, 0x80, 0x80, 0x80);
        GsPktSetXYZVecI_13eeb0(dl, &b);
        GsPktSetUV_13ed60(dl, 0x3F, 0x5F);
        GsPktSetRGBAQ_13ee40(dl, 0x80, 0x80, 0x80, 0x80);
        GsPktSetXYZVecI_13eeb0(dl, &a);
        GsPktClose_13f5b0(dl);
    }
    DrawListEndPrim_141a20(ctx);
}

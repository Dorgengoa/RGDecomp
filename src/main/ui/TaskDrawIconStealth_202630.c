#include "types.h"

typedef union Rect { struct { s32 x, y, w, h; }; f32 f[4]; } Rect;
typedef struct Sub { u8 pad0[0x250]; f32 m250; } Sub;
typedef struct Own { u8 pad0[0x20]; Sub *m20; } Own;

extern f32 Cosf_128d30(f32);
extern void GsPktSetOriginMode_13e2f0(void *, s32);
extern void GsPktSetTexFilter_13e3d0(void *, s32);
extern void GsPktSetUseUV_13e3e0(void *, s32);
extern void GsPktSetTextured_13e400(void *, s32);
extern void GsPktSetFrameMask_13e420(void *, s32);
extern void GsPktSetZWriteMask_13e430(void *, s32);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktEnableAlphaTest_13e4d0(void *, s32);
extern void GsPktSetBlendMode_13e4f0(void *, s32);
extern void GsPktSetAlphaBlend_13e500(void *, s32);
extern void GsPktSetTexture_13ec00(void *, s32);
extern void GsPktSetUVFixed_13ed90(void *, s32, s32);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void GsPktSetXYZ_13ef10(void *, s32, s32, s32);
extern void GsPktClose_13f5b0(void *);
extern void GsPktOpenPrim_13f730(void *, s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern void *DrawListBeginPrim_141b00(s32);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern f32 AngleWrap_1cbf30(f32);
extern Own *GetGameData_1fede0(void);
extern s32 TexelToUVFixed_205e20(s32);
extern s32 PartyHasStealthMember_3a1d70(Sub *);
extern s32 CharaSysStealthActive_3a1d90(Sub *);
extern u8 D_0045C340[0x400];
extern f32 D_0047D804;
extern f32 D_0047D83C;
typedef struct Quad { f32 a, b, c, d; } Quad;
extern Quad D_0047E5D0 __attribute__((section(".sdata")));
extern f32 D_0047E5D4;
extern f32 D_0047E5D8;
extern f32 D_0047E5DC;
extern f32 D_00481B94;

static inline f32 fab(f32 x) { return x < 0.0f ? -x : x; }

void TaskDrawIconStealth_202630(void)
{
    Rect r;
    Own *own;
    f32 t;
    f32 v;
    f32 k;
    s32 h;
    void *dp;
    s32 tex;
    s32 y;
    s32 w;
    s32 hh;

    if (D_00481B94 <= 0.0f) return;
    own = GetGameData_1fede0();
    if (CharaSysStealthActive_3a1d90(own->m20) == 0) return;
    k = D_00481B94;
    if (!(own->m20->m250 <= 0.0f) && PartyHasStealthMember_3a1d70(own->m20) == 0) {
        t = own->m20->m250;
        t = t / 30.0f;
        if (t < 3.0f) {
            v = fab(Cosf_128d30(AngleWrap_1cbf30(D_0047D83C * t)));
            k = D_00481B94 * v;
        } else if (t < 10.0f) {
            v = fab(Cosf_128d30(AngleWrap_1cbf30(D_0047D804 * (t - 3.0f))));
            k = D_00481B94 * v;
        }
    }
    if (k <= 0.0f) return;
    h = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(h, 0x32B, 1.0f);
    dp = DrawListBeginPrim_141b00(h);
    tex = GetDrawCtxNameTable_15de40();
    GsPktSetOriginMode_13e2f0(dp, 0);
    GsPktSetAlphaBlend_13e500(dp, 1);
    GsPktSetBlendMode_13e4f0(dp, 1);
    GsPktEnableAlphaTest_13e4d0(dp, 1);
    GsPktSetZWriteMask_13e430(dp, 1);
    GsPktSetFrameMask_13e420(dp, 1);
    GsPktEnableZTest_13e460(dp, 0);
    GsPktSetTexFilter_13e3d0(dp, 1);
    GsPktSetTextured_13e400(dp, 1);
    GsPktSetUseUV_13e3e0(dp, 1);
    GsPktOpenPrim_13f730(dp, 6);
    GsPktSetTexture_13ec00(dp, NameTableFindByName_159fb0(tex, D_0045C340, 0x32B));
    *(Quad *)&r = D_0047E5D0;
    GsPktSetRGBAQ_13ee40(dp, 0x80, 0x80, 0x80, (s32)(128.0f * k));
    y = r.y;
    GsPktSetUVFixed_13ed90(dp, TexelToUVFixed_205e20(r.x), TexelToUVFixed_205e20(y));
    GsPktSetXYZ_13ef10(dp, 0x1B00, 0x180, 0);
    hh = r.h;
    w = r.w;
    GsPktSetUVFixed_13ed90(dp, TexelToUVFixed_205e20(r.x + w), TexelToUVFixed_205e20(y + hh));
    GsPktSetXYZ_13ef10(dp, (w + 0x1B0) * 16, (hh + 0x18) * 16, 0);
    GsPktClose_13f5b0(dp);
    DrawListEndPrim_141a20(h);
}

#include "types.h"

/* 0x16D0 frame: items[51][96] @0x80 and vv[51][4] @0x13A0 -- the stride
   and the two base offsets pin the counts.  Last-declared local gets the
   lowest address, so vv is declared first. */

extern void *GetDrawCtx_15de80(void);
extern void *DrawListBeginPrim_141b00(void *);
extern void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern void DrawListEndPrim_141a20(void *);
extern void GsPktSetOriginMode_13e2f0(void *, s32);
extern void GsPktSetTextured_13e400(void *, s32);
extern void GsPktSetAlphaBlend_13e500(void *, s32);
extern void GsPktSetBlendMode_13e4f0(void *, s32);
extern void GsPktEnableAlphaTest_13e4d0(void *, s32);
extern void GsPktSetGouraud_13e3b0(void *, s32);
extern void GsPktSetTexFilter_13e3d0(void *, s32);
extern void GsPktSetZWriteMask_13e430(void *, s32);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktSetUseUV_13e3e0(void *, s32);
extern s32 SplineSampleCatmullRom_2d77c0(f32 *, void *, s32, s32, s32, s32);
extern void sceVu0CopyVector(void *, void *);
extern void TrailRibbonSetNodes_32c750(void *, void *, s32);
extern void TrailRibbonSetColor_32c730(void *, f32, f32, f32, f32);
extern void TrailRibbonDraw_32c370(void *, void *, s32, f32);

void MovingLineDraw_2d5ff0(void *p)
{
    f32 vv[51][4];
    u8 items[51][96];
    u8 *q;
    void *ctx;
    void *dl;
    s32 cnt;
    s32 i;
    u8 *it;
    f32 step;
    f32 y;

    q = (u8 *)p;
    if (*(s16 *)(q + 0x120) != 0) {
        if (*(s32 *)(q + 0x12C) >= 2) {
            ctx = GetDrawCtx_15de80();
            dl = DrawListBeginPrim_141b00(ctx);
            DrawListAddTexLoad_1418c0(ctx, *(s16 *)(q + 0x144), 1.0f);
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
            cnt = SplineSampleCatmullRom_2d77c0(vv[0], q, *(s32 *)(q + 0x12C), 3, 0,
                               *(s32 *)(q + 0x12C));
            step = *(f32 *)(q + 0x13C) / (f32)cnt;
            y = (*(f32 *)(q + 0x134) + *(f32 *)(q + 0x13C)) - 1.0f;
            for (i = 0; i < cnt; i++) {
                it = items[i];
                sceVu0CopyVector(it, vv[i]);
                *(f32 *)(it + 0x50) = *(f32 *)(q + 0x124);
                *(f32 *)(it + 0x30) = *(f32 *)(q + 0x130);
                *(f32 *)(it + 0x34) = y;
                *(f32 *)(it + 0x38) = 1.0f;
                *(f32 *)(it + 0x40) =
                    (*(f32 *)(q + 0x130) + *(f32 *)(q + 0x138)) - 1.0f;
                *(f32 *)(it + 0x44) = y;
                y -= step;
                *(f32 *)(it + 0x48) = 1.0f;
            }
            TrailRibbonSetNodes_32c750(q + 0x100, items, cnt);
            TrailRibbonSetColor_32c730(q + 0x100, 128.0f, 128.0f, 128.0f, 96.0f);
            TrailRibbonDraw_32c370(q + 0x100, dl, *(s32 *)(q + 0x140), 0.0f);
            DrawListEndPrim_141a20(ctx);
        }
    }
}

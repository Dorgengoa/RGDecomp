#include "types.h"

extern void *GetDrawCtx_15de80(void);
extern void *DrawListBeginPrim_141b00(void *);
extern void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern void DrawListEndPrim_141a20(void *);
extern void GsPktSetAlphaBlend_13e500(void *, s32);
extern void GsPktSetBlendMode_13e4f0(void *, s32);
extern void GsPktEnableAlphaTest_13e4d0(void *, s32);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktSetZWriteMask_13e430(void *, s32);
extern void GsPktSetTextured_13e400(void *, s32);
extern void GsPktSetUseUV_13e3e0(void *, s32);
extern void GsPktSetOriginMode_13e2f0(void *, s32);
extern void GsPktSetTexFilter_13e3d0(void *, s32);
extern void LightningBoltDraw_2d67a0(void *, void *, s32);

void LightningMgrDraw_2d6530(void *p)
{
    u8 *q;
    void *ctx;
    void *dl;
    u8 *it;
    s32 i;

    q = (u8 *)p;
    if (*(s32 *)q != 0) {
        ctx = GetDrawCtx_15de80();
        dl = DrawListBeginPrim_141b00(ctx);
        DrawListAddTexLoad_1418c0(ctx, *(s16 *)(q + 8), 1.0f);
        GsPktSetAlphaBlend_13e500(dl, 1);
        GsPktSetBlendMode_13e4f0(dl, 2);
        GsPktEnableAlphaTest_13e4d0(dl, 1);
        GsPktEnableZTest_13e460(dl, 1);
        GsPktSetZWriteMask_13e430(dl, 1);
        GsPktSetTextured_13e400(dl, 1);
        GsPktSetUseUV_13e3e0(dl, 1);
        GsPktSetOriginMode_13e2f0(dl, 1);
        GsPktSetTexFilter_13e3d0(dl, 1);
        it = *(u8 **)q;
        for (i = 0; i < 0x40; i++) {
            LightningBoltDraw_2d67a0(it, dl, *(s32 *)(q + 4));
            it += 0xD0;
        }
        DrawListEndPrim_141a20(ctx);
    }
}

/* rgp:protos */
#define RGP_SELF_BladeLineDraw_2d5c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* stack locals are allocated in REVERSE declaration order (last declared
   gets the lowest address): vv @0x130, tmp @0x120, items @0x60. */

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

void BladeLineDraw_2d5c40(void *p)
{
    f32 vv[2][4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    u8 items[2][96] __attribute__((aligned(16)));
    u8 *q;
    void *ctx;
    void *dl;
    s32 i;
    u8 *it;

    q = (u8 *)p;
    if (*(s32 *)q != 0) {
        ctx = GetDrawCtx_15de80();
        dl = DrawListBeginPrim_141b00(ctx);
        DrawListAddTexLoad_1418c0(ctx, *(s16 *)(q + 0x44), 1.0f);
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
        sceVu0ScaleVector(tmp, (f32 *)(q + 0x20),
                          (*(f32 *)(q + 0x30) / 2.0f) * *(f32 *)(q + 0x34));
        sceVu0AddVector(vv[0], (f32 *)(q + 0x10), tmp);
        sceVu0SubVector(vv[1], (f32 *)(q + 0x10), tmp);
        vv[1][3] = 1.0f;
        vv[0][3] = 1.0f;
        for (i = 0; i < 2; i++) {
            it = items[i];
            sceVu0CopyVector(it, vv[i]);
            *(f32 *)(it + 0x50) = 2.5f;
            *(f32 *)(it + 0x30) = 63.0f * (f32)i;
            *(s32 *)(it + 0x34) = 0;
            *(f32 *)(it + 0x38) = 1.0f;
            *(f32 *)(it + 0x40) = 63.0f * (f32)i;
            *(f32 *)(it + 0x44) = 63.0f;
            *(f32 *)(it + 0x48) = 1.0f;
        }
        TrailRibbonSetNodes_32c750(q + 0x50, items, 2);
        TrailRibbonSetColor_32c730(q + 0x50, 128.0f, 128.0f, 128.0f,
                     128.0f * *(f32 *)(q + 0x38));
        TrailRibbonDraw_32c370(q + 0x50, dl, *(s32 *)(q + 0x40), 2.0f);
        DrawListEndPrim_141a20(ctx);
    }
}

/* rgp:protos */
#define RGP_SELF_GuardEffectDraw_2d50b0 1
#include "port/game_protos.h"
#line 1
/* PARK 1/3: RIGHT LENGTH (107w), 26 bad. */
#include "types.h"

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

void GuardEffectDraw_2d50b0(u8 *arg0) {
    f32 sp80[4] __attribute__((aligned(16)));
    f32 sp70[4] __attribute__((aligned(16)));
    f32 sp60[4] __attribute__((aligned(16)));
    f32 sp50[4] __attribute__((aligned(16)));
    s32 temp_2;
    f32 temp_f12;
    s32 temp_2_2;
    u8 *var_17;
    s32 var_16;

    if (*(s32 *)(arg0 + 0x334) != 0) {
        temp_2 = GetDrawCtx_15de80();
        temp_2_2 = ((s32)DrawListBeginPrim_141b00(temp_2));
        GsPktSetOriginMode_13e2f0(temp_2_2, 1);
        GsPktSetTextured_13e400(temp_2_2, 0);
        GsPktSetAlphaBlend_13e500(temp_2_2, 1);
        GsPktSetBlendMode_13e4f0(temp_2_2, 2);
        GsPktEnableAlphaTest_13e4d0(temp_2_2, 1);
        GsPktSetGouraud_13e3b0(temp_2_2, 1);
        GsPktSetTexFilter_13e3d0(temp_2_2, 1);
        GsPktSetZWriteMask_13e430(temp_2_2, 1);
        GsPktEnableZTest_13e460(temp_2_2, 1);
        var_17 = arg0 + 0x20;
        var_16 = 0;
        do {
            if (!(*(f32 *)(var_17 + 0x20) <= 0.0f)) {
                temp_f12 = *(f32 *)(var_17 + 0x24);
                if (!(temp_f12 <= 0.0f)) {
                    sceVu0ScaleVector(sp50, var_17 + 0x10, temp_f12);
                    sceVu0AddVector(sp60, var_17, sp50);
                    if ((ProjectToScreen_15d340(sp80, var_17) != 0) && (ProjectToScreen_15d340(sp70, sp60) != 0)) {
                        GsPktOpenPrim_13f730(temp_2_2, 1);
                        GsPktSetRGBAQ_13ee40(temp_2_2, 0x80, 0x80, 0x80, 0x60);
                        GsPktSetXYZVecI_13eeb0(temp_2_2, sp80);
                        GsPktSetRGBAQ_13ee40(temp_2_2, 0xFA, 0xE6, 0, 0xB4);
                        GsPktSetXYZVecI_13eeb0(temp_2_2, sp70);
                        GsPktClose_13f5b0(temp_2_2);
                    }
                }
            }
            var_16 += 1;
            var_17 += 0x30;
        } while (var_16 < 0x10);
        DrawListEndPrim_141a20(temp_2);
    }
}

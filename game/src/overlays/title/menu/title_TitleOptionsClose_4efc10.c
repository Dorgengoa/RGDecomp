/* rgp:protos */
#define RGP_SELF_title_TitleOptionsClose_4efc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EFC10 -- lay out the options page: twelve calls that
 * alternate colour (func_290690, three floats) and placement (func_290F50, an
 * integer pair plus a scale), all against the same gp-relative handle.
 *
 * The tail guard is a `bc1fl` whose delay slot carries `ld $31`, the shared
 * epilogue, so the body is the positively guarded arm -- and `c.le.s` with the
 * branch taken on FALSE means the body runs when the value is <= 0.
 */

extern void *D_00484250;
extern void *D_00484254;
extern f32 D_0047D518;
extern f32 D_0047D51C;
extern f32 D_0047D520;
extern f32 D_0047D52C;
extern f32 D_0047D548;
extern f32 D_0047D54C;
extern f32 D_0047D550;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleOptionsClose_4efc10(s32 a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00484254, 0x8, 0.0f, D_0047D51C, -1.0f);
        UiMoveWidgetUniform_290f50(D_00484254, 0x8, 0xC8, 0, D_0047D520, 0);
        UiFadeWidgetAlpha_290690(D_00484254, 0xA, 0.0f, D_0047D548, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484254, 0x7, 0.0f, D_0047D54C, -1.0f);
        UiMoveWidgetUniform_290f50(D_00484254, 0x12, -0x12, 0xC, D_0047D518, 0);
        UiMoveWidgetUniform_290f50(D_00484254, 0x11, -0xF, 0xF, D_0047D518, 0);
        UiFadeWidgetAlpha_290690(D_00484254, 0x12, 0.0f, D_0047D52C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484254, 0x11, 0.0f, D_0047D52C, -1.0f);
        UiMoveWidgetUniform_290f50(D_00484254, 0x48, 0x200, 0x3C, D_0047D550, 0);
        UiFadeWidgetAlpha_290690(D_00484254, 0x48, 0.0f, D_0047D54C, -1.0f);
        UiMoveWidgetUniform_290f50(D_00484254, 0x47, 0x206, 0x41, D_0047D550, 0);
        UiFadeWidgetAlpha_290690(D_00484254, 0x47, 0.0f, D_0047D54C, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00484254, 7) <= 0.0f) {
        title_TitleSceneOverlayModeOff_4eaa00();
        title_TitleSetCardPollEnabled_4ed350(0);
        McEndSession_372d60();
        StateMachineSetState_28ede0(D_00484250, 4, 0);
    }
    return 1;
}

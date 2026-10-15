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

extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);
extern f32 func_290770(void *a, s32 b);
extern void title_TitleSceneOverlayModeOff_4eaa00(void);
extern void title_TitleSetCardPollEnabled_4ed350(s32 a);
extern void func_372D60(void);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 title_TitleOptionsClose_4efc10(s32 a, s32 b)
{
    if (b != 0) {
        func_290690(D_00484254, 0x8, 0.0f, D_0047D51C, -1.0f);
        func_290F50(D_00484254, 0x8, 0xC8, 0, 0, D_0047D520);
        func_290690(D_00484254, 0xA, 0.0f, D_0047D548, -1.0f);
        func_290690(D_00484254, 0x7, 0.0f, D_0047D54C, -1.0f);
        func_290F50(D_00484254, 0x12, -0x12, 0xC, 0, D_0047D518);
        func_290F50(D_00484254, 0x11, -0xF, 0xF, 0, D_0047D518);
        func_290690(D_00484254, 0x12, 0.0f, D_0047D52C, -1.0f);
        func_290690(D_00484254, 0x11, 0.0f, D_0047D52C, -1.0f);
        func_290F50(D_00484254, 0x48, 0x200, 0x3C, 0, D_0047D550);
        func_290690(D_00484254, 0x48, 0.0f, D_0047D54C, -1.0f);
        func_290F50(D_00484254, 0x47, 0x206, 0x41, 0, D_0047D550);
        func_290690(D_00484254, 0x47, 0.0f, D_0047D54C, -1.0f);
    }
    if (func_290770(D_00484254, 7) <= 0.0f) {
        title_TitleSceneOverlayModeOff_4eaa00();
        title_TitleSetCardPollEnabled_4ed350(0);
        func_372D60();
        func_28EDE0(D_00484250, 4, 0);
    }
    return 1;
}

#include "types.h"

extern f32 Sinf_128fd0(f32);
extern f32 PhaseAdvanceWrapPi_28b630(void *, f32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);

extern f32 D_0047D35C;
extern f32 D_0047D444;
extern const volatile f32 D_0047D484 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_004824D4;

void MenuWidgetPulseColor_2b3200(void)
{
    f32 f;
    PhaseAdvanceWrapPi_28b630(&D_004824D4, D_0047D484);
    f = D_0047D444 * Sinf_128fd0(D_004824D4);
    UiSetWidgetColor_2905b0(D_00482360, 0x76, D_0047D35C + f, 1.0f, 1.0f, 1.0f);
}

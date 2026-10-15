/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- `const` +
   __attribute__((section(".sdata"))) on the gp float extern(s) this unit
   READS.  The barrier it removes is the surrounding stores, not a write to
   the symbol; const-ing only the floats is right, const-ing every extern
   goes length-wrong. */
#include "types.h"

extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern s32 StateMachineSetState_28ede0(s32, s32, s32);

extern const f32 D_0047D5F4 __attribute__((section(".sdata")));
extern const f32 D_0047D5FC __attribute__((section(".sdata")));
extern s32 D_00482360;
extern s32 D_0048235C;

s32 MenuTacticsCmdCloseState_354680(void)
{
    f32 t0;
    s32 o0;

    t0 = D_0047D5F4;
    o0 = D_00482360;
    UiFadeWidgetAlpha_290690(o0, 0xC6, 0.0f, t0, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 0.0f, D_0047D5FC, -1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x96, 0);
    return 1;
}

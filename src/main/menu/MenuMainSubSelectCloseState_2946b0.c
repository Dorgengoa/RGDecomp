/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- `const` +
   __attribute__((section(".sdata"))) on the gp float extern(s) this unit
   READS.  The barrier it removes is the surrounding stores, not a write to
   the symbol; const-ing only the floats is right, const-ing every extern
   goes length-wrong. */
#include "types.h"

extern void UiFadeWidgetAlpha_290690(void *arg0, s32 arg1, f32 fa, f32 fb, f32 fc);
extern s32 StateMachineSetState_28ede0(void *arg0, s32 arg1, s32 arg2);
extern const f32 D_0047D794 __attribute__((section(".sdata")));
extern u8 D_004DB1B0[];
extern s32 D_00482350;

s32 MenuMainSubSelectCloseState_2946b0(void)
{
    UiFadeWidgetAlpha_290690(D_004DB1B0, 0x1AD, 0.0f, D_0047D794, -1.0f);
    StateMachineSetState_28ede0(&D_00482350, 2, 0);
    return 1;
}

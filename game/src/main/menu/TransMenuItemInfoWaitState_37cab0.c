/* rgp:protos */
#define RGP_SELF_TransMenuItemInfoWaitState_37cab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048470C;
extern s32 D_00484720;
extern u8 D_004B2570[];
extern u8 D_004E9230[];

s32 TransMenuItemInfoWaitState_37cab0(void)
{
    s32 t0;
    s32 r0;
    s32 t1;

    t0 = D_00484720;
    r0 = MenuGridCursorInput_28e170(t0, D_004B2570, 0, 0);
    if ((u32)(r0 + -1) < 2) {
        t1 = D_0048470C;
        StateMachineSetState_28ede0(t1, 0x3C, 0);
    }
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}

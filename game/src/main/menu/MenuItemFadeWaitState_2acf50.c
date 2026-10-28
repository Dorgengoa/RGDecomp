/* rgp:protos */
#define RGP_SELF_MenuItemFadeWaitState_2acf50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;

s32 MenuItemFadeWaitState_2acf50(void)
{
    s32 r0;
    s32 t0;
    s32 r1;

    r0 = MenuItemCmdFadeSequenceStep_2adce0(0x88);
    if (r0 != 0) {
        t0 = D_0048235C;
        r1 = StateMachineSetState_28ede0(t0, 0x39, 0);
    }
    return 1;
}

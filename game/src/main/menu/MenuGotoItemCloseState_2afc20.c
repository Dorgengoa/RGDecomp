/* rgp:protos */
#define RGP_SELF_MenuGotoItemCloseState_2afc20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;

s32 MenuGotoItemCloseState_2afc20(void)
{
    s32 r;

    r = StateMachineSetState_28ede0(D_0048235C, 0xA, 0);
    return 1;
}

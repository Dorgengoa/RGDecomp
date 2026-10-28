/* rgp:protos */
#define RGP_SELF_MenuItemGridExitState_2af650 1
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
extern s32 D_00482360;

s32 MenuItemGridExitState_2af650(void)
{
    s32 t0;
    s32 t1;

    t0 = D_00482360;
    UiSetWidgetsVisibleById_291110(t0, 0x70, 0, 1);
    t1 = D_0048235C;
    StateMachineSetState_28ede0(t1, 0xA, 0);
    return 1;
}

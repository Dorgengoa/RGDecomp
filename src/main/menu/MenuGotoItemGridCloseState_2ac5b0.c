#include "types.h"

extern s32 StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;

s32 MenuGotoItemGridCloseState_2ac5b0(void)
{
    s32 r;

    r = StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    return 1;
}

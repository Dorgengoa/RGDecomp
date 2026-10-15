#include "types.h"

extern void StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;

void MainMenuSetState_390d60(s32 p0)
{
    s32 t0;

    t0 = D_0048235C;
    StateMachineSetState_28ede0(t0, p0, 0);
}

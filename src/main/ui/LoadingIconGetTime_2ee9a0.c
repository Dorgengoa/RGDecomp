#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_00482790;

f32 LoadingIconGetTime_2ee9a0(void)
{
    f32 t0;

    t0 = D_00482790;
    return ((t0 / 30.0f) - 3.0f);
}

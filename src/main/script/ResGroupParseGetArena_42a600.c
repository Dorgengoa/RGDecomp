#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FE0;

s32 ResGroupParseGetArena_42a600(void)
{
    s32 t0;

    t0 = D_00483FE0;
    if (t0 != 0) {
        return (t0 + 0x168);
    }
    return 0;
}

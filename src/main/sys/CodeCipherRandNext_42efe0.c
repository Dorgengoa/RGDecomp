#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048031C;

s32 CodeCipherRandNext_42efe0(void)
{
    s32 t0;

    t0 = D_0048031C;
    D_0048031C = ((t0 * 0x21FC436) + 1);
    return ((t0 * 0x21FC436) + 1);
}

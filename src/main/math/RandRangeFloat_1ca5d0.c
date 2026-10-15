#include "types.h"

extern s32 Rand_133710(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 RandRangeFloat_1ca5d0(f32 fa0)
{
    s32 r0;

    r0 = Rand_133710();
    return ((fa0 * ((f32)r0)) / 2147483648.0f);
}

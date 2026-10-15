#include "types.h"

extern void Nop_1ed090(void);
extern void AreaBoxReset_1e98c0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void AreaBoxInit_1e01f0(s32 p0)
{
    Nop_1ed090();
    AreaBoxReset_1e98c0(p0);
}

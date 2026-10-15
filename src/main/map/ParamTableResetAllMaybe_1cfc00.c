#include "types.h"

extern void ParamRecReset_1cfdb0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ParamTableResetAllMaybe_1cfc00(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        ParamRecReset_1cfdb0((p0 + 0x58A0));
        l0 = ((l1 + 1) < 0xE0);
        l1 = (l1 + 1);
    } while (l0 != 0);
}

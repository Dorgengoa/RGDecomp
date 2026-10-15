#include "types.h"

extern void EventStateResetMaybe_26b780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004BD980[];
extern const s32 D_004BDA1C;

void EventStateInitMaybe_26b740(void)
{
    s32 l0;

    l0 = 0;
    do {
        *(s32 *)((u8 *)D_004BD980 + (l0 << 2) + 0x68) = 0;
        l0 = (l0 + 1);
    } while (l0 < 0xD);
    *(s32 *)&D_004BDA1C = 0;
    EventStateResetMaybe_26b780(l0);
}

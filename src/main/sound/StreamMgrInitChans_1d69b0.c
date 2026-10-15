#include "types.h"

extern void StreamChanInit_1d7610(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void StreamMgrInitChans_1d69b0(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        StreamChanInit_1d7610((p0 + (((l1 << 3) - l1) << 5)));
        l0 = ((l1 + 1) < 4);
        l1 = (l1 + 1);
    } while (l0 != 0);
}

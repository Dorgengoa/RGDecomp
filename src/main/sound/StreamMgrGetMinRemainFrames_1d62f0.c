#include "types.h"

extern s32 StreamChanGetRemainFrames_1d6a10(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 StreamMgrGetMinRemainFrames_1d62f0(s32 p0)
{
    s32 l0;
    s32 l1;
    s32 l2;
    s32 r3;
    s32 rv4;

    l1 = 0x708;
    l2 = 0;
    do {
        r3 = StreamChanGetRemainFrames_1d6a10((p0 + (((l2 << 3) - l2) << 5)));
        rv4 = l1;
        if (r3 < l1) {
            rv4 = r3;
        }
        l0 = ((l2 + 1) < 4);
        l1 = rv4;
        l2 = (l2 + 1);
    } while (l0 != 0);
    return l1;
}

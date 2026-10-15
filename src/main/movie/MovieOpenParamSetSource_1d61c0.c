#include "types.h"

extern void MovieOpenParamInit_1d6230(s32);
extern void PathLocalize_1c28c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MovieOpenParamSetSource_1d61c0(s32 p0, s32 p1, s32 p2)
{
    s32 l1;
    s32 l2;

    MovieOpenParamInit_1d6230(p0);
    l2 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xC0) = p2;
        l1 = ((l2 + 1) < 6);
        l2 = (l2 + 1);
    } while (l1 != 0);
    PathLocalize_1c28c0((p0 + 0x80), p1);
}

#include "types.h"

extern s32 BitArraySetReturnOld_384360(s32, s32, s32);
extern s32 MenuObjSlotIsActive_3849d0(s32);
extern void MotionListResetAll_171e00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MenuObjSetStopMotion_384a80(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 r3;

    r0 = BitArraySetReturnOld_384360((p0 + 0x4155), 1, 1);
    r1 = BitArraySetReturnOld_384360((p0 + 0x4155), 2, 1);
    l2 = 0;
    do {
        r3 = MenuObjSlotIsActive_3849d0(((p0 + (((l2 * 0x3C) + l2) << 5)) + 0x13B0));
        if (r3 != 0) {
            MotionListResetAll_171e00(((p0 + (((l2 * 0x3C) + l2) << 5)) + 0x15B0));
        }
        l2 = (l2 + 1);
    } while (l2 < 2);
}

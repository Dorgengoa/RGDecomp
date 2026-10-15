#include "types.h"

extern void HpGaugeSetBarWidth_31e300(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void HpGaugeClearSlots_31e9c0(s32 p0)
{
    s32 l1;
    s32 l2;

    HpGaugeSetBarWidth_31e300(p0, 0x28);
    l2 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l2 << 1)) = -1;
        *(s64 *)((u8 *)p0 + (l2 << 3) + 0x20) = -1;
        *(s16 *)((u8 *)p0 + (l2 << 1) + 0xA0) = -1;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xC0) = 0x3F800000;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x140) = 0x3F800000;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x100) = 0x3F800000;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x180) = 0x3F800000;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x1D0) = 0x3F800000;
        *(u8 *)((u8 *)p0 + l2 + 0x1C0) = 0;
        *(u8 *)((u8 *)p0 + l2 + 0x210) = 0;
        l1 = ((l2 + 1) < 0x10);
        l2 = (l2 + 1);
    } while (l1 != 0);
}

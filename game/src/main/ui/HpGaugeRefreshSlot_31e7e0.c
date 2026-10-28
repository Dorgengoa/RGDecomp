/* rgp:protos */
#define RGP_SELF_HpGaugeRefreshSlot_31e7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 HpGaugeRefreshSlot_31e7e0(s32 p0, s32 p1, s32 p2)
{
    s32 rv1;
    s32 r0;

    if (p2 != -1) {
        *(s64 *)((u8 *)(p2 << 3) + p0 + 0x20) = 0x4E;
        *(s16 *)((u8 *)(p2 << 1) + p0 + 0xA0) = -1;
        *(u8 *)((u8 *)p2 + p0 + 0x1C0) = 1;
        rv1 = (p2 + p0);
    } else {
        r0 = FindS16Index16_31e870(p0, p1);
        *(s64 *)((u8 *)(r0 << 3) + p0 + 0x20) = 0x4E;
        *(s16 *)((u8 *)(r0 << 1) + p0 + 0xA0) = -1;
        *(u8 *)((u8 *)r0 + p0 + 0x1C0) = 1;
        rv1 = (r0 + p0);
    }
    return 1;
}

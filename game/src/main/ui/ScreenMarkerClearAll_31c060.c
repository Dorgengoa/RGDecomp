/* rgp:protos */
#define RGP_SELF_ScreenMarkerClearAll_31c060 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ScreenMarkerClearAll_31c060(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 << 1)) = -1;
        *(s16 *)((u8 *)p0 + (l1 << 1) + 0x40) = -1;
        *(s16 *)((u8 *)p0 + (l1 << 1) + 0xA0) = -1;
        *(u8 *)((u8 *)p0 + l1 + 0x80) = 0;
        *(u8 *)((u8 *)p0 + l1 + 0x120) = 0;
        l0 = ((l1 + 1) < 0x20);
        l1 = (l1 + 1);
    } while (l0 != 0);
}

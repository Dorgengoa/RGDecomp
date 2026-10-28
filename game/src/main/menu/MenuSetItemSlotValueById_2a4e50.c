/* rgp:protos */
#define RGP_SELF_MenuSetItemSlotValueById_2a4e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MenuSetItemSlotValueById_2a4e50(s32 p0, s32 p1, s32 p2)
{
    s32 l0;
    s32 l1;
    s32 t0;

    l1 = 0;
    do {
        t0 = *(s32 *)((u8 *)p0 + (l1 << 3) + 0x54);
        if (t0 == p1) {
            *(s32 *)((u8 *)p0 + (l1 << 3) + 0x58) = p2;
        }
        l0 = ((l1 + 1) < 3);
        l1 = (l1 + 1);
    } while (l0 != 0);
}

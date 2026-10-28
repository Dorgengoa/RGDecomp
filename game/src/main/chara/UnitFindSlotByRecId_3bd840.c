/* rgp:protos */
#define RGP_SELF_UnitFindSlotByRecId_3bd840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UnitFindSlotByRecId_3bd840(s32 p0, s32 p1)
{
    s32 l0;
    s32 r1;

    l0 = 0;
    while (l0 < 0xA) {
        r1 = EquipSlotGetRecId_3a0760(((p0 + (l0 * 0x24)) + 0x278));
        if (p1 == r1) {
            return ((p0 + (l0 * 0x24)) + 0x278);
        }
        l0 = (l0 + 1);
    }
    return 0;
}

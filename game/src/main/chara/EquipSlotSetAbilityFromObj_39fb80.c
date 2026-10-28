/* rgp:protos */
#define RGP_SELF_EquipSlotSetAbilityFromObj_39fb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 EquipSlotSetAbilityFromObj_39fb80(s32 p0, struct Obj0 *p1, s32 p2)
{
    s32 rv1;
    s32 t0;
    s32 r0;

    rv1 = (r0 & 0xFF);
    if (p1 == 0) {
        rv1 = 0;
    } else {
        t0 = p1->m0C;
        r0 = EquipSlotSetAbility_3a07b0(p0, t0, (long long)(p2));
        rv1 = (r0 & 0xFF);
    }
    return rv1;
}

/* rgp:protos */
#define RGP_SELF_EquipSlotFindNthLinkedMember_39f790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483748;

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 EquipSlotFindNthLinkedMember_39f790(s32 p0, s32 p1)
{
    struct Obj0 * t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    struct Obj0 * t1;
    s32 t2;
    s32 r1;

    t0 = D_00483748;
    rv3 = rv2;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        r0 = ((short)EquipSlotGetNthLinkedId_3a04e0(p0, p1));
        rv2 = r1;
        if (r0 < 0) {
            rv2 = 0;
        } else {
            t1 = D_00483748;
            t2 = D_00483748->m18;
            r1 = ((s32)PartyFindMember_3c2130(t2, r0, 1, 0, -1, 0, 0));
            rv2 = r1;
        }
        rv3 = rv2;
    }
    return rv3;
}

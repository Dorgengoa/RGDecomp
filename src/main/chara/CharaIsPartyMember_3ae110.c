#include "types.h"

extern s32 PartyHasMember_3c1e70(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483820;

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 CharaIsPartyMember_3ae110(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 r0;

    t0 = D_00483820;
    if (t0 != 0) {
        t1 = p0->m0C;
        r0 = PartyHasMember_3c1e70(t0, t1);
        return r0;
    }
    return 0;
}

/* rgp:protos */
#define RGP_SELF_CharaIsInReserve_3ae0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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

s32 CharaIsInReserve_3ae0e0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 r0;

    t0 = D_00483820;
    if (t0 != 0) {
        t1 = p0->m0C;
        r0 = PartyIsInReserve_3c1bd0(t0, t1);
        return r0;
    }
    return 0;
}

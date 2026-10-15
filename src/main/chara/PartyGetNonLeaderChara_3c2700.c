#include "types.h"

extern s32 PartyGetNonLeaderId_3c2750(s32, s32);
extern s32 CharaMgrPoolFindById_3a8c60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483890;

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
};

s32 PartyGetNonLeaderChara_3c2700(s32 p0, s32 p1)
{
    struct Obj0 * t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    struct Obj0 * t1;
    s32 t2;
    s32 r1;

    t0 = D_00483890;
    rv3 = rv2;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        r0 = PartyGetNonLeaderId_3c2750(p0, p1);
        rv2 = r1;
        if (r0 < 0) {
            rv2 = 0;
        } else {
            t1 = D_00483890;
            t2 = D_00483890->m14;
            r1 = CharaMgrPoolFindById_3a8c60(t2, r0);
            rv2 = r1;
        }
        rv3 = rv2;
    }
    return rv3;
}

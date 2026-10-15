#include "types.h"

extern s32 CharaMgrPoolFindById_3a8c60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj1 * D_00483890;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18E];
    s16 m18E;
};

struct Obj1 {
    u8 pad000[0x14];
    s32 m14;
};

s32 PartyGetLeaderChara_3c2820(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s32 t2;
    s32 r0;

    t0 = D_00483890;
    if (t0 != 0) {
        t1 = p0->m18E;
        t2 = D_00483890->m14;
        r0 = CharaMgrPoolFindById_3a8c60(t2, t1);
        return r0;
    }
    return 0;
}

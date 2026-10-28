/* rgp:protos */
#define RGP_SELF_CharaSysGetBattleResultMemberMaybe_3a2040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj2 * D_004837C0;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x238];
    struct Obj1 *m238;
};

struct Obj1 {
    u8 pad000[0x1C8];
    s32 m1C8;
};

struct Obj2 {
    u8 pad000[0x18];
    s32 m18;
};

s32 CharaSysGetBattleResultMemberMaybe_3a2040(struct Obj0 *p0, s32 p1)
{
    struct Obj2 *t0;
    struct Obj1 *t1;
    s32 s;
    s32 t3;
    s32 r1;
    s32 r2;

    if (p1 < 0) {
        return 0;
    }
    t0 = D_004837C0;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m238;
    if (t1 != 0) {
        s = t1->m1C8;
    } else {
        s = 0;
    }
    if (s == 0) {
        return 0;
    }
    t3 = t0->m18;
    r1 = PartyCountMembers_3c2010(t3, 1, 1);
    r2 = PartyCountReserve_3c1c20(t3, 1, 1);
    if (p1 >= (r1 + r2)) {
        return 0;
    }
    return (s + ((p1 * 3) << 3)) + 4;
}

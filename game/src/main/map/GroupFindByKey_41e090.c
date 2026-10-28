/* rgp:protos */
#define RGP_SELF_GroupFindByKey_41e090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004644A8;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
};

struct Obj1 {
    u8 pad000[0x94];
    s32 m94;
};

s32 GroupFindByKey_41e090(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t2;
    struct Obj1 *l1;
    s32 l0;
    s32 t3;
    s32 r4;

    t0 = p0->m08;
    if (t0 == 0) {
        return 0;
    }
    t2 = D_004644A8;
    l1 = (struct Obj1 *)p0->m0C;
    l0 = 0;
    while (l0 < t2) {
        t3 = l1->m94;
        if (t3 == 0) {
            goto Lc3;
        }
        r4 = GroupEntryMatchesKey_3f40e0(t3, p1);
        if (r4 != 0) {
            return (s32)l1;
        }
    Lc3:;
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)((u8 *)l1 + 0x98);
    }
    return 0;
}

/* rgp:protos */
#define RGP_SELF_BestiaryCountFindMaybe_3c3440 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00465B70;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x17C];
    s32 m17C;
};

struct Obj1 {
    s16 m00;
};

s32 BestiaryCountFindMaybe_3c3440(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    struct Obj1 *l0;
    s32 l1;
    s16 t2;

    t0 = p0->m17C;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_00465B70;
    l0 = (struct Obj1 *)t0;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m00;
        if (t2 == p1) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 4);
    }
    return 0;
}

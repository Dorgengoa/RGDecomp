/* rgp:protos */
#define RGP_SELF_MapIdListFind_1e5a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xA0];
    s32 mA0;
};

struct Obj1 {
    s16 m00;
};

s32 MapIdListFind_1e5a80(struct Obj0 *p0, s32 p1)
{
    struct Obj1 *l0;
    s32 t0;
    s32 l1;
    s16 t1;

    l0 = (struct Obj1 *)p0;
    t0 = p0->mA0;
    l1 = 0;
    while (l1 < t0) {
        t1 = l0->m00;
        if (t1 == p1) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 8);
    }
    return 0;
}

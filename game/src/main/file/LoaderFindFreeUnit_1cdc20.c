/* rgp:protos */
#define RGP_SELF_LoaderFindFreeUnit_1cdc20 1
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
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
};

struct Obj1 {
    u8 pad000[0x80];
    s16 m80;
};

s32 LoaderFindFreeUnit_1cdc20(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 l0;
    struct Obj1 *l1;
    s16 t2;

    t0 = p0->m10;
    if (t0 == 0) {
        return -1;
    }
    t1 = p0->m14;
    l0 = 0;
    l1 = (struct Obj1 *)t0;
    while (l0 < t1) {
        t2 = l1->m80;
        if (t2 < 0) {
            return l0;
        }
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)((u8 *)l1 + 0x98);
    }
    return -1;
}

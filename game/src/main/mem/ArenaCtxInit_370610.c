/* rgp:protos */
#define RGP_SELF_ArenaCtxInit_370610 1
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
    struct Obj1 *m00;
    s32 m04;
    s32 m08;
};

struct Obj1 {
    u8 pad000[0x28];
    s32 m28;
    s32 m2C;
};

s32 ArenaCtxInit_370610(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 rv0;
    s32 t0;
    s32 t1;

    rv0 = 1;
    if (p1 == 0) {
        rv0 = 0;
    } else {
        p0->m00 = p1;
        t0 = p1->m2C;
        t1 = p1->m28;
        p0->m04 = (t1 + (t0 << 4));
        p0->m08 = 0;
        rv0 = 1;
    }
    return rv0;
}

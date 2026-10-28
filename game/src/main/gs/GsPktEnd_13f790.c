/* rgp:protos */
#define RGP_SELF_GsPktEnd_13f790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0xE8];
    s32 mF0;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

s32 GsPktEnd_13f790(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *r0;
    s32 t1;

    p0->m04 = 0;
    t0 = p0->m00;
    r0 = MemStackAllocQw_14d950(t0, 1);
    r0->m00 = 0x60000000;
    r0->m04 = 0;
    r0->m08 = 0;
    r0->m0C = 0;
    t1 = p0->mF0;
    return t1;
}

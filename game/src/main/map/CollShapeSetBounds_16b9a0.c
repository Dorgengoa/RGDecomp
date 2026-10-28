/* rgp:protos */
#define RGP_SELF_CollShapeSetBounds_16b9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u128 m00;
    u128 m10;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x8];
    u128 m10;
    u128 m20;
};

void CollShapeSetBounds_16b9a0(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m10 = p1->m00;
    p0->m20 = p1->m10;
    p0->m04 = 1;
}

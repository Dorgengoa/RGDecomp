/* rgp:protos */
#define RGP_SELF_StrMapCtor_1a2940 1
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
    s32 m00;
    s32 m04;
    u8 m08;
    u8 pad009[0x3];
    struct Obj0 *m0C;
};

struct Obj1 {
    u8 m00;
};

struct Obj0 *StrMapCtor_1a2940(struct Obj0 *p0, struct Obj1 *p1)
{
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = p1->m00;
    p0->m0C = (struct Obj0 *)((u8 *)p0 + 4);
    return p0;
}

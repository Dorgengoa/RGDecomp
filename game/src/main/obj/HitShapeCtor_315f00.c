/* rgp:protos */
#define RGP_SELF_HitShapeCtor_315f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 m00;
    u8 pad001[0x3];
    s32 m04;
    s32 m08;
    u8 m0C;
};

struct Obj0 *HitShapeCtor_315f00(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = -1;
    p0->m08 = -1;
    p0->m0C = 0;
    return p0;
}

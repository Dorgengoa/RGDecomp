/* rgp:protos */
#define RGP_SELF_EffParamApplyAlpha_1a85d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    f32 m00;
};

struct Obj1 {
    u8 pad000[0x4C];
    f32 m4C;
};

struct Obj2 {
    f32 m00;
};

void EffParamApplyAlpha_1a85d0(struct Obj1 *p0, struct Obj2 *p1, struct Obj0 *p2)
{
    p1->m00 = (p2->m00 * p0->m4C);
}

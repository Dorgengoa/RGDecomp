/* rgp:protos */
#define RGP_SELF_CharaSetReqMove_238710 1
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
    f32 m00;
    f32 m04;
    f32 m08;
};

struct Obj1 {
    u8 pad000[0xD0];
    f32 mD0;
    f32 mD4;
    f32 mD8;
    s32 mDC;
};

void CharaSetReqMove_238710(struct Obj1 *p0, struct Obj0 *p1)
{
    f32 t0;
    f32 t1;
    f32 t2;

    t0 = p1->m08;
    t1 = p1->m04;
    t2 = p1->m00;
    p0->mD0 = t2;
    p0->mD4 = t1;
    p0->mD8 = t0;
    p0->mDC = 0;
}

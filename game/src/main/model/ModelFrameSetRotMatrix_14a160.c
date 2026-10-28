/* rgp:protos */
#define RGP_SELF_ModelFrameSetRotMatrix_14a160 1
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
    u128 m20;
};

struct Obj1 {
    u8 pad000[0x29];
    u8 m29;
    u8 pad02A[0x36];
    u128 m60;
    u128 m70;
    u128 m80;
};

void ModelFrameSetRotMatrix_14a160(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m60 = p1->m00;
    p0->m70 = p1->m10;
    p0->m80 = p1->m20;
    p0->m29 = 1;
}

/* rgp:protos */
#define RGP_SELF_CameraGetEyeGoal_1603b0 1
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
    u8 pad000[0xF0];
    u128 mF0;
};

struct Obj1 {
    u128 m00;
};

void CameraGetEyeGoal_1603b0(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m00 = p0->mF0;
}

/* rgp:protos */
#define RGP_SELF_AttackObjBaseSetRadius_228e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x190];
    f32 m190;
};

void AttackObjBaseSetRadius_228e90(struct Obj0 *p0, f32 fa0)
{
    p0->m190 = fa0;
}

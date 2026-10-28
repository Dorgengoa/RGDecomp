/* rgp:protos */
#define RGP_SELF_EffectInstanceSetScale_2dd550 1
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
};

struct Obj1 {
    u8 pad000[0x60];
    u128 m60;
};

void EffectInstanceSetScale_2dd550(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m60 = p1->m00;
}

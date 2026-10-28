/* rgp:protos */
#define RGP_SELF_CharaAbilityViewCtor_3a8180 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472210[];
extern u8 D_00472230[];
extern u8 D_00472250[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

struct Obj0 *CharaAbilityViewCtor_3a8180(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    p0->m00 = D_00472250;
    p0->m00 = D_00472230;
    p0->m00 = D_00472210;
    p0->m04 = p1;
    p0->m08 = p2;
    p0->m0C = p3;
    return p0;
}

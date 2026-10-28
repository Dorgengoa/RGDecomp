/* rgp:protos */
#define RGP_SELF_EffModelResCtor_1a8380 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004709C8[];
extern u8 D_00470E80[];
extern u8 D_00470EA0[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
};

struct Obj0 *EffModelResCtor_1a8380(struct Obj0 *p0)
{
    p0->m00 = D_004709C8;
    p0->m00 = D_00470EA0;
    p0->m08 = 0;
    p0->m04 = 0;
    p0->m00 = D_00470E80;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    return p0;
}

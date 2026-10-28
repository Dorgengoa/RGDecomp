/* rgp:protos */
#define RGP_SELF_MotionEventTexAnimeHandlerCtor_1ef3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471160[];
extern u8 D_004711C0[];
extern u8 D_004711E0[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
};

struct Obj0 *MotionEventTexAnimeHandlerCtor_1ef3a0(struct Obj0 *p0)
{
    p0->m00 = D_004711E0;
    p0->m00 = D_004711C0;
    p0->m04 = 0;
    p0->m00 = D_00471160;
    return p0;
}

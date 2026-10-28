/* rgp:protos */
#define RGP_SELF_MotionEventSeHandlerCtor_1ef400 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004711A0[];
extern u8 D_004711C0[];
extern u8 D_004711E0[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
};

struct Obj0 *MotionEventSeHandlerCtor_1ef400(struct Obj0 *p0)
{
    p0->m00 = D_004711E0;
    p0->m00 = D_004711C0;
    p0->m04 = 0;
    p0->m00 = D_004711A0;
    return p0;
}

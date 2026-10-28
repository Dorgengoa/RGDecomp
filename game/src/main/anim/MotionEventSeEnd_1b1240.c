/* rgp:protos */
#define RGP_SELF_MotionEventSeEnd_1b1240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2C];
    s32 m2C;
};

s32 MotionEventSeEnd_1b1240(s32 p0, struct Obj0 *p1)
{
    p1->m2C = -1;
    return 1;
}

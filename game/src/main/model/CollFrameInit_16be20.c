/* rgp:protos */
#define RGP_SELF_CollFrameInit_16be20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF0];
    s32 mF0;
    s32 mF4;
};

void CollFrameInit_16be20(struct Obj0 *p0)
{
    p0->mF0 = 1;
    p0->mF4 = 0;
    FrameInitFields_14a8d0(p0);
}

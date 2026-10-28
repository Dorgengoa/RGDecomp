/* rgp:protos */
#define RGP_SELF_InsectCageSeStopLoops_384540 1
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
    s32 m00;
    u8 m04;
    u8 m05;
};

void InsectCageSeStopLoops_384540(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m00;
    SoundStopEntry_1b8bc0(t0, 0, 0);
    t1 = p0->m00;
    SoundStopEntry_1b8bc0(t1, 2, 0);
    p0->m04 = 0;
    p0->m05 = 0;
}

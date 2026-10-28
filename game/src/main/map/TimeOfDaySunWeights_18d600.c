/* rgp:protos */
#define RGP_SELF_TimeOfDaySunWeights_18d600 1
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
    u8 pad000[0x8];
    s32 m08;
};

void TimeOfDaySunWeights_18d600(s32 p0, struct Obj0 *p1)
{
    TimeOfDayPhaseWeights_18d630(p0, p1);
    p1->m08 = 0;
}

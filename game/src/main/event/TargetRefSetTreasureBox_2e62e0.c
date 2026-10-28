/* rgp:protos */
#define RGP_SELF_TargetRefSetTreasureBox_2e62e0 1
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
    s16 m00;
    s16 m02;
    s32 m04;
    s32 m08;
};

void TargetRefSetTreasureBox_2e62e0(struct Obj0 *p0, s32 p1)
{
    TargetRefClear_2e71d0(p0);
    p0->m00 = 0xB;
    p0->m02 = p1;
    p0->m04 = 0;
    p0->m08 = 0;
}

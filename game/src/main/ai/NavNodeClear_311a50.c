/* rgp:protos */
#define RGP_SELF_NavNodeClear_311a50 1
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
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s16 m18;
    s16 m1A;
    s16 m1C;
};

void NavNodeClear_311a50(struct Obj0 *p0)
{
    p0->m18 = -1;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m10 = 0;
    p0->m0C = 0;
    p0->m14 = 0;
    p0->m1A = 0;
    p0->m1C = 0;
    NavNodeResetDist_311820(p0);
}

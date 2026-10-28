/* rgp:protos */
#define RGP_SELF_EvFollowObjReset_2f8170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x110];
    s32 m110;
    s32 m114;
    s32 m118;
    s32 m11C;
    s32 m120;
    s32 m124;
    u8 m128;
    u8 pad129[0xF];
    s32 m138;
    s32 m13C;
    s32 m140;
};

void EvFollowObjReset_2f8170(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xE0));
    p0->m110 = 0;
    p0->m114 = 0;
    p0->m118 = 0;
    p0->m11C = 0;
    p0->m120 = 0;
    p0->m128 = 0;
    p0->m124 = 0;
    p0->m138 = 0;
    p0->m13C = 0;
    p0->m140 = -1;
}

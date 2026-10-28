/* rgp:protos */
#define RGP_SELF_MapReleaseSlot2Area_1e2de0 1
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
    u8 pad000[0x6];
    s16 m06;
};

void MapReleaseSlot2Area_1e2de0(struct Obj0 *p0, s32 p1)
{
    p0->m06 = -1;
    MapAreaReleaseAndReset_1e2d60(p0, (struct Obj0 *)((u8 *)p0 + 0x1CC0), p1);
}

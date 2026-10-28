/* rgp:protos */
#define RGP_SELF_MapReleaseSlot3Area_1e2dc0 1
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
    s16 m08;
};

void MapReleaseSlot3Area_1e2dc0(struct Obj0 *p0, s32 p1)
{
    p0->m08 = -1;
    MapAreaReleaseAndReset_1e2d60(p0, (struct Obj0 *)((u8 *)p0 + 0x1E8C), p1);
}

/* rgp:protos */
#define RGP_SELF_MapSkyInit_1e6360 1
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
    u8 pad000[0x17BC];
    s32 m17BC;
    s16 m17C0;
    s16 m17C2;
    s16 m17C4;
    s16 m17C6;
};

void MapSkyInit_1e6360(struct Obj0 *p0)
{
    MapSkyResetModels_17f8a0(p0);
    LoadHandleReset_1ccc10((struct Obj0 *)((u8 *)p0 + 0x17B0));
    p0->m17BC = 0;
    p0->m17C0 = -1;
    p0->m17C2 = -1;
    p0->m17C4 = 0;
    p0->m17C6 = 0;
}

/* rgp:protos */
#define RGP_SELF_MapDataGetTexGroupBase_1e78e0 1
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
    u8 pad000[0x8];
    s32 m08;
};

s32 MapDataGetTexGroupBase_1e78e0(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;
    s32 r1;

    r0 = ((unsigned char)MapDataIsLoaded_1e79d0(p0));
    if (r0 != 0) {
        t0 = p0->m08;
        r1 = MapAreaDataGetTexGroupBase_1e8bc0(t0);
        return r1;
    }
    return -1;
}

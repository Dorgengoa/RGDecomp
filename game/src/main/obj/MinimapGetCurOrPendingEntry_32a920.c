/* rgp:protos */
#define RGP_SELF_MinimapGetCurOrPendingEntry_32a920 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x170];
    s32 m170;
    s32 m174;
};

s32 MinimapGetCurOrPendingEntry_32a920(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m170;
    if (t0 != 0) {
        return t0;
    }
    t1 = p0->m174;
    if (t1 != 0) {
        return t1;
    }
    return 0;
}

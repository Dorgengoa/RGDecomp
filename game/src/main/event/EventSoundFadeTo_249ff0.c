/* rgp:protos */
#define RGP_SELF_EventSoundFadeTo_249ff0 1
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
    u8 pad000[0xC];
    f32 m0C;
    s32 m10;
};

struct Obj0 *EventSoundFadeTo_249ff0(s32 p0, s32 p1, s32 p2, s32 p3, f32 fa0)
{
    struct Obj0 *r0;

    r0 = EventSoundTableFindOrAdd_24a060(p0, p1, p2);
    if (r0 != 0) {
        r0->m0C = fa0;
        r0->m10 = p3;
    }
    return r0;
}

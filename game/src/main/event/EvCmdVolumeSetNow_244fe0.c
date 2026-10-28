/* rgp:protos */
#define RGP_SELF_EvCmdVolumeSetNow_244fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 EvCmdVolumeSetNow_244fe0(s32 p0)
{
    f32 r0;
    struct Obj0 * t0;
    s32 t1;
    struct Obj0 * t2;
    s32 t3;

    r0 = TaggedGetFloat_2490d0(p0);
    t0 = gEventContext;
    t1 = gEventContext->m00;
    GameSceneSoundSetVolumeNow_1d0400(t1, r0);
    t2 = gEventContext;
    t3 = gEventContext->m00;
    GameSceneSoundSlot4SetVolume_1d0630(t3, r0);
    return 1;
}

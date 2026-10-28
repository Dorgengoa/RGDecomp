/* rgp:protos */
#define RGP_SELF_EvCmdVolumeFadeOut_244e90 1
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

s32 EvCmdVolumeFadeOut_244e90(s32 p0)
{
    s32 r0;
    s32 t1;
    s32 r1;
    s32 t3;
    s32 r2;

    r0 = ScriptGetInt_2490f0(p0);
    t1 = gEventContext->m00;
    r1 = (GameSceneSoundFadeVolume_1d0370(t1, r0, 0.0f), (s32)0);
    t3 = gEventContext->m00;
    r2 = GameSceneSoundSlot4FadeTo_1d0610(t3, r0, 0.0f);
    return 1;
}

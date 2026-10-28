/* rgp:protos */
#define RGP_SELF_EvScriptCmdVolumeSetMass_3014d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482830;
extern u8 D_004E66D0[];

s32 EvScriptCmdVolumeSetMass_3014d0(s32 p0, s32 p1)
{
    s32 t0;
    f32 r0;
    s32 r1;

    if (p1 != 1) {
        return 0;
    }
    t0 = D_00482830;
    if (t0 == 0) {
        return 1;
    }
    r0 = ScriptArgGetFloat_301a20(p0);
    r1 = (EventVolumeRecSetMass_2e4d10(D_004E66D0, r0), (s32)0);
    return 1;
}

/* rgp:protos */
#define RGP_SELF_EvCmdEffectStopByName_2599f0 1
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

s32 EvCmdEffectStopByName_2599f0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = ((s32)GetEffectMgr_2d9040());
        r1 = ScriptGetCodeAddr_26a200(p0);
        r2 = EffectStopByName_2e14f0(r0, r1);
        rv3 = 1;
    }
    return rv3;
}

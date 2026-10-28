/* rgp:protos */
#define RGP_SELF_EvScriptCmdFollowObjSetRatio_2ffd00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E6880[];

s32 EvScriptCmdFollowObjSetRatio_2ffd00(s32 p0, s32 p1)
{
    s32 rv2;
    f32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 != 1) {
        rv2 = 0;
    } else {
        r0 = ScriptArgGetFloat_301a20(p0);
        r1 = (EvFollowObjSetRatio_2f7f50(D_004E6880, r0), (s32)0);
        rv2 = 1;
    }
    return rv2;
}

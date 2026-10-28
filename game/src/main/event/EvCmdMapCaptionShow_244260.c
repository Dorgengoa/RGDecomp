/* rgp:protos */
#define RGP_SELF_EvCmdMapCaptionShow_244260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMapCaptionShow_244260(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv5;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ((s32)GetMapMgr_201a90());
    r1 = MapMgrCaptionShow_1e2650(r0);
    if (p1 > 0) {
        r2 = ScriptGetInt_2490f0(p0);
        r3 = MapMgrCaptionSetOffsetY_1e2640(r0, r2);
        rv5 = r3;
    } else {
        r4 = MapMgrCaptionSetOffsetY_1e2640(r0, -0x40);
        rv5 = r4;
    }
    return 1;
}

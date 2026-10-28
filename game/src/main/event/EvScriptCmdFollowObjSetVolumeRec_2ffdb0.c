/* rgp:protos */
#define RGP_SELF_EvScriptCmdFollowObjSetVolumeRec_2ffdb0 1
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

extern u8 D_004E6880[];

s32 EvScriptCmdFollowObjSetVolumeRec_2ffdb0(s32 p0, s32 p1)
{
    s32 rv4;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    rv4 = 1;
    if (p1 != 1) {
        rv4 = 0;
    } else {
        r0 = ((s32)GetEventObjMgr_2d1960());
        r1 = ScriptArgGetStr_301a00(p0);
        r2 = ((s32)EventObjMgrFindVolumeRecByName_2e9bc0(r0, r1));
        r3 = (EvFollowObjSetVolumeRec_2f8080(D_004E6880, r2), (s32)0);
        rv4 = 1;
    }
    return rv4;
}

/* rgp:protos */
#define RGP_SELF_EvCmdLoadWaitAreasReadyMaybe_25cfa0 1
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

s32 EvCmdLoadWaitAreasReadyMaybe_25cfa0(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    if (p1 <= 0) {
        return 0;
    }
    r0 = LoadingIconCanHide_2ee930();
    if (r0 == 0) {
        r1 = (ScriptSetRefInt_26a1e0(p0, 0), (s32)0);
        return 1;
    }
    r2 = ((s32)GetMapMgr_201a90());
    r3 = ((unsigned char)MapLoadIsSettledMaybe_1e4e10(r2, 0));
    if ((r3 & 0xFF) == 1) {
        r4 = (ScriptSetRefInt_26a1e0(p0, 1), (s32)0);
        return 1;
    }
    ScriptSetRefInt_26a1e0(p0, 0);
    return 1;
}

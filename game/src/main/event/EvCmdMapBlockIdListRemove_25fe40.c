/* rgp:protos */
#define RGP_SELF_EvCmdMapBlockIdListRemove_25fe40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMapBlockIdListRemove_25fe40(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv5;
    s32 r3;
    s32 r4;

    r0 = ((s32)GetMapMgr_201a90());
    r1 = ScriptGetCodeAddr_26a200(p0);
    r2 = MapSlotsFindBlockByName_1e4910(r0, r1, 0);
    rv5 = 1;
    if (r2 == 0) {
        rv5 = 0;
    } else {
        r3 = ((short)MapDataGetId_1e7bd0(r2));
        r4 = MapBlockIdListRemove_1e3310(r0, r3);
        rv5 = 1;
    }
    return rv5;
}

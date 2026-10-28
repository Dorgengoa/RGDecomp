/* rgp:protos */
#define RGP_SELF_MapSequencerFindOrAddMoverByAreaName_2fa260 1
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

int MapSequencerFindOrAddMoverByAreaName_2fa260(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GetMapMgr_201a90());
    r1 = MapSlotsFindIdByName_1e4520(r0, p1);
    return MapSequencerFindOrAddMover_2fa2c0(p0, r1, p2);
}

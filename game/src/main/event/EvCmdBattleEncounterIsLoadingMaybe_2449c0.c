/* rgp:protos */
#define RGP_SELF_EvCmdBattleEncounterIsLoadingMaybe_2449c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdBattleEncounterIsLoadingMaybe_2449c0(s32 p0, s32 p1)
{
    s32 rv2;
    s32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 <= 0) {
        rv2 = 0;
    } else {
        r0 = BattleEncounterIsLoadingMaybe_2f2530();
        r1 = (ScriptSetRefInt_249030(p0, (r0 & 0xFF)), (s32)0);
        rv2 = 1;
    }
    return rv2;
}

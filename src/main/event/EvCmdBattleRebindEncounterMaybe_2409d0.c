#include "types.h"

extern s32 ScriptGetInt_2490f0(s32);
extern void BattleRebindEncounterMaybe_2f2d90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdBattleRebindEncounterMaybe_2409d0(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;

    rv1 = -1;
    if (p1 == 1) {
        r0 = ScriptGetInt_2490f0(p0);
        rv1 = r0;
    }
    BattleRebindEncounterMaybe_2f2d90(rv1);
    return 1;
}

#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern void PartyAllySuggestCancel_2eea00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdPartyAllySuggestCancel_2698f0(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;

    rv1 = -1;
    if (p1 > 0) {
        r0 = ScriptGetInt_26a2a0(p0);
        rv1 = r0;
    }
    PartyAllySuggestCancel_2eea00(rv1);
    return 1;
}

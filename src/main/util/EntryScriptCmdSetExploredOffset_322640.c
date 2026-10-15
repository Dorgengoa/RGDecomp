#include "types.h"

extern s32 GetEntryTableGlobal_32c2e0(void);
extern s32 EntryTableGetCurrent_323530(s32);
extern s32 VariantGetInt_15f780(s32);
extern s32 EntrySetExploredOffset_323900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EntryScriptCmdSetExploredOffset_322640(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = GetEntryTableGlobal_32c2e0();
    r1 = EntryTableGetCurrent_323530(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = VariantGetInt_15f780(p0);
    r3 = EntrySetExploredOffset_323900(r1, r2);
    return 1;
}

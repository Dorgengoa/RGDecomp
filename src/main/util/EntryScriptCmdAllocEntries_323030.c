#include "types.h"

extern s32 GetEntryTableGlobal_32c2e0(void);
extern s32 VariantGetInt_15f780(s32);
extern void EntryListSetCount_3236a0(s32, s32);
extern s32 EntryListAllocEntries_3235b0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EntryScriptCmdAllocEntries_323030(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r3;

    r0 = GetEntryTableGlobal_32c2e0();
    if (r0 == 0) {
        return 0;
    }
    r1 = VariantGetInt_15f780(p0);
    EntryListSetCount_3236a0(r0, r1);
    r3 = EntryListAllocEntries_3235b0(r0);
    return 1;
}

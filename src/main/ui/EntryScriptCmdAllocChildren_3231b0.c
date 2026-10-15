#include "types.h"

extern s32 GetEntryTableGlobal_32c2e0(void);
extern s32 VariantGetInt_15f780(s32);
extern void EntryListSetChildCount_3237a0(s32, s32);
extern void EntryListAllocChildren_3236c0(s32);
extern s32 EntryListSetChildCursor_3233b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EntryScriptCmdAllocChildren_3231b0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r4;

    r0 = GetEntryTableGlobal_32c2e0();
    if (r0 == 0) {
        return 0;
    }
    r1 = VariantGetInt_15f780(p0);
    EntryListSetChildCount_3237a0(r0, r1);
    EntryListAllocChildren_3236c0(r0);
    r4 = EntryListSetChildCursor_3233b0(r0, 0);
    return 1;
}

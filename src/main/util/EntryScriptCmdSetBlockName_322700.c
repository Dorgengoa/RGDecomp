#include "types.h"

extern s32 GetEntryTableGlobal_32c2e0(void);
extern s32 EntryTableGetCurrent_323530(s32);
extern s32 SlotGetInt_15f720(s32);
extern s32 EntrySetBlockName_323960(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EntryScriptCmdSetBlockName_322700(s32 p0)
{
    s32 r0;
    s32 rv5;
    s32 r1;
    s32 rv4;
    s32 r2;
    s32 r3;

    r0 = GetEntryTableGlobal_32c2e0();
    rv5 = rv4;
    if (r0 == 0) {
        rv5 = 0;
    } else {
        r1 = EntryTableGetCurrent_323530(r0);
        rv4 = 1;
        if (r1 == 0) {
            rv4 = 0;
        } else {
            r2 = SlotGetInt_15f720(p0);
            r3 = EntrySetBlockName_323960(r1, r2);
            rv4 = 1;
        }
        rv5 = rv4;
    }
    return rv5;
}

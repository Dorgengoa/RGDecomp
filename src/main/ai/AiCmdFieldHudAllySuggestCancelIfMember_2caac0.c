#include "types.h"

extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 FieldHudGetSuggestMember_203c20(void);
extern s32 FieldHudAllySuggestCancel_203c80(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdFieldHudAllySuggestCancelIfMember_2caac0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;

    r0 = ScriptSlotGetInt_2cc9c0(p0);
    r1 = FieldHudGetSuggestMember_203c20();
    rv3 = r1;
    if (r0 == r1) {
        r2 = FieldHudAllySuggestCancel_203c80();
        rv3 = r2;
    }
    return 1;
}

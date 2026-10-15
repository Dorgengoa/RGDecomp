#include "types.h"

extern s32 FieldHudGetSuggestMember_203c20(void);
extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdFieldHudGetSuggestMember_2caa60(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = FieldHudGetSuggestMember_203c20();
    r1 = ScriptSlotStoreIntRef_2cc900(p0, r0);
    return 1;
}

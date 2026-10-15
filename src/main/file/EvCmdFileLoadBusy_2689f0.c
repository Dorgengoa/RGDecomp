#include "types.h"

extern s32 FileReqAnyIncomplete_1825f0(void);
extern void ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdFileLoadBusy_2689f0(s32 p0)
{
    s32 r0;

    r0 = FileReqAnyIncomplete_1825f0();
    ScriptSetRefInt_26a1e0(p0, r0);
    return 1;
}

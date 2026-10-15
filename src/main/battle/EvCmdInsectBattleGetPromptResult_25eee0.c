#include "types.h"

extern s32 InsectBattleGetPromptResult_319500(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdInsectBattleGetPromptResult_25eee0(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = InsectBattleGetPromptResult_319500();
    if (p1 > 0) {
        r1 = ScriptSetRefInt_26a1e0(p0, r0);
    }
    return 1;
}

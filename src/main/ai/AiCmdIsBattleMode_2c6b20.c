#include "types.h"

extern s32 GetGameMode_1f59c0(void);
extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdIsBattleMode_2c6b20(s32 p0, s32 p1)
{
    s32 rv2;
    s32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 <= 0) {
        rv2 = 0;
    } else {
        r0 = GetGameMode_1f59c0();
        r1 = ScriptSlotStoreIntRef_2cc900(p0, (r0 == 7));
        rv2 = 1;
    }
    return rv2;
}

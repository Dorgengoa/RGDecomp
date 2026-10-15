#include "types.h"

extern s32 IsInBattle_288420(void);
extern s32 GetGameMode_1f59c0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 IsInBattleMode_288380(void)
{
    s32 r0;
    s32 rv6;
    s32 r1;
    s32 rv5;
    s32 r2;
    s32 rv4;
    s32 r3;

    r0 = IsInBattle_288420();
    rv6 = rv5;
    if (r0 == 0) {
        rv6 = 0;
    } else {
        r1 = GetGameMode_1f59c0();
        rv5 = rv4;
        if (r1 == 7) {
            rv5 = 1;
        } else {
            r2 = GetGameMode_1f59c0();
            rv4 = (r3 == 9);
            if (r2 == 8) {
                rv4 = 1;
            } else {
                r3 = GetGameMode_1f59c0();
                rv4 = (r3 == 9);
            }
            rv5 = rv4;
        }
        rv6 = rv5;
    }
    return rv6;
}

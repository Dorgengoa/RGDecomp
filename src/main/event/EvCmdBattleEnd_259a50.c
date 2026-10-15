#include "types.h"

extern s32 GetGameData_1fede0(void);
extern void GameDataBattleEnd_3e67c0(s32, s32, s32, s32, s32);
extern s32 GameDataStatusClearAllPartial_3e6760(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdBattleEnd_259a50(void)
{
    s32 r0;
    s32 r2;

    r0 = GetGameData_1fede0();
    GameDataBattleEnd_3e67c0(r0, 4, 0, 1, 0);
    r2 = GameDataStatusClearAllPartial_3e6760(r0);
    return 1;
}

#include "types.h"

extern s32 GetGameData_1fede0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern void GameDataUpdateManagers_3e63a0(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameDataTick_1febd0(void)
{
    s32 r0;
    s32 r1;
    f32 r2;

    r0 = GetGameData_1fede0();
    r1 = GetCurrentScene_1f5be0();
    r2 = GameSceneGetTimeStep_1ceba0(r1);
    GameDataUpdateManagers_3e63a0(r0, r2);
}

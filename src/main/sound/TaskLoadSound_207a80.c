#include "types.h"

/* ONE symbol, TWO entries: a `j` TAIL CALL into the second entry with a null
   argument, then GameSceneSoundSlotsPoll_1d0a90(GetCurrentScene_1f5be0(p), p). */

extern void *GetCurrentScene_1f5be0(void *p);
extern void GameSceneSoundSlotsPoll_1d0a90(void *a, void *b);

void FUN_00207a80_e1(void *p);

void TaskLoadSound_207a80(void)
{
    FUN_00207a80_e1(0);
}

void FUN_00207a80_e1(void *p)
{
    GameSceneSoundSlotsPoll_1d0a90(GetCurrentScene_1f5be0(p), p);
}

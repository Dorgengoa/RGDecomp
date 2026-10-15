#include "types.h"

extern s32 D_004837C0;
extern s32 D_004837C4;
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32 GameReqQueuePushBack_1f5b50(s32, s32);

s32 CharaSysRequestBattle_3a5610(void)
{
    if (D_004837C0 == 0) goto zero;
    if (D_004837C4 != 0) goto ok;
zero:
    return 0;
ok:
    GameReqQueueRemoveById_1f5a10(7);
    GameReqQueuePushBack_1f5b50(7, 2);
    return 1;
}

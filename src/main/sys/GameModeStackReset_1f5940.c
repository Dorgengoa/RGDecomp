#include "types.h"

extern s32 D_004B51A0[16];
extern s32 D_004B51E0[16];
extern void ClearGameReqHold_1f5880(void);

void GameModeStackReset_1f5940(void)
{
    s32 i;

    ClearGameReqHold_1f5880();
    for (i = 0; i < 16; i++) {
        D_004B51A0[i] = -1;
        D_004B51E0[i] = -1;
    }
}

/* rgp:protos */
#define RGP_SELF_GameModeStackReset_1f5940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004B51A0[16];
extern s32 D_004B51E0[16];
/*rgp*/

void GameModeStackReset_1f5940(void)
{
    s32 i;

    ClearGameReqHold_1f5880();
    for (i = 0; i < 16; i++) {
        D_004B51A0[i] = -1;
        D_004B51E0[i] = -1;
    }
}

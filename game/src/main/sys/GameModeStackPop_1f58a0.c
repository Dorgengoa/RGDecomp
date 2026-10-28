/* rgp:protos */
#define RGP_SELF_GameModeStackPop_1f58a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004B51A0[];
extern s32 D_004B51E0[];

void GameModeStackPop_1f58a0(void)
{
    s32 i;

    for (i = 1; i < 0x10; i++) {
        D_004B51A0[i - 1] = D_004B51A0[i];
        D_004B51E0[i - 1] = D_004B51E0[i];
    }
}

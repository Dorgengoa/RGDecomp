#include "types.h"

extern s32 D_004B51A0[];
extern s32 D_004B51E0[];

void GameModeStackPush_1f58f0(s32 p0, s32 p1)
{
    s32 i;

    i = 0xF;
    do {
        D_004B51A0[i] = D_004B51A0[i - 1];
        D_004B51E0[i] = D_004B51E0[i - 1];
        i = i - 1;
    } while (i > 0);
    D_004B51A0[0] = p0;
    D_004B51E0[0] = p1;
}

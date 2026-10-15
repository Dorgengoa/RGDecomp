#include "types.h"
/* insect 0x0051C2B0 -- 64 bytes, 16 instructions. */

extern void insect_InsectBattleLogScrollUp_51c180(void *a);
extern s32  insect_InsectBattleLogIsEmpty_51b8b0(void *a);

void insect_InsectBattleLogClear_51c2b0(void *a)
{
    do {
        insect_InsectBattleLogScrollUp_51c180(a);
    } while (!insect_InsectBattleLogIsEmpty_51b8b0(a));
}

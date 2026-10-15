#include "types.h"

typedef struct C_FUN_003ce1a0 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
} C_FUN_003ce1a0;

extern C_FUN_003ce1a0 *GameRecGetCageSlot_3ce1f0(void);

s32 GameRecMarkCageSlotReclaimable_3ce1a0(void)
{
    C_FUN_003ce1a0 *p;

    p = GameRecGetCageSlot_3ce1f0();
    if (p == 0) return 0;
    p->b1 = 1;
    return 1;
}

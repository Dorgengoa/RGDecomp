#include "types.h"

typedef struct C_FUN_003ce040 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
} C_FUN_003ce040;

extern C_FUN_003ce040 *GameRecGetInsectRecSlot_3ce090(void);

s32 GameRecMarkInsectRecSlotReclaimable_3ce040(void)
{
    C_FUN_003ce040 *p;

    p = GameRecGetInsectRecSlot_3ce090();
    if (p == 0) return 0;
    p->b1 = 1;
    return 1;
}

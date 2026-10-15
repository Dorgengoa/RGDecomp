#include "types.h"

typedef struct C_FUN_003ce300 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
} C_FUN_003ce300;

extern C_FUN_003ce300 *GameRecGetInsectSlot_3ce350(void);

s32 GameRecMarkInsectSlotReclaimable_3ce300(void)
{
    C_FUN_003ce300 *p;

    p = GameRecGetInsectSlot_3ce350();
    if (p == 0) return 0;
    p->b1 = 1;
    return 1;
}

/* rgp:protos */
#define RGP_SELF_GameRecMarkInsectRecSlotReclaimable_3ce040 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/

s32 GameRecMarkInsectRecSlotReclaimable_3ce040(int rgp_a0, int rgp_a1)
{
    C_FUN_003ce040 *p;

    p = ((C_FUN_003ce040 *)GameRecGetInsectRecSlot_3ce090((int)rgp_a0, (int)rgp_a1));
    if (p == 0) return 0;
    p->b1 = 1;
    return 1;
}

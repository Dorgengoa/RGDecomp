/* rgp:protos */
#define RGP_SELF_MapBlockGetName_1dff20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on

/*rgp*/
/*rgp*/

s32 MapBlockGetName_1dff20(void *arg0, s32 arg1)
{
    if (((short)MapDataGetParentId_1e7bb0((void *)arg0)) != 0xC8) {
        return *(s32 *)((u8 *)arg0 + 0x54);
    }
    switch (arg1) {
    default:
        if ((u32)(arg1 - 0x88D) >= 2U) break;
    case 0x86C:
    case 0x86B:
    case 0x86A:
        return *(s32 *)((u8 *)arg0 + 0x54);
    }
    return ((s32)MapBlockGetStoryName_1dffb0(arg0));
}

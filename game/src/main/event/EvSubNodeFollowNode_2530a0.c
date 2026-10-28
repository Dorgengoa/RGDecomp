/* rgp:protos */
#define RGP_SELF_EvSubNodeFollowNode_2530a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
extern u8 D_004BDDB0[0x400];

s32 EvSubNodeFollowNode_2530a0(void *arg0, void *arg1) {
    u8 sp30[0x10] __attribute__((aligned(16)));
    s32 temp_3;

    if (!(EventCastSlotGetFrameWorldPos_257c20(&(*(u8 *)D_004BDDB0), *(s32 *)((u8 *)arg0 + 0x20), (u8 *)arg0 + 0x2C, sp30) != 0)) {
        return 0;
    }
    VecAdd_13be20((s32)((u8 *)arg1 + 0x70), sp30, (u8 *)arg0 + 0x10);
    temp_3 = *(s32 *)((u8 *)arg0 + 0x24);
    if ((temp_3 >= 0) && (*(s32 *)((u8 *)arg1 + 0x40) >= temp_3)) {
        *(s32 *)((u8 *)arg1 + 0x40) = 0;
        return 0;
    }
    if (temp_3 > 0) {
        *(s32 *)((u8 *)arg1 + 0x40) = *(s32 *)((u8 *)arg1 + 0x40) + 1;
    }
    return 1;
    return 0;
}

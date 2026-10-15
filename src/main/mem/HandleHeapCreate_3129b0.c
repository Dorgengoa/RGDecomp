#pragma opt_common_subs off
#pragma divbyzerocheck on
#include "types.h"

u8 *OperatorNew_100990(s32);                              /* extern */

u8 **HandleHeapCreate_3129b0(u8 **arg0, s32 arg1, u32 arg2, u32 arg3) {typedef struct {s32 f0;s32 f4;s32 f8;s32 fc;s32 f10;s32 f14;s32 f18;s32 f1c;s32 f20;} LaneA_0;

    u32 temp_4;
    u8 *temp_2;

    temp_2 = OperatorNew_100990(0x24);
    if (temp_2 != 0) {
        if (*(volatile u32*)temp_2 != 0) {
            (((LaneA_0*)temp_2)->f0) = 0;
        }

        if (arg3 == 0) {
        }
        (((LaneA_0*)temp_2)->f0) = (s32) (arg3 * ((u32) ((arg1 + arg3) - 1) / arg3));

        if (arg3 == 0) {
        }
        (((LaneA_0*)temp_2)->f4) = (s32) (arg3 * (arg2 / arg3));
        (((LaneA_0*)temp_2)->f8) = arg3;
        (((LaneA_0*)temp_2)->fc) = (s32) (((LaneA_0*)temp_2)->f0);
        (((LaneA_0*)temp_2)->f10) = (s32) ((((LaneA_0*)temp_2)->f0) + (((LaneA_0*)temp_2)->f4));
        (((LaneA_0*)temp_2)->f14) = 0;
        (((LaneA_0*)temp_2)->f18) = 0;
        (((LaneA_0*)temp_2)->f1c) = 0;
        temp_4 = (((LaneA_0*)temp_2)->f8);

        if (temp_4 == 0) {
        }
        (((LaneA_0*)temp_2)->f20) = (s32) (temp_4 * ((u32) (temp_4 + 0xB) / temp_4));
    }
    *arg0 = temp_2;
    return arg0;
}

#include "types.h"
#pragma opt_common_subs off

extern void EventCastPlayMotion_2583a0(void *arg0, s32 arg1, void *arg2, s32 arg3, f32 arg4);
extern u8 D_004BDDB0[];

s32 EvSubNodePlayMotionNow_2526d0(void *arg0, void *arg1)
{
    s32 *temp_2;
    s32 temp_3;

    if (*(s32 *)((u8 *)arg0 + 0x28) == 0) {
        EventCastPlayMotion_2583a0(D_004BDDB0, *(s32 *)((u8 *)arg1 + 0x60), (u8 *)arg0 + 0x2C,
                     *(s32 *)((u8 *)arg0 + 0x20), *(f32 *)((u8 *)arg0 + 0x24));
        temp_2 = *(s32 **)((u8 *)arg0 + 0x4C);
        if (temp_2 != NULL) {
            temp_3 = *temp_2;
            if (temp_3 == 0x19 || temp_3 == 0x1D) {
                return 0;
            }
        }
        return *(s32 *)((u8 *)arg0 + 0x28) = 1;
    }
    return 0;
}

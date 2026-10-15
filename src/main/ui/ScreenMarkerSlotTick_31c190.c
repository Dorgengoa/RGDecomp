#include "types.h"
#pragma no_branch_likely on
#pragma opt_common_subs off
#pragma no_branch_likely off

typedef struct T31c190 {
    s16 unk0;
    u8 pad2[0x40 - 2];
    s16 unk40;
    u8 pad42[0xA0 - 0x42];
    s16 unkA0;
} T31c190;

extern s32 ScreenMarkerGetPinned_31bf10(s32,s32,s16, T31c190 *);
extern void ScreenMarkerSetFadeOut_31bf50(s32, s32, s32);
extern void ScreenMarkerSlotFadeOutTick_31c120(s32, s32);

void ScreenMarkerSlotTick_31c190(s32 arg0, s32 arg1)
{
    s32 dummy0,dummy1;
    s32 temp_17;
    T31c190 *temp_7;
    s16 temp_6;
    s16 *count;

    temp_17 = arg1 * 2;
    temp_7 = (T31c190 *)(arg0 + temp_17);
    if ((temp_6 = temp_7->unk0) != -1) {
        count = &temp_7->unk40;
        if ((*count > 0) && (ScreenMarkerGetPinned_31bf10(dummy0,dummy1,temp_6,temp_7) == 0)) {
            *count = *count - 1;
        }
        if (*count <= 0) {
            if (!(((T31c190 *)(temp_17 + arg0))->unkA0 == -1)) {
                ScreenMarkerSlotFadeOutTick_31c120(arg0, arg1);
            } else {
                ScreenMarkerSetFadeOut_31bf50(arg0, arg1, 0xF);
            }
        }
    }
}

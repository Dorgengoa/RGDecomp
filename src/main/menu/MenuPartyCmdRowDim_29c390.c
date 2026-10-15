#include "types.h"

extern void UiSetWidgetColor_2905b0(s32 arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
extern void *MenuGetCursorPos_29fae0(void);
extern f32 D_0047D288;
extern u16 D_0047EC10;
extern u16 D_0047EC00;

s32 MenuPartyCmdRowDim_29c390(void *arg0,s32 arg1, s64 arg2)
{
    if (*(s8 *)((u8 *)MenuGetCursorPos_29fae0() + 0x1) == 0) {
        UiSetWidgetColor_2905b0(*(s32 *)((u8 *)arg0 + 0x4C4),
            *(u16 *)((u8 *)&D_0047EC00 + ((s16)arg2 * 2)),
            D_0047D288, D_0047D288, D_0047D288, 1.0f);
    } else {
        UiSetWidgetColor_2905b0(*(s32 *)((u8 *)arg0 + 0x4C4),
            *(u16 *)((u8 *)&D_0047EC10 + ((s16)arg2 * 2)),
            D_0047D288, D_0047D288, D_0047D288, 1.0f);
    }
    return 0;
}

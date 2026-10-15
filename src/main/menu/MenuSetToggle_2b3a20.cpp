#include "types.h"
extern "C" {

extern void PlayMenuSe_289ef0(s32 arg0);
extern void UiSetSpriteU_28f930(s32 arg0, s32 arg1, s32 arg2, s64 arg3);
extern s32 D_00482360 __attribute__((section(".sdata")));
extern s8 D_004824CC;

void MenuSetToggle_2b3a20(s32 arg0, s64 arg1) {
    u32 temp_18;

    temp_18 = (u8)!(bool)arg1;
    if (D_004824CC == temp_18) {
        PlayMenuSe_289ef0(4);
    }
    D_004824CC = (s8) arg1;
    UiSetSpriteU_28f930(D_00482360, arg0, 0x4C, (s16)arg1);
    UiSetSpriteU_28f930(D_00482360, arg0, 0x18, temp_18 & 0xFF);
}

}

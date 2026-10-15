#include "types.h"

u8 *UiGetWidgetSprite_28fe10(s32,s32,s32);                            /* extern */

void UiSetSpritePosSizeUv_28f710(s32 pdA, s32 pdB, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8, s32 arg_sp10) {
    u8 *temp_2;

    temp_2 = UiGetWidgetSprite_28fe10(pdA,pdB,arg_sp10);
    if (temp_2 != 0) {
        if (arg2 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0x0)) = arg2;
        }
        if (arg3 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0x2)) = arg3;
        }
        if (arg4 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0x4)) = arg4;
        }
        if (arg5 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0x6)) = arg5;
        }
        if (arg6 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0x8)) = arg6;
        }
        if (arg7 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0xA)) = arg7;
        }
        if (arg_sp0 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0xC)) = (s16) arg_sp0;
        }
        if (arg_sp8 != -0x270F) {
            (*(u16 *)((u8 *)temp_2 + 0xE)) = (s16) arg_sp8;
        }
    }
}

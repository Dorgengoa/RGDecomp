#include "types.h"
#pragma opt_dead_assignments off

/* 5 bad -> 4: UiGetWidgetSprite_28fe10 takes THREE arguments and retail leaves `$a1`
   holding this function's own second parameter, so the literal 0 is the
   THIRD (build/s23/argscreen.py found it).
   Remaining 4: ptr10 lands in $a1 and shift5 in $v1 for retail, $v1/$a0 for
   us -- decl-order swap, both inline forms, a named s16 for the 0x2C field,
   shift-first and `* 0x20` are ONE object at 4 bad. */

extern void UiSetItemIconUv_288e50(void *arg0, s16 arg1, s32 arg2, s32 arg3);
extern s32 UiGetWidgetSprite_28fe10(s32 arg0, s32 arg1, s32 arg2);

s32 MenuItemGridDrawCell_2a4d30(s32 *arg0, s32 unused1, void *arg2, s32 arg3) {
    u8 *p2;
    s32 temp_2;
    s32 temp_4;
    s32 var_3;
    s32 var_4;
    u8 *temp_16;
    u8 *ptr10;
    s32 shift5;

    p2 = (u8 *)arg2;
    temp_4 = *arg0;
    if (temp_4 == 0) {
        return 0;
    }
    temp_2 = UiGetWidgetSprite_28fe10(temp_4, unused1, 0);
    if (temp_2 == 0) {
        return 0;
    }
    ptr10 = *(u8 **)(p2 + 0x10);
    shift5 = arg3 << 5;
    temp_16 = (u8 *)(temp_2 + shift5);
    UiSetItemIconUv_288e50(temp_16, *(s16 *)(ptr10 + 0x2C), 0x28, 0x2D);
    var_3 = arg3 & 7;
    *(u16 *)(temp_16 + 0x1C) = *(u16 *)(temp_16 + 0x1C) | 2;
    if ((arg3 < 0) && (var_3 != 0)) {
        var_3 -= 8;
    }
    var_4 = arg3 >> 3;
    *(s16 *)(temp_16 + 0) = (s16)((var_3 * 0x2A) + 2);
    if (arg3 < 0) {
        var_4 = (s32)(arg3 + 7) >> 3;
    }
    *(s16 *)(temp_16 + 2) = (s16)((var_4 * 0x32) - 1);
    return 1;
}

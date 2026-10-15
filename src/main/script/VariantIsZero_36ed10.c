#include "types.h"

s32 DoubleEqual_1002f0(s32, s64);                           /* extern */

s32 VariantIsZero_36ed10(u8 *arg0) {
    s32 var_2;
    u32 temp_2;

    temp_2 = (*(s32 *)((u8 *)arg0 + 0x0));
    switch (temp_2) {
    case 1:
        return (*(s8 *)((u8 *)arg0 + 0x8)) == 0;
    case 2:
        return (u8) (*(u8 *)((u8 *)arg0 + 0x8)) == 0;
    case 3:
        return (s16) (*(s16 *)((u8 *)arg0 + 0x8)) == 0;
    case 4:
        return (u16) (*(u16 *)((u8 *)arg0 + 0x8)) == 0;
    case 5:
        return (s32) (*(s32 *)((u8 *)arg0 + 0x8)) == 0;
    case 6:
        return (s32) (*(s32 *)((u8 *)arg0 + 0x8)) == 0;
    case 7:
        return (s64) (*(s64 *)((u8 *)arg0 + 0x8)) == 0;
    case 8:
        return (s64) (*(s64 *)((u8 *)arg0 + 0x8)) == 0;
    case 9:
        return (*(f32 *)((u8 *)arg0 + 0x8)) == 0.0f;
    case 10:
        return DoubleEqual_1002f0(0, (s64) (*(s64 *)((u8 *)arg0 + 0x8)));
    default:
        var_2 = 0;
        /* Duplicate return node #14. Try simplifying control flow for better match */
        return var_2;
    }
}

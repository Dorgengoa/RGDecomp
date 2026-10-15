#include "types.h"

extern void XformRecSetDefaultNameMaybe_1c6940(void *, s32);

void XformRecArrayResetMaybe_2615a0(void *arg0) {
    s32 temp_5;
    s32 var_17;
    s32 var_5;
    u8 *temp_16;
    u8 *temp_3;

    var_17 = 0;
    do {
        temp_5 = var_17 * 0x60;
        temp_16 = (u8 *)arg0 + temp_5;
        *(s16 *)(temp_16 + 0x50) = 2;
        *(s16 *)(temp_16 + 0x52) = 0;
        *(s16 *)(temp_16 + 0x58) = 0;
        *(s16 *)(temp_16 + 0x5E) = -1;
        *(s16 *)(temp_16 + 0x5A) = -1;
        *(s16 *)(temp_16 + 0x5C) = -1;
        *(u32 *)(temp_16 + 0x0) = 0;
        *(u32 *)(temp_16 + 0x4) = 0;
        *(u32 *)(temp_16 + 0x8) = 0;
        *(u32 *)(temp_16 + 0xC) = 0x3F800000;
        *(u32 *)(temp_16 + 0x10) = 0;
        *(u32 *)(temp_16 + 0x14) = 0;
        *(u32 *)(temp_16 + 0x18) = 0;
        *(u32 *)(temp_16 + 0x1C) = 0x3F800000;
        *(u32 *)(temp_16 + 0x20) = 0;
        *(u32 *)(temp_16 + 0x24) = 0;
        *(u32 *)(temp_16 + 0x28) = 0;
        *(u32 *)(temp_16 + 0x2C) = 0x3F800000;
        XformRecSetDefaultNameMaybe_1c6940(temp_16, temp_5);
        var_5 = 0;
        do {
            temp_3 = temp_16 + (var_5 * 4);
            var_5 += 1;
            *(u32 *)(temp_3 + 0x30) = 0x41000000;
        } while (var_5 < 4);
        var_17 += 1;
    } while (var_17 < 8);
    *(s32 *)((u8 *)arg0 + 0x300) = 0;
}

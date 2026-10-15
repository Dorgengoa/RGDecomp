/* PARK 1/3: length-wrong (58w vs retail 63w). Deep nested-if pyramid over raw offset casts; likely a missed struct field width (s16 vs s32) somewhere in the nest. */
#include "types.h"
#pragma opt_propagation off

s32 ConstructNewArray_100710(s32, s32, s32, s32, s32);
s32 VariantGetInt_15f780(s32 xa0, s32, s32);
s32 ArenaNew_4235b0(s32, void *, s32, s32);
extern u8 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdAllocSubEntries_422d20(void) {
    s32 u_0;
                s32 arg_h4;

    s16 temp_5;
    s32 temp_2_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_5_2;
    s32 temp_6;
    u8 *temp_16;
    u8 *temp_17;
    u8 *temp_2;

    temp_16 = D_004830F8;
    temp_5 = *(s16 *)(temp_16 + 0x7C);
    if (temp_5 <= 0) {
        return 1;
    }
    temp_3 = D_004830FC - 1;
    if (temp_3 >= temp_5) {
        return 1;
    }
    temp_2 = *(u8 **)(temp_16 + 0x8C) + (temp_3 << 5);
    temp_6 = *(s32 *)(temp_2 + 0x18);
    if (temp_6 == 0) {
        return 1;
    }
    temp_5_2 = *(s32 *)(temp_2 + 0x14);
    if (temp_5_2 <= 0) {
        return 1;
    }
    temp_3_2 = *(s32 *)(temp_16 + 0xBC);
    if (!((temp_3_2 - 1) < temp_5_2)) {
        return 1;
    }
    temp_17 = (u8 *)(temp_6 + (temp_3_2 << 5)) - 0x20;
    temp_2_2 = VariantGetInt_15f780(u_0, temp_5_2, temp_6);
    *(s32 *)(temp_17 + 0x14) = temp_2_2;
    if (temp_2_2 > 0) {
        arg_h4 = temp_2_2;
        *(s32 *)(temp_17 + 0x18) = ConstructNewArray_100710(ArenaNew_4235b0((temp_2_2 * 0x10) + 0x10, temp_16 + 0x6C, 4, -1), 0, 0, 0x10, arg_h4);
    } else {
        *(s32 *)(temp_17 + 0x18) = 0;
    }
    *(s32 *)(temp_16 + 0xC0) = 0;
    return 1;
}

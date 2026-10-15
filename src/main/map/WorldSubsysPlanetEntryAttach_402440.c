#include "types.h"

s32 DataTableInitWithCount_368b00(s32, s32, s32);                      /* extern */
s32 WorldSubsysPlanetEntryBind_403920(s32, u8 *, s32);                   /* extern */
extern u8 D_004657D8[0x400];

s32 WorldSubsysPlanetEntryAttach_402440(u8 *arg0, u8 *arg1) {
    s32 temp_6;
    s32 temp_5;
    s32 temp_5_2;
    s32 var_16;
    u8 *temp_2;

    if (arg1 == 0) {
        return 0;
    }
    temp_6 = *(s16 *)((u8 *)arg1 + 0x8);
    if (temp_6 < 0 || temp_6 >= 2) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x0)) == 0) {
        return 0;
    }
    temp_5 = (*(s32 *)((u8 *)arg0 + 0xC));
    var_16 = 0;
    if (temp_5 != 0) {
        var_16 = temp_5 + (temp_6 * 0xA8);
    }
    temp_2 = (unsigned char *)((*(s32 *)((u8 *)arg0 + 0x4)));
    if (temp_2 != 0) {
        temp_5_2 = (*(s32 *)((u8 *)temp_2 + 0x8)) + (temp_6 * 0x58);
        if ((temp_5_2 != 0) && (var_16 != 0) && ((*(s32 *)D_004657D8) == 0)) {
            DataTableInitWithCount_368b00(var_16, temp_5_2, temp_6);
        }
    }
    if (var_16 != 0) {
        WorldSubsysPlanetEntryBind_403920(var_16, arg1, (*(s32 *)D_004657D8) != 0);
    }
    return 1;
}

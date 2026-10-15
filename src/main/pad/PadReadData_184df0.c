#include "types.h"

extern s32 scePadRead(s32, s32, u8 *);

s32 PadReadData_184df0(void *arg0, s32 arg1, s32 arg2) {
    u8 sp30[0x18];
    s32 temp_4;
    s32 var_16;
    s32 var_2;
    s32 var_2_2;
    s32 b1;

    var_16 = 0;
    if (!(scePadRead(arg1, arg2, sp30) != 0)) {
        return 0;
    }
    if (sp30[0] == 0) {
        b1 = sp30[1];
        temp_4 = (b1 & 0xF) * 2;
        if (temp_4 >= 2) {
            var_2 = (((sp30[2] << 8) | sp30[3]) ^ 0xFFFF) & 0xFFFF;
        } else {
            var_2 = 0;
        }
        *(s32 *)((u8 *)arg0 + 0) = var_2 & 0xFFFF;
        var_16 = b1 >> 4;
        if (temp_4 >= 6) {
            *(s32 *)((u8 *)arg0 + 0x10) = sp30[4];
            *(s32 *)((u8 *)arg0 + 0xC) = sp30[5];
            *(s32 *)((u8 *)arg0 + 8) = sp30[6];
            *(s32 *)((u8 *)arg0 + 4) = sp30[7];
        } else {
            *(s32 *)((u8 *)arg0 + 0x10) = 0x80;
            *(s32 *)((u8 *)arg0 + 0xC) = 0x80;
            *(s32 *)((u8 *)arg0 + 8) = 0x80;
            *(s32 *)((u8 *)arg0 + 4) = 0x80;
        }
    }
    return var_16;
    return 0;
}

#include "types.h"
#pragma opt_repositioncode on

extern s32 FileSlotOpen_180710(s8 *, s32);
extern s32 FileSlotGetSize_180d50(s32, s32 *, s32);
extern void FileMakeDevicePath_181980(s32, s8 *);
extern void FileSlotCloseThunk_180540(s32);

s32 FileGetSizeByPath_181ee0(s32 pd0, s32 *arg1)
{
    s8 sp30[0x100];
    s32 temp_17;
    s32 temp_2;
    s8 *var_3;
    u32 var_2;

    if (arg1 != NULL) {
        *arg1 = 0;
    }
    var_3 = sp30;
    var_2 = 0x100;
    if (var_3 != NULL) {
        do {
            *var_3 = 0;
            var_2 -= 1;
            var_3 += 1;
        } while (var_2 != 0);
    }
    FileMakeDevicePath_181980(pd0, sp30);
    temp_2 = FileSlotOpen_180710(sp30, 0);
    if (temp_2 >= 0) {
        temp_17 = FileSlotGetSize_180d50(temp_2, arg1, 0);
        FileSlotCloseThunk_180540(temp_2);
        return temp_17;
    }
    return 0;
}

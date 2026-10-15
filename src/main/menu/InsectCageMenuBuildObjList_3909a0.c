#include "types.h"
#pragma opt_propagation off

extern s32 InsectCageMenuGetCurCageItem_391030(s32 arg0);
extern s32 InsectRecSlotGetItem_3cfb30(s32 arg0, s32 arg1);
extern void *D_004832AC;
extern u8 D_004E94A0[0x400];

s32 InsectCageMenuBuildObjList_3909a0(void)
{
    s32 var_18;

    s32 *temp_2;
    s32 var_7;
    s32 var_4;
    s32 temp_17;
        s32 arg_h0;
    s32 var_16;
    s32 temp_2_2;
    void *temp_4;

    var_4 = 0;
    do {
        temp_2 = (s32 *)((u8 *)&(*(u8 *)D_004E94A0) + (var_4 * 4));
        var_4 += 1;
        *temp_2 = 0;
    } while (var_4 < 5);
    var_18 = 0;
    temp_17 = InsectCageMenuGetCurCageItem_391030(var_4);
    var_16 = 0;
    do {
        arg_h0 = temp_17;
        temp_2_2 = InsectRecSlotGetItem_3cfb30(arg_h0, var_16);
        var_7 = 0;
        while (var_7 < 5) {
            temp_4 = (u8 *)D_004832AC + (var_7 * 0x9D0);
            if ((*(s8 *)((u8 *)temp_4 + 0x985) != 0) && (*(s32 *)((u8 *)temp_4 + 0x96C) == temp_2_2)) {
                var_18 += 1;
                *(void **)((u8 *)&(*(u8 *)D_004E94A0) + (var_16 * 4)) = temp_4;
                break;
            } else {
                var_7 += 1;
            }
        }
        var_16 += 1;
    } while (var_16 < 5);
    return var_18;
}

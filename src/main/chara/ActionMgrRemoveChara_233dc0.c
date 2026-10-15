#include "types.h"
#pragma opt_dead_code off
#pragma opt_common_subs off

extern void MemStackHeapFree_14dcb0(s32 arg0, s32 arg1);
extern s32 CharaGetId_214a80(s32 arg0);
extern s32 CharaGetHeapBlock_214a90(s32 arg0);
extern void CharaActInfoClear_214c30(s32 arg0);
extern s32 CharaGetActInfoBlock_214cc0(s32 arg0);
extern s32 IntCompare_42ca30(s32 arg0, s32 arg1);
extern void DListRemove_42e4e0(void *arg0, s32 arg1);
extern s32 DListGetHead_42ea60(void *arg0);
extern s32 DListGetCountPow2_42ea70(void *arg0);
extern s32 DListNodeAdvance_42eb00(s32 arg0, s32 arg1);

void ActionMgrRemoveChara_233dc0(void *arg0, s32 arg1)
{
    s32 var_21_2;
    s32 var_21;
    s32 var_20_2;
    s32 var_20;
    s32 var_19_2;
    s32 var_19;
    s32 var_18;
    s32 temp_2_5;
    s32 temp_2_4;
    s32 temp_2_3;
    s32 temp_2_2;
    s32 temp_2;
    s32 temp_16;

    if (*(s32 *)((u8 *)arg0 + 0x3C) != 0) {
        temp_2 = DListGetHead_42ea60((u8 *)arg0 + 0x20);
        var_20 = temp_2;
        if (temp_2 == 0) {
            var_21 = 0;
        } else {
            var_21 = 0;
            var_19 = DListGetCountPow2_42ea70((u8 *)arg0 + 0x20);
            while (var_19 > 0) {
                var_19 = var_19 >> 1;
                temp_2_2 = DListNodeAdvance_42eb00(var_20, var_19);
                if (temp_2_2 != 0) {
                    temp_2_3 = IntCompare_42ca30(arg1, CharaGetId_214a80(temp_2_2 + 0x10));
                    if (temp_2_3 == 0) {
                        var_21 = temp_2_2;
                        break;
                    } else {
                        if (temp_2_3 > 0) {
                            var_20 = temp_2_2;
                        }
                        continue;
                    }
                } else {
                    continue;
                }
            }
        }
        if (var_21 == 0) {
            var_18 = 0;
        } else {
            var_18 = var_21 + 0x10;
        }
        if (var_18 != 0) {
            MemStackHeapFree_14dcb0(*(s32 *)((u8 *)arg0 + 0x3C), CharaGetActInfoBlock_214cc0(var_18));
            CharaActInfoClear_214c30(var_18);
        }
    }
    var_20_2 = DListGetHead_42ea60((u8 *)arg0 + 0x20);
    if (var_20_2 == 0) {
        var_21_2 = 0;
    } else {
        var_21_2 = 0;
        var_19_2 = DListGetCountPow2_42ea70((u8 *)arg0 + 0x20);
        while (var_19_2 > 0) {
            var_19_2 = var_19_2 >> 1;
            temp_2_4 = DListNodeAdvance_42eb00(var_20_2, var_19_2);
            if (temp_2_4 != 0) {
                temp_2_5 = IntCompare_42ca30(arg1, CharaGetId_214a80(temp_2_4 + 0x10));
                if (temp_2_5 == 0) {
                    var_21_2 = temp_2_4;
                    break;
                } else {
                    if (temp_2_5 > 0) {
                        var_20_2 = temp_2_4;
                    }
                    continue;
                }
            } else {
                continue;
            }
        }
    }
    if (var_21_2 != 0) {
        temp_16 = *(s32 *)((u8 *)arg0 + 0x3C);
        if (var_21_2 != 0) {
            if (temp_16 != 0) {
                MemStackHeapFree_14dcb0(temp_16, CharaGetHeapBlock_214a90(var_21_2 + 0x10));
            }
            DListRemove_42e4e0((u8 *)arg0 + 0x20, var_21_2);
        }
    }
}

#include "types.h"

class L2341 {
public:
    u8 pad0[0xC];
    virtual s32 add(s32);
};

extern "C" {
void MemStackHeapFree_14dcb0(s32, s32);
s32 MemStackHeapAllocBack_14dcf0(s32, u32);
u32 AlignUp16_1cacd0(s32);
s32 CharaGetId_214a80(s32);
s32 CharaInitFromData_215050(s32, s32, s32);
void CharaInit_2150c0(s32);
s32 IntCompare_42ca30(s32, s32);
s32 DListGetHead_42ea60(void *);
s32 DListGetCountPow2_42ea70(void *);
s32 DListNodeAdvance_42eb00(s32, s32);
void DListNodeInit_42ec10(s32);
}

extern "C" s32 ActionMgrFindOrAddChara_2341b0(u8 *arg0, s32 arg1)
{
    s32 var_19;
    s32 var_18;
    s32 var_17;
    s32 temp_2_3;
    s32 temp_2_2;
    s32 temp_2;
    s32 temp_22;
    s32 temp_16;
    s32 res;

    if (arg1 == 0) {
        return 0;
    }
    temp_22 = CharaGetId_214a80(arg1);
    temp_2 = DListGetHead_42ea60(arg0 + 0x20);
    var_18 = temp_2;
    if (temp_2 == 0) {
        var_19 = 0;
    } else {
        var_19 = 0;
        var_17 = DListGetCountPow2_42ea70(arg0 + 0x20);
        while (var_17 > 0) {
            var_17 = var_17 >> 1;
            temp_2_2 = DListNodeAdvance_42eb00(var_18, var_17);
            if (temp_2_2 != 0) {
                temp_2_3 = IntCompare_42ca30(temp_22, CharaGetId_214a80(temp_2_2 + 0x10));
                if (temp_2_3 == 0) {
                    var_19 = temp_2_2;
                    break;
                } else {
                    if (temp_2_3 > 0) {
                        var_18 = temp_2_2;
                    }
                }
            }
        }
    }
    if (var_19 == 0) {
        temp_16 = *(s32 *)(arg0 + 0x3C);
        if (!(arg1 != 0 && temp_16 != 0)) {
            res = 0;
        } else {
            var_19 = MemStackHeapAllocBack_14dcf0(temp_16, AlignUp16_1cacd0(0xB80) >> 4);
            if ((var_19 != 0) && (DListNodeInit_42ec10(var_19), CharaInit_2150c0(var_19 + 0x10), (CharaInitFromData_215050(var_19 + 0x10, var_19, arg1) != 0)) &&
                ((L2341 *)(arg0 + 0x20))->add(var_19) != 0) {
                res = var_19;
            } else {
                MemStackHeapFree_14dcb0(temp_16, var_19);
                res = 0;
            }
        }
        var_19 = res;
    }
    if (var_19 == 0) {
        return 0;
    }
    return var_19 + 0x10;
}

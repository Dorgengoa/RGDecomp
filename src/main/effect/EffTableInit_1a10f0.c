#include "types.h"
#pragma opt_common_subs off

extern s32 OperatorNewArray_100900(s32);
extern void MemStackRefCountInc_14d7e0(s32);
extern void EffTableRelease_1a0fd0(void);
extern void EffTableSetSubHeapMaybe_1a10a0(void *, s32);

void EffTableInit_1a10f0(void *arg0, void *arg1)
{
    s32 temp_2;
    s32 temp_3;
    s32 temp_4;
    s32 temp_4_2;
    s32 var_17;
    s32 var_5;

    EffTableRelease_1a0fd0();
    temp_4 = *(s32 *)((u8 *)arg1 + 0);
    var_17 = *(s32 *)((u8 *)arg1 + 4);
    if (temp_4 != 0) {
        if (var_17 == 0) {
            var_17 = temp_4;
        }
        *(s32 *)((u8 *)arg0 + 8) = temp_4;
        MemStackRefCountInc_14d7e0(temp_4);
        EffTableSetSubHeapMaybe_1a10a0(arg0, var_17);
        temp_2 = *(s32 *)((u8 *)arg1 + 8);
        temp_3 = *(s32 *)((u8 *)arg1 + 0xC);
        *(s32 *)((u8 *)arg0 + 0x110) = temp_3;
        if (temp_3 > 0) {
            *(s32 *)((u8 *)arg0 + 0x114) = temp_2;
            temp_2 = OperatorNewArray_100900(*(s32 *)((u8 *)arg0 + 0x110) * 4);
            *(s32 *)((u8 *)arg0 + 0x118) = temp_2;
            if (temp_2 != 0) {
                var_5 = 0;
                while (var_5 < *(s32 *)((u8 *)arg0 + 0x110)) {
                    temp_4_2 = var_5 * 4;
                    var_5 += 1;
                    *(s32 *)(*(u8 **)((u8 *)arg0 + 0x118) + temp_4_2) = 0;
                    continue;
                }
            }
        }
    }
}

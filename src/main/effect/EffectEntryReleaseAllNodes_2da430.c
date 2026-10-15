#include "types.h"

extern void EffectEntryReleaseNode_2da6c0(void *, s32);

void EffectEntryReleaseAllNodes_2da430(u8 *arg0)
{
    u8 *temp_3;
    u8 *temp_3_2;
    s32 *var_4;
    s32 temp_5;

    if (*(void **)(arg0 + 4) == NULL) {
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    for (;;) {
        temp_3 = *(u8 **)(arg0 + 4);
        if (temp_3 == NULL) {
            var_4 = NULL;
        } else {
            var_4 = (s32 *)(temp_3 + 0x10);
            temp_3_2 = *(u8 **)temp_3;
            *(void **)(arg0 + 4) = temp_3_2;
            if (temp_3_2 == NULL) {
                *(s32 *)(arg0 + 8) = 1;
            }
        }
        if (var_4 != NULL) {
            temp_5 = *var_4;
            if (temp_5 != 0) {
                EffectEntryReleaseNode_2da6c0(arg0, temp_5);
            }
            continue;
        }
        break;
    }
    *(void **)(arg0 + 4) = NULL;
    *(s32 *)(arg0 + 8) = 0;
    *(s32 *)(arg0 + 0xAC) = 0;
}

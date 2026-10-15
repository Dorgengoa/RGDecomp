#include "types.h"

void *EffectEntryFindNodeByUid_2da0c0(u8 *arg0, s32 arg1)
{
    u8 *temp_2;
    u8 *temp_2_2;
    u8 **var_3;
    void *temp_2_3;

    if (*(void **)(arg0 + 4) == NULL) {
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    for (;;) {
        temp_2 = *(u8 **)(arg0 + 4);
        if (temp_2 == NULL) {
            var_3 = NULL;
        } else {
            var_3 = (u8 **)(temp_2 + 0x10);
            temp_2_2 = *(u8 **)temp_2;
            *(void **)(arg0 + 4) = temp_2_2;
            if (temp_2_2 == NULL) {
                *(s32 *)(arg0 + 8) = 1;
            }
        }
        if (var_3 != NULL) {
            temp_2_3 = *var_3;
            if ((temp_2_3 != NULL) && (arg1 == *(s32 *)((u8 *)temp_2_3 + 0xC))) {
                *(void **)(arg0 + 4) = NULL;
                *(s32 *)(arg0 + 8) = 0;
                return *var_3;
            }
            continue;
        }
        *(void **)(arg0 + 4) = NULL;
        *(s32 *)(arg0 + 8) = 0;
        return NULL;
    }
}

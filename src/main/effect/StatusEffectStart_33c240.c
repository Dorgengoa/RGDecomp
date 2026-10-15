#include "types.h"
#pragma opt_dead_code off

extern void StatusEffectSlotSetup_33d080(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void StatusEffectStart_33c240(s32 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *cur;
    void *found;
    s32 idx;

    found = NULL;
    for (idx = 0; idx < 0x10; idx++) {
        cur = (void *)*arg0;
        cur = (u8 *)cur + idx * 0xE0;
        if (*(s16 *)((u8 *)cur + 0x10) == 0) {
            found = cur;
            break;
        }
    }
    if (found != NULL) {
        StatusEffectSlotSetup_33d080(found, arg2, arg1, arg3);
    }
}

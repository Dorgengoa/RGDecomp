#include "types.h"
#pragma opt_common_subs off

extern s32 EffectInstanceSetParamFloat_2dd6b0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void EffectEntryNodeSetParamFloat_2d9f10(void *arg0, void *arg1, s32 arg2) {
    void *cur;
    void *next;
    void **slot;
    void *payload;
    s32 id;

    if (*(void **)((u8 *)arg0 + 4) == NULL) {
        *(void **)((u8 *)arg0 + 4) = *(void **)((u8 *)arg0 + 0);
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    for (;;) {
        cur = *(void **)((u8 *)arg0 + 4);
        if (cur == NULL) {
            slot = NULL;
        } else {
            slot = (void **)((u8 *)cur + 0x10);
            next = *(void **)cur;
            *(void **)((u8 *)arg0 + 4) = next;
            if (next == NULL) {
                *(s32 *)((u8 *)arg0 + 8) = 1;
            }
        }
        if (slot != NULL) {
            payload = *slot;
            if ((payload != NULL) && (id = *(s32 *)((u8 *)payload + 8), (*(s32 *)((u8 *)arg1 + 0x10) == id)) && (arg2 >= 0) && (arg2 < 0x10)) {
                EffectInstanceSetParamFloat_2dd6b0(payload, arg2, arg2, id);
            } else {
                continue;
            }
        }
        break;
    }
    *(void **)((u8 *)arg0 + 4) = NULL;
    *(s32 *)((u8 *)arg0 + 8) = 0;
}

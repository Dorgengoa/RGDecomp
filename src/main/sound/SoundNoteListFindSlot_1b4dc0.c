#include "types.h"

typedef struct {
    s32 unk0;
    u8 *unk4;
} T1b4dc0_arg0;

s32 *SoundNoteListFindSlot_1b4dc0(T1b4dc0_arg0 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *temp_8;
    s32 *var_2;
    s32 temp_11;
    s32 i;
    s32 j;

    if (*(s32 *)((u8 *)arg0 + 4) == 0) {
        return NULL;
    }
    *arg1 = 0;
    var_2 = NULL;
    temp_11 = arg0->unk0;
    for (i = 0; i < temp_11; i++) {
        temp_8 = (s32 *)arg0->unk4;
        temp_8 = (s32 *)((u8 *)temp_8 + i * 0x14);
        if (*temp_8 < 0) {
            var_2 = temp_8;
            break;
        }
    }
    if (arg2 >= 0) {
        for (j = 0; j < (s32)(u32)temp_11; j++) {
            temp_8 = (s32 *)arg0->unk4;
            temp_8 = (s32 *)((u8 *)temp_8 + j * 0x14);
            if (*temp_8 >= 0 && arg2 == *temp_8 && arg3 == *(s16 *)((u8 *)temp_8 + 8)) {
                *arg1 = 1;
                return (s32 *)(arg0->unk4 + (j * 0x14));
            }
        }
    }
    return var_2;
}

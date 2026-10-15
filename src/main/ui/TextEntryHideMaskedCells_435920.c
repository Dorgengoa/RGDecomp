#include "types.h"

extern void *UiFindWidget_290460(s32, s32);

s32 TextEntryHideMaskedCells_435920(s32 *arg0) {
    u8 *var_10;
    void *temp_2;
    s8 temp_2_2;
    s8 *var_9;
    s32 var_8;
    s32 temp_4;

    temp_4 = *arg0;
    if (temp_4 != 0) {
    temp_2 = UiFindWidget_290460(temp_4, 0xE);
    if (temp_2 == NULL) {
        return 1;
    }
    var_10 = *(u8 **)((u8 *)temp_2 + 0x20);
    if (var_10 == NULL) {
        return 2;
    }
    var_9 = (s8 *)arg0 + 0x197;
    if (var_9 == NULL) {
        return 3;
    }
    var_8 = 0;
    do {
        temp_2_2 = *var_9;
        if (temp_2_2 == 0x5F || temp_2_2 == 0x2E) {
            *(s16 *)((u8 *)var_10 + 0xE) = 0;
            *(s16 *)((u8 *)var_10 + 6) = 0;
            *(s16 *)((u8 *)var_10 + 0xC) = 0;
            *(s16 *)((u8 *)var_10 + 4) = 0;
        } else {
            *(s16 *)((u8 *)var_10 + 4) = 0xE;
            *(s16 *)((u8 *)var_10 + 0xC) = 0x12;
            *(s16 *)((u8 *)var_10 + 0xE) = 6;
            *(s16 *)((u8 *)var_10 + 6) = 6;
        }
        var_8 += 1;
        var_9 += 1;
        var_10 += 0x20;
    } while (var_8 < 0xAE);
    }
    return 0;
}

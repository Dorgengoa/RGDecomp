#include "types.h"
#pragma optimization_level 3

extern void MesWinClose_2774f0(s32, void *, s32);

typedef struct {
    void *unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
} T24f4e0_arg0;

void EventVoiceListClear_24f4e0(T24f4e0_arg0 *arg0) {
    u8 *var_5_2;
    s32 temp_4;
    s32 var_5;
    s32 var_6;

    if (arg0->unk4 != NULL) {
        var_5 = -1;
    } else {
        var_5 = 0;
        arg0->unk4 = arg0->unk0;
        arg0->unk8 = 0;
    }
    if (var_5 == 0) {
        do {
            var_5_2 = arg0->unk4;
            if (var_5_2 == NULL) {
                var_6 = 0;
            } else {
                var_6 = (s32)(var_5_2 + 0x10);
                var_5_2 = *(u8 **)var_5_2;
                arg0->unk4 = var_5_2;
                if (var_5_2 == NULL) {
                    arg0->unk8 = 1;
                }
            }
        } while (var_6 != 0);
        arg0->unk4 = NULL;
        arg0->unk8 = 0;
        arg0->unk0 = NULL;
        arg0->unk4 = NULL;
        arg0->unk8 = 0;
        temp_4 = arg0->unkC;
        if (temp_4 != 0) {
            MesWinClose_2774f0(temp_4, var_5_2, var_6);
        }
    }
}

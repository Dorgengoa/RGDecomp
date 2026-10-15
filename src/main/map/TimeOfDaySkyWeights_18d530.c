#include "types.h"

extern void TimeOfDayPhaseWeights_18d630(s32, void *);
extern f32 TimeOfDayGetHour_18d920(void);
extern f32 D_0047E070;

typedef struct {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    s32 unkC;
} S;

void TimeOfDaySkyWeights_18d530(s32 arg0, S *arg1) {
    f32 temp_f0;
    f32 temp_f20;

    temp_f20 = TimeOfDayGetHour_18d920();
    TimeOfDayPhaseWeights_18d630(arg0, (void *)arg1);
    if (temp_f20 < D_0047E070) {
        if (temp_f20 <= (D_0047E070 - 2.0f)) {
            goto check3;
        }
        arg1->unk8 = 0.0f;
        arg1->unkC = 0;
        goto after_outer;
check3:
        temp_f0 = D_0047E070 - 3.0f;
        if (!(temp_f20 <= temp_f0)) {
            arg1->unk8 = 1.0f - (temp_f20 - temp_f0);
        }
after_outer:;
    }
    if (!(arg1->unk8 <= 0.0f)) {
        *(f32 *)&arg1->unkC = 0.0f;
        arg1->unk4 = 0.0f;
    }
}

#include "types.h"

extern void *ParamTableGetRec_1cfbc0(void);

void ParamTableStepFade_1cfa70(void) {
    f32 temp_f0;
    u8 *temp_2;

    temp_2 = (u8 *)ParamTableGetRec_1cfbc0();
    if (temp_2 != NULL) {
        *(f32 *)(temp_2 + 4) += *(f32 *)(temp_2 + 8);
        temp_f0 = *(f32 *)(temp_2 + 4);
        if (temp_f0 <= 0.0f) {
            if (*(f32 *)(temp_2 + 8) < 0.0f) {
                *(f32 *)(temp_2 + 8) = 0.0f;
            }
            *(f32 *)(temp_2 + 4) = 0.0f;
        }
        if (!(*(f32 *)(temp_2 + 4) < 1.0f)) {
            if (!(*(f32 *)(temp_2 + 8) <= 0.0f)) {
                *(f32 *)(temp_2 + 8) = 0.0f;
            }
            *(f32 *)(temp_2 + 4) = 1.0f;
        }
    }
}

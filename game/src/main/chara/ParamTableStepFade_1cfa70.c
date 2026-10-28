/* rgp:protos */
#define RGP_SELF_ParamTableStepFade_1cfa70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void ParamTableStepFade_1cfa70(void *rgp_a0, int rgp_a1) {
    f32 temp_f0;
    u8 *temp_2;

    temp_2 = (u8 *)ParamTableGetRec_1cfbc0((void *)rgp_a0, (int)rgp_a1);
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

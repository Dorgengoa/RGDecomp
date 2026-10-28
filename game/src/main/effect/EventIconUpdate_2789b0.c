/* rgp:protos */
#define RGP_SELF_EventIconUpdate_2789b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D7C4;
extern f32 D_0047D7CC;

void EventIconUpdate_2789b0(u8 *arg0) {
    f32 temp_f1;
    f32 temp_f1_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_3_3;
    s32 var_17;
    u8 *temp_16;

    if (*(s32 *)(arg0 + 0x404) != 0) {
        var_17 = 0;
        do {
            temp_16 = arg0 + (var_17 << 6);
            if (!(*(s32 *)(temp_16 + 0x28) < 0) != 0) {
                temp_3 = *(s32 *)(temp_16 + 0x2C);
                if (temp_3 > 0) {
                    temp_3_3 = temp_3 - 1;
                    *(s32 *)(temp_16 + 0x2C) = temp_3_3;
                    if (temp_3_3 == 0) {
                        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 0x20, 0, 1.0f);
                    }
                } else {
                    VecAdd_13be20(temp_16, temp_16, temp_16 + 0x10);
                    *(f32 *)(temp_16 + 0x14) = *(f32 *)(temp_16 + 0x14) - D_0047D7C4;
                    if (*(s32 *)(temp_16 + 0x38) != 0) {
                        temp_f1 = *(f32 *)(temp_16 + 0x34);
                        if (!(temp_f1 <= *(f32 *)(temp_16 + 4))) {
                            *(f32 *)(temp_16 + 4) = temp_f1;
                            *(f32 *)(temp_16 + 0x14) = *(f32 *)(temp_16 + 0x14) * -0.5f;
                        }
                    } else {
                        if (*(f32 *)(temp_16 + 0x34) < *(f32 *)(temp_16 + 4)) {
                            *(s32 *)(temp_16 + 0x38) = 1;
                        }
                    }
                    temp_f1_2 = *(f32 *)(temp_16 + 0x24);
                    if (temp_f1_2 < 1.0f) {
                        *(f32 *)(temp_16 + 0x24) = temp_f1_2 + D_0047D7CC;
                    }
                    temp_3_2 = *(s32 *)(temp_16 + 0x30) - 1;
                    *(s32 *)(temp_16 + 0x30) = temp_3_2;
                    if (temp_3_2 == 0) {
                        *(s32 *)(temp_16 + 0x28) = -1;
                        *(u32 *)(temp_16 + 0x20) = 0x3F800000;
                        *(f32 *)(temp_16 + 0x24) = 1.0f;
                        *(u128 *)(temp_16 + 0) = 0;
                        *(u128 *)(temp_16 + 0x10) = 0;
                        *(s32 *)(temp_16 + 0x2C) = 0;
                        *(s32 *)(temp_16 + 0x30) = 0x2D;
                        *(f32 *)(temp_16 + 0x34) = 0.0f;
                        *(s32 *)(temp_16 + 0x38) = 0;
                    }
                }
            }
            var_17 += 1;
        } while (var_17 < 0x10);
    }
}

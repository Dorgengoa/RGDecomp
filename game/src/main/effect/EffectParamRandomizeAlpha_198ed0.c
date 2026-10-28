/* rgp:protos */
#define RGP_SELF_EffectParamRandomizeAlpha_198ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern f32 D_0047D420;

void EffectParamRandomizeAlpha_198ed0(void *arg0, void *arg1) {
    f32 var_f0;
    s32 temp_4;

    temp_4 = *(s32 *)((u8 *)arg0 + 0x10);
    if (temp_4 <= 0) {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20);
    } else if (temp_4 == 1) {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20) +
                 *(f32 *)((u8 *)arg0 + 0x30) *
                     (2.0f * (RandFloat_1980f0((u8 *)arg1 + 4) - 0.5f));
    } else if (temp_4 == 2) {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20) +
                 *(f32 *)((u8 *)arg0 + 0x30) *
                     (D_0047D420 * RandGaussian_197d70((u8 *)arg1 + 4));
    } else {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20);
    }
    *(f32 *)((u8 *)arg1 + 0x4C) = var_f0;
}

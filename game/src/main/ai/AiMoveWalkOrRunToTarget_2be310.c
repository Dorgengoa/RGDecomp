/* rgp:protos */
#define RGP_SELF_AiMoveWalkOrRunToTarget_2be310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D85C;

void AiMoveWalkOrRunToTarget_2be310(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, f32 fparg0)
{
    u8 sp60[0x10] __attribute__((aligned(16)));
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f20_5;
    f32 temp_f21;
    f32 var_f0;
    f32 var_f12_2;
    s32 temp_16;

    temp_16 = *arg1;
    CharaGetPos_2388a0(temp_16, sp60);
    temp_f21 = (VecDistXZ_1cb3f0(arg2, sp60) - CharaGetCollRadius_2386a0(temp_16)) - fparg0;
    AiSetSpeedScale_2c0ec0(arg0, 1.0f);
    if (GetGameMode_1f59c0() == 6) {
        AiSetSpeedCapScale_2c0eb0(arg0, 0.125f);
    } else {
        AiSetSpeedCapScale_2c0eb0(arg0, 1.0f);
    }
    if (!(temp_f21 < AiGetStopDistance_2c0fb0(arg0))) {
        CharaAddFlags_212460(temp_16, (long long)(1));
        if ((GetGameMode_1f59c0() == 6) && !(temp_f21 < AiGetRunDistance_2c0fa0(arg0))) {
            CharaAddFlags_212460(temp_16, (long long)(2));
            temp_f20_2 = AiGetKeepDistanceMaybe_2c0f90(arg0);
            temp_f20_3 = temp_f20_2 - AiGetRunDistance_2c0fa0(arg0);
            var_f12_2 = (temp_f21 - AiGetRunDistance_2c0fa0(arg0)) / temp_f20_3;
            if (var_f12_2 < 0.0f) {
                var_f12_2 = 0.0f;
            }
            var_f12_2 = var_f12_2 + 0.5f;
            var_f0 = D_0047D85C;
            if (!(var_f12_2 <= var_f0)) {
                goto block_15;
            }
        } else {
            temp_f20_4 = AiGetRunDistance_2c0fa0(arg0);
            temp_f20_5 = temp_f20_4 - AiGetStopDistance_2c0fb0(arg0);
            var_f12_2 = (temp_f21 - AiGetStopDistance_2c0fb0(arg0)) / temp_f20_5;
            if (var_f12_2 < 0.0f) {
                var_f12_2 = 0.0f;
            }
            var_f12_2 = var_f12_2 + 0.5f;
            var_f0 = 1.0f;
            if (!(var_f12_2 <= 1.0f)) {
block_15:
                var_f12_2 = var_f0;
            }
        }
        AiSetSpeedScale_2c0ec0(arg0, var_f12_2);
    }
    if (!(VecLengthSqXZ_1cb450(arg3, 0) <= 0.0f)) {
        CharaSetDirNormalizedMaybe_213b30(temp_16, arg3);
        CharaSetMoveDirMaybe_213b00(temp_16, arg3);
    }
}

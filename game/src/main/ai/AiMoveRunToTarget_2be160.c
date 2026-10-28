/* rgp:protos */
#define RGP_SELF_AiMoveRunToTarget_2be160 1
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
extern f32 D_0047D85C;

void AiMoveRunToTarget_2be160(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, f32 fparg0)
{
    s32 buf[4] __attribute__((aligned(16)));
    f32 d;
    f32 range;
    f32 t;
    s32 h;

    h = *arg1;
    CharaGetPos_2388a0(h, buf);
    d = VecDistXZ_1cb3f0(arg2, buf) - CharaGetCollRadius_2386a0(h) - fparg0;
    AiSetSpeedScale_2c0ec0(arg0, 1.0f);
    AiSetSpeedCapScale_2c0eb0(arg0, 0.125f);
    if (!(d < AiGetStopDistance_2c0fb0(arg0))) {
        CharaAddFlags_212460(h, (long long)(1));
        CharaAddFlags_212460(h, (long long)(2));
        range = AiGetKeepDistanceMaybe_2c0f90(arg0) - AiGetStopDistance_2c0fb0(arg0);
        t = (d - AiGetStopDistance_2c0fb0(arg0)) / range;
        if (t < 0.0f) {
            t = 0.0f;
        }
        t += 0.25f;
        if (!(t <= D_0047D85C)) {
            t = D_0047D85C;
        }
        AiSetSpeedScale_2c0ec0(arg0, t);
    }
    if (!(VecLengthSqXZ_1cb450(arg3, 0) <= 0.0f)) {
        CharaSetDirNormalizedMaybe_213b30(h, arg3);
        CharaSetMoveDirMaybe_213b00(h, arg3);
    }
}

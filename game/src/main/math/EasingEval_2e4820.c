/* rgp:protos */
#define RGP_SELF_EasingEval_2e4820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern f32 D_0047D1FC;

f32 EasingEval_2e4820(s32 arg0, f32 x) {
    f32 t;

    switch (arg0 & 0xF) {
    case 1:
        return x * x;
    case 2:
        t = 1.0f - x;
        return 1.0f - t * t;
    case 3:
        if (x < 0.5f) {
            return 2.0f * (x * x);
        } else {
            t = 1.0f - x;
            return 1.0f - 2.0f * (t * t);
        }
    case 4:
        if (x < 0.5f) {
            t = x - 0.5f;
            t = 0.5f + -2.0f * (t * t);
        } else {
            t = x - 0.5f;
            t = 0.5f + 2.0f * (t * t);
        }
        return t;
    case 5:
        t = x - 0.5f;
        return 1.0f + -4.0f * (t * t);
    case 6:
        return 0.5f * (1.0f - Cosf_128d30(D_0047D1FC * x));
    case 0:
    default:
        return x;
    }
}

/* rgp:protos */
#define RGP_SELF_LetterboxSetFade_277ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

int LetterboxSetFade_277ea0(f32 *out, f32 a, f32 b, f32 c)
{ int rgp_v0 = 0;
    void *p;
    s32 n;
    s32 m;
    f32 t;

    if ((rgp_v0 = SysModeMsgIsKeyCapWarpStartMaybe_27bc40()) != 0) {
        return rgp_v0;
    }
    if (b <= 1.0f) {
        b = 1.0f;
    }
    if (a < 0.0f) {
        a = 0.0f;
    }
    if (a > 1.0f) {
        a = 1.0f;
    }
    p = GetDrawCtx_15de80();
    n = DrawEnvGetWidth_1451e0(p);
    m = (rgp_v0 = DrawEnvGetHeight_1451d0(p));
    t = 0.5f * ((f32)m - 63.0f * (f32)n / 96.0f);
    out[0] = t - c;
    out[1] = c + t;
    out[4] = a;
    out[2] = (a - out[3]) / b;
return rgp_v0; }

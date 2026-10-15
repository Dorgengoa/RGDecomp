#include "types.h"

extern s32 SysModeMsgIsKeyCapWarpStartMaybe_27bc40(f32 *);
extern void *GetDrawCtx_15de80(void);
extern s32 DrawEnvGetWidth_1451e0(void *);
extern s32 DrawEnvGetHeight_1451d0(void *);

void LetterboxSetFade_277ea0(f32 *out, f32 a, f32 b, f32 c)
{
    void *p;
    s32 n;
    s32 m;
    f32 t;

    if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40(out) != 0) {
        return;
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
    m = DrawEnvGetHeight_1451d0(p);
    t = 0.5f * ((f32)m - 63.0f * (f32)n / 96.0f);
    out[0] = t - c;
    out[1] = c + t;
    out[4] = a;
    out[2] = (a - out[3]) / b;
}

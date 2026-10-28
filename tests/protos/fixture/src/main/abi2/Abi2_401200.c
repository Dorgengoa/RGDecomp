#include "types.h"
/* 2026-10-18 rules (docs/PROTOS.md "Rules added 2026-10-18").
   ee-round-floor: AngleWrap_1cbf30's `(t + 12582912.0f) - 12582912.0f`; the EE FPU
   rounds toward zero (floor for these t), SSE to nearest.
   def-v0-return: insect_InsectBattleIsSideAi_4f1950 shape: a void def whose two
   branches each tail-call a value function; its caller reads the value.
   u128-view: U128Id_401340 returns s32; its caller's view said u128.
   ee-round-floor control value: AngleWrapT_401200(0.006f) == 0.006f. */

f32 AngleWrapT_401200(f32 x)
{
    f32 t;
    f32 s;

    s = (x < 0.0f) ? -1.0f : 1.0f;
    t = 0.5f + ((x < 0.0f) ? -x : x) / 6.2831855f;
    t = (t + 12582912.0f) - 12582912.0f;
    return x - (6.2831855f * s) * t;
}

s32 V0Flag_401280(s32 *o, s32 k)
{
    return o[k];
}

void V0Pick_4012c0(s32 *o, s32 f)
{
    if (f == 0) {
        V0Flag_401280(o, 0);
    } else {
        V0Flag_401280(o, 1);
    }
}

/* MapGetNorthAngle_1e36b0 shape: `G(..); return;` early exit, then G(..) at the end */
void V0Early_401300(s32 *o, s32 f)
{
    if (f != 0) {
        V0Flag_401280(o, 1);
        return;
    }
    V0Flag_401280(o, 0);
}

s32 U128Id_401340(s32 *p)
{
    return p[2];
}

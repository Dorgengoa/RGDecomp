/* rgp:protos */
#define RGP_SELF_AngleWrap_1cbf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D290;

f32 AngleWrap_1cbf30(f32 fparg0)
{
    f32 spC;
    s32 sp8;
    f32 f3;
    f32 t;
    f32 y;

    spC = fparg0;
    sp8 = ((*(s32 *)&spC) & 0x80000000) | 0x3F800000;
    if (fparg0 < 0.0f) {
        f3 = -fparg0;
    } else {
        f3 = fparg0;
    }
    t = 0.5f + f3 / D_0047D290;
    t = __builtin_floorf(t);
    y = D_0047D290 * (*(f32 *)&sp8);
    return fparg0 - y * t;
}

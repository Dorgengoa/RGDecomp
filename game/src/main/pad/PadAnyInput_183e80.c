/* rgp:protos */
#define RGP_SELF_PadAnyInput_183e80 1
#define RGP_SELF_axis 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
/* PARK (round 1): length 0x188 vs retail 0x1C8, large gap. */
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

static inline s32 axis(s32 v, s32 d)
{
    s32 t;

    t = v - 0x80;
    if (t < 0x32 && t > -0x32) {
        return 0;
    }
    if (t > 0) {
        t = ((t - 0x31) << 7) / d;
    } else {
        t = ((t + 0x32) << 7) / d;
    }
    return t;
}

s32 PadAnyInput_183e80(void *arg0)
{
    return axis(S32(arg0, 8), 78) | (axis(S32(arg0, 0xC), 78) | (S32(arg0, 4) | axis(S32(arg0, 0x14), 78) | axis(S32(arg0, 0x10), 78)));
}

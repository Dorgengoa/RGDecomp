#pragma opt_dead_assignments off
#include "types.h"
#pragma divbyzerocheck on

extern f32 Sinf_128fd0(f32 arg0);
extern s32 Rand_133710(void);
extern f32 D_0047D248;
extern f32 D_0047D5B8;
extern f32 D_0047D5D4;

static inline f32 mul(f32 a, f32 b)
{
    return a * b;
}

f32 LightFlickerScale_18e2c0(u8 *o, s32 t)
{
    s32 type;
    s32 period;
    f32 amp;

    type = *(s32 *)(o + 0x40);
    period = (s32)*(f32 *)(o + 0x94);
    amp = *(f32 *)(o + 0x90);
    switch (type) {
    case 4:
        switch (*(s32 *)(o + 0x8C)) {
        case 0:
            return 1.0f;
        case 1:
            return mul(1.0f, (1.0f - amp) + (amp * (f32)Rand_133710()) / 2147483648.0f);
        case 2:
            if (period > 0) {
                return mul(1.0f, 1.0f - (0.5f * amp) * (1.0f + Sinf_128fd0((D_0047D5D4 * (f32)(t % period)) / (f32)period)));
            }
            return 1.0f;
        case 3:
            if (period > 0) {
                return mul(1.0f, 1.0f - (amp * (f32)(t % period)) / (f32)period);
            }
            return 1.0f;
        }
        break;
    case 2:
    case 3:
        return D_0047D248 + (D_0047D5B8 * (f32)Rand_133710()) / 2147483648.0f;
    }
    return 1.0f;
}

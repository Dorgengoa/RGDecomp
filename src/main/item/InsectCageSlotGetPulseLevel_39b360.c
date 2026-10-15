#include "types.h"

typedef struct { u8 pad[0x2C]; s32 f2C; } T_0039b360;

extern f32 D_0047D1FC;
extern f32 Sinf_128fd0(f32);

f32 InsectCageSlotGetPulseLevel_39b360(T_0039b360 *p)
{
    s32 n;
    f32 r;

    r = 1.0f;
    n = p->f2C;
    if (n < 0x9C4) {
        r = 1.0f - Sinf_128fd0(D_0047D1FC * ((f32)n / 100.0f / 25.0f));
        if (r > 1.0f) r = 1.0f;
    }
    return r;
}

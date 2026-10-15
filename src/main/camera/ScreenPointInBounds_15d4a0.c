#include "types.h"

typedef struct { u8 pad[0x14]; f32 f14, f18; } Q_0015d4a0;

extern void *D_004810A4;

s32 ScreenPointInBounds_15d4a0(f32 *p)
{
    void *g;
    Q_0015d4a0 *q;
    f32 x;
    f32 y;

    g = D_004810A4;
    g = (g == 0) ? 0 : *(void **)((s32)g + 0xF20);
    q = (Q_0015d4a0 *)((s32)g + 0x14);
    x = p[0];
    if (x >= 0.0f) {
        if (x <= 16.0f * q->f14) goto ok;
    }
    return 0;
ok:
    y = p[1];
    if (y < 0.0f) goto fail;
    if (y <= 16.0f * q->f18) goto one;
    return 0;
one:
    return 1;
fail:
    return 0;
}

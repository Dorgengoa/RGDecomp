#include "types.h"

extern void TargetRefSetModelFrame_2e6560(u8 *p, void *a, void *b, void *c, f32 t);

void SwordTrailSetEndRef_2159b0(u8 *base, s32 i, void *a, void *b, void *c)
{
    if (i < 0 || i >= 2) return;
    TargetRefSetModelFrame_2e6560(base + i * 48 + 0x30, a, b, c, 0.0f);
}

#include "types.h"

void HpGaugeSetSlotAlpha_31e350(void *p, s32 i, f32 v)
{
    if (i >= 0x10) i = 0xF;
    if (v >= 2.0f) v = 2.0f;
    if (v <= 0.0f) v = 0.0f;
    *(f32 *)(i * 4 - (0 - (s32)p) + 0x180) = v;
}

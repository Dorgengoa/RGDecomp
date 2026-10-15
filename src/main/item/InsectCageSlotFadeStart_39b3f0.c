#include "types.h"

struct T39B3F0 { u8 pad000[0x24]; f32 f24; f32 f28; };

extern void InsectCageSlotSetFadeLevel_39b450(struct T39B3F0 *p, f32 x);

void InsectCageSlotFadeStart_39b3f0(struct T39B3F0 *p, s32 n)
{
    if (n <= 0) {
        InsectCageSlotSetFadeLevel_39b450(p, 1.0f);
        return;
    }
    p->f28 = (1.0f - p->f24) / (f32)n;
}

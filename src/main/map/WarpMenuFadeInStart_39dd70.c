#include "types.h"

struct T39DD70 { u8 pad000[0x28]; f32 f28; f32 f2C; };

extern void WarpMenuFadeReset_39dd10(struct T39DD70 *p, f32 x);

void WarpMenuFadeInStart_39dd70(struct T39DD70 *p, f32 x)
{
    if (x <= 0.0f) {
        WarpMenuFadeReset_39dd10(p, 1.0f);
        return;
    }
    p->f2C = (1.0f - p->f28) / x;
}

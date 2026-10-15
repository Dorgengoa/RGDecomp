#include "types.h"

struct T32AB40 { u8 pad000[0xDC]; f32 fDC; f32 fE0; s32 fE4; f32 fE8; };

extern f32 MinimapGetDrawAlpha_32a180(struct T32AB40 *p);

void MinimapStartCrossfade_32ab40(struct T32AB40 *p, f32 x)
{
    f32 r;

    p->fDC = MinimapGetDrawAlpha_32a180(p);
    p->fE4 = 0;
    r = 1.0f / x;
    p->fE0 = -r;
    p->fE8 = r;
}

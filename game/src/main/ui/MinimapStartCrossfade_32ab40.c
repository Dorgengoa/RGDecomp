/* rgp:protos */
#define RGP_SELF_MinimapStartCrossfade_32ab40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T32AB40 { u8 pad000[0xDC]; f32 fDC; f32 fE0; s32 fE4; f32 fE8; };

/*rgp*/

void MinimapStartCrossfade_32ab40(struct T32AB40 *p, f32 x)
{
    f32 r;

    p->fDC = MinimapGetDrawAlpha_32a180(p);
    p->fE4 = 0;
    r = 1.0f / x;
    p->fE0 = -r;
    p->fE8 = r;
}

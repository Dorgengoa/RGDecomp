/* rgp:protos */
#define RGP_SELF_ItemStackSetCount_3d3870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3D3870 { u8 pad000[0x14]; s16 f14; };

/*rgp*/

void ItemStackSetCount_3d3870(struct T3D3870 *p, s16 v)
{
    s32 r;

    p->f14 = v;
    if (v < 0) {
        p->f14 = 0;
        return;
    }
    r = ItemGetStackLimit_3d4480((void *)p);
    if (r < p->f14) {
        p->f14 = r;
    }
}

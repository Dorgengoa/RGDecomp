/* rgp:protos */
#define RGP_SELF_LightningMgrFadeBolts_2d6640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T2D6640 { u8 *f00; };

/*rgp*/

void LightningMgrFadeBolts_2d6640(struct T2D6640 *p)
{
    u8 *q;
    s32 i;

    q = p->f00;
    if (q == 0) return;
    for (i = 0; i < 0x40; i++) {
        LightningBoltFade_2d68e0(q);
        q += 0xD0;
    }
}

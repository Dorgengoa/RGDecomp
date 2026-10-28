/* rgp:protos */
#define RGP_SELF_MoviePlayerWaitTick_1d5810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1D5810 { u8 pad000[0x17900]; u8 f17900; };

/*rgp*/

void MoviePlayerWaitTick_1d5810(struct T1D5810 *p)
{
    s32 i;

    if (p->f17900 == 0) return;
    for (i = 0; i < 4; i++) {
        ThreadYield_1d2b70();
    }
}

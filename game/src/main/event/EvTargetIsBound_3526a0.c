/* rgp:protos */
#define RGP_SELF_EvTargetIsBound_3526a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3526A0 { u8 pad000[0x34]; s32 f34; };

/*rgp*/

s32 EvTargetIsBound_3526a0(struct T3526A0 *p)
{
    if (p->f34 == 0) {
        return 0;
    }
    return TargetRefIsActive_2e6f00(p);
}

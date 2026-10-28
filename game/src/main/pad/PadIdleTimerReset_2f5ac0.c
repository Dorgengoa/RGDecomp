/* rgp:protos */
#define RGP_SELF_PadIdleTimerReset_2f5ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the small-data s32 D_0048277C. */

extern s32 D_0048277C;

void PadIdleTimerReset_2f5ac0(void)
{
    D_0048277C = 0;
}

#include "types.h"

/* Zero the small-data s32 D_0048277C. */

extern s32 D_0048277C;

void PadIdleTimerReset_2f5ac0(void)
{
    D_0048277C = 0;
}

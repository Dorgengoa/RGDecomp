/* rgp:protos */
#define RGP_SELF_FrameCounterReset_1c6b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the small-data s64 D_00481630. */

extern s64 D_00481630;

void FrameCounterReset_1c6b10(void)
{
    D_00481630 = 0;
}

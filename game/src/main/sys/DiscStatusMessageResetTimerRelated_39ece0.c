/* rgp:protos */
#define RGP_SELF_DiscStatusMessageResetTimerRelated_39ece0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the small-data s16 D_004836E4. */

extern s16 D_004836E4;

void DiscStatusMessageResetTimerRelated_39ece0(void)
{
    D_004836E4 = 0;
}

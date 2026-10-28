/* rgp:protos */
#define RGP_SELF_LeaderSwitchMenuIsActive_39d200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_0048361C. */

extern u8 D_0048361C;

u8 LeaderSwitchMenuIsActive_39d200(void)
{
    return D_0048361C;
}

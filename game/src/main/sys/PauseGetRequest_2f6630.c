/* rgp:protos */
#define RGP_SELF_PauseGetRequest_2f6630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_00482778. */

extern u8 D_00482778;

u8 PauseGetRequest_2f6630(void)
{
    return D_00482778;
}

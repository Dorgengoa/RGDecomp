/* rgp:protos */
#define RGP_SELF_MovieIsStarted_1d5640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004817BC. */

extern u8 D_004817BC;

u8 MovieIsStarted_1d5640(void)
{
    return D_004817BC;
}

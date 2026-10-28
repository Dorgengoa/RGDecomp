/* rgp:protos */
#define RGP_SELF_ClearPad2Enabled_2882a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the small-data u8 D_004821BC. */

extern u8 D_004821BC;

void ClearPad2Enabled_2882a0(void)
{
    D_004821BC = 0;
}

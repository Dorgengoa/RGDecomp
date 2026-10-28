/* rgp:protos */
#define RGP_SELF_IsPad2Enabled_2882c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004821BC. */

extern u8 D_004821BC;

u32 IsPad2Enabled_2882c0(void)
{
    return (u8)(D_004821BC);
}

/* rgp:protos */
#define RGP_SELF_SaveIsBusy_376b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004831F0. */

extern u8 D_004831F0;

u8 SaveIsBusy_376b00(void)
{
    return D_004831F0;
}

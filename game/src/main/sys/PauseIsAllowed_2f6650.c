/* rgp:protos */
#define RGP_SELF_PauseIsAllowed_2f6650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_00482774. */

extern u8 D_00482774;

u8 PauseIsAllowed_2f6650(void)
{
    return D_00482774;
}

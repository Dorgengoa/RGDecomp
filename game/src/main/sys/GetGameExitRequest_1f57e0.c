/* rgp:protos */
#define RGP_SELF_GetGameExitRequest_1f57e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004819AC. */

extern u8 D_004819AC;

u8 GetGameExitRequest_1f57e0(void)
{
    return D_004819AC;
}

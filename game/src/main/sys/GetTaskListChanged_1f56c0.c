/* rgp:protos */
#define RGP_SELF_GetTaskListChanged_1f56c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004819B0. */

extern u8 D_004819B0;

u8 GetTaskListChanged_1f56c0(void)
{
    return D_004819B0;
}

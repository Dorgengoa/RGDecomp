/* rgp:protos */
#define RGP_SELF_GetDoorCursorObj_1fdb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_00481A58. */

extern s32 D_00481A58;

s32 GetDoorCursorObj_1fdb10(void)
{
    return D_00481A58;
}

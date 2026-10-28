/* rgp:protos */
#define RGP_SELF_GetGameData_1fede0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B8B30.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B8B30[];

void *GetGameData_1fede0(void)
{
    return D_004B8B30;
}

/* rgp:protos */
#define RGP_SELF_SysGetModeMsg_1c39b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004A3EF0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004A3EF0[];

void *SysGetModeMsg_1c39b0(void)
{
    return D_004A3EF0;
}

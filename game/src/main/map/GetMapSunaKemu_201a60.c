/* rgp:protos */
#define RGP_SELF_GetMapSunaKemu_201a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BB480.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB480[];

void *GetMapSunaKemu_201a60(void)
{
    return D_004BB480;
}

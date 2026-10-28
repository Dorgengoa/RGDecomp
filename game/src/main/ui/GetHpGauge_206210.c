/* rgp:protos */
#define RGP_SELF_GetHpGauge_206210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BC6C0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BC6C0[];

void *GetHpGauge_206210(void)
{
    return D_004BC6C0;
}

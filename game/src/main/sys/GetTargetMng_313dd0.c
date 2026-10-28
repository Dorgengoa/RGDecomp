/* rgp:protos */
#define RGP_SELF_GetTargetMng_313dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004E7E60.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E7E60[];

void *GetTargetMng_313dd0(void)
{
    return D_004E7E60;
}

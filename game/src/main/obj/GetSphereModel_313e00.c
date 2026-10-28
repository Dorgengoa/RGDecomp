/* rgp:protos */
#define RGP_SELF_GetSphereModel_313e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004E7BE0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E7BE0[];

void *GetSphereModel_313e00(void)
{
    return D_004E7BE0;
}

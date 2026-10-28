/* rgp:protos */
#define RGP_SELF_LocaleconvR_130998 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_00458000.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_00458000[];

void *LocaleconvR_130998(void)
{
    return D_00458000;
}

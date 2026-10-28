/* rgp:protos */
#define RGP_SELF_GetHpGaugeThin_206220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BC470.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BC470[];

void *GetHpGaugeThin_206220(void)
{
    return D_004BC470;
}

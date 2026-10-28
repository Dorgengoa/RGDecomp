/* rgp:protos */
#define RGP_SELF_MesItemNameTableDefault_277700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004D3980.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D3980[];

void *MesItemNameTableDefault_277700(void)
{
    return D_004D3980;
}

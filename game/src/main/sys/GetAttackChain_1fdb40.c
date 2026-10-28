/* rgp:protos */
#define RGP_SELF_GetAttackChain_1fdb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B86C0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B86C0[];

void *GetAttackChain_1fdb40(void)
{
    return D_004B86C0;
}

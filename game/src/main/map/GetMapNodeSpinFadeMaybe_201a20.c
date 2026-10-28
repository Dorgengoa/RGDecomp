/* rgp:protos */
#define RGP_SELF_GetMapNodeSpinFadeMaybe_201a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the small-data object D_00481B10.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_00481B10;

void *GetMapNodeSpinFadeMaybe_201a20(void)
{
    return &D_00481B10;
}

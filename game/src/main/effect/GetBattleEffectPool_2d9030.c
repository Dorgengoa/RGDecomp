/* rgp:protos */
#define RGP_SELF_GetBattleEffectPool_2d9030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the small-data object D_00482688.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_00482688;

void *GetBattleEffectPool_2d9030(void)
{
    return &D_00482688;
}

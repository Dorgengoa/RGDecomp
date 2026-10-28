/* rgp:protos */
#define RGP_SELF_InsectronEnemyTeamFindMaybe_3e8490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Tail value is TableFindFloorByKey_40b230's; the StateVarGet_3ccac0 result lands in argument
   three, so it is a named intermediate in the source. */

s32 InsectronEnemyTeamFindMaybe_3e8490(u8 *p, s32 a, s32 b)
{
    s32 r;

    r = ((short)StateVarGet_3ccac0(*(s32 *)(p + 0x10), 5));
    return ((s32)TableFindFloorByKey_40b230(*(s32 *)(*(u8 **)(p + 0x8) + 0xA0), a, r, b));
}

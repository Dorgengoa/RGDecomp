/* rgp:protos */
#define RGP_SELF_ItemWeaponIsKindOf_3d5c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ItemWeaponIsKindOf_3d5c10(s32 a, s32 b)
{
    if (b == 2) return 1;
    return b == 0;
}

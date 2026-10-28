/* rgp:protos */
#define RGP_SELF_CharaWeaponStateValidateMaybe_20a600 1
#include "port/game_protos.h"
#line 1
#include "types.h"
s32 CharaWeaponStateValidateMaybe_20a600(s32 p0)
{
    if (p0 == 3) {
        goto ok;
    }
    if (p0 == 2) {
        goto ok;
    }
    if (p0 == 1) {
        goto ok;
    }
    if (p0 == 0) {
        goto ok;
    }
    return -1;
ok:
    return p0;
}

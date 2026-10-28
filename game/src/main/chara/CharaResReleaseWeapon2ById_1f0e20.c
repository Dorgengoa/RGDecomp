/* rgp:protos */
#define RGP_SELF_CharaResReleaseWeapon2ById_1f0e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of ActCfgTableRunEvntByName_21f680 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

void CharaResReleaseWeapon2ById_1f0e20(void *self, void *arg, void *key)
{
    void *found;

    found = CharaResFindById_1efba0(self, key);
    if (found != 0) {
        CharaResReleaseWeapon2_1f2f90(found, arg);
    }
}

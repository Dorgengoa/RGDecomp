/* rgp:protos */
#define RGP_SELF_CharaResReleaseWeapon1ById_1f0e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of ActCfgTableRunEvntByName_21f680 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

void CharaResReleaseWeapon1ById_1f0e60(void *self, void *arg, void *key)
{
    void *found;

    found = CharaResFindById_1efba0(self, key);
    if (found != 0) {
        CharaResReleaseWeapon1_1f3050(found, arg);
    }
}

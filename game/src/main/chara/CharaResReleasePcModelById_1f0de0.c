/* rgp:protos */
#define RGP_SELF_CharaResReleasePcModelById_1f0de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of ActCfgTableRunEvntByName_21f680 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

void CharaResReleasePcModelById_1f0de0(void *self, void *arg, void *key)
{
    void *found;

    found = CharaResFindById_1efba0(self, key);
    if (found != 0) {
        CharaResReleasePcModel_1f2f50(found);
    }
}

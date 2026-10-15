#include "types.h"

/* Known-positive sibling shape of ActCfgTableRunEvntByName_21f680 (byte-identical, in cunits). */

extern void *CharaResFindById_1efba0(void *self, void *key);
extern void CharaResReleaseWeapon1_1f3050(void *found, void *arg);

void CharaResReleaseWeapon1ById_1f0e60(void *self, void *arg, void *key)
{
    void *found;

    found = CharaResFindById_1efba0(self, key);
    if (found != 0) {
        CharaResReleaseWeapon1_1f3050(found, arg);
    }
}

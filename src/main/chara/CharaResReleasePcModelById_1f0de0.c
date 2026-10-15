#include "types.h"

/* Known-positive sibling shape of ActCfgTableRunEvntByName_21f680 (byte-identical, in cunits). */

extern void *CharaResFindById_1efba0(void *self, void *key);
extern void CharaResReleasePcModel_1f2f50(void *found, void *arg);

void CharaResReleasePcModelById_1f0de0(void *self, void *arg, void *key)
{
    void *found;

    found = CharaResFindById_1efba0(self, key);
    if (found != 0) {
        CharaResReleasePcModel_1f2f50(found, arg);
    }
}

#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

extern s32 CharaDataFindById_1ed990(void);
extern void CharaDataRecReleaseSubRecs_1ee0d0(s32 handle);

void CharaDataReleaseSubRecsById_1ed7a0(void)
{
    s32 handle;

    handle = CharaDataFindById_1ed990();
    if (handle != 0) {
        CharaDataRecReleaseSubRecs_1ee0d0(handle);
    }
}

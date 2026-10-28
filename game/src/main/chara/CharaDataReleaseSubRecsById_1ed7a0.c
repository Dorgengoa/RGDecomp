/* rgp:protos */
#define RGP_SELF_CharaDataReleaseSubRecsById_1ed7a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

/*rgp*/
/*rgp*/

void CharaDataReleaseSubRecsById_1ed7a0(int rgp_a0, int rgp_a1)
{
    s32 handle;

    handle = CharaDataFindById_1ed990((int)rgp_a0, (int)rgp_a1);
    if (handle != 0) {
        CharaDataRecReleaseSubRecs_1ee0d0(handle);
    }
}

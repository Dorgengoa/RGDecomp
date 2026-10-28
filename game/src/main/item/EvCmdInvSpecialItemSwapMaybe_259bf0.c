/* rgp:protos */
#define RGP_SELF_EvCmdInvSpecialItemSwapMaybe_259bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdInvSpecialItemSwapMaybe_259bf0(void *p0)
{
    void *h;
    s32 r;

    h = GetGameData_1fede0();
    r = ScriptGetInt_26a2a0(p0);
    if (r == 1) {
        InvSpecialItemSwapMaybe_3e43a0(h);
    } else if (r == 0) {
        InvSpecialItemRestoreMaybe_3e4250(h);
    }
    return 1;
}

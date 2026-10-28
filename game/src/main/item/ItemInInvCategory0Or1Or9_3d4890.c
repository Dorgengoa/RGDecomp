/* rgp:protos */
#define RGP_SELF_ItemInInvCategory0Or1Or9_3d4890 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/

s32 ItemInInvCategory0Or1Or9_3d4890(s32 p0)
{
    s32 ok;

    ok = (((unsigned char)ItemInInvCategory0_3d4960(p0)) != 0);
    if (!ok) {
        ok = (((unsigned char)ItemInInvCategory1_3d4920(p0)) != 0);
    }
    if (!ok) {
        ok = (((unsigned char)ItemInInvCategory9_3d48e0(p0)) != 0);
    }
    return ok;
}

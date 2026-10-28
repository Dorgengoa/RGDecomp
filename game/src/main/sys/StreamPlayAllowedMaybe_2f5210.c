/* rgp:protos */
#define RGP_SELF_StreamPlayAllowedMaybe_2f5210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/

s32 StreamPlayAllowedMaybe_2f5210(void)
{
    s16 v;

    if (GetKeyCapModeMaybe_1c3540() == 0) {
        return 1;
    }
    v = *((s16 *)SysGetModeMsg_1c39b0());
    if (v == 6 || v == 2) {
        return 1;
    }
    return 0;
}

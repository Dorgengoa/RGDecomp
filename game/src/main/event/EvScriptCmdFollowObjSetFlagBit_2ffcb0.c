/* rgp:protos */
#define RGP_SELF_EvScriptCmdFollowObjSetFlagBit_2ffcb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8  D_004E6880[];
/*rgp*/
/*rgp*/

s32 EvScriptCmdFollowObjSetFlagBit_2ffcb0(void *self, s32 b)
{
    if (b != 0) {
        return 0;
    }
    EvObjSetFlags_2f9cb0(D_004E6880, EvObjGetFlags_2f9ce0(D_004E6880) | 0x10000);
    return 1;
}

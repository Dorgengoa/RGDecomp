/* rgp:protos */
#define RGP_SELF_EvScriptCmdObjLiftSetFlagBit_2fea40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8  D_004E7000[];
/*rgp*/
/*rgp*/

s32 EvScriptCmdObjLiftSetFlagBit_2fea40(void *self, s32 b)
{
    if (b != 0) {
        return 0;
    }
    EvObjSetFlags_2f9cb0(D_004E7000, EvObjGetFlags_2f9ce0(D_004E7000) | 0x80000);
    return 1;
}

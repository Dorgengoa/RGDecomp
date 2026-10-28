/* rgp:protos */
#define RGP_SELF_InfoCfgImgEndCmd_1aa350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct Big9D3A0 { s32 v; s32 pad[3]; } D_0049D3A0;
/*rgp*/

s32 InfoCfgImgEndCmd_1aa350(void)
{
    if (D_0049D3A0.v == 0) {
        return 0;
    }
    GetDrawCtxNameTable_15de40();
    return 1;
}

#include "types.h"

extern struct Big9D3A0 { s32 v; s32 pad[3]; } D_0049D3A0;
extern void GetDrawCtxNameTable_15de40(void);

s32 InfoCfgImgEndCmd_1aa350(void)
{
    if (D_0049D3A0.v == 0) {
        return 0;
    }
    GetDrawCtxNameTable_15de40();
    return 1;
}

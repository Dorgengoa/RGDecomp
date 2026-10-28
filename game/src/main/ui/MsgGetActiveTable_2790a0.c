/* rgp:protos */
#define RGP_SELF_MsgGetActiveTable_2790a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 D_00484180;
extern s32 D_00481BBC;

s32 MsgGetActiveTable_2790a0(void)
{
    s32 t;

    t = SysGetCurMode_1c39a0();
    if (t == 1) {
        return D_00484180;
    }
    if (t == 0) {
        return D_00481BBC;
    }
    return 0;
}

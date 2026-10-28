/* rgp:protos */
#define RGP_SELF_NavCfgCmdNodeFlags_30a6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_0048296C __attribute__((section(".sdata")));
extern u8 D_00452300[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavCfgCmdNodeFlags_30a6d0(void *p, s32 mode)
{
    s32 n;
    void *x;

    if (mode != 1) {
        return 0;
    }
    if (D_0048296C == 0) {
        return 1;
    }
    n = ((unsigned short)NavGraphGetNodeCount_310cb0(D_0048296C));
    x = NavGraphGetNode_310cd0(D_0048296C, n - 1);
    if (x == 0) {
        return 1;
    }
    NavNodeSetFlags_3118a0(x, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(p), D_00452300, 0));
    return 1;
}

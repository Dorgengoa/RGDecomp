/* rgp:protos */
#define RGP_SELF_NavCfgCmdEdgeFlags_30a630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_0048296C __attribute__((section(".sdata")));
extern u8 D_00452330[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavCfgCmdEdgeFlags_30a630(void *p, s32 mode)
{
    s32 n;
    void *x;

    if (mode != 1) {
        return 0;
    }
    if (D_0048296C == 0) {
        return 1;
    }
    n = ((unsigned short)NavGraphGetEdgeCount_310c00(D_0048296C));
    x = NavGraphGetEdge_310c20(D_0048296C, n - 1);
    if (x == 0) {
        return 1;
    }
    NavEdgeSetFlags_311650(x, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(p), D_00452330, 0));
    return 1;
}

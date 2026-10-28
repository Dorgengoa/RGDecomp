/* rgp:protos */
#define RGP_SELF_CharaNormalTableActNormalEnd_23ce90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481EF8;
extern u8 D_004BCDB0[];
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaNormalTableActNormalEnd_23ce90(void *a0, s32 flag)
{
    if (flag != 0) {
        return 0;
    }
    CharaNormalTableFindAndLoad_233a20(GetActionMgr_1fdb50(), D_00481EF8, D_004BCDB0);
    ActCfgTablesReset_23fdd0();
    return 1;
}

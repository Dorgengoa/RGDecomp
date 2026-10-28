/* rgp:protos */
#define RGP_SELF_CharaTableActDefineEnd_23c780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481EF8;
extern u8 D_004BCDE0[];
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaTableActDefineEnd_23c780(void *a0, s32 flag)
{
    if (flag != 0) {
        return 0;
    }
    CharaTableFindAndLoad_233920(GetActionMgr_1fdb50(), D_00481EF8, D_004BCDE0);
    ActCfgTablesReset_23fdd0();
    return 1;
}

#include "types.h"

extern s32 D_00481EF8;
extern u8 D_004BCDE0[];
extern void *GetActionMgr_1fdb50(void);
extern void CharaTableFindAndLoad_233920(void *, s32, u8 *);
extern void ActCfgTablesReset_23fdd0(void);

s32 CharaTableActDefineEnd_23c780(void *a0, s32 flag)
{
    if (flag != 0) {
        return 0;
    }
    CharaTableFindAndLoad_233920(GetActionMgr_1fdb50(), D_00481EF8, D_004BCDE0);
    ActCfgTablesReset_23fdd0();
    return 1;
}

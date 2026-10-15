#include "types.h"

extern s32 D_00481EF8;
extern u8 D_004BCDB0[];
extern void *GetActionMgr_1fdb50(void);
extern void CharaNormalTableFindAndLoad_233a20(void *, s32, u8 *);
extern void ActCfgTablesReset_23fdd0(void);

s32 CharaNormalTableActNormalEnd_23ce90(void *a0, s32 flag)
{
    if (flag != 0) {
        return 0;
    }
    CharaNormalTableFindAndLoad_233a20(GetActionMgr_1fdb50(), D_00481EF8, D_004BCDB0);
    ActCfgTablesReset_23fdd0();
    return 1;
}

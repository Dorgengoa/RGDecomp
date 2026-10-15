#include "types.h"

typedef struct G_FUN_00301dd0 {
    u8 pad000[0x10];
    s32 f10;
} G_FUN_00301dd0;

typedef struct O_FUN_00301dd0 O_FUN_00301dd0;

extern G_FUN_00301dd0 *GetGameData_1fede0(void);
extern void StateFlag256Set_3cc4c0(s32 h, s32 a, s32 b);
extern void MinimapSetCurAllExplored_32b6c0(s32 n);
extern O_FUN_00301dd0 *GetWorldDataMgr_1fedf0(void);
extern void HandleEntriesReleaseExcept_3f0aa0(O_FUN_00301dd0 *o, s32 n);

s32 EvScriptCmdTransporterReset_301dd0(void)
{
    G_FUN_00301dd0 *g;

    g = GetGameData_1fede0();
    StateFlag256Set_3cc4c0(g->f10, 0x80, 0);
    MinimapSetCurAllExplored_32b6c0(0);
    StateFlag256Set_3cc4c0(g->f10, 0x80, 0);
    HandleEntriesReleaseExcept_3f0aa0(GetWorldDataMgr_1fedf0(), -1);
    return 1;
}

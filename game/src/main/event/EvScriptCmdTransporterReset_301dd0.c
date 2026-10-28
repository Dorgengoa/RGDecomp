/* rgp:protos */
#define RGP_SELF_EvScriptCmdTransporterReset_301dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct G_FUN_00301dd0 {
    u8 pad000[0x10];
    s32 f10;
} G_FUN_00301dd0;

typedef struct O_FUN_00301dd0 O_FUN_00301dd0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptCmdTransporterReset_301dd0(void)
{
    G_FUN_00301dd0 *g;

    g = ((G_FUN_00301dd0 *)GetGameData_1fede0());
    StateFlag256Set_3cc4c0(g->f10, 0x80, 0);
    MinimapSetCurAllExplored_32b6c0(0);
    StateFlag256Set_3cc4c0(g->f10, 0x80, 0);
    HandleEntriesReleaseExcept_3f0aa0(((O_FUN_00301dd0 *)GetWorldDataMgr_1fedf0()), -1);
    return 1;
}

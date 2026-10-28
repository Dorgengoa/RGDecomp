/* rgp:protos */
#define RGP_SELF_EvScriptCmdScriptRecInit_301900 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482820;
extern s32 D_00482828;
extern u8 D_004E66B0[0x400];

s32 EvScriptCmdScriptRecInit_301900(s32 arg0, s32 arg1) {
    s32 temp_2;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 1) {
        return 0;
    }
    D_00482820 = EventScratchAlloc_301b00(0x1400);
    D_00482828 = EventScratchAlloc_301b00(0x300);
    if (D_00482820 == 0 || D_00482828 == 0) {
        return 1;
    }
    EventScriptRecInit_2e3a30(D_004E66B0, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0)), D_00482828, 0);
    return 1;
}

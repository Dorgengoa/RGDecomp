/* rgp:protos */
#define RGP_SELF_EvScriptCmdVolumeRecInit_301620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482830;
extern u8 D_004E66D0[];

s32 EvScriptCmdVolumeRecInit_301620(s32 arg0, s32 arg1) {
    s32 t2;
    s32 t;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 1) {
        return 0;
    }
    D_00482830 = t2 = EventScratchAlloc_301b00(0x1000);
    if (t2 == 0) {
        return 1;
    }
    EventVolumeRecInit_2e4ec0(D_004E66D0, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0)), t2, 0);
    return 1;
    return 0;
}

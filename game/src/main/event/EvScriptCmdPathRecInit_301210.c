/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathRecInit_301210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00482838;
extern s32 D_00482840;
extern s32 D_00482848;
extern u8 D_004E6700[0x400];

s32 EvScriptCmdPathRecInit_301210(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_17;
    s32 temp_2;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 1) {
        return 0;
    }
    D_00482838 = EventScratchAlloc_301b00(0xC00);
    D_00482840 = EventScratchAlloc_301b00(0x400);
    temp_2 = EventScratchAlloc_301b00(0x200);
    temp_16 = D_00482838;
    D_00482848 = temp_2;
    if (temp_16 == 0 || (temp_17 = D_00482840) == 0 || temp_2 == 0) {
        return 1;
    }
    EventPathRecInit_2e4340(D_004E6700, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0)), temp_16, 0, temp_17, 0);
    return 1;
}

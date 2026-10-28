/* rgp:protos */
#define RGP_SELF_MapCmdSetShareHeapSize_1eb1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_common_subs on

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004818F8 __attribute__((section(".sdata")));
extern s32 D_004818FC __attribute__((section(".sdata")));

s32 MapCmdSetShareHeapSize_1eb1b0(s32 arg0, s32 arg1) {
    s32 temp_2_2;
    void *temp_2;

    if (arg1 != 2) {
        return 0;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) return 1;
    temp_2 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if ((!(*(s32 *)((u8 *)temp_2 + 0x40) != 0)) || (!(*(s16 *)((u8 *)temp_2 + 0x38) > 0))) return 1;
    temp_2_2 = ((s32)MapRecTableFindShareByName_1dd340(temp_2, ScriptArgGetStr_1ecb80(arg0)));
    if (temp_2_2 == 0) {
        return 1;
    }
    MapDataSetHeapSize_1e7470(temp_2_2, ScriptArgGetInt_1ecbe0(arg0 + 8));
    return 1;
}

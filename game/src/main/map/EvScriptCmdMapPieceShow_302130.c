/* rgp:protos */
#define RGP_SELF_EvScriptCmdMapPieceShow_302130 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptCmdMapPieceShow_302130(s32 pad0, u8 *arg1, s32 arg2) {
    s32 temp_2;
    void *temp_2_2;
    s32 b;

    if (arg2 != 4) {
        return 1;
    }
    temp_2 = EvScriptArgsFindMapObj_3026d0(arg1, arg1 + 5);
    if (temp_2 == 0) {
        return 1;
    }
    temp_2_2 = NodeObjFindChildByName_195040(temp_2, ScriptArgGetStr_302cb0(arg1 + 0xA));
    if (temp_2_2 == NULL) {
        return 1;
    }
    b = ScriptArgGetInt_302d70(arg1 + 0xF) != 0;
    if (b != 0) {
        *(s16 *)((u8 *)temp_2_2 + 0x32) = 1;
    } else {
        *(s16 *)((u8 *)temp_2_2 + 0x32) = 0;
    }
    return 1;
}

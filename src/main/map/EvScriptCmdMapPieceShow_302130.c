#include "types.h"
#pragma opt_common_subs off

extern void *NodeObjFindChildByName_195040(s32, s32);
extern s32 EvScriptArgsFindMapObj_3026d0(u8 *, u8 *);
extern s32 ScriptArgGetStr_302cb0(u8 *);
extern s32 ScriptArgGetInt_302d70(u8 *);

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

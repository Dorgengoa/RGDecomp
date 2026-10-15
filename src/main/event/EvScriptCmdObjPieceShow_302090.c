/* main s27m: CLOSED -- the 0x32 field is s16 and the bool is MATERIALISED (tb = f() != 0)
   then tested `if (tb != 0)`. */
#include "types.h"

extern void *NodeObjFindChildByName_195040(s32 arg0, s32 arg1);
extern s32 ScriptArgGetStr_302cb0(s32 arg0);
extern s32 ScriptArgGetInt_302d70(s32 arg0);

s32 EvScriptCmdObjPieceShow_302090(void *arg0, s32 arg1, s32 arg2)
{
    s32 tb;
    s32 temp_16;
    void *temp_2;

    if (arg2 != 2) {
        return 1;
    }
    temp_16 = *(s32 *)((u8 *)arg0 + 0x8);
    if (temp_16 == 0) {
        return 1;
    }
    temp_2 = NodeObjFindChildByName_195040(temp_16, ScriptArgGetStr_302cb0(arg1));
    if (temp_2 == NULL) {
        return 1;
    }
    tb = ScriptArgGetInt_302d70(arg1 + 5) != 0;
    if (tb != 0) {
        *(s16 *)((u8 *)temp_2 + 0x32) = 1;
    } else {
        *(s16 *)((u8 *)temp_2 + 0x32) = 0;
    }
    return 1;
}

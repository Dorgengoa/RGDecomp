#include "types.h"

extern s32 GetEventObjMgr_2d1960(void);
extern void EvDoorObjCloseByName_2e8e30(s32 arg0, s32 arg1);
extern s32 ScriptArgGetStr_302cb0(s32 arg0);
extern s32 ScriptArgGetInt_302d70(s32 arg0);

s32 EvScriptCmdDoorClose_301f60(void *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;
    s32 t;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 1;
    }
    if (arg2 > 1) {
        temp_16 = *(s32 *)((u8 *)arg0 + 0x14);
        if (temp_16 != ScriptArgGetInt_302d70(arg1 + 5)) {
            return 1;
        }
    }
    t = GetEventObjMgr_2d1960();
    EvDoorObjCloseByName_2e8e30(t, ScriptArgGetStr_302cb0(arg1));
    return 1;
}

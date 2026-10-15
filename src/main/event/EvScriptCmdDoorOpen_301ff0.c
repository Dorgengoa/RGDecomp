#include "types.h"

extern s32 GetEventObjMgr_2d1960(void);
extern void EvDoorObjOpenByName_2e8f30(s32, s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 ScriptArgGetInt_302d70(s32);

s32 EvScriptCmdDoorOpen_301ff0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_16;
    s32 temp_16_2;

    if (arg2 != 1 && arg2 != 2) {
        return 1;
    }
    if (arg2 > 1) {
        temp_16 = *(s32 *)((u8 *)arg0 + 0x14);
        if (temp_16 != ScriptArgGetInt_302d70(arg1 + 5)) {
            return 1;
        }
    }
    temp_16_2 = GetEventObjMgr_2d1960();
    EvDoorObjOpenByName_2e8f30(temp_16_2, ScriptArgGetStr_302cb0(arg1), 0);
    return 1;
}

/* main s22: ScriptSlotGetInt_2cc9c0 really takes ONE argument (merged definition
   `s32 ScriptSlotGetInt_2cc9c0(Slot *v)`) and retail passes the un-advanced arg0.
   Corrected; the 3-word pointer-advance residue is unchanged. */
#include "types.h"

extern void *GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern void *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct { u8 b[8]; } E8;
s32 AiCmdObjFindIdByDataId_2c7ec0(E8 *arg0, s32 arg1)
{
    s32 temp_17;
    s32 var_16;
    u8 *temp_2;

    if (arg1 != 2) {
        return 0;
    }
    temp_17 = ScriptSlotGetInt_2cc9c0((s32) arg0++);
    var_16 = -1;
    temp_2 = (u8 *)ObjMgrFindFiltered_3bb190(*(s32 *)((u8 *)GetGameData_1fede0() + 0x1C), temp_17, 1, 1, 0, 0, 0, 0);
    if (temp_2 != NULL) {
        var_16 = *(s32 *)(temp_2 + 0xC);
    }
    ScriptSlotStoreIntRef_2cc900((s32) arg0, var_16);
    return 1;
}

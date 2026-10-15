#include "types.h"



extern void *GetGameData_1fede0(void);
extern void AiSetStateVarWatch_2bbbe0(s32, s32, s32);
extern s32 ScriptSlotGetCodeAddr_2cc980(void *);
extern s32 ScriptSlotGetInt_2cc9c0(void *);
extern s16 *TableFindByName_421fb0(s32, s32);
extern u8 D_004DB930[0x400];

s32 AiCmdSetStateVarWatch_2c4fa0(s64 *arg0, s32 arg1)
{
u8 *temp_16;
s32 var_17;
s64 *temp_18;
s32 var_2;
s32 temp_4;
s32 key;
if (arg1 != 2) {
        return 0;
    }
    temp_16 = (u8 *)GetGameData_1fede0();
    var_17 = ScriptSlotGetInt_2cc9c0(arg0++);
    temp_18 = arg0;
    temp_4 = *(s32 *)temp_18;
    var_2 = -1;
    switch (temp_4) {
    case 0:
        var_2 = ScriptSlotGetInt_2cc9c0(temp_18);
        break;
    case 2:
        key = ScriptSlotGetCodeAddr_2cc980(temp_18);
        var_2 = *TableFindByName_421fb0(*(s32 *)(*(u8 **)(*(u8 **)(temp_16 + 0x10) + 4) + 0x10), key);
        break;
    }
    if (var_2 < 0) {var_17 = 0;}
    AiSetStateVarWatch_2bbbe0((*(s32 *)D_004DB930), var_17, var_2);
    return 1;
}

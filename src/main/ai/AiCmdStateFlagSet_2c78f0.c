#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 ScriptSlotGetCodeAddr_2cc980(s64 * arg0);
extern s32 ScriptSlotGetInt_2cc9c0(s64 * arg0);
extern void StateFlagSetByName_3ccaf0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void StateFlagSet_3ccb70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 AiCmdStateFlagSet_2c78f0(s64 *arg0)
{
    s32 a;
    void *t;

    t = GetGameData_1fede0();
    switch (*(s32 *)arg0) {
    case 0:
    case 1:
        a = ScriptSlotGetInt_2cc9c0(arg0++);
        StateFlagSet_3ccb70(*(s32 *)((u8 *)t + 0x10), a, ScriptSlotGetInt_2cc9c0(arg0) != 0, 1);
        break;
    case 2:
        a = ScriptSlotGetCodeAddr_2cc980(arg0++);
        StateFlagSetByName_3ccaf0(*(s32 *)((u8 *)t + 0x10), a, ScriptSlotGetInt_2cc9c0(arg0) != 0, 1);
        break;

    }
    return 1;
}

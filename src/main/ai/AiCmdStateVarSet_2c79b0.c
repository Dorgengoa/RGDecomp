#include "types.h"

typedef struct G002c79b0 {
    u8 pad0[0x10];
    s32 unk10;
} G002c79b0;

extern G002c79b0 *GetGameData_1fede0(void);
extern s32 ScriptSlotGetCodeAddr_2cc980(s32 arg0);
extern s64 ScriptSlotGetInt_2cc9c0(s32 arg0);
extern void StateVarSetByName_3cc940(s32 arg0, s32 arg1, s16 arg2, s32 arg3);
extern void StateVarSet_3cc9c0(s32 arg0, s64 arg1, s16 arg2, s32 arg3);

s32 AiCmdStateVarSet_2c79b0(s64 *arg0)
{
    G002c79b0 *g;
    s32 a;
    s64 b;

    g = GetGameData_1fede0();
    switch (*(s32 *)arg0) {
    case 0:
    case 1:
        b = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        StateVarSet_3cc9c0(g->unk10, b, ScriptSlotGetInt_2cc9c0((s32)arg0), 1);
        break;
    case 2:
        a = ScriptSlotGetCodeAddr_2cc980((s32)arg0++);
        StateVarSetByName_3cc940(g->unk10, a, ScriptSlotGetInt_2cc9c0((s32)arg0), 1);
        break;
    }
    return 1;
}

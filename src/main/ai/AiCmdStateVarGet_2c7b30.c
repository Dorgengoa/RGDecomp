#include "types.h"


extern void *GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s64 *, s32);
extern s32 ScriptSlotGetCodeAddr_2cc980(s64 *);
extern s32 ScriptSlotGetInt_2cc9c0(s64 *);
extern s32 StateVarGetByName_3cca60(s32, s32);
extern s32 StateVarGet_3ccac0(s32, s32);

s32 AiCmdStateVarGet_2c7b30(s64 *arg0)
{
    s64 *p;
    s32 kind;
    s32 r;
    void *ctx;

    p = arg0;
    ctx = GetGameData_1fede0();
    kind = *(s32 *)p;
    r = -1;
    switch (kind) {
    case 0:
    case 1:
        r = StateVarGet_3ccac0(*(s32 *)((u8 *)ctx + 0x10), ScriptSlotGetInt_2cc9c0(p++));
        break;
    case 2:
        r = StateVarGetByName_3cca60(*(s32 *)((u8 *)ctx + 0x10), ScriptSlotGetCodeAddr_2cc980(p++));
        break;
    }
    ScriptSlotStoreIntRef_2cc900(p, r);
    return 1;
}

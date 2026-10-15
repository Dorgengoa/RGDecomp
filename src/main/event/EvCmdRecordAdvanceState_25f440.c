#include "types.h"

extern void *GetGameData_1fede0(void);
extern void ScriptSetRefInt_26a1e0(s32, s32);
extern s32 RecordAdvanceState_430bf0(void *, s32);

s32 EvCmdRecordAdvanceState_25f440(s32 arg0, s32 arg1) {
    s32 val;
    s32 flag;
    void *ctxPtr;
    void *sub;

    ctxPtr = *(void **)((u8 *)GetGameData_1fede0() + 0x24);
    sub = *(void **)((u8 *)ctxPtr + 0x1188);
    val = *(s32 *)((u8 *)sub + 8);
    flag = RecordAdvanceState_430bf0(ctxPtr, 0) != 0;
    if (arg1 > 0) {
        s32 old = arg0;
        arg0 += 8;
        ScriptSetRefInt_26a1e0(old, flag);
    }
    if (arg1 >= 2) {
        ScriptSetRefInt_26a1e0(arg0, val);
    }
    return 1;
}

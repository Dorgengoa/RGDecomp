#include "types.h"

extern s32 ScriptGetInt_26a2a0(void *a);
extern s32 ScriptGetCodeAddr_26a200(void *a);
extern void TaskSetEnabled_27c2a0(s32 a, s32 b);

s32 EvCmdTaskSetEnabled_25ae10(void *a0)
{
    void *q;
    s32 r1;
    s32 r2;

    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptGetInt_26a2a0(q);
    r2 = ScriptGetCodeAddr_26a200(a0);
    TaskSetEnabled_27c2a0(r1 != 0, r2);
    return 1;
}

#include "types.h"

extern s32 ScriptGetInt_2490f0(void *a);
extern s32 ScriptGetCodeAddr_249050(void *a);
extern void TaskSetEnabled_27c2a0(s32 a, s32 b);

s32 EvCmdTaskSetEnabled_241bf0(void *a0)
{
    void *q;
    s32 r1;
    s32 r2;

    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptGetInt_2490f0(q);
    r2 = ScriptGetCodeAddr_249050(a0);
    TaskSetEnabled_27c2a0(r1 != 0, r2);
    return 1;
}

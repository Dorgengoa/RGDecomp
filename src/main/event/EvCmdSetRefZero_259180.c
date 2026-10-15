#include "types.h"

extern void ScriptSetRefInt_26a1e0(void *p, s32 z);

s32 EvCmdSetRefZero_259180(void *p, s32 k)
{
    if (k > 0) goto run;
    return 0;
run:
    ScriptSetRefInt_26a1e0(p, 0);
    return 1;
}

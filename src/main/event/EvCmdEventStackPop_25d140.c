#include "types.h"

extern s32 D_004BD980[];
extern void *D_00481F78;
extern s32 ScriptGetInt_26a2a0(void);
extern void RecStackPop_1c4140(void *, s32);

s32 EvCmdEventStackPop_25d140(void)
{
    s32 *e;
    s32 r = ScriptGetInt_26a2a0();
    if (r < 0) goto zero;
    if (r < 8) goto ok;
zero:
    return 0;
ok:
    e = &D_004BD980[r];
    RecStackPop_1c4140(D_00481F78, *e);
    *e = -1;
    return 1;
}

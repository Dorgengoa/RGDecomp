#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 GetSysParamTable_1c6be0(void);
extern s32 ScriptGetInt_26a2a0(struct S8 *);
extern s32 SysParamTableGetInt_15fe80(s32, s32);
extern void ScriptSetRefInt_26a1e0(struct S8 *, s32);

s32 EvCmdSysParamGetInt_25d240(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;

    if (p1 != 2) {
        return 0;
    }
    r0 = GetSysParamTable_1c6be0();
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = SysParamTableGetInt_15fe80(r0, r1);
    ScriptSetRefInt_26a1e0(p0, r2);
    return 1;
}

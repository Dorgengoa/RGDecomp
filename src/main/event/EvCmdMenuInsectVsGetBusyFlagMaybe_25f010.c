#include "types.h"
extern s32 InsectVsGetBusyFlagThunkMaybe_4f32f0(void);
extern void ScriptSetRefInt_26a1e0(s32, s32);

s32 EvCmdMenuInsectVsGetBusyFlagMaybe_25f010(s32 p0, s32 p1)
{
    s32 r0;
    s32 a;

    r0 = InsectVsGetBusyFlagThunkMaybe_4f32f0();
    a = r0 & 0xFF;
    if (p1 > 0) {
        ScriptSetRefInt_26a1e0(p0, a);
    }
    return 1;
}

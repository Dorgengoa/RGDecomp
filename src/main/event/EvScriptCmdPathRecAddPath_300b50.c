#include "types.h"
extern void *ScriptArgGetStr_301a00(void *);
extern void EventPathTemplateAddPath_300b90(void *, s32, void *);
void EvScriptCmdPathRecAddPath_300b50(void *p0, s32 p1)
{
    void *r0;
    r0 = ScriptArgGetStr_301a00(p0);
    EventPathTemplateAddPath_300b90((u8 *)p0 + 8, p1 - 1, r0);
}

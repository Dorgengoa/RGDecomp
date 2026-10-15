#include "types.h"

extern f32 ScriptArgGetFloat_301a20(void *);
extern s32 EventPathRecPointPush_3010a0(f32, f32, f32, f32, f32, f32, f32, f32, f32);

s32 EvScriptCmdPathPointAddPos_300ea0(void *p, s32 mode)
{
    f32 a, b, c;

    if (mode != 3) return 0;
    a = ScriptArgGetFloat_301a20(p);
    b = ScriptArgGetFloat_301a20((void *)((u8 *)p + 8));
    c = ScriptArgGetFloat_301a20((void *)((u8 *)p + 0x10));
    return EventPathRecPointPush_3010a0(a, b, c, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
}

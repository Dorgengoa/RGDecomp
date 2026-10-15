#include "types.h"

typedef struct { s32 a, b; } T_00300d80;

extern f32 ScriptArgGetFloat_301a20(void *);
extern s32 EventPathRecPointPush_3010a0(f32, f32, f32, f32, f32, f32, f32, f32, f32);

s32 EvScriptCmdPathPointAddScale_300d80(T_00300d80 *q, s32 mode)
{
    f32 a;
    f32 b;
    f32 c;

    if (mode != 3) return 0;
    a = ScriptArgGetFloat_301a20(q);
    b = ScriptArgGetFloat_301a20((void *)((s32)q + 8));
    c = ScriptArgGetFloat_301a20((void *)((s32)q + 0x10));
    return EventPathRecPointPush_3010a0(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, a, b, c);
}

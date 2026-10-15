#include "types.h"

typedef struct Arg {
    s32 a;
    s32 b;
} Arg;

extern f32  ScriptSlotGetFloat_334890(Arg *p);
extern void ScriptSlotStoreIntRef_3347f0(Arg *p, s32 v);
extern s32  AngleDiffSign_13c0d0(f32 a, f32 b, f32 c);

s32 ScriptCmdAngleDiffSign_334210(Arg *p)
{
    f32 a;
    f32 b;
    f32 c;

    a = ScriptSlotGetFloat_334890(p++);
    b = ScriptSlotGetFloat_334890(p++);
    c = ScriptSlotGetFloat_334890(p++);
    ScriptSlotStoreIntRef_3347f0(p, AngleDiffSign_13c0d0(a, b, c));
    return 1;
}

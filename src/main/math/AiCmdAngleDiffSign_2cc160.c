#include "types.h"

typedef struct Arg {
    s32 a;
    s32 b;
} Arg;

extern f32  ScriptSlotGetFloat_2cc9a0(Arg *p);
extern void ScriptSlotStoreIntRef_2cc900(Arg *p, s32 v);
extern s32  AngleDiffSign_13c0d0(f32 a, f32 b, f32 c);

s32 AiCmdAngleDiffSign_2cc160(Arg *p)
{
    f32 a;
    f32 b;
    f32 c;

    a = ScriptSlotGetFloat_2cc9a0(p++);
    b = ScriptSlotGetFloat_2cc9a0(p++);
    c = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreIntRef_2cc900(p, AngleDiffSign_13c0d0(a, b, c));
    return 1;
}

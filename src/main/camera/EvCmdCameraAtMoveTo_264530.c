#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern void EventCameraNodeAddAtMoveTo_254000(s32, Vec4 *, s32);
extern s32 D_00482060;

s32 EvCmdCameraAtMoveTo_264530(Cmd *p0)
{
    Vec4 v;

    VEC4_ZERO(v);
    v.x = TaggedGetFloat_26a280((s32)p0++);
    v.y = TaggedGetFloat_26a280((s32)p0++);
    v.z = TaggedGetFloat_26a280((s32)p0++);
    v.w = 1.0f;
    EventCameraNodeAddAtMoveTo_254000(D_00482060, &v, ScriptGetInt_26a2a0((s32)p0));
    return 1;
}

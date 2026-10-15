#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern void EventCameraNodeAddMoveToEased_254060(s32, Vec4 *, Vec4 *, s32, s32, f32);
extern s32 D_00482060;

s32 EvCmdCameraMoveToEased_2645b0(Cmd *p0)
{
    Vec4 a, b;
    s32 u, w;

    VEC4_ZERO(a);
    VEC4_ZERO(b);
    a.x = TaggedGetFloat_26a280((s32)p0++);
    a.y = TaggedGetFloat_26a280((s32)p0++);
    a.z = TaggedGetFloat_26a280((s32)p0++);
    a.w = 1.0f;
    b.x = TaggedGetFloat_26a280((s32)p0++);
    b.y = TaggedGetFloat_26a280((s32)p0++);
    b.z = TaggedGetFloat_26a280((s32)p0++);
    b.w = 1.0f;
    u = ScriptGetInt_26a2a0((s32)p0++);
    w = ScriptGetInt_26a2a0((s32)p0++);
    EventCameraNodeAddMoveToEased_254060(D_00482060, &a, &b, u, w, TaggedGetFloat_26a280((s32)p0));
    return 1;
}

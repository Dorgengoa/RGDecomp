#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern void EventCameraNodeAddSetAt_254180(s32, Vec4 *);
extern s32 D_00482060;

s32 EvCmdCameraQueueSetAt_264890(Cmd *p0)
{
    Vec4 v;

    VEC4_ZERO(v);
    v.x = TaggedGetFloat_26a280((s32)p0++);
    v.y = TaggedGetFloat_26a280((s32)p0++);
    v.z = TaggedGetFloat_26a280((s32)p0);
    v.w = 1.0f;
    EventCameraNodeAddSetAt_254180(D_00482060, &v);
    return 1;
}

#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern void EventCameraNodeAddOrbitSetAll_253ce0(s32, f32, f32, f32);
extern s32 D_00482060;

s32 EvCmdCameraSetOrbitAll_264760(Cmd *p0)
{
    f32 x, y;

    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    EventCameraNodeAddOrbitSetAll_253ce0(D_00482060, x, y, TaggedGetFloat_26a280((s32)p0));
    return 1;
}

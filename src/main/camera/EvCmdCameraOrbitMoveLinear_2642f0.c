#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern void EventCameraNodeAddOrbitMoveLinear_253c70(s32, f32, f32, s32, f32);
extern s32 D_00482060;

s32 EvCmdCameraOrbitMoveLinear_2642f0(Cmd *p0)
{
    f32 x, y, z;

    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    z = TaggedGetFloat_26a280((s32)p0++);
    EventCameraNodeAddOrbitMoveLinear_253c70(D_00482060, x, y, ScriptGetInt_26a2a0((s32)p0), z);
    return 1;
}

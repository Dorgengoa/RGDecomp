#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern void EventCameraNodeAddEyeAtVelDecay_253ea0(s32, f32, s32);
extern s32 D_00482060;

s32 EvCmdCameraEyeAtVelDecay_2643c0(Cmd *p0)
{
    f32 x;

    x = TaggedGetFloat_26a280((s32)p0++);
    EventCameraNodeAddEyeAtVelDecay_253ea0(D_00482060, x, ScriptGetInt_26a2a0((s32)p0));
    return 1;
}

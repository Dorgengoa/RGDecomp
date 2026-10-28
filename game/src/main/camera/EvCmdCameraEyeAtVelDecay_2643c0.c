/* rgp:protos */
#define RGP_SELF_EvCmdCameraEyeAtVelDecay_2643c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482060;

s32 EvCmdCameraEyeAtVelDecay_2643c0(Cmd *p0)
{
    f32 x;

    x = TaggedGetFloat_26a280((s32)p0++);
    EventCameraNodeAddEyeAtVelDecay_253ea0(D_00482060, ScriptGetInt_26a2a0((s32)p0), x);
    return 1;
}

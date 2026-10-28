/* rgp:protos */
#define RGP_SELF_EvCmdCameraOrbitMoveLinear_2642f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482060;

s32 EvCmdCameraOrbitMoveLinear_2642f0(Cmd *p0)
{
    f32 x, y, z;

    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    z = TaggedGetFloat_26a280((s32)p0++);
    EventCameraNodeAddOrbitMoveLinear_253c70(D_00482060, ScriptGetInt_26a2a0((s32)p0), x, y, z);
    return 1;
}

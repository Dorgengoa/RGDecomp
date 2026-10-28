/* rgp:protos */
#define RGP_SELF_EvCmdCameraQueueSetEye_264900 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
extern s32 D_00482060;

s32 EvCmdCameraQueueSetEye_264900(Cmd *p0)
{
    Vec4 v __attribute__((aligned(16)));

    VEC4_ZERO(v);
    v.x = TaggedGetFloat_26a280((s32)p0++);
    v.y = TaggedGetFloat_26a280((s32)p0++);
    v.z = TaggedGetFloat_26a280((s32)p0);
    v.w = 1.0f;
    EventCameraNodeAddSetEye_2541c0(D_00482060, &v);
    return 1;
}

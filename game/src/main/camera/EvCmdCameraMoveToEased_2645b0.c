/* rgp:protos */
#define RGP_SELF_EvCmdCameraMoveToEased_2645b0 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/
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

/* rgp:protos */
#define RGP_SELF_EvCmdCameraSplineAddPoint_264430 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
extern s32 D_00482060;

/* two stack Vec4s: LAST declared gets the LOWEST address, so `a` is the
   0x30 slot and `b` the 0x20 slot. */
s32 EvCmdCameraSplineAddPoint_264430(Cmd *p0)
{
    Vec4 a, b;

    VEC4_ZERO(a);
    a.x = TaggedGetFloat_26a280((s32)p0++);
    a.y = TaggedGetFloat_26a280((s32)p0++);
    a.z = TaggedGetFloat_26a280((s32)p0++);
    a.w = 1.0f;
    VEC4_ZERO(b);
    b.x = TaggedGetFloat_26a280((s32)p0++);
    b.y = TaggedGetFloat_26a280((s32)p0++);
    b.z = TaggedGetFloat_26a280((s32)p0);
    b.w = 1.0f;
    EventCameraNodeAddSplineAddPoint_253f20(D_00482060, &a, &b);
    return 1;
}

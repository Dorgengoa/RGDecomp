/* rgp:protos */
#define RGP_SELF_EvCmdCameraSetOrbitAll_264760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
extern s32 D_00482060;

s32 EvCmdCameraSetOrbitAll_264760(Cmd *p0)
{
    f32 x, y;

    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    EventCameraNodeAddOrbitSetAll_253ce0(D_00482060, x, y, TaggedGetFloat_26a280((s32)p0));
    return 1;
}

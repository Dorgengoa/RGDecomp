/* rgp:protos */
#define RGP_SELF_NodeDistanceToCamera_185f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b, c, d; } T_00185f00;

/*rgp*/
/*rgp*/
/*rgp*/

f32 NodeDistanceToCamera_185f00(void *p)
{
    T_00185f00 v __attribute__((aligned(16)));
    void *q;

    if (*(s32 *)((s32)p + 0x40) == 0) return 0.0f;
    NodeGetWorldPos_186100(p, &v);
    q = GetDrawCtx_15de80();
    return CameraDistToEye_13fd00(q, &v);
}

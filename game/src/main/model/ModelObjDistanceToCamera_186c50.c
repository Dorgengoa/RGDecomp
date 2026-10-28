/* rgp:protos */
#define RGP_SELF_ModelObjDistanceToCamera_186c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_00186c50;
typedef struct {
    s32 f0;
    void *f4;
    u8 pad[0x180 - 8];
    s32 f180;
    u8 pad2[0x1CC - 0x184];
    s32 f1CC;
} T_00186c50;

/*rgp*/
/*rgp*/
/*rgp*/

f32 ModelObjDistanceToCamera_186c50(T_00186c50 *p)
{
    V_00186c50 v __attribute__((aligned(16)));
    void *q;
    void *r;

    if (p->f1CC == 0) return 0.0f;
    q = p->f4;
    if (q == 0) {
        r = GetDrawCtx_15de80();
        return CameraDistToEye_13fd00(r, &p->f180);
    }
    FrameTransformPoint_148f60(q, &v, &p->f180);
    r = GetDrawCtx_15de80();
    return CameraDistToEye_13fd00(r, &v);
}

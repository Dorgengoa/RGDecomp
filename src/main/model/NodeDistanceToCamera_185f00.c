#include "types.h"

typedef struct { s32 a, b, c, d; } T_00185f00;

extern void NodeGetWorldPos_186100(void *, T_00185f00 *);
extern void *GetDrawCtx_15de80(void);
extern f32 CameraDistToEye_13fd00(void *, T_00185f00 *);

f32 NodeDistanceToCamera_185f00(void *p)
{
    T_00185f00 v;
    void *q;

    if (*(s32 *)((s32)p + 0x40) == 0) return 0.0f;
    NodeGetWorldPos_186100(p, &v);
    q = GetDrawCtx_15de80();
    return CameraDistToEye_13fd00(q, &v);
}

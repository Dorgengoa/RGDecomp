/* rgp:protos */
#define RGP_SELF_CameraProjectToScreenStq_1c8f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

int CameraProjectToScreenStq_1c8f10(s32 *o1, f32 *o2, void *arg2, f32 x, f32 y)
{
    f32 v[4] __attribute__((aligned(16)));
    void *r;
    f32 s;

    r = GetDrawCtxCamera_15de60();
    MatMulPoint_1cb8e0(v, (u8 *)r + 0x1C0, arg2);
    s = 1.0f / v[3];
    o2[0] = x * s;
    o2[1] = y * s;
    o2[2] = s;
    o2[3] = 0.0f;
    v[0] = v[0] * s;
    v[1] = v[1] * s;
    v[2] = v[2] * s;
    o1[0] = (s32)(16.0f * v[0]);
    o1[1] = (s32)(16.0f * v[1]);
    o1[2] = (s32)v[2];
    o1[3] = 0;
    return CameraScreenPointVisible_15d520(v);
}

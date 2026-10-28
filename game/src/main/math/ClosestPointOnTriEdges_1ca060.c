/* rgp:protos */
#define RGP_SELF_ClosestPointOnTriEdges_1ca060 1
#define RGP_SELF_proj 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline f32 proj(const void *p1, const void *p2, const void *ref)
{
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    f32 d;

    VecSub_1cbd00(&a, p1, ref);
    VecSub_1cbd00(&b, p2, ref);
    d = VecDistSq_1cb3c0(&a, &b);
    if (d == 0.0f) {
        return 0.0f;
    }
    return VecDotDiff_1cba40(&a, &b, &a) / d;
}

void ClosestPointOnTriEdges_1ca060(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    f32 t;

    t = proj((void *)arg2, (void *)arg3, (void *)arg5);
    if (t < 0.0f) {
        t = proj((void *)arg1, (void *)arg2, (void *)arg5);
        if (t > 1.0f) {
            VecCopyAsPoint_1cbe10((void *)arg0, (void *)arg2);
        } else {
            VecLerpPoint_1cbac0((void *)arg0, (void *)arg2, (void *)arg1, t);
        }
        return;
    }
    if (t > 1.0f) {
        t = proj((void *)arg3, (void *)arg1, (void *)arg5);
        if (t < 0.0f) {
            VecCopyAsPoint_1cbe10((void *)arg0, (void *)arg3);
        } else {
            VecLerpPoint_1cbac0((void *)arg0, (void *)arg4, (void *)arg3, t);
        }
        return;
    }
    VecLerpPoint_1cbac0((void *)arg0, (void *)arg3, (void *)arg2, t);
}

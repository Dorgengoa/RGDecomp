/* rgp:protos */
#define RGP_SELF_ClosestPointOnSegment_1c9f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V1C9 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V1C9;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ClosestPointOnSegment_1c9f60(void *a, void *b, void *c, void *d)
{
    V1C9 v70 __attribute__((aligned(16)));
    V1C9 v60 __attribute__((aligned(16)));
    f32 len;
    f32 t;
    f32 s;

    VecSub_1cbd00(&v70, b, d);
    VecSub_1cbd00(&v60, c, d);
    len = VecDistSq_1cb3c0(&v70, &v60);
    t = 0.0f;
    if (len == 0.0f) {
        t = 0.0f;
    } else {
        t = VecDotDiff_1cba40(&v70, &v60, &v70) / len;
    }
    if (t <= 0.0f) {
        s = 0.0f;
    } else {
        s = (t >= 1.0f) ? 1.0f : t;
    }
    VecLerpPoint_1cbac0(a, c, b, s);
}

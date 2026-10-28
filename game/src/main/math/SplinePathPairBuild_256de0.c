/* rgp:protos */
#define RGP_SELF_SplinePathPairBuild_256de0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    V4 pts[16];
    V4 pts2[16];
    s32 n;
    s32 len;
    u8 pathA[0x5A4 - 0x208];
    u8 pathB[4];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 SplinePathPairBuild_256de0(Obj *arg0)
{
    struct {
        f32 d[16];
        s32 seg[16];
    } w;
    V4 p0 __attribute__((aligned(16)));
    V4 p1 __attribute__((aligned(16)));
    V4 q0 __attribute__((aligned(16)));
    V4 q1 __attribute__((aligned(16)));
    f32 *dp;
    s32 i;
    s32 j;
    f32 sum;

    if (arg0->n <= 0) {
        return 1;
    }
    for (i = 0; i < arg0->n - 1; i++) {
        dp = &w.d[i];
        *dp = VecDistance_13d3d0(&arg0->pts[i], &arg0->pts[i + 1]);
    }
    for (j = 0; j < arg0->n - 1; j++) {
        w.seg[j] = arg0->len / (arg0->n - 1);
    }
    SplineBuild_257560(arg0->pathA, arg0->pts, w.seg, arg0->n, 0.0f);
    sum = 0.0f;
    for (;;) {
        SplineGetPos_257160(arg0->pathA, &p0);
        if (SplineStep_257190(arg0->pathA) != 0) {
            break;
        }
        SplineGetPos_257160(arg0->pathA, &p1);
        sum += VecDistance_13d3d0(&p0, &p1);
    }
    SplineBuild_257560(arg0->pathA, arg0->pts, w.seg, arg0->n, sum / (f32)arg0->len);
    for (i = 0; i < arg0->n - 1; i++) {
        dp = &w.d[i];
        *dp = VecDistance_13d3d0(&arg0->pts2[i], &arg0->pts2[i + 1]);
    }
    for (j = 0; j < arg0->n - 1; j++) {
        w.seg[j] = arg0->len / (arg0->n - 1);
    }
    SplineBuild_257560(arg0->pathB, arg0->pts2, w.seg, arg0->n, 0.0f);
    sum = 0.0f;
    for (;;) {
        SplineGetPos_257160(arg0->pathB, &q0);
        if (SplineStep_257190(arg0->pathB) != 0) {
            break;
        }
        SplineGetPos_257160(arg0->pathB, &q1);
        sum += VecDistance_13d3d0(&q0, &q1);
    }
    SplineBuild_257560(arg0->pathB, arg0->pts2, w.seg, arg0->n, sum / (f32)arg0->len);
    return 0;
}

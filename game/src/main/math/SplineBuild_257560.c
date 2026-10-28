/* rgp:protos */
#define RGP_SELF_SplineBuild_257560 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3


typedef struct Seg {
    s32 t0;
    s32 dt;
    f32 a[3];
    f32 b[3];
    f32 c[3];
    f32 d[3];
} Seg;

typedef struct Spline {
    Seg seg[16];
    s32 n;          /* 0x380 */
    s32 pad384[2];
    f32 pos[3];     /* 0x38C */
    f32 f;          /* 0x398 */
} Spline;

/*rgp*/
/*rgp*/

void SplineBuild_257560(Spline *s, f32 (*src)[4], s32 *times, s32 n, f32 f) {
    f32 pts[18][4] __attribute__((aligned(16)));
    s32 i;
    s32 j;
    f32 *p;
    Seg *e;
    f32 p1;
    f32 p0;
    f32 d;
    f32 m0;
    f32 m1;

    SplineInit_257860(s);
    if (n <= 0) {
        return;
    }
    s->n = n;
    s->f = f;
    for (i = 0; i < s->n; i++) {
        sceVu0CopyVector(pts[i], src[i]);
    }
    sceVu0CopyVector(pts[s->n], src[s->n - 1]);
    sceVu0CopyVector(pts[s->n + 1], src[s->n - 1]);
    s->pos[0] = src[0][0];
    s->pos[1] = src[0][1];
    s->pos[2] = src[0][2];
    for (i = 0; i < s->n; i++) {
        if (i == 0) {
            s->seg[i].t0 = 0;
            s->seg[i].dt = times[i];
        } else if (i == s->n - 1) {
            s->seg[i].t0 = s->seg[i - 1].t0 + s->seg[i - 1].dt;
            s->seg[i].dt = 0;
        } else {
            s->seg[i].t0 = s->seg[i - 1].t0 + s->seg[i - 1].dt;
            s->seg[i].dt = times[i];
        }
    }
    for (i = 0; i < s->n; i++) {
        for (j = 0; j < 3; j++) {
            p0 = pts[i][j];
            p1 = pts[i + 1][j];
            if (i == 0) {
                m0 = pts[i + 1][j] - pts[i][j];
            } else {
                m0 = ((f32)s->seg[i - 1].dt * (pts[i + 1][j] - pts[i][j]) + (f32)s->seg[i].dt * (pts[i][j] - pts[i - 1][j])) / (f32)(s->seg[i - 1].dt + s->seg[i].dt);
            }
            if (i == s->n - 1) {
                m1 = pts[i + 2][j] - pts[i + 1][j];
            } else {
                m1 = ((f32)s->seg[i].dt * (pts[i + 2][j] - pts[i + 1][j]) + (f32)s->seg[i + 1].dt * (pts[i + 1][j] - pts[i][j])) / (f32)(s->seg[i].dt + s->seg[i + 1].dt);
            }
            s->seg[i].a[j] = m1 + (m0 + (2.0f * p0 - 2.0f * p1));
            s->seg[i].b[j] = -3.0f * p0 + 3.0f * p1 - 2.0f * m0 - m1;
            s->seg[i].c[j] = m0;
            s->seg[i].d[j] = p0;
        }
    }
}

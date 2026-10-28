/* rgp:protos */
#define RGP_SELF_SplineSampleCatmullRom_2d77c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off

typedef struct { f32 x, y, z, w; } V4;

/*rgp*/
/*rgp*/


s32 SplineSampleCatmullRom_2d77c0(V4 *out, V4 *pts, s32 n, s32 steps, s32 off, s32 wrap) {
    V4 M[4] __attribute__((aligned(16)));
    V4 G[4] __attribute__((aligned(16)));
    V4 A[4] __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    V4 r __attribute__((aligned(16)));
    s32 idx[4] __attribute__((aligned(16)));
    f32 a, b, c;
    f32 d;
    f32 t;
    f32 lim;
    f32 step;
    s32 cnt;
    s32 i;
    s32 k;
    s32 *p;
    f32 *o;

    if (n < 3) {
        return 0;
    }
    a = 0.5f;
    b = 0.25f;
    c = 1.25f;
    A[0].x = -b / a;
    A[1].x = 1.0f;
    d = (f32)steps - 1.0f;
    A[0].y = 1.5f;
    A[0].z = (-a - b) / a;
    A[1].y = -c / a;
    A[1].z = 2.0f;
    A[1].w = -a;
    A[2].x = -b / a;
    A[2].z = a;
    A[3].x = 0.0f;
    A[2].y = 0.0f;
    A[3].y = 1.0f;
    A[0].w = a;
    A[3].z = 0.0f;
    A[2].w = 0.0f;
    A[3].w = 0.0f;
    cnt = 0;
    for (i = 0; i < n - 1; i++) {
        if (i > 0 && i < n - 2) {
            idx[1] = i; idx[0] = i - 1; idx[2] = i + 1; idx[3] = i + 2;
        } else {
            if (i <= 0) {
                idx[0] = 0; idx[2] = 1; idx[1] = 0; idx[3] = 2;
            }
            if (i >= n - 2) {
                idx[1] = i; idx[0] = i - 1; idx[3] = idx[2] = i + 1;
            }
        }
        for (k = 0; k < 4; k++) {
            p = &idx[k];
            *p += off;
            if (*p >= wrap) *p -= wrap;
            if (*p < 0) *p += wrap;
        }
        for (k = 0; k < 4; k++) {
            V4 *s;
            V4 *q;
            s = &pts[*(s32 *)((u32)&idx[k])];
            q = &G[k];
            q->x = s->x; q->y = s->y; q->z = s->z; q->w = 0.0f;
        }
        sceVu0MulMatrix(M, G, A);
        t = 0.0f;
        step = 1.0f / d;
        lim = 1.0f - step;
        for (; t < lim; t += step) {
            v.y = t * t; v.x = t * (t * t); v.z = t; v.w = 1.0f;
            MtxMulVec4_10a8c0(&r, M, &v);
            o = (f32 *)&out[cnt];
            for (k = 0; k < 3; k++) {
                o[k] = (&r.x)[k];
            }
            cnt++;
            o[3] = 1.0f;
        }
    }
    return cnt;
}

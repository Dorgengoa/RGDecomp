#include "types.h"
#pragma opt_propagation off
#pragma divbyzerocheck on

typedef struct { f32 x, y, z, w; } V4;

typedef struct {
    V4 pt[16];
    s32 total;
    s32 n;
    u8 sp[4];
} O;

extern f32 VecDistance_13d3d0(V4 *, V4 *);
extern void SplineGetPos_257160(u8 *, V4 *);
extern s32 SplineStep_257190(u8 *);
extern void SplineBuild_257560(u8 *, O *, s32 *, s32, f32);

s32 SplinePathBuild_256ac0(O *o) {
    s32 t[16];
    f32 d[16];
    V4 a;
    V4 b;
    f32 sum;
    s32 i;

    if (o->n <= 0) {
        return 1;
    }
    for (i = 0; i < o->n - 1; i++) {
        { f32 *p = &d[i]; *p = VecDistance_13d3d0(&o->pt[i], &o->pt[i + 1]); }
    }
    for (i = 0; i < o->n - 1; i++) {
        t[i] = o->total / (o->n - 1);
    }
    SplineBuild_257560(o->sp, o, t, o->n, 0.0f);
    sum = 0.0f;
    for (;;) {
        SplineGetPos_257160(o->sp, &a);
        if (SplineStep_257190(o->sp) != 0) {
            break;
        }
        SplineGetPos_257160(o->sp, &b);
        sum += VecDistance_13d3d0(&a, &b);
    }
    SplineBuild_257560(o->sp, o, t, o->n, sum / (f32)o->total);
    return 0;
}

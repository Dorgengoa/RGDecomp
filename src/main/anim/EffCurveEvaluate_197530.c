#include "types.h"
#pragma opt_propagation off

extern void EffCurveFindKeySpan_197700(void *, s32 *);
extern f32 EffCurveSplineEval_1973e0(void *, f32, s32, s32);

typedef struct Frame00197530 {
    s32 sp20;
    s32 sp24;
    f32 sp28;
} Frame00197530;

typedef struct { u8 pad[8]; s32 count; u8 pad2[8]; s32 type; u8 pad3[4]; f32 *arr; } O;

static inline s32 has(O *o) { return o->count > 0; }

f32 EffCurveEvaluate_197530(O *arg0) {
    Frame00197530 frame;
    if (has(arg0) == 0) {
        return 0.0f;
    }

    EffCurveFindKeySpan_197700(arg0, (s32 *)&frame);
    switch (arg0->type) {
    case 1:
        return (1.0f - frame.sp28) * arg0->arr[frame.sp20] + frame.sp28 * arg0->arr[frame.sp24];
    case 2:
        return EffCurveSplineEval_1973e0(arg0, frame.sp28, frame.sp20, frame.sp24);
    case 0:
    default:
        return arg0->arr[frame.sp20];

    }
}

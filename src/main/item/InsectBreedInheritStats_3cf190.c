#include "types.h"
#pragma divbyzerocheck on
#pragma optimization_level 3

s32 Rand_133710();
void InsectSetStats_3d13d0(s32, s32 *);
void InsectGetStats_3d1470(s32, s32 *);

static inline void Max(s32 *p, s32 v) {
    if (*p < v) {
        *p = v;
    }
}

void InsectBreedInheritStats_3cf190(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 lim[9];
    s32 out[9];
    s32 i;
    s32 *p;

    InsectGetStats_3d1470(arg0, lim);
    for (i = 0; i < 9; i++) {
        out[i] = arg1[i];
        if (out[i] < arg2[i]) {
            out[i] = arg2[i];
        }
        if (out[i] < lim[i]) {
            out[i] = lim[i];
        }
        out[i] += Rand_133710() % 5 - 2;
        out[i] = out[i] * 90 / 100;
    }
    InsectSetStats_3d13d0(arg0, out);
}

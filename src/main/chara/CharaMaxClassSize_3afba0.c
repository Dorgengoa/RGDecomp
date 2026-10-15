#include "types.h"

typedef struct A_FUN_003afba0 {
    s32 v[7];
} A_FUN_003afba0;

extern A_FUN_003afba0 D_00454610 __attribute__((aligned(4)));

s32 CharaMaxClassSize_3afba0(void)
{
    A_FUN_003afba0 a;
    s32 best;
    s32 i;
    s32 v;

    a = D_00454610;
    best = 0;
    i = 0;
    while (1) {
        v = a.v[i];
        if (v <= 0) break;
        if (best < v) best = v;
        i = i + 1;
    }
    return best;
}

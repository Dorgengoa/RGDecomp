#include "types.h"

typedef struct {
    s32 p0;
    f32 f4;
    s32 p8[3];
    f32 f14;
    s32 p18[3];
    f32 f24;
} T_002c0d80;

f32 CollTriMaxY_2c0d80(T_002c0d80 *p)
{
    f32 a;
    f32 b;

    a = p->f4;
    b = p->f14;
    if (b < a) {
        if (p->f24 < a) return a;
    }
    if (p->f24 < b) return b;
    return p->f24;
}

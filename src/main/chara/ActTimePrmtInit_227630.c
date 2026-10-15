#include "types.h"

typedef struct Q226 {
    f32 x;
    f32 y;
    f32 z;
    s32 a;
    s32 b;
} Q226;

void ActTimePrmtInit_227630(Q226 *out, u64 v, f32 x, f32 y, f32 z)
{
    out->x = z;
    out->y = x;
    out->z = y;
    out->a = (s32)v;
    out->b = (s32)(v >> 32);
}

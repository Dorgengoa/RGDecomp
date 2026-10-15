#include "types.h"

typedef struct Q227 {
    f32 x;
    f32 y;
    s32 a;
    s32 b;
} Q227;

void ActTimeAttrInit_227710(Q227 *out, u64 v, f32 x, f32 y)
{
    out->x = x;
    out->y = y;
    out->a = (s32)v;
    out->b = (s32)(v >> 32);
}

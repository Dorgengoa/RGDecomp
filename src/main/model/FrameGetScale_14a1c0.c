#include "types.h"
typedef unsigned __int128 u128;
typedef struct V0014a1c0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V0014a1c0;

typedef struct S0014a1c0 {
    u8 pad[0x1C];
    V0014a1c0 *f1C;
} S0014a1c0;

void FrameGetScale_14a1c0(S0014a1c0 *s, V0014a1c0 *out)
{
    V0014a1c0 *p;

    p = s->f1C;
    if (p != 0) {
        *(u128 *)out = *(u128 *)p;
    } else {
        out->z = 1.0f;
        out->y = 1.0f;
        out->x = 1.0f;
        out->w = 0.0f;
    }
}

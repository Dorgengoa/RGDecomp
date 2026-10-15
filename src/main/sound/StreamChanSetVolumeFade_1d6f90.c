#include "types.h"

typedef struct { u8 pad[0x84]; f32 f84; s32 f88; f32 f8C; f32 f90; } T_001d6f90;

void StreamChanSetVolumeFade_1d6f90(T_001d6f90 *p, s32 n, f32 v)
{
    p->f8C = v;
    if (v < 0.0f) {
        p->f8C = 0.0f;
    }
    if (p->f8C > 1.0f) {
        p->f8C = 1.0f;
    }
    if (n <= 0) {
        n = 1;
    }
    p->f90 = (p->f8C - p->f84) / (f32)n;
}

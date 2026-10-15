#include "types.h"

typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10, f14;
    s16 f18, f1A;
} S_003938F0;

typedef struct { u8 pad[0x20]; S_003938F0 *f20; } T_003938F0;

void InsectUiWindowFillSetSizeMaybe_3938f0(void *unused, T_003938F0 *p, f32 x, f32 y)
{
    S_003938F0 *s;

    if (p == 0) return;
    s = p->f20;
    if (s == 0) return;
    s->f0 = 0;
    s->f2 = 0;
    s->f4 = (s16)x;
    s->f6 = (s16)y;
    s->fC = 4;
    s->fE = 4;
    s->f8 = 0x34;
    s->fA = 0x8C;
    s->f18 = 0;
    s->f1A = 0;
    s->f10 = 0;
    s->f14 = 0;
}

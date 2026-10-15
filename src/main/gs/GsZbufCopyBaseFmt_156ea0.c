#include "types.h"

typedef struct D {
    u8 pad0[0x30];
    u16 a : 9;
    u16 a_hi : 7;
    u8 pad32;
    u8 b : 4;
    u8 b_hi : 4;
} D;

typedef struct S {
    u16 f0 : 9;
    u16 f0_hi : 7;
    u8 pad2;
    u8 f3 : 4;
    u8 f3_hi : 4;
} S;

void GsZbufCopyBaseFmt_156ea0(D *d, S *s)
{
    u16 v;
    u8 w;

    v = s->f0;
    d->a = v;
    w = s->f3;
    d->b = w;
}

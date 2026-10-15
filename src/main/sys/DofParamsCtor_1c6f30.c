#include "types.h"

typedef struct S1C6 {
    s32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
} S1C6;

S1C6 *DofParamsCtor_1c6f30(S1C6 *p)
{
    p->f00 = 1;
    p->f04 = 1.0f;
    p->f08 = (f32)3000;
    p->f0C = 4000.0f;
    p->f10 = (f32)5000;
    return p;
}

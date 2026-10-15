#include "types.h"

typedef struct S387 {
    u8  pad000[0x10];
    s32 mA;
    s32 mB;
    u8  padC[0x24 - (0x10 + 8)];
    s32 mC;
} S387;

extern f32 RandFloat_13c010(S387 *p);

void MenuObjParamsRollTime_387f60(S387 *p)
{
    s32 a;
    s32 d;
    f32 t;

    a = p->mA;
    t = RandFloat_13c010(p);
    d = p->mB - a;
    p->mC = (s32)((f32)a + (f32)d * t);
}

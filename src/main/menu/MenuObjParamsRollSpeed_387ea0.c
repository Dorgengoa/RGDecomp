#include "types.h"

struct T387EA0 { u8 pad000[0x4]; f32 f04; f32 f08; u8 pad00C[0x24]; f32 f30; };

extern f32 RandFloat_13c010(struct T387EA0 *p);

void MenuObjParamsRollSpeed_387ea0(struct T387EA0 *p)
{
    f32 a;
    f32 t;
    f32 d;

    a = p->f04;
    t = RandFloat_13c010(p);
    d = p->f08 - a;
    p->f30 = a + d * t;
}

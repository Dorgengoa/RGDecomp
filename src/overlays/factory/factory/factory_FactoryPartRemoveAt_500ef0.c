#include "types.h"

typedef struct S { u8 pad00[0x2E8]; s16 f2E8; } S;

extern u8 factory_FactoryPartLiftAt_501f30(S *p);

u8 factory_FactoryPartRemoveAt_500ef0(S *p)
{
    u8 r;

    r = factory_FactoryPartLiftAt_501f30(p);
    p->f2E8 = -1;
    return r;
}

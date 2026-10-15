#include "types.h"

typedef struct A {
    u8  pad00[0x2E8];
    s16 f2E8;
} A;

extern u8 factory_FactoryPartLiftAtPos_501ed0(A *p);

u8 factory_FactoryPartRemoveAtPos_500ec0(A *p)
{
    u8 r;

    r = factory_FactoryPartLiftAtPos_501ed0(p);
    p->f2E8 = -1;
    return r;
}

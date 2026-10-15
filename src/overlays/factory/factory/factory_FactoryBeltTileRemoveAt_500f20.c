#include "types.h"

typedef struct A {
    u8  pad00[0x2E6];
    s16 f2E6;
} A;

extern u8 factory_FactoryBeltTileRemoveAtCell_501f90(A *p);

u8 factory_FactoryBeltTileRemoveAt_500f20(A *p)
{
    u8 r;

    r = factory_FactoryBeltTileRemoveAtCell_501f90(p);
    p->f2E6 = -1;
    return r;
}

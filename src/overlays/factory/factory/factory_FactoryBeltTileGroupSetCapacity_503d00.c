#include "types.h"

typedef struct A {
    u8  pad00[0xA];
    s16 f0A;
} A;

extern A *factory_FactoryBeltTileGroupFindById_5040d0(void *p, s32 a, s32 b);

void factory_FactoryBeltTileGroupSetCapacity_503d00(void *p, s32 a, s32 b)
{
    A *e;

    e = factory_FactoryBeltTileGroupFindById_5040d0(p, a, b);
    if (e != 0) {
        e->f0A = b;
    }
}

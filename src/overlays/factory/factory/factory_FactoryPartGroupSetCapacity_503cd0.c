#include "types.h"

typedef struct Group { u8 pad00[0xA]; s16 f0A; } Group;

extern Group *factory_FactoryPartGroupFindById_504080(s32 h, s32 k);

void factory_FactoryPartGroupSetCapacity_503cd0(s32 h, s32 k, s16 v)
{
    Group *g;

    g = factory_FactoryPartGroupFindById_504080(h, k);
    if (g != 0) {
        g->f0A = v;
    }
}

#include "types.h"

typedef struct Group { u8 pad00[0x4]; } Group;

extern Group *factory_FactoryPartGroupFindById_504080(s32 h, s32 k);
extern void  *factory_FactoryPartGroupGetObj_4fea80(Group *g, s32 i);

void *factory_FactoryPartGroupGetObjById_5035b0(s32 h, s32 k, s32 i)
{
    Group *g;

    g = factory_FactoryPartGroupFindById_504080(h, k);
    if (g != 0) {
        return factory_FactoryPartGroupGetObj_4fea80(g, i);
    }
    return 0;
}

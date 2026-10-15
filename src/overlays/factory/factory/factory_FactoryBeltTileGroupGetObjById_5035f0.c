#include "types.h"

extern void *factory_FactoryBeltTileGroupFindById_5040d0(void *p, s32 a, s32 b);
extern s32   factory_FactoryBeltTileGroupGetObj_4ff180(void *e, s32 b);

s32 factory_FactoryBeltTileGroupGetObjById_5035f0(void *p, s32 a, s32 b)
{
    void *e;

    e = factory_FactoryBeltTileGroupFindById_5040d0(p, a, b);
    if (e != 0) {
        return factory_FactoryBeltTileGroupGetObj_4ff180(e, b);
    }
    return 0;
}

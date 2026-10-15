#include "types.h"

extern s32 factory_FactoryGridColFromX_503f60(void *p);
extern s32 factory_FactoryGridCellCenterX_503760(void *p, s32 a);

s32 factory_FactoryGridSnapX_5036a0(void *p)
{
    return factory_FactoryGridCellCenterX_503760(p, factory_FactoryGridColFromX_503f60(p));
}

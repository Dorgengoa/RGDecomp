#include "types.h"

extern s32 factory_FactoryFineGridColFromX_504020(void *p);
extern s32 factory_FactoryFineGridCellCenterX_5037c0(void *p, s32 a);

s32 factory_FactoryFineGridSnapX_503700(void *p)
{
    return factory_FactoryFineGridCellCenterX_5037c0(p, factory_FactoryFineGridColFromX_504020(p));
}

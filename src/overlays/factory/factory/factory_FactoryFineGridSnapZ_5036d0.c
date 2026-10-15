#include "types.h"

typedef struct S { u8 pad00[0x4]; } S;

extern s32  factory_FactoryFineGridRowFromZ_503fc0(S *p);
extern void factory_FactoryFineGridCellCenterZ_503790(S *p, s32 v);

void factory_FactoryFineGridSnapZ_5036d0(S *p)
{
    factory_FactoryFineGridCellCenterZ_503790(p, factory_FactoryFineGridRowFromZ_503fc0(p));
}

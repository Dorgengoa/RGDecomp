#include "types.h"

typedef struct S { u8 pad00[0x4]; } S;

extern s32  factory_FactoryGridRowFromZ_503f00(S *p);
extern void factory_FactoryGridCellCenterZ_503730(S *p, s32 v);

void factory_FactoryGridSnapZ_503670(S *p)
{
    factory_FactoryGridCellCenterZ_503730(p, factory_FactoryGridRowFromZ_503f00(p));
}

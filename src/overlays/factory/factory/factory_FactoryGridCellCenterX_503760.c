#include "types.h"

typedef struct S { u8 pad00[0x2A8]; f32 f2A8; u8 pad2AC[0xC]; f32 f2B8; } S;

f32 factory_FactoryGridCellCenterX_503760(S *p, s32 i)
{
    return p->f2B8 + (0.5f + i) * p->f2A8;
}

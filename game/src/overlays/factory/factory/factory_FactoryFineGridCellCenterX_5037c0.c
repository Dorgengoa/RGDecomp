/* rgp:protos */
#define RGP_SELF_factory_FactoryFineGridCellCenterX_5037c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x29C]; f32 f29C; u8 pad2A0[0x18]; f32 f2B8; } S;

f32 factory_FactoryFineGridCellCenterX_5037c0(S *p, s32 i)
{
    return p->f2B8 + (0.5f + i) * p->f29C;
}

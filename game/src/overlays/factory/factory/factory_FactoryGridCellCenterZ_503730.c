/* rgp:protos */
#define RGP_SELF_factory_FactoryGridCellCenterZ_503730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad00[0x2A8];
    f32 f2A8;
    u8  pad2AC[0x14];
    f32 f2C0;
} A;

f32 factory_FactoryGridCellCenterZ_503730(A *o, s32 i)
{
    return o->f2C0 + (0.5f + i) * o->f2A8;
}

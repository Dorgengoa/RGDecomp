#include "types.h"

typedef struct A {
    u8  pad00[0x29C];
    f32 f29C;
    u8  pad2A0[0x20];
    f32 f2C0;
} A;

f32 factory_FactoryFineGridCellCenterZ_503790(A *o, s32 i)
{
    return o->f2C0 + (0.5f + i) * o->f29C;
}

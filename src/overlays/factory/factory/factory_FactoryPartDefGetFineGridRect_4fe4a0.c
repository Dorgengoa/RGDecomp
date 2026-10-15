#include "types.h"

typedef struct A {
    u8  pad00[0x30];
    s32 f30;
    s32 f34;
} A;

extern void factory_FactoryGridRectAt_4fe600(A *o, s32 b, s32 x, s32 y, s32 c, s32 d, s32 e);

void factory_FactoryPartDefGetFineGridRect_4fe4a0(A *o, s32 b, s32 c, s32 d, s32 e)
{
    factory_FactoryGridRectAt_4fe600(o, b, o->f30, o->f34, c, d, e);
}

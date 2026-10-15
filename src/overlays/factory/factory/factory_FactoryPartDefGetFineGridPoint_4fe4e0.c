#include "types.h"

typedef struct A {
    u8  pad00[0x20];
    s32 f20;
    s32 f24;
} A;

extern void factory_FactoryGridPointAt_4fe7c0(A *o, s32 b, s32 x, s32 y, s32 c, s32 d, s32 e);

void factory_FactoryPartDefGetFineGridPoint_4fe4e0(A *o, s32 b, s32 c, s32 d, s32 e)
{
    factory_FactoryGridPointAt_4fe7c0(o, b, o->f20, o->f24, c, d, e);
}

#include "types.h"

typedef struct S {
    s32 f00;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
} S;

extern void factory_FactorySlotResetState_4ff590(S *p);

void factory_FactorySlotClear_4ff5d0(S *p)
{
    p->f00 = 0;
    p->f04 = -1;
    p->f06 = 0;
    p->f08 = -1;
    p->f0A = 0;
    p->f0C = 0;
    factory_FactorySlotResetState_4ff590(p);
}

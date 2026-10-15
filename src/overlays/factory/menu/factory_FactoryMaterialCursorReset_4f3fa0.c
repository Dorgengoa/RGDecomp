#include "types.h"

typedef struct A {
    s32 f00;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
} A;

void factory_FactoryMaterialCursorReset_4f3fa0(A *p)
{
    p->f00 = 0;
    p->f04 = 0;
    p->f06 = -1;
    p->f08 = -1;
    p->f0C = 0;
    p->f0A = 0;
}

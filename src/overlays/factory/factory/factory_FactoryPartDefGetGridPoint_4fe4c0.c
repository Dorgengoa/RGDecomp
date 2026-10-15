#include "types.h"

typedef struct S { u8 pad00[0x28]; s32 f28; s32 f2C; } S;

extern void factory_FactoryGridPointAt_4fe7c0(S *p, s32 a, s32 b, s32 c, s32 d, s32 e,
                                 s32 f);

void factory_FactoryPartDefGetGridPoint_4fe4c0(S *p, s32 a, s32 b, s32 c, s32 d)
{
    factory_FactoryGridPointAt_4fe7c0(p, a, p->f28, p->f2C, b, c, d);
}

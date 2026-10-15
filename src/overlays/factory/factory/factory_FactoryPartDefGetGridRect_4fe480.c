#include "types.h"

typedef struct S { u8 pad00[0x38]; s32 f38; s32 f3C; } S;

extern void factory_FactoryGridRectAt_4fe600(S *p, s32 a, s32 b, s32 c, s32 d, s32 e,
                                 s32 f);

void factory_FactoryPartDefGetGridRect_4fe480(S *p, s32 a, s32 b, s32 c, s32 d)
{
    factory_FactoryGridRectAt_4fe600(p, a, p->f38, p->f3C, b, c, d);
}

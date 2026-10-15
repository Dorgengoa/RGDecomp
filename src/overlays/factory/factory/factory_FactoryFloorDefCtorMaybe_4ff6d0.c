#include "types.h"

typedef struct S { u8 pad00[0x4]; } S;

extern void factory_FactoryFloorDefInitMaybe_4ff5f0(S *p, s32 a, s32 b, s32 c, s32 d, s32 e,
                                 s32 f, s32 g, s32 h, s32 i);

S *factory_FactoryFloorDefCtorMaybe_4ff6d0(S *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f,
                        s32 g, s32 h, s32 i)
{
    factory_FactoryFloorDefInitMaybe_4ff5f0(p, a, b, c, d, e, f, g, h, i);
    return p;
}

/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefPathCtor_4ff960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x4]; } S;

/*rgp*/


S *factory_FactoryPartDefPathCtor_4ff960(S *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f,
                        s32 g, s32 h)
{
    factory_FactoryPartDefPathInit_4ff810(p, a, b, c, d, e, f, g, h);
    return p;
}

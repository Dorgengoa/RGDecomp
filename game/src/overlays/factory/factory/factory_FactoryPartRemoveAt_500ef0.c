/* rgp:protos */
#define RGP_SELF_factory_FactoryPartRemoveAt_500ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x2E8]; s16 f2E8; } S;

/*rgp*/

u8 factory_FactoryPartRemoveAt_500ef0(S *p, int rgp_a1, int rgp_a2)
{
    u8 r;

    r = factory_FactoryPartLiftAt_501f30(p, (int)rgp_a1, (int)rgp_a2);
    p->f2E8 = -1;
    return r;
}

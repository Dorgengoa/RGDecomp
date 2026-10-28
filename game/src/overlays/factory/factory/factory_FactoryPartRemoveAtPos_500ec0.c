/* rgp:protos */
#define RGP_SELF_factory_FactoryPartRemoveAtPos_500ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad00[0x2E8];
    s16 f2E8;
} A;

/*rgp*/

u8 factory_FactoryPartRemoveAtPos_500ec0(A *p, float rgp_f0, float rgp_f1)
{
    u8 r;

    r = factory_FactoryPartLiftAtPos_501ed0(p, (float)rgp_f0, (float)rgp_f1);
    p->f2E8 = -1;
    return r;
}

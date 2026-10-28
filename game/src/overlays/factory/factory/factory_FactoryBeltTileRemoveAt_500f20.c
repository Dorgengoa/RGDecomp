/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltTileRemoveAt_500f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad00[0x2E6];
    s16 f2E6;
} A;

/*rgp*/

u8 factory_FactoryBeltTileRemoveAt_500f20(A *p, int rgp_a1, int rgp_a2)
{
    u8 r;

    r = factory_FactoryBeltTileRemoveAtCell_501f90(p, (int)rgp_a1, (int)rgp_a2);
    p->f2E6 = -1;
    return r;
}

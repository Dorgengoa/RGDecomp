/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltTileGroupSetCapacity_503d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad00[0xA];
    s16 f0A;
} A;

/*rgp*/

void factory_FactoryBeltTileGroupSetCapacity_503d00(void *p, s32 a, s32 b)
{
    A *e;

    e = ((A *)factory_FactoryBeltTileGroupFindById_5040d0(p, a));
    if (e != 0) {
        e->f0A = b;
    }
}

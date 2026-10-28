/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupSetCapacity_503cd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Group { u8 pad00[0xA]; s16 f0A; } Group;

/*rgp*/

void factory_FactoryPartGroupSetCapacity_503cd0(s32 h, s32 k, s16 v)
{
    Group *g;

    g = ((Group *)factory_FactoryPartGroupFindById_504080(h, k));
    if (g != 0) {
        g->f0A = v;
    }
}

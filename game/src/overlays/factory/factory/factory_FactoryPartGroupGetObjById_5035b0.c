/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupGetObjById_5035b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Group { u8 pad00[0x4]; } Group;

/*rgp*/
/*rgp*/

void *factory_FactoryPartGroupGetObjById_5035b0(s32 h, s32 k, s32 i)
{
    Group *g;

    g = ((Group *)factory_FactoryPartGroupFindById_504080(h, k));
    if (g != 0) {
        return factory_FactoryPartGroupGetObj_4fea80(g, i);
    }
    return 0;
}

/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltTileGroupGetObjById_5035f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 factory_FactoryBeltTileGroupGetObjById_5035f0(void *p, s32 a, s32 b)
{
    void *e;

    e = factory_FactoryBeltTileGroupFindById_5040d0(p, a);
    if (e != 0) {
        return ((s32)factory_FactoryBeltTileGroupGetObj_4ff180(e, b));
    }
    return 0;
}

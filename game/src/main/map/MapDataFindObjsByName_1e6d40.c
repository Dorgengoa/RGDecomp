/* rgp:protos */
#define RGP_SELF_MapDataFindObjsByName_1e6d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MapDataFindObjsByName_1e6d40(s32 pad0, s32 a1, s32 a2, s32 a3)
{
    s32 h;

    if (((a1 == 0) || (a2 == 0)) || (a3 <= 0)) return 0;
    h = MapDataGetModel_1e7810((void *)pad0);
    if (h != 0) {
        return MapObjFindAllByName_188cf0(h, a1, a2, a3);
    }
    return 0;
    return MapObjFindAllByName_188cf0(h, a1, a2, a3);
}

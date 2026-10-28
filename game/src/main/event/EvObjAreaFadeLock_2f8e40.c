/* rgp:protos */
#define RGP_SELF_EvObjAreaFadeLock_2f8e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void EvObjAreaFadeLock_2f8e40(u8 *p)
{
    void *a;

    if (*(f32 *)(p + 0xE4) < 1.0f) {
        a = GetMapMgr_201a90();
        MapSetDataFlag4ById_1e4d30(a, EvObjGetAreaId_2f8f30(p), 1);
    }
}

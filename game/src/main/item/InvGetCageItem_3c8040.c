/* rgp:protos */
#define RGP_SELF_InvGetCageItem_3c8040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 InvGetCageItem_3c8040(void *a0, void *a1)
{
    void *r;

    r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B1, a1, 0);
    if (r == 0) {
        r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B1, a1, 9);
        if (r == 0) {
            return 0;
        }
    }
    return ((s32)InvObjCastToCage_3d3c80(r, 0, 0, 0));
}

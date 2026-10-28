/* rgp:protos */
#define RGP_SELF_InvGetItem4B0_3c80c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 InvGetItem4B0_3c80c0(void *a0, void *a1)
{
    void *r;

    r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B0, a1, 0);
    if (r == 0) {
        r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B0, a1, 9);
        if (r == 0) {
            return 0;
        }
    }
    return ((s32)InvObjCastToItem4B0_3d3cd0(r, 0, 0, 0));
}

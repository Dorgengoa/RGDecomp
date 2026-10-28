/* rgp:protos */
#define RGP_SELF_HeapProbeLargestGapMaybe_2504d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 HeapProbeLargestGapMaybe_2504d0(u8 *arg0)
{
    s32 r;
    s32 v;

    v = *(s32 *)(arg0 + 0x1808);
    r = ((s32)MemStackHeapAlloc_14db10(v, 2, 0, 0x40));
    MemStackReturnToOwnerMaybe_14dad0(v);
    MemStackHeapFree_14dcb0(v, r);
    return r;
}

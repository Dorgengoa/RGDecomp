/* rgp:protos */
#define RGP_SELF_ActDataFindCnctByMask_225c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Mask search over the 8-byte-stride table at +0x1C (count s16 at +0x24).
   The accessor is called TWICE - the `and` result is held in a
   callee-saved register across the second call. */

/*rgp*/

s32 ActDataFindCnctByMask_225c00(s32 arg0, long long arg1)
{
    s32 p;
    s32 i;

    p = *(s32 *)(arg0 + 0x1C);
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)(arg0 + 0x24); i++, p += 8) {
        if ((arg1 & ActDataCnctGetCmndMask_2274c0(p)) == ActDataCnctGetCmndMask_2274c0(p)) {
            return p;
        }
    }
    return 0;
}

/* rgp:protos */
#define RGP_SELF_ActCfgTableFindCnctByMaskRefs_2208a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Iterate an 8-byte-stride pair array, handing each pair plus the float
   through to ActCfgTableFindCnctByMask_220950 and returning the first non-zero result. */

/*rgp*/

s32 ActCfgTableFindCnctByMaskRefs_2208a0(s32 arg0, s32 arg1, s32 arg2, long long arg3, f32 f)
{
    s32 i;
    s32 r;

    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < arg2; i++, arg1 += 8) {
        r = ((s32)ActCfgTableFindCnctByMask_220950(arg0, *(s32 *)arg1, *(s32 *)(arg1 + 4), (long long)(arg3), f));
        if (r != 0) {
            return r;
        }
    }
    return 0;
}

/* rgp:protos */
#define RGP_SELF_BitArrayAlloc_42ced0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/

s32 BitArrayAlloc_42ced0(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_2_2;
    u16 var_2;
    u32 temp_16;
    u32 temp_2;

    *(s32 *)((u8 *)arg0 + 0) = 0;
    *(u32 *)((u8 *)arg0 + 4) = 0U;
    *(s32 *)((u8 *)arg0 + 8) = 0;
    temp_2 = AlignUp_311a80(arg1, 0x20);
    *(s32 *)((u8 *)arg0 + 0) = 0;
    temp_16 = temp_2 >> 5;
    *(u32 *)((u8 *)arg0 + 4) = 0U;
    if (temp_16 == 0) {
        var_2 = 0;
    } else {
        temp_2_2 = ((s32)BumpArenaAlloc_42e300(temp_16 * 4, arg2, arg3));
        *(s32 *)((u8 *)arg0 + 0) = temp_2_2;
        if (temp_2_2 == 0) {
            var_2 = 0;
        } else {
            *(u32 *)((u8 *)arg0 + 4) = temp_16;
            var_2 = 1;
        }
    }
    if (!var_2) {
        return 0;
    }
    *(s32 *)((u8 *)arg0 + 8) = arg1;
    return 1;
    return 0;
}

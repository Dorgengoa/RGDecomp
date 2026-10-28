/* rgp:protos */
#define RGP_SELF_GroupFindSubEntryNth_425520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 GroupFindSubEntryNth_425520(void *arg0, s64 arg1, s32 arg2, s32 arg3)
{
    s32 temp_2;

    if (*(s32 *)((u8 *)arg0 + 0x8) == 0) {
        return 0;
    }
    temp_2 = GroupFindByKey_4256c0(arg0, (s32)(s16)arg1);
    if (temp_2 != 0) {
        return ((s32)GroupSubEntryFindNth_425e10(temp_2, (long long)(arg2), arg3));
    }
    return 0;
}

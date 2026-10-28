/* rgp:protos */
#define RGP_SELF_MotResCopyAndRelocate_154650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MotResCopyAndRelocate_154650(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_17;
    s32 temp_2;
    s32 var_18;
    s32 var_2;

    var_18 = arg1;
    if (var_18 == 0) {
        return 0;
    }
    if (arg3 > 0) {
        var_2 = arg3 >> 4;
        if (arg3 < 0) {
            var_2 = (arg3 + 0xF) >> 4;
        }
        temp_17 = var_2 + 1;
        temp_2 = MemStackAllocQw_14d950(arg2, temp_17);
        if (temp_2 == 0) {
            return 0;
        }
        QwordCopy_14cee0(temp_2, var_18, temp_17);
        var_18 = temp_2;
    }
    return !MotResRelocate_14bd50(arg0, var_18) & 0xFF;
}

/* rgp:protos */
#define RGP_SELF_EventRefListAllResolved_304890 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/

s32 EventRefListAllResolved_304890(void *arg0) {
    s32 temp_16;
    s32 var_17;

    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    var_17 = 0;
    while (var_17 < *(s32 *)((u8 *)arg0 + 8)) {
        temp_16 = var_17 * 0x30;
        if (((((short)TargetRefGetKind_2e7130(*(s32 *)((u8 *)arg0 + 4) + temp_16)) == 6) ||
             (((short)TargetRefGetKind_2e7130(*(s32 *)((u8 *)arg0 + 4) + temp_16)) == 7)) &&
            (TargetRefGetObj_2e7110(*(s32 *)((u8 *)arg0 + 4) + temp_16) == 0)) {
            return 0;
        }
        var_17 += 1;
    }
    return 1;
}

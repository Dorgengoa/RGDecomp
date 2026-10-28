/* rgp:protos */
#define RGP_SELF_MinimapMgrAdd_322170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MinimapMgrAdd_322170(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8) {
    s32 volatile spBC;
    s32 var_17;
    s32 temp_16;

    spBC = arg7;
    GetGameData_1fede0();
    if (MinimapMgrFindSlotByName_322340(arg0, arg1) != 0) {
        return 0;
    }
    var_17 = 0;
    while (var_17 < 3) {
        temp_16 = arg0 + var_17 * 0x1B0;
        if (MinimapSlotIsActive_322510(temp_16) == 0) {
            if (MinimapSlotLoad_3224d0(temp_16, arg2, arg3, arg4, arg5, arg6, spBC, arg_sp0, (int)((s64)arg_sp8)) != 0) {
                MinimapSlotSetName_322530(temp_16, arg1);
                return 1;
            }
            return 0;
        }
        var_17 += 1;
    }
    return 0;
}

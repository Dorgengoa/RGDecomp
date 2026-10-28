/* rgp:protos */
#define RGP_SELF_MapResolveGroundMaterialIdMaybe_1e5290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapResolveGroundMaterialIdMaybe_1e5290(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_2_2;
    void *var_2;

    if (arg2 != 0) {
        return arg2;
    }
    if (arg2 == 0) {
        temp_2 = MapSlotsFindBlockById_1e49b0(arg0, arg1, 0);
        if (temp_2 != 0) {
            temp_2_2 = MapSlotsFindShareById_1e4a50(arg0, ((short)MapBlockGetShareId_1e0080(temp_2)), 0);
            if (temp_2_2 != 0) {
                var_2 = MapDataGetModel_1e7810(temp_2_2);
            } else {
                var_2 = MapDataGetModel_1e7810(temp_2);
            }
            if (var_2 != NULL) {
                arg2 = *(s32 *)((u8 *)var_2 + 0x1FC);
            }
        }
    }
    return arg2;
}

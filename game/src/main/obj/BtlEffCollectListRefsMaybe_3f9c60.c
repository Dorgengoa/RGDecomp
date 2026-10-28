/* rgp:protos */
#define RGP_SELF_BtlEffCollectListRefsMaybe_3f9c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 BtlEffCollectListRefsMaybe_3f9c60(s32 unused0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 *var_16;
    s32 var_20;
    s32 var_8;

    var_8 = arg4;
    if (arg1 == NULL) {
        return var_8;
    }
    var_16 = *(s32 **)((u8 *)arg1 + 0x18);
    if (var_16 == NULL) {
        return var_8;
    }
    for (var_20 = 0; var_20 < *(s16 *)((u8 *)arg1 + 0x12); var_20++, var_16++) {
        var_8 = ArrayAddUnique_3f9c00(*var_16, arg2, arg3, var_8);
    }
    return var_8;
}

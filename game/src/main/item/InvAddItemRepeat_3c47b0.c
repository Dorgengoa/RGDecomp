/* rgp:protos */
#define RGP_SELF_InvAddItemRepeat_3c47b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S003c47b0 {
    u8 pad0[0x10];
    s32 unk10;
} S003c47b0;

/*rgp*/
/*rgp*/
/*rgp*/
extern S003c47b0 *D_00483890;

s32 InvAddItemRepeat_3c47b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_18;
    s32 var_17;
    s32 var_16;

    var_18 = 0;
    var_17 = 0;
    while (var_17 < arg3) {
        var_16 = ((s32)InvAddItemCoreMaybe_3c6540(arg0, arg1, arg2, 1, -1, 0, 0));
        if ((var_16 == 0) && ((arg2 == 0) || (arg2 == 1) || (arg2 == 0xA))) {
            var_16 = ((s32)InvAddItemCoreMaybe_3c6540(arg0, arg1, 9, 1, -1, 0, 0));
            if ((var_16 != 0) && (D_00483890 != NULL)) {
                StateFlagSet_3ccb70(D_00483890->unk10, 0x7F8, 1, 1);
            }
        }
        if (var_18 == 0) {
            var_18 = var_16;
        }
        var_17 += 1;
    }
    if ((var_18 != 0) && ((arg2 == 0) || (arg2 == 1) || (arg2 == 0xA))) {
        MapApplySaveStateMaybe_1fe560();
    }
    return var_18;
}

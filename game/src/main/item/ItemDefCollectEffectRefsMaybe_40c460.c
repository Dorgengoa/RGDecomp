/* rgp:protos */
#define RGP_SELF_ItemDefCollectEffectRefsMaybe_40c460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/

s32 ItemDefCollectEffectRefsMaybe_40c460(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_17;
    s32 var_16 = arg4;
    void *temp_2;
    void *temp_3;

    if (arg1 == NULL) {
        return var_16;
    }
    temp_3 = *(void **)((u8 *)arg0 + 4);
    if (temp_3 == NULL) {
        return var_16;
    }
    temp_17 = *(s32 *)((u8 *)temp_3 + 0x48);
    if (temp_17 == 0) {
        return var_16;
    }
    var_16 = BtlEffSetRowCollectRefsMaybe_3f9da0(temp_17, *(s32 *)((u8 *)arg1 + 0x24), arg2, arg3, arg4);
    var_16 = BtlEffSetRowCollectRefsMaybe_3f9da0(temp_17, *(s32 *)((u8 *)arg1 + 0x28), arg2, arg3, var_16);
    temp_2 = ItemDefGetWeaponData_40e110(arg1);
    if (temp_2 != NULL) {
        var_16 = BtlEffSetRowCollectRefsMaybe_3f9da0(temp_17, *(s32 *)((u8 *)temp_2 + 0x28), arg2, arg3, var_16);
    }
    return var_16;
}

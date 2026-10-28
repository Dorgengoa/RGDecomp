/* rgp:protos */
#define RGP_SELF_CharaCollectEffectRefsMaybe_3aaef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct S003aaef0 {
    u8 pad0[0x23E];
    s16 unk23E[2];
    s16 unk242;
    s16 unk244;
} S003aaef0;

typedef struct D00483818Type {
    u8 pad0[0x18];
    s32 unk18;
} D00483818Type;

/*rgp*/
/*rgp*/
/*rgp*/
extern D00483818Type *D_00483818;

s32 CharaCollectEffectRefsMaybe_3aaef0(S003aaef0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    u8 *var_20;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 var_16_2;
    s32 var_17;
    s16 *var_16;
    s32 var_21;

    var_17 = arg5;
    if (D_00483818 == NULL) {
        return var_17;
    }
    if (arg1 != 0) {
        var_16 = arg0->unk23E;
        var_21 = 0;
        do {
            temp_2 = ((s32)InvFindByUniqueId_3c85d0(D_00483818->unk18, *var_16, -1, 0));
            if (temp_2 != 0) {
                var_17 = ItemCollectEffectRefsMaybe_3d4e10(temp_2, arg3, arg4, var_17);
            }
            var_21 += 1;
            var_16 = &var_16[1];
        } while (var_21 < 2);
        temp_2_2 = ((s32)InvFindByUniqueId_3c85d0(D_00483818->unk18, arg0->unk242, -1, 0));
        if (temp_2_2 != 0) {
            var_17 = ItemCollectEffectRefsMaybe_3d4e10(temp_2_2, arg3, arg4, var_17);
        }
        temp_2_3 = ((s32)InvFindByUniqueId_3c85d0(D_00483818->unk18, arg0->unk244, -1, 0));
        if (temp_2_3 != 0) {
            var_17 = ItemCollectEffectRefsMaybe_3d4e10(temp_2_3, arg3, arg4, var_17);
        }
    }
    if (arg2 != 0) {
        var_20 = (u8 *) arg0 + 0x308;
        var_16_2 = 0;
        do {
            if (var_20 != NULL) {
                var_17 = EquipSlotCollectEffectRefsMaybe_3a03e0(var_20, arg3, arg4, var_17);
            }
            var_16_2 += 1;
            var_20 += 0x28;
        } while (var_16_2 < 0xA);
    }
    return var_17;
}

/* rgp:protos */
#define RGP_SELF_ScriptFnSpawnObj_3d8000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00483960;
extern s32 D_00483964;

void ScriptFnSpawnObj_3d8000(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s64 temp_16;
    f32 var_f23;
    f32 var_f22;
    f32 var_f21;
    f32 var_f20;
    s32 temp_16_2;
    s32 temp_2_2;
    s32 temp_2_3;
    u8 var_18;
    void *temp_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    temp_16 = (s64)(s16)VariantGetS16_36fcc0(arg3);
    if (arg2 >= 2) {
        VariantGetS16_36fcc0(arg3 + 0x38);
    }
    var_f23 = 0.0f;
    var_18 = 0;
    var_f22 = 0.0f;
    var_f21 = 0.0f;
    var_f20 = 0.0f;
    if (arg2 >= 6) {
        var_18 = 1;
        var_f23 = VariantGetFloat_36f7a0(arg3 + 0x70);
        var_f22 = VariantGetFloat_36f7a0(arg3 + 0xA8);
        var_f21 = VariantGetFloat_36f7a0(arg3 + 0xE0);
        var_f20 = VariantGetFloat_36f7a0(arg3 + 0x118);
    }
    temp_2 = ObjSpawnTreeValidated_2f3370((void *)(temp_16));
    if (temp_2 != NULL) {
        temp_16_2 = S32(temp_2, 0xC);
        if (var_18) {
            temp_2_2 = ((s32)GetActionMgr_1fdb50());
            if (temp_2_2 != 0) {
                temp_2_3 = ((s32)ActionMgrFindById_233b50(temp_2_2, temp_16_2));
                if (temp_2_3 != 0) {
                    CharaSetPosXYZ_2139e0(temp_2_3, var_f23, var_f22, var_f21);
                    CharaSetYaw_2138f0(temp_2_3, var_f20);
                }
            }
        }
        VariantSetS32_36f040(arg0, 1, 1);
    }
}

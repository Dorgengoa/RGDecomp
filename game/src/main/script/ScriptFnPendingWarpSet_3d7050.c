/* rgp:protos */
#define RGP_SELF_ScriptFnPendingWarpSet_3d7050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x1A6];
    s16 unk1A6;
} Elem18_00483960;

typedef struct {
    u8 pad0[0x18];
    Elem18_00483960 *unk18;
} Obj00483960;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Obj00483960 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnPendingWarpSet_3d7050(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_17;
    s32 temp_16;
    s32 temp_2;
    s32 var_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    temp_16 = VariantGetS32_36fb30(arg3);
    var_2 = -1;
    if (arg2 >= 2) {
        var_2 = VariantGetS32_36fb30(arg3 + 0x38);
    }
    PartyPendingWarpSet_3c98b0(D_00483960->unk18, temp_16, var_2, -1.0f, -1.0f);
    temp_17 = D_00483960->unk18->unk1A6;
    temp_2 = ((s32)GetMapMgr_201a90());
    if (temp_2 != 0) {
        MapMgrWarpMenuLoad_1e2f60(temp_2, temp_17, temp_16, 1);
    }
    VariantSetS32_36f040(arg0, 1, 1);
}

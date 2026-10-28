/* rgp:protos */
#define RGP_SELF_ScriptFnPartyRemoveMember_3d8b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off


typedef struct S00483960_2 {
    u8 pad14[0x14];
    s32 unk14;
    s32 unk18;
} S00483960_2;

typedef struct Obj3a8a70 {
    u8 pad[0xC];
    s32 unkC;
} Obj3a8a70;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern S00483960_2 *D_00483960;
extern s32 D_00483964;

void ScriptFnPartyRemoveMember_3d8b10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 id;
    s32 var_16;
    s32 h;
    Obj3a8a70 *temp_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    id = VariantGetS16_36fcc0(arg3);
    var_16 = 0;
    if (arg2 >= 2) {
        var_16 = ((signed char)VariantGetS8_36fe50(arg3 + 0x38)) != 0;
    }
    temp_2 = ((Obj3a8a70 *)CharaMgrPoolFindByDataId_3a8a70(D_00483960->unk14, id, 1, 1, 0, 0, 0));
    if (temp_2 != NULL) {
        h = temp_2->unkC;
        VariantSetS32_36f040(arg0, PartyRemoveMember_3c0fa0(D_00483960->unk18, h, var_16, 0) != 0, 1);
    }
}

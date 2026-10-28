#pragma opt_propagation off
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
VC_VPTR_MEMBER;






























































































































































































































s32 get(s32 a0) { return VCM(s32, (void *, s32), 0x384, a0); }
};
extern "C" {
#pragma opt_common_subs off

extern s32 EquipSlotGetAbilityAbltName_3a06b0(s32 arg0);
extern s32 EquipSlotGetAbilityWeaponSlot_3a06e0(s32 arg0);
extern s32 CharaSysGetEncounterIdMaybe_3a36d0(s32 arg0);
extern s32 ItemGetWeaponAbltName_3d4f60(s32 arg0);
extern s32 D_0048016C;
extern void *D_00483818;

typedef s32 (*fn384_t)(void *, s32);

s32 CharaGetWeaponAbltName_3acb10(void *arg0, s32 arg1)
{
    s32 temp_2; s32 cmp;
    s32 temp_2_2;
    s32 temp_4;
    s32 var_18;
    void *vtbl;

    void *g=D_00483818;
    if (g == NULL) {
        return 0;
    }
    if ((*(s16 *)((u8 *)arg0 + 4) == 0x2AF9) &&
        (CharaSysGetEncounterIdMaybe_3a36d0(*(s32 *)((u8 *)g + 0x20)) == 0x271B)) {
        return D_0048016C;
    }
    var_18 = 0;
    vtbl = *(void **)((u8 *)arg0 + 0);
    temp_2 = ((Self *)arg0)->get(arg1);
    if (temp_2 != 0) {
        var_18 = ItemGetWeaponAbltName_3d4f60(temp_2);
    }
    temp_4 = *(s32 *)((u8 *)arg0 + 0x498);
    if (temp_4 != 0) { cmp=EquipSlotGetAbilityWeaponSlot_3a06e0(temp_4); if (cmp == arg1) {
        temp_2_2 = EquipSlotGetAbilityAbltName_3a06b0(*(s32 *)((u8 *)arg0 + 0x498));
        if (temp_2_2 != 0) {
            var_18 = temp_2_2;
        }
    }
    } return var_18;
}

}

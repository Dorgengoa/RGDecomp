#include "types.h"

class VE7160 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void act(f32 v) { VCM(void, (void *, f32), 0x2C0, v); }
};

typedef struct S00483960 {
    u8 pad0[0x1C];
    s32 unk1C;
} S00483960;

extern "C" {
extern void VariantSetS32_36f040(s32, s32, s32);
extern s32 VariantGetS32_36fb30(s32);
extern VE7160 *ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(s32, s32);
extern S00483960 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;
}

extern "C" void ScriptFnObjHpRaiseToPercent_3d7160(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_17;
    s32 var_16;
    VE7160 *temp_2;

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
    temp_17 = VariantGetS32_36fb30(arg3);
    var_16 = 0x32;
    if (arg2 >= 2) {
        var_16 = VariantGetS32_36fb30(arg3 + 0x38);
    }
    temp_2 = ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(D_00483960->unk1C, temp_17);
    if (temp_2 != NULL) {
        temp_2->act((f32)var_16);
    }
    VariantSetS32_36f040(arg0, 1, 1);
}

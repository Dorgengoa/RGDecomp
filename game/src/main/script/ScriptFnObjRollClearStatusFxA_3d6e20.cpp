#include "types.h"

class VE6E20 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void act(s32 a, s32 b) { VCM(void, (void *, s32, s32), 0x1C4, a, b); }
};

typedef struct {
    u8 pad0[0x1C];
    s32 unk1C;
} Obj00483960;

extern "C" {
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS32_36fb30(s32);
VE6E20 *ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(s32, s32);
extern Obj00483960 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;
}

extern "C" void ScriptFnObjRollClearStatusFxA_3d6e20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    VE6E20 *temp_2;

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
    temp_2 = ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(D_00483960->unk1C, VariantGetS32_36fb30(arg3));
    if (temp_2 != NULL) {
        temp_2->act(0x64, 0);
    }
    VariantSetS32_36f040(arg0, 1, 1);
}

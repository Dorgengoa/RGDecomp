#include "types.h"

class Obj3BAE30 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 slot228() { return VCM0(s32, 0x228); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 slot434() { return VCM0(s32, 0x434); }
};

typedef struct ArgObj {
    u8 pad0[0x10];
    void *unk10;
} ArgObj;

typedef struct ListObj {
    u8 pad0[0x14];
    s32 unk14;
} ListObj;

extern "C" Obj3BAE30 *PoolGetUsedElem_36acb0(void *, s32);

extern "C" s32 ObjMgrCountHpLow_3bae30(ArgObj *arg0) {
    ListObj *temp_2;
    s32 temp_17;
    s32 var_20;
    s32 var_19;
    Obj3BAE30 *temp_2_2;

    temp_2 = (ListObj *)arg0->unk10;
    if (temp_2 == NULL) {
        return 0;
    }
    temp_17 = temp_2->unk14;
    var_20 = 0;
    for (var_19 = 0; var_19 < temp_17; var_19++) {
        temp_2_2 = PoolGetUsedElem_36acb0(arg0->unk10, var_19);
        if (temp_2_2 != NULL) {
            if (temp_2_2->slot434() == 0) {
                if (temp_2_2->slot228() != 0) {
                    var_20 += 1;
                }
            }
        }
    }
    return var_20;
}

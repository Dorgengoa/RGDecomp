#include "types.h"

extern "C" {
class VT384 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    VT384 * get(s32 a0) { return VCM(VT384 *, (void *, s32), 0x384, a0); }
};

typedef struct Obj8680 {
    u8 pad[0x14];
    s32 unk14;
} Obj8680;

void *GetGameData_1fede0(void);
s32 CharaGetActionTable_214cd0(s32);
s32 ActCfgTableGetAtkPrmName_223510(s32, s32, s8, s32);
s32 ActionMgrFindById_233b50(void *, s32);
VT384 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern u8 D_004B8680[0x400];

s32 CharaGetAtkPrmName_1fb3c0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_2_3;
    VT384 *temp_2_4;
    VT384 *temp_2_2;

    if (arg2 == 0) {
        return arg2;
    }
    temp_2_3 = ActionMgrFindById_233b50(D_004B8680, arg0);
    if (temp_2_3 == 0) {
        return arg2;
    }
    temp_2 = CharaGetActionTable_214cd0(temp_2_3);
    if (temp_2 == 0) {
        return arg2;
    }
    temp_2_4 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)GetGameData_1fede0() + 0x14), arg0);
    if (temp_2_4 == NULL) {
        return arg2;
    }
    temp_2_2 = temp_2_4->get(arg1);
    if (temp_2_2 == NULL) {
        return arg2;
    }
    arg2 = ActCfgTableGetAtkPrmName_223510(temp_2, arg1, *(s8 *)(*(u8 **)((u8 *)temp_2_2 + 0x10) + 3), arg2);
    return arg2;
}

}

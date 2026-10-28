/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v141() { return VCM0(s32, 0x23C); }
};

extern "C" s32 GetGameData_1fede0();
extern "C" void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern "C" s32 ScriptSlotGetInt_2cc9c0(s32);
extern "C" struct C0 *ActorFindById_3eb870(s32, s32);
extern "C" s32 D_004DB928;

extern "C" s32 AiCmdUnitGetInvulnerable_2c5aa0(s32 arg0, s32 arg1)
{
    s32 var_18;
    s32 temp_16;
    s32 var_2;
    s32 temp_4;
    struct C0 *temp_2;

    var_18 = arg0;
    temp_16 = GetGameData_1fede0();
    var_2 = D_004DB928;
    if (arg1 == 2) {
        temp_4 = var_18;
        var_18 += 8;
        var_2 = ScriptSlotGetInt_2cc9c0(temp_4);
    }
    temp_2 = ActorFindById_3eb870(temp_16, var_2);
    if (temp_2 == NULL) {
        return 0;
    }
    ScriptSlotStoreIntRef_2cc900(var_18, temp_2->v141() & 0xFF);
    return 1;
}

#include "types.h"
extern "C" {

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 g(s32 a0) { return VCM(s32, (void *, s32), 0x1E0, a0); }
    
    
    
    
    
    
    
    s32 f(s32 a0) { return VCM(s32, (void *, s32), 0x200, a0); }
    
    s32 h(s32 a0) { return VCM(s32, (void *, s32), 0x208, a0); }
};

extern s32 GetGameData_1fede0();
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern VC *ActorFindById_3eb870(s32, s32);

s32 AiCmdUnitTestStatus_2c65c0(s64 *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 r1;
    s32 r2;
    a = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    b = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    r1 = 0;
    r2 = 0;
    a = (s32)ActorFindById_3eb870(GetGameData_1fede0(), a);
    if (a != 0) {
        r1 = ((VC *)a)->g(b) & 0xFF;
        if (r1 != 0) {
            r2 = ((VC *)a)->f(b) & 0xFF;
        } else {
            r2 = ((VC *)a)->h(b) & 0xFF;
        }
    }
    ScriptSlotStoreIntRef_2cc900((s32)arg0++, r1);
    if (arg1 == 4) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0, r2);
    }
    return 1;
}

}

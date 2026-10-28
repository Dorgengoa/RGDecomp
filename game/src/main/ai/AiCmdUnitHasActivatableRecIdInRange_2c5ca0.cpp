#include "types.h"

class V2c5ca0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 test(s32 a0) { return VCM(s32, (void *, s32), 0x2D0, a0); }
};

extern "C" {
extern s32 GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s32 arg0, s32 arg1);
extern s32 ScriptSlotGetInt_2cc9c0(s32 arg0);
extern V2c5ca0 *ActorFindById_3eb870(s32 arg0, s32 arg1);
extern u8 D_004DB928[0x400];
}

extern "C" s32 AiCmdUnitHasActivatableRecIdInRange_2c5ca0(s64 *arg0)
{
    s32 obj;
    s32 key;
    s32 base;
    V2c5ca0 *o;
    s32 i;

    obj = GetGameData_1fede0();
    key = *(s32 *)D_004DB928;
    base = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    o = ActorFindById_3eb870(obj, key);
    if (o == NULL) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0, 0);
        return 1;
    }
    for (i = 0; i < 3; i++) {
        if (o->test(base + i) != 0) {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, 1);
            return 1;
        }
    }
    ScriptSlotStoreIntRef_2cc900((s32)arg0, 0);
    return 1;
}

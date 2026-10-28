#include "types.h"
extern "C" {
class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x) { VCM(void, (void *, s32), 0x4E0, x); }
};

extern u8 *GetGameData_1fede0(void);
extern void EffectTimedSlotSpawn_2d8e40(s32);
extern s32 ScriptSlotGetInt_3348b0(s32);
extern void CharaSysStatusClear_3a1510(s32, s32);
extern VC *CharaMgrPoolFindById_3a8c60(s32, s32);

s32 ScriptCmdStatusToGaugeMaybe_32cba0(s32 arg0, s32 arg1)
{
    u8 *g;
    s32 id;
    VC *o;

    if (arg1 < 2) {
        return 1;
    }
    g = GetGameData_1fede0();
    if (ScriptSlotGetInt_3348b0(arg0 + 8) != 0) {
        id = ScriptSlotGetInt_3348b0(arg0 + 0x10);
        o = CharaMgrPoolFindById_3a8c60(*(s32 *)(g + 0x14), id);
        if (o != NULL) {
            o->f(ScriptSlotGetInt_3348b0(arg0));
            EffectTimedSlotSpawn_2d8e40(id);
        }
    } else {
        CharaSysStatusClear_3a1510(*(s32 *)(g + 0x20), ScriptSlotGetInt_3348b0(arg0));
    }
    return 1;
}
}

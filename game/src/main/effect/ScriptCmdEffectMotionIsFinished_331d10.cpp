#include "types.h"
#pragma opt_propagation off

class VE331D10 {
public:
    u8 pad000[0x190];
    VC_VPTR_MEMBER;
    
    
    
    s32 v4() { return VCM0(s32, 0x18); }
};

extern "C" VE331D10 *D_004826E0;

extern "C" s32 MotionListIsFinished_171d90(s32, s32);
extern "C" void ScriptSlotStoreIntRef_3347f0(s32, s32);
extern "C" void ScriptSlotGetInt_3348b0(s32);

extern "C" s32 ScriptCmdEffectMotionIsFinished_331d10(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 p;
    s32 var_16;

    if (arg1 != 2) {
        return 0;
    }
    p = arg0;
    ScriptSlotGetInt_3348b0(arg0 + 8);
    var_16 = 1;
    if (D_004826E0 != NULL) {
        temp_2 = D_004826E0->v4();
        if (temp_2 != 0) {
            var_16 = MotionListIsFinished_171d90(temp_2 + 0x1F0, -1);
        }
    }
    ScriptSlotStoreIntRef_3347f0(p, var_16);
    return 1;
}

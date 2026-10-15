#include "types.h"

class Obj004826E0 {
    u8 pad0[0x190];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual s32 v18();
};

extern "C" {
extern s32 ModelObjPlayMotionByName_1867a0(s32, s32, s32);
extern s32 ScriptSlotGetCodeAddr_334870(s32);
extern s32 ScriptSlotGetInt_3348b0(s32);
extern Obj004826E0 *D_004826E0;
}

extern "C" s32 ScriptCmdEffectPlayMotion_331e00(s64 *arg0, s32 arg1)
{
    s32 temp_17;
    s32 temp_2;
    s32 var_16;

    if (arg1 < 2 || arg1 > 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    temp_17 = ScriptSlotGetCodeAddr_334870((s32)arg0++);
    var_16 = 0;
    if (arg1 > 2) {
        var_16 = ScriptSlotGetInt_3348b0((s32)arg0);
    }
    if (D_004826E0 == 0) {
        return 0;
    }
    temp_2 = D_004826E0->v18();
    if (temp_2 != 0) {
        ModelObjPlayMotionByName_1867a0(temp_2, temp_17, var_16);
    }
    return 1;
}

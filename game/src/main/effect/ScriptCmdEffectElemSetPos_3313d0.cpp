#include "types.h"

#undef NULL
#define NULL 0
extern "C" {

void ScriptSlotsToVec4_334810(void *, s32);
s32 ScriptSlotGetInt_3348b0(s32);
void sceVu0CopyVector(s32, void *);

class VC_0 {
public:
    u8 pad[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x60); }
};
typedef struct Obj4826E0 {
    u8 pad[0x190];
} Obj4826E0;
extern Obj4826E0 *D_004826E0;

s32 ScriptCmdEffectElemSetPos_3313d0(s64 *arg0, s32 arg1) {
    u8 sp50[16] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_2;
    s32 var_18;
    s32 var_19;
    s32 t;
    if ((arg1 != 4) & (arg1 != 5)) {
        return 0;
    }
    var_18 = ScriptSlotGetInt_3348b0((s32)arg0++);
    ScriptSlotsToVec4_334810(&sp50, (s32)arg0);
    t = (s32)arg0 + 0x18;
    var_19 = 1;
    if (arg1 == 5) {
        var_19 = ScriptSlotGetInt_3348b0(t);
    }
    temp_2 = ((VC_0 *)D_004826E0)->f();
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = var_19 + var_18;
    while (var_18 < temp_16) {
        sceVu0CopyVector(temp_2 + (var_18 * 0xC0) + 0xA0, &sp50);
        var_18 += 1;
    }
    return 1;
}

}

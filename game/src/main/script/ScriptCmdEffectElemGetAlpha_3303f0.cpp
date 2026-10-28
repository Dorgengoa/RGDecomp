#include "types.h"
extern "C" {

extern void ScriptSlotStoreFloatRef_3347d0(s32 arg0, f32 arg1);
extern s32 ScriptSlotGetInt_3348b0(s32);

class C_4826E0 {
public:
    u8 pad[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * get() { return VCM0(void *, 0x60); }
};
extern C_4826E0 *D_004826E0;

s32 ScriptCmdEffectElemGetAlpha_3303f0(s64 * arg0, s32 arg1)
{
    s32 temp_16;
    void *temp_2;

    if (arg1 != 2) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_3348b0((s32)arg0++);
    temp_2 = D_004826E0->get();
    if (temp_2 != NULL) {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, ((f32 *)((u8 *)temp_2 + 0xBC))[temp_16 * 0x30]);
    } else {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, 1.0f);
    }
    return 1;
}

}

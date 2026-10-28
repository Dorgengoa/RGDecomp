#include "types.h"

struct B32f { u8 pad00[0xB0]; };

class T32f : public B32f {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void s44(f32 *v) { VCM(void, (void *, f32 *), 0x44, v); }
};

extern "C" void *GetObjRefTable_313de0(void);
extern "C" void *ScriptSlotGetInt_3348b0(void *);
extern "C" T32f *HandleRegistryLookup_314aa0(void *, void *);
extern "C" void ScriptSlotStoreFloatRef_3347d0(void *, f32);

extern "C" s32 ScriptCmdAttackObjGetVelocity_32f180(u8 *a0, s32 mode)
{
    f32 v[4] __attribute__((aligned(16)));
    void *r;
    void *s;
    T32f *t;

    if (mode != 4) {
        return 0;
    }
    r = GetObjRefTable_313de0();
    s = ScriptSlotGetInt_3348b0(a0);
    t = HandleRegistryLookup_314aa0(r, s);
    if (t == 0) {
        return 1;
    }
    t->s44(v);
    ScriptSlotStoreFloatRef_3347d0(a0 + 0x8, v[0]);
    ScriptSlotStoreFloatRef_3347d0(a0 + 0x10, v[1]);
    ScriptSlotStoreFloatRef_3347d0(a0 + 0x18, v[2]);
    return 1;
}

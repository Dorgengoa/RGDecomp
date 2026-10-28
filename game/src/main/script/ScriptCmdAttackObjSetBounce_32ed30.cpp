#include "types.h"

class C32E {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v24(f32 a0) { VCM(void, (void *, f32), 0x68, a0); }
};

extern "C" void *GetObjRefTable_313de0(void);
extern "C" void *ScriptSlotGetInt_3348b0(void *p);
extern "C" C32E *HandleRegistryLookup_314aa0(void *a, void *b);
extern "C" f32 ScriptSlotGetFloat_334890(void *p);

extern "C" s32 ScriptCmdAttackObjSetBounce_32ed30(void *p, s32 mode)
{
    void *a;
    C32E *c;

    if (mode != 2) {
        return 0;
    }
    a = GetObjRefTable_313de0();
    c = HandleRegistryLookup_314aa0(a, ScriptSlotGetInt_3348b0(p));
    if (c == 0) {
        return 1;
    }
    c->v24(ScriptSlotGetFloat_334890((u8 *)p + 8));
    return 1;
}

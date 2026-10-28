#include "types.h"

struct Base21 {
    u8 pad000[0xB0];
};

class C0 : public Base21 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v19(f32 a, f32 b, f32 c) { VCM(void, (void *, f32, f32, f32), 0x54, a, b, c); }
};

extern "C" void *GetObjRefTable_313de0(void);
extern "C" void *ScriptSlotGetInt_3348b0(void *a);
extern "C" class C0 *HandleRegistryLookup_314aa0(void *a, void *b);
extern "C" f32 ScriptSlotGetFloat_334890(void *a);

extern "C" s32 ScriptCmdAttackObjSetPos_32f220(void *a, s32 mode)
{
    void *x;
    class C0 *o;
    f32 p;
    f32 q;
    f32 r;

    if (mode != 4) {
        return 0;
    }
    x = GetObjRefTable_313de0();
    o = HandleRegistryLookup_314aa0(x, ScriptSlotGetInt_3348b0(a));
    if (o == 0) {
        return 1;
    }
    p = ScriptSlotGetFloat_334890((u8 *)a + 8);
    q = ScriptSlotGetFloat_334890((u8 *)a + 0x10);
    r = ScriptSlotGetFloat_334890((u8 *)a + 0x18);
    o->v19(p, q, r);
    return 1;
}

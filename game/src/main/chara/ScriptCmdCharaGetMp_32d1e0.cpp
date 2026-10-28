#include "types.h"

/* lane N4 family: ScriptCmdCharaGetMp_32d1e0 / ScriptCmdCharaGetHp_32d2b0 (208 B each).
   C++: two virtual calls through a vptr at 0x00, slots 0x10C and 0x130. */

typedef struct { s32 a; s32 b; } Arg;

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vA() { return VCM0(s32, 0x10C); }
    
    
    
    
    
    
    
    
    s32 vB(s32 a0) { return VCM(s32, (void *, s32), 0x130, a0); }
};

extern "C" void *GetGameData_1fede0(void);
extern "C" s32 ScriptSlotGetInt_3348b0(Arg *);
extern "C" void *CharaMgrPoolFindById_3a8c60(void *, s32);
extern "C" void ScriptSlotStoreIntRef_3347f0(Arg *, s32);

extern "C" s32 ScriptCmdCharaGetMp_32d1e0(Arg *p, s32 kind)
{
    s32 r1;
    s32 r2;
    void *a;
    VE *o;
    s32 t;

    a = GetGameData_1fede0();
    t = ScriptSlotGetInt_3348b0(p++);
    r1 = 0;
    r2 = 0;
    o = (VE *)CharaMgrPoolFindById_3a8c60(*(void **)((u8 *)a + 0x14), t);
    if (o != 0) {
        r1 = o->vA();
        r2 = o->vB(1);
    }
    ScriptSlotStoreIntRef_3347f0(p++, r1);
    if (kind == 3) {
        ScriptSlotStoreIntRef_3347f0(p, r2);
    }
    return 1;
}

#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v58() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v72(s32 a0) { return VCM(s32, (void *, s32), 0x128, a0); }
};


struct S8 { s32 a; s32 b; };

extern "C" s32 GetGameData_1fede0(void);
extern "C" s32 ScriptGetInt_26a2a0(struct S8 *);
extern "C" s32 ActorFindById_3eb870(s32, s32);
extern "C" void ScriptSetRefInt_26a1e0(struct S8 *, s32);

extern "C" s32 EvCmdGetHp_25aa20(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv6;
    s32 rv7;
    s32 r2;

    r0 = GetGameData_1fede0();
    r1 = ScriptGetInt_26a2a0(p0++);
    rv6 = 0;
    rv7 = 0;
    r2 = ActorFindById_3eb870(r0, r1);
    if (r2 != 0) {
        rv6 = ((struct C0 *)r2)->v58();
        rv7 = ((struct C0 *)r2)->v72(1);
    }
    ScriptSetRefInt_26a1e0(p0++, rv6);
    if (p1 == 3) {
        ScriptSetRefInt_26a1e0(p0, rv7);
    }
    return 1;
}

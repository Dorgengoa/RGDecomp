#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v142(s32 a0) { return VCM(s32, (void *, s32), 0x240, a0); }
};


struct S8 { s32 a; s32 b; };

extern "C" s32 GetGameData_1fede0(void);
extern "C" s32 ScriptSlotGetInt_2cc9c0(S8 *);
extern "C" s32 ActorFindById_3eb870(s32, s32);

extern "C" s32 D_004DB928;

extern "C" s32 AiCmdUnitSetInvulnerable_2c5b30(S8 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r4;
    s32 r5;

    r0 = GetGameData_1fede0();
    rv2 = D_004DB928;
    if (p1 == 2) {
        rv2 = ScriptSlotGetInt_2cc9c0(p0++);
    }
    r4 = ActorFindById_3eb870(r0, rv2);
    if (r4 == 0) {
        return 0;
    }
    r5 = ScriptSlotGetInt_2cc9c0(p0);
    ((struct C0 *)r4)->v142((r5 != 0));
    return 1;
}

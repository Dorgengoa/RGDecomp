#include "types.h"
typedef struct { s32 a, b; } E8_2c67f0;
struct O2c67f0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v102(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }
};
extern "C" s32 ScriptSlotGetInt_2cc9c0(E8_2c67f0 *);
extern "C" s32 GetGameData_1fede0(void);
extern "C" O2c67f0 * ActorFindById_3eb870(s32, s32);

extern "C" s32 AiCmdUnitSetStatus_2c67f0(E8_2c67f0 *p0)
{
    s32 a;
    s32 b;
    s32 c;
    s32 ctx;
    O2c67f0 *o;

    a = ScriptSlotGetInt_2cc9c0(p0++);
    b = ScriptSlotGetInt_2cc9c0(p0++);
    c = ScriptSlotGetInt_2cc9c0(p0);
    ctx = GetGameData_1fede0();
    o = ActorFindById_3eb870(ctx, a);
    if (o != 0) {
        o->v102(b, c != 0, 1);
    }
    return 1;
}

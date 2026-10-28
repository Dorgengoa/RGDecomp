#include "types.h"
typedef struct { s32 a, b; } E8_2c5ff0;
struct O2c5ff0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v155(s32 a0) { return VCM(s32, (void *, s32), 0x274, a0); }
};
extern "C" s32 GetGameData_1fede0(void);
extern "C" s32 ScriptSlotGetInt_2cc9c0(E8_2c5ff0 *);
extern "C" O2c5ff0 * ActorFindById_3eb870(s32, s32);
extern "C" void ScriptSlotStoreIntRef_2cc900(E8_2c5ff0 *, s32);
extern "C" struct rgp_anon_D_004DB928 { s32 v; s32 pad[3]; } D_004DB928;

extern "C" s32 AiCmdUnitIsActionGaugeFull_2c5ff0(E8_2c5ff0 *p0, s32 p1)
{
    s32 ctx;
    s32 k;
    O2c5ff0 *o;
    s32 r;

    ctx = GetGameData_1fede0();
    k = D_004DB928.v;
    if (p1 == 2) {
        k = ScriptSlotGetInt_2cc9c0(p0++);
    }
    o = ActorFindById_3eb870(ctx, k);
    if (o == 0) {
        return 0;
    }
    r = o->v155(-1);
    if (r != 0) {
        ScriptSlotStoreIntRef_2cc900(p0, 1);
    } else {
        ScriptSlotStoreIntRef_2cc900(p0, 0);
    }
    return 1;
}

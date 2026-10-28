/* rgp:protos */
#line 1
#include "types.h"

struct Base332680 { u8 pad000[0x190]; };
struct C332680 : Base332680 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    void v13(s16 k, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, s16, int, int), 0x3C, k, rgp_fwd2, rgp_fwd3); }
};

extern "C" struct C332680 *D_004826E0;

extern "C" s32 ScriptCmdEffectSetNextEntryId_332680(void *a, s32 k, int rgp_a2, int rgp_a3)
{
    if (k == 1) goto run;
    return 0;
run:
    D_004826E0->v13((s16)k, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return 1;
}

/* rgp:protos */
#line 1
#include "types.h"

struct E12 { u8 p0[8]; s32 m8; };

class VE16C {
public:
    u8 pad000[0x30];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    s32 v12(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x38, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad034[0x54 - 0x34];
    s32 unk54;
};

extern "C" void CollMeshSetTriAttr_16cd10(VE16C *arg0, s32 arg1, s32 arg2, int rgp_a3)
{
    E12 *temp_4;

    if ((arg1 < 0) || (arg1 >= arg0->v12((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3)))) {
        return;
    }
    temp_4 = (E12 *)arg0->unk54;
    if (temp_4 != NULL) {
        temp_4[arg1].m8 = arg2;
    }
}

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

extern "C" s32 CollMeshGetTriAttr_16cc90(VE16C *arg0, s32 arg1, int rgp_a2, int rgp_a3) {
    E12 *temp_3;

    if ((arg1 < 0) || (arg1 >= arg0->v12((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)))) {
        return 0;
    }
    temp_3 = (E12 *)arg0->unk54;
    if (temp_3 != 0) {
        return temp_3[arg1].m8;
    }
    return 0;
}

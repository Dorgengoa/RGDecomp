/* rgp:protos */
#line 1
#include "types.h"

class Obj5C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12() { VCM0(void, 0x38); }
    
    
    
    
    
    
    
    
    void v21(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x5C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

class Obj003ABD70 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12() { VCM0(void, 0x38); }
    u8 pad4[0x498 - 4];
    Obj5C *unk498;
};

extern "C" s32 CharaDeactivateEquipSlot_3abd70(Obj003ABD70 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Obj5C *temp;

    temp = arg0->unk498;
    if (temp != NULL) {
        temp->v21((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    arg0->unk498 = 0;
    arg0->v12();
    return 1;
}

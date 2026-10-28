/* rgp:protos */
#line 1
#include "types.h"

class Base003bd620 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void unk38() { VCM0(void, 0x38); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void unk114(s32 x) { VCM(void, (void *, s32), 0x114, x); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 unk2D0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x2D0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 EquipSlotDynamicCastKind2_39fe70(s32, int, int, int);
extern "C" s32 EquipSlotGetScaledCost_3a05c0(s32 x);

extern "C" s32 UnitUseAbility_3bd620(Base003bd620 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 temp;

    if (arg1 < 0) {
        return 0;
    }
    temp = arg0->unk2D0((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (temp == 0) {
        return 0;
    }
    if (EquipSlotDynamicCastKind2_39fe70(temp, 0, 0, 0) == 0) {
        return 0;
    }
    arg0->unk114(-EquipSlotGetScaledCost_3a05c0(temp));
    arg0->unk38();
    return temp;
}

/* rgp:protos */
#line 1
#include "types.h"

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v52() { return VCM0(s32, 0xD8); }
    
    
    
    
    
    
    
    
    
    
    
    s32 v64(s32 a0) { return VCM(s32, (void *, s32), 0x108, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v226(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x390, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" Ent * InvObjCastToSpecialWeapon_3d3d50(s32, int, int, int);

extern "C" s32 CharaCanUseSpecialWeaponRelated_3ad020(Ent *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 temp_2_2;
    Ent *temp_2;

    temp_2_2 = arg0->v226((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (temp_2_2 == 0) {
        return 0;
    }
    if ((s32)(*(u8 *)((u8 *)arg0 + 0x4BC)) > 0) {
        return 1;
    }
    temp_2 = InvObjCastToSpecialWeapon_3d3d50(temp_2_2, 0, 0, 0);
    if (temp_2->v52() > 0) {
        return 1;
    }
    s32 r = temp_2->v64(arg0->v21()) != 0;
    return r ^ 1;
}

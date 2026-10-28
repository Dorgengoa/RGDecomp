/* rgp:protos */
#line 1
#include "types.h"

extern "C" void ItemWeaponSetup_3d3730(void *, int, int, int);

class ObjD3050 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 slotBC(s32 a0) { return VCM(s32, (void *, s32), 0xC4, a0); }
};

extern "C" s32 ItemSpecialWeaponSetup_3d3050(ObjD3050 *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    ItemWeaponSetup_3d3730((void *)self, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    self->slotBC(1);
    return 1;
}

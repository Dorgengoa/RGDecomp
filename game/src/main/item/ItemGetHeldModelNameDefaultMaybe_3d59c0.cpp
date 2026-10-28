/* rgp:protos */
#line 1
#include "types.h"

class V3D59C0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v14(s32 a) { VCM(void, (void *, s32), 0x40, a); }
};

extern "C" s32 ItemPosInvalid_3d49a0(void *);

extern "C" void ItemGetHeldModelNameDefaultMaybe_3d59c0(V3D59C0 *o)
{
    o->v14(0);
}

extern "C" u32 func_003D59C0_e1(void *rgp_a0)
{
    bool r = !((unsigned char)ItemPosInvalid_3d49a0((void *)rgp_a0));
    return (bool)(r);
}

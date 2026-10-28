#include "types.h"

class VA96 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12() { VCM0(void, 0x38); }

    u8 pad004[0x4BC];
    u8 b0 : 1;
    u8 b1 : 7;
};

extern "C" void CharaSetAltFormFlagMaybe_3a96a0(VA96 *o, s32 b)
{
    o->b0 = b;
    o->v12();
}

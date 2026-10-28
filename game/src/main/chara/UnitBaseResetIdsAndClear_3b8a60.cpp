#include "types.h"

struct B3B8A60 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    void v9() { VCM0(void, 0x2C); }
};

struct C3B8A60 : B3B8A60 {
    s16 f04;
    u8 pad006[6];
    s32 f0C;
};

extern "C" void UnitBaseResetIdsAndClear_3b8a60(struct C3B8A60 *p)
{
    p->f04 = -1;
    p->f0C = -1;
    p->v9();
}

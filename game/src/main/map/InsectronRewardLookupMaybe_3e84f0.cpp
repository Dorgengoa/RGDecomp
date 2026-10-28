#include "types.h"

struct B3E84F0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v26() { VCM0(void, 0x70); }
};
struct C3E84F0 : B3E84F0 {};
struct A3E84F0 { u8 pad000[0xC]; struct C3E84F0 *f0C; };
struct S3E84F0 { u8 pad000[0xA0]; struct A3E84F0 *fA0; };
struct T3E84F0 { u8 pad000[0x8]; struct S3E84F0 *f08; };

extern "C" void InsectronRewardLookupMaybe_3e84f0(struct T3E84F0 *p)
{
    p->f08->fA0->f0C->v26();
}

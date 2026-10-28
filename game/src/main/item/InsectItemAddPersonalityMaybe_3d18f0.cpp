#include "types.h"

struct S3D18F0 { u8 pad000[0x26]; s8 f26; };
struct B3D18F0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v100(s32 a) { VCM(void, (void *, s32), 0x198, a); }
};
struct C3D18F0 : B3D18F0 { u8 pad004[0x14]; struct S3D18F0 *f18; };

extern "C" void InsectItemAddPersonalityMaybe_3d18f0(struct C3D18F0 *p, s32 a)
{
    p->v100(p->f18->f26 + a);
}

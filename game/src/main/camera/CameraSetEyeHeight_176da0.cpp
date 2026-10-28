/* rgp:protos */
#line 1
#include "types.h"

struct B_0017 {
    u8 pad[0xC0];
};

struct C_0017 : public B_0017 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v16() { return VCM0(int, 0x48); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v35(void * a0) { VCM(void, (void *, void *), 0x94, a0); }
    void v36(void * a0) { VCM(void, (void *, void *), 0x98, a0); }
};

typedef struct { f32 x, y, z, w; } A_0017;

extern "C" int CameraSetEyeHeight_176da0(C_0017 *p, f32 v)
{ int rgp_v0;
    A_0017 b __attribute__((aligned(16)));
    A_0017 a __attribute__((aligned(16)));

    p->v35(&a);
    p->v36(&b);
    rgp_v0 = p->v16();
    b.y = a.y + v;
return rgp_v0; }

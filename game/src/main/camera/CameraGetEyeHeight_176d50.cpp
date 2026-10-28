/* rgp:protos */
#line 1
#include "types.h"

struct B_0017 {
    u8 pad[0xC0];
};

struct C_0017 : public B_0017 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v35(void * a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, void *, int, int), 0x94, a0, rgp_fwd2, rgp_fwd3); }
    void v36(void * a0) { VCM(void, (void *, void *), 0x98, a0); }
};

typedef struct { f32 x, y, z, w; } A_0017;

extern "C" f32 CameraGetEyeHeight_176d50(C_0017 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    A_0017 b __attribute__((aligned(16)));
    A_0017 a __attribute__((aligned(16)));

    p->v35(&a, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    p->v36(&b);
    return b.y - a.y;
}

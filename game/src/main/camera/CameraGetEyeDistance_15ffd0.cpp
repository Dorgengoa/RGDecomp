/* rgp:protos */
#line 1
#include "types.h"

struct Vec4_0015FFD0 {
    f32 x, y, z, w;
};

class VE15FFD0 {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v35(Vec4_0015FFD0 *out, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, Vec4_0015FFD0 *, int, int), 0x94, out, rgp_fwd2, rgp_fwd3); }
    void v36(Vec4_0015FFD0 *out) { VCM(void, (void *, Vec4_0015FFD0 *), 0x98, out); }
};
extern "C" f32 VecDistance_13d3d0(const Vec4_0015FFD0 *a, const Vec4_0015FFD0 *b);

extern "C" void CameraGetEyeDistance_15ffd0(VE15FFD0 *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Vec4_0015FFD0 b __attribute__((aligned(16)));
    Vec4_0015FFD0 a __attribute__((aligned(16)));

    self->v35(&a, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    a.y = 0.0f;
    self->v36(&b);
    b.y = 0.0f;
    VecDistance_13d3d0(&a, &b);
}

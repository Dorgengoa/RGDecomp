#include "types.h"

class C0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    f32 v191(f32 a0) { return VCM(f32, (void *, f32), 0x304, a0); }
};

struct Obj0 {
    u8 pad000[0x1E8];
    f32 mF;
};

extern "C" void CharaMeterSet_3b1680(struct Obj0 *p0, f32 v)
{
    f32 mx;

    mx = ((class C0 *)p0)->v191(v);
    p0->mF = v;
    if (v < 0.0f) {
        p0->mF = 0.0f;
    } else if (v > mx) {
        p0->mF = mx;
    }
}

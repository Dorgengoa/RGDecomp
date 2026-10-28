#include "types.h"

struct Vec317340 { f32 x; f32 y; f32 z; };

class Base317340 { public: u8 pad000[0xB0]; };
class V317340 : public Base317340 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v19(struct Vec317340 *v, f32 x, f32 y, f32 z) { VCM(void, (void *, struct Vec317340 *, f32, f32, f32), 0x54, v, x, y, z); }
};

extern "C" void AttackObjBaseSetPosVec_317340(V317340 *o, struct Vec317340 *v)
{
    o->v19(v, v->x, v->y, v->z);
}

extern "C" s32 func_00317340_e1(void)
{
    return 1;
}

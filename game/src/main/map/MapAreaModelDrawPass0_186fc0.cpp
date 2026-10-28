#include "types.h"

class Base186FC0 { public: u8 pad000[0x68]; };
class V186FC0 : public Base186FC0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void v10(s32 a, s32 b) { VCM(void, (void *, s32, s32), 0x30, a, b); }
};

extern "C" s32 FadeIsVisible_186de0(void *a);

extern "C" void MapAreaModelDrawPass0_186fc0(V186FC0 *o)
{
    o->v10(0, 0);
}

extern "C" void func_00186FC0_e1(V186FC0 *o)
{
    o->v10(1, 0);
}

extern "C" s32 func_00186FC0_e2(V186FC0 *o)
{
    if (*(s16 *)((u8 *)o + 0x32) != 0) {
        return FadeIsVisible_186de0((u8 *)o + 0x3C);
    }
    return 0;
}

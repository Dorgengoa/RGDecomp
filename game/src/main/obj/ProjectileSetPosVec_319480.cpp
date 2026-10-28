#include "types.h"

/* ProjectileSetPosVec_319480 -- 52 B, TWO entries.  vptr at 0xB0 (non-polymorphic base). */

struct V319B { unsigned char pad[0xB0]; };
class V319 : public V319B {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v19(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x54, a0, a1, a2); }
};

struct S319 { u8 pad000[0x1B0]; f32 m1B0; f32 m1B4; f32 m1B8; s32 m1BC; };

struct Vec319 { f32 x; f32 y; f32 z; };

extern "C" void ProjectileSetPosVec_319480(V319 *o, Vec319 *v) { o->v19(v->x, v->y, v->z); }

extern "C" void func_00319480_e1(S319 *o, f32 a, f32 b, f32 c)
{
    o->m1B0 = a;
    o->m1B4 = b;
    o->m1B8 = c;
    o->m1BC = 0;
}

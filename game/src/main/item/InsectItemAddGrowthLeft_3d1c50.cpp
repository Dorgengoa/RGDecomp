#include "types.h"

/* InsectItemAddGrowthLeft_3d1c50 -- TWO entries: a virtual tail call and a clamping setter. */

struct S1C50 { u8 pad000[0x19]; u8 m19; u8 m1A; };

class T {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v79(s32 a0) { VCM(void, (void *, s32), 0x144, a0); }

    u8 pad004[0x14];
    S1C50 *m18;
};

extern "C" void InsectItemAddGrowthLeft_3d1c50(T *o, s32 d) { o->v79(o->m18->m1A + d); }

extern "C" u32 func_003D1C50_e1(T *o, s32 v)
{
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    o->m18->m1A = v;
    {
        u8 t = o->m18->m19;
        if (t < o->m18->m1A) o->m18->m1A = t;
    }
    return (u8)(o->m18->m1A);
}

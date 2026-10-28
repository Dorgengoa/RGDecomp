#include "types.h"

/* InsectItemAddHp_3d1be0 -- TWO entries: a virtual tail call and a clamping setter. */

struct S1BE0 { u8 pad000[0x14]; s16 m14; s16 m16; };

class T {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v85(s32 a0) { VCM(void, (void *, s32), 0x15C, a0); }

    u8 pad004[0x14];
    S1BE0 *m18;
};

extern "C" void InsectItemAddHp_3d1be0(T *o, s32 d) { o->v85(o->m18->m16 + d); }

extern "C" s32 func_003D1BE0_e1(T *o, s16 v)
{
    o->m18->m16 = v;
    if (o->m18->m16 < 0) o->m18->m16 = 0;
    {
        s16 t = o->m18->m14;
        if (t < o->m18->m16) o->m18->m16 = t;
    }
    return (s16)(o->m18->m16);
}

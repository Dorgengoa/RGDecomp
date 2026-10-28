#include "types.h"

/* InsectItemAddMaxHp_3d1b60 -- TWO entries: a virtual tail call and a clamping setter. */

struct S1B60 { u8 pad000[0x14]; s16 m14; s16 m16; };

class T {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v81(s32 a0) { VCM(void, (void *, s32), 0x14C, a0); }

    u8 pad004[0x14];
    S1B60 *m18;
};

extern "C" void InsectItemAddMaxHp_3d1b60(T *o, s32 d) { o->v81(o->m18->m14 + d); }

extern "C" s32 func_003D1B60_e1(T *o, s16 v)
{
    o->m18->m14 = v;
    if (o->m18->m14 <= 0) o->m18->m14 = 1;
    if (o->m18->m14 > 999) o->m18->m14 = 999;
    o->m18->m16 = o->m18->m14;
    return (s16)(o->m18->m14);
}

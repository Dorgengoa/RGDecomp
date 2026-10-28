#include "types.h"

/* InsectItemAddSatiety_3d1b00 -- TWO entries: a virtual tail call and a clamping setter. */

struct S1B00 { u8 pad000[0x18]; s8 m18; };
extern "C" struct rgp_anon_D_00465D80 { s32 v; s32 pad[3]; } D_00465D80;

class T {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v88(s32 a0) { VCM(void, (void *, s32), 0x168, a0); }

    u8 pad004[0x14];
    S1B00 *m18;
};

extern "C" void InsectItemAddSatiety_3d1b00(T *o, s32 d) { o->v88(o->m18->m18 + d); }

extern "C" s32 func_003D1B00_e1(T *o, s32 v)
{
    if (v < 0) v = 0;
    if (D_00465D80.v < v) v = D_00465D80.v;
    o->m18->m18 = v;
    return (s8)(o->m18->m18);
}

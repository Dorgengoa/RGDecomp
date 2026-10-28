#include "types.h"

/* ONE symbol, TWO entry points: a virtual tail call (vtable slot 0x180,
   index 94) then the clamp/set accessor.  See src/s23c/ContainerViewGetAtFwd_40a290.cpp. */

typedef struct M {
    u8  pad000[0x1E];
    s16 m1E;
} M;

struct OD {
    u8 pad000[0x18];
    M *m18;
};

class O {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v94(s32 a0) { VCM(void, (void *, s32), 0x180, a0); }
};

extern "C" s32 D_00465D68;

extern "C" void InsectItemAddDefense_3d1a40(O *o, s32 d)
{
    o->v94(((OD *)o)->m18->m1E + d);
}

extern "C" s32 func_003D1A40_e1(O *o, s32 v)
{
    OD *d = (OD *)o;

    if (v < 0) v = 0;
    /* ONE load of the limit: reading the extern twice made mwcc
       emit two lui/lw pairs, two words longer than retail. */
    {
        s32 lim = D_00465D68;
        if (v > lim) v = lim;
    }
    d->m18->m1E = (s16)v;
    return (s16)(d->m18->m1E);
}

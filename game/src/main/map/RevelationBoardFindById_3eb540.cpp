/* rgp:protos */
#line 1
#include "types.h"

class C0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 x, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, x, rgp_fwd2, rgp_fwd3); }
};

struct C {
    u8 pad000[0x10];
    class C0 *obj;
};

struct B {
    u8 pad000[0x8C];
    struct C *m8C;
};

struct A {
    u8 pad000[0x8];
    struct B *m08;
};

extern "C" s32 RevelationBoardFindById_3eb540(struct A *a, s32 x, int rgp_a2, int rgp_a3)
{
    struct B *p;

    p = a->m08;
    if (p != 0) {
        return p->m8C->obj->v26(x, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    return 0;
}

/* rgp:protos */
#line 1
#include "types.h"

struct E_00402330 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    void v6(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x20, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad[164];
};

struct B_00402330 {
    u8 pad0[8];
    s16 f8;
};

struct S_00402330 {
    u8 pad0[0xC];
    E_00402330 *fC;
};

extern "C" s32 WorldSubsysPlanetEntryDetach_402330(S_00402330 *self, B_00402330 *b, int rgp_a2, int rgp_a3)
{
    s32 i;
    E_00402330 *p;
    if (b != 0) goto g1;
    return 0;
g1:
    i = b->f8;
    if (i < 0) goto zero;
    if (i < 2) goto ok;
zero:
    return 0;
ok:
    p = self->fC;
    if (p != 0) {
        p[i].v6((int)(long)(b), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    return 1;
}

/* rgp:protos */
#line 1
#include "types.h"

class Base {
public:
    u8 pad000[0x2C];
};

class St : public Base {
public:

    VC_VPTR_MEMBER; void v0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

struct VP {
    u8    pad000[0x2C];
    void *vptr;
};

struct VQ {
    s32   pad000[0xB];
    void *vptr;
};

struct BigD { void *p; s32 pad[3]; };
extern "C" BigD D_004713E0;
extern "C" BigD D_004713A0;

extern "C" St *DebugTaskItemCtor_288440(St *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    VP *v = (VP *)o;

    v->vptr = &D_004713E0;
    o->v0((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    v->vptr = &D_004713A0;
    o->v0();
    return o;
}

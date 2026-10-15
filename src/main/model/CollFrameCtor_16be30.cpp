#include "types.h"

class Base {
public:
    u8 pad000[0xE0];
};

class St : public Base {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct VP {
    u8    pad000[0xE0];
    void *vptr;
};

struct VQ {
    s32   pad000[0x38];
    void *vptr;
};

struct BigD { void *p; s32 pad[3]; };
extern BigD D_0046FFA0;
extern BigD D_004702A0;

extern "C" St *CollFrameCtor_16be30(St *o)
{
    VP *v = (VP *)o;

    v->vptr = &D_0046FFA0;
    o->v2();
    v->vptr = &D_004702A0;
    o->v2();
    return o;
}

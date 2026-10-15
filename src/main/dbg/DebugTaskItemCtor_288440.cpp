#include "types.h"

class Base {
public:
    u8 pad000[0x2C];
};

class St : public Base {
public:

    virtual void v0();
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
extern BigD D_004713E0;
extern BigD D_004713A0;

extern "C" St *DebugTaskItemCtor_288440(St *o)
{
    VP *v = (VP *)o;

    v->vptr = &D_004713E0;
    o->v0();
    v->vptr = &D_004713A0;
    o->v0();
    return o;
}

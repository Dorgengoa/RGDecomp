#include "types.h"

struct E_00402330 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
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

extern "C" s32 WorldSubsysPlanetEntryDetach_402330(S_00402330 *self, B_00402330 *b)
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
        p[i].v6();
    }
    return 1;
}

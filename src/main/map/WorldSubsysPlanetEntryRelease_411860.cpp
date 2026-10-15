#include "types.h"

struct A_00411860 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void v6();
    u8 pad[160];
};

struct B_00411860 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void v6();
    u8 pad[152];
};

struct C_00411860 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void v6();
    u8 pad[148];
};

struct D_00411860 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void v6();
    u8 pad[176];
};

struct E_00411860 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void v6();
    u8 pad[756];
};

struct X_00411860 {
    u8 pad0[8];
    s16 f8;
};

struct S_00411860 {
    u8 pad0[0x3C];
    A_00411860 *f3C;
    B_00411860 *f40;
    u8 pad44[4];
    C_00411860 *f48;
    D_00411860 *f4C;
    E_00411860 *f50;
};

extern "C" s32 WorldSubsysPlanetEntryRelease_411860(S_00411860 *self, X_00411860 *b)
{
    s32 i;
    A_00411860 *pA;
    B_00411860 *pB;
    C_00411860 *pC;
    D_00411860 *pD;
    E_00411860 *pE;
    if (b != 0) goto g1;
    return 0;
g1:
    i = b->f8;
    if (i < 0) goto zero;
    if (i < 2) goto ok;
zero:
    return 0;
ok:
    pA = self->f3C;
    if (pA != 0) {
        pA[i].v6();
    }
    pB = self->f40;
    if (pB != 0) {
        pB[i].v6();
    }
    pC = self->f48;
    if (pC != 0) {
        pC[i].v6();
    }
    pD = self->f4C;
    if (pD != 0) {
        pD[i].v6();
    }
    pE = self->f50;
    if (pE != 0) {
        pE[i].v6();
    }
    return 1;
}

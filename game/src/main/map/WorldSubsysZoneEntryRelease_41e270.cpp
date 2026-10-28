#include "types.h"

extern "C" s32 D_004644A8[];

struct A_0041e270 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    void v6() { VCM0(void, 0x20); }
    u8 pad[148];
};

struct B_0041e270 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    void v6() { VCM0(void, 0x20); }
    u8 pad[148];
};

struct X_0041e270 {
    u8 pad0[0x10];
    s16 f10;
};

struct S_0041e270 {
    u8 pad0[8];
    A_0041e270 *f8;
    B_0041e270 *fC;
};

extern "C" s32 WorldSubsysZoneEntryRelease_41e270(S_0041e270 *self, X_0041e270 *b)
{
    s32 i;
    A_0041e270 *pA;
    B_0041e270 *pB;
    if (b != 0) goto g1;
    return 0;
g1:
    i = b->f10;
    if (i < 0) goto zero;
    if (i < D_004644A8[0]) goto ok;
zero:
    return 0;
ok:
    pA = self->f8;
    if (pA != 0) {
        pA[i].v6();
    }
    pB = self->fC;
    if (pB != 0) {
        pB[i].v6();
    }
    return 1;
}

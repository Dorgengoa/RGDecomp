/* rgp:protos */
#line 1
#include "types.h"

class B6C {
public:
    u8 pad0[0x100];
    s32 m100;
    u8 pad104[0x170 - 0x104];
    f32 f170;
    u8 pad174[0x1B0 - 0x174];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    s32 f24() { return VCM0(s32, 0x24); }
    s32 f28() { return VCM0(s32, 0x28); }
};

class A196 {
public:
    u8 pad0[0x32];
    s16 m32;
    u8 pad34[0x50 - 0x34];
    s32 m50;
    u8 pad54[0x64 - 0x54];
    f32 m64;
    VC_VPTR_MEMBER;
    f32 fC() { return VCM0(f32, 0xC); }
    
    
    
    
    s32 f20() { return VCM0(s32, 0x20); }
};

class A196x : public A196 {
public:
    B6C *m6C;
};
#define M6C(a) ((a)->m6C)

extern "C" {
void ModelSetRootMatrix_1512e0(B6C *, void *);
void ModelDetachRootFrames_151460(B6C *);
void NodeCalcWorldMatrix_186130(void *, void *);
}

extern "C" s32 NodeObjBasicDrawModel_196b10(A196x *arg0, s32 arg1)
{
    u8 sp50[0x40] __attribute__((aligned(16)));
    f32 v;
    f32 save;
    s32 r;
    void *u;
    B6C *o;

    if (arg0->m32 == 0) {
        return 0;
    }
    if (M6C(arg0) == 0) {
        return 0;
    }
    if (M6C(arg0) != 0) {
        NodeCalcWorldMatrix_186130((void *)arg0, sp50);
        ModelSetRootMatrix_1512e0(M6C(arg0), sp50);
    }
    if (M6C(arg0) != 0 && arg0->f20() != 0) {
        save = M6C(arg0)->f170;
        v = arg0->m64;
        if (arg0->m50 != 0) {
            v *= arg0->fC();
        }
        M6C(arg0)->f170 = v;
        if (arg1 != 0) {
            r = M6C(arg0)->f24();
        } else {
            r = M6C(arg0)->f28();
        }
        M6C(arg0)->f170 = save;
    }
    o = M6C(arg0);
    if (o != 0) {
        o->m100 = 0;
        ModelDetachRootFrames_151460(o);
    }
    return r;
}

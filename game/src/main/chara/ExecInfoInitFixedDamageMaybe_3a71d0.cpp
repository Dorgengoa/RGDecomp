/* rgp:protos */
#line 1
#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f70(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

struct Sub48 {
    u8 pad0[0xC];
    VObj *unkC;
};

struct Mgr {
    u8 pad0[0x48];
    Sub48 *unk48;
};

struct D004837B0T {
    u8 pad0[0x8];
    Mgr *unk8;
};

struct Obj003a71d0 {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[0xA - 0x6];
    s16 unkA;
    u8 padC[0x1C - 0xC];
    s16 unk1C;
    u8 pad1E[2];
    s32 unk20;
    u8 pad24[0x2C - 0x24];
    s16 unk2C;
    u8 flag : 1;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[2];
    s16 unk46[5];
    s32 unk50;
};

extern "C" {
void ExecInfoInit_3a7940(void *);
extern D004837B0T *D_004837B0;
}

extern "C" s32 ExecInfoInitFixedDamageMaybe_3a71d0(Obj003a71d0 *obj, s16 arg1, s32 arg2)
{
    Mgr *m;
    s32 r;
    s32 i;

    ExecInfoInit_3a7940((void *)obj);
    if (D_004837B0 == 0) {
        return 0;
    }
    m = D_004837B0->unk8;
    if (m == 0) {
        return 0;
    }
    obj->unk4 = 6;
    obj->unkA = arg1;
    obj->unk1C = 6;
    obj->unk20 = 0;
    r = m->unk48->unkC->f70(arg2);
    if (r == 0) {
        return 0;
    }
    obj->unk20 = r;
    obj->unk50 = 0;
    obj->unk2C = 0;
    obj->flag = 0;
    obj->unk30 = 1.0f;
    obj->unk34 = 1.0f;
    obj->unk38 = 1.0f;
    obj->unk3C = 1.0f;
    obj->unk40 = 0;
    for (i = 0; i < 5; i++) {
        obj->unk46[i] = 0;
    }
    return 1;
}

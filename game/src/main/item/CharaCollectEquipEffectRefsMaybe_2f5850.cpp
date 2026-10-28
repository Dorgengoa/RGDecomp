#include "types.h"

struct V2f5850 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f374(s32 a0) { return VCM(s32, (void *, s32), 0x374, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f3bc() { return VCM0(s32, 0x3BC); }
    
    
    
    
    s32 f3d0() { return VCM0(s32, 0x3D0); }
};

struct T2f5850 {
    u8 pad[0x14];
    s32 m14;
    s32 m18;
};

extern "C" {
T2f5850 *GetGameData_1fede0(void);
V2f5850 *CharaMgrPoolFindById_3a8c60(s32, u32);
s32 InvFindByUniqueId_3c85d0(s32, s32, s32, s32);
s32 ItemCollectEffectRefsMaybe_3d4e10(s32, s32, s32, s32);
}

extern "C" s32 CharaCollectEquipEffectRefsMaybe_2f5850(u32 arg0, s32 arg1, s32 arg2)
{
    T2f5850 *top;
    s32 acc;
    V2f5850 *o;
    bool flag;
    s32 e;

    if (arg1 == 0) {
        return 0;
    }
    top = GetGameData_1fede0();
    o = CharaMgrPoolFindById_3a8c60(top->m14, arg0);
    if (o == 0) {
        return 0;
    }
    acc = 0;
    flag = false;
    if (arg0 < 8 && ((1 << arg0) & 0xB5)) {
        flag = true;
    } else {
        flag = flag;
    }
    e = InvFindByUniqueId_3c85d0(top->m18, o->f374(flag), -1, 0);
    if (e != 0) {
        acc = ItemCollectEffectRefsMaybe_3d4e10(e, arg1, arg2, 0);
    }
    e = InvFindByUniqueId_3c85d0(top->m18, o->f374(!flag), -1, 0);
    if (e != 0) {
        acc = ItemCollectEffectRefsMaybe_3d4e10(e, arg1, arg2, acc);
    }
    e = InvFindByUniqueId_3c85d0(top->m18, o->f3bc(), -1, 0);
    if (e != 0) {
        acc = ItemCollectEffectRefsMaybe_3d4e10(e, arg1, arg2, acc);
    }
    e = InvFindByUniqueId_3c85d0(top->m18, o->f3d0(), -1, 0);
    if (e != 0) {
        acc = ItemCollectEffectRefsMaybe_3d4e10(e, arg1, arg2, acc);
    }
    return acc;
}

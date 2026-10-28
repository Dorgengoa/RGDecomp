/* rgp:protos */
#line 1
#include "types.h"

class R3AA460 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f104(s32 a0) { VCM(void, (void *, s32), 0x104, a0); }
};

class S3AA460 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f70(s32 a0) { VCM(void, (void *, s32), 0x70, a0); }
};

class M3AA460 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f264() { return VCM0(s32, 0x264); }
    
    void f26C(f32 a0) { VCM(void, (void *, f32), 0x26C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    R3AA460 * f388() { return VCM0(R3AA460 *, 0x388); }
    R3AA460 * f38C() { return VCM0(R3AA460 *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    R3AA460 * f3C4() { return VCM0(R3AA460 *, 0x3C4); }
    
    
    
    
    R3AA460 * f3D8() { return VCM0(R3AA460 *, 0x3D8); }
};

struct Slot3AA460 {
    S3AA460 s;
    u8 pad[0x24];
};

struct L3AA460 {
    M3AA460 m;
    u8 pad4[0x8];
    s32 unkC;
    u8 pad10[0x308 - 0x10];
    Slot3AA460 arr[10];
};

extern "C" s32 GetActionMgr_1fdb50(void);
extern "C" u8 *ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern "C" s32 UnitBaseClearDeathTime_3b1530(void *, int, int, int);

extern "C" s32 CharaOnRevive_3aa460(L3AA460 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    u8 *p;
    s32 t;
    s32 i;
    R3AA460 *r;

    if (UnitBaseClearDeathTime_3b1530((void *)arg0, (int)arg1, (int)rgp_a2, (int)rgp_a3) == 0) {
        return 0;
    }
    arg0->m.f26C(arg0->m.f264());
    p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg0->unkC);
    if (p != 0) {
        t = *(s32 *)(p + 0xA44) & ~0x1000;
        *(s32 *)(p + 0xA44) = t;
        *(s32 *)(p + 0xA44) = t & ~0x2000;
    }
    for (i = 0; i < 10; i++) {
        arg0->arr[i].s.f70(arg1);
    }
    for (i = 1; i <= 4; i++) {
        r = 0;
        switch (i) {
        case 1:
            r = arg0->m.f388();
            break;
        case 2:
            r = arg0->m.f38C();
            break;
        case 3:
            r = arg0->m.f3C4();
            break;
        case 4:
            r = arg0->m.f3D8();
            break;
        }
        if (r != 0) {
            r->f104(arg1);
        }
    }
    return 1;
}

#include "types.h"



typedef struct { s8 b[9]; } Tbl9;

typedef struct Inner {
    u8 pad[3];
    s8 val;
} Inner;

typedef struct Info {
    u8 pad[0x10];
    Inner *p10;
} Info;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * f388() { return VCM0(Info *, 0x388); }
    Info * f38C() { return VCM0(Info *, 0x38C); }
};

typedef struct Mgr {
    u8 pad[0x14];
    void *p14;
} Mgr;

extern "C" Mgr *GetGameData_1fede0(void);
extern "C" Obj *CharaMgrPoolFindById_3a8c60(void *, s32);
extern "C" s8 D_0047E478;
extern "C" s8 D_0047E488;

extern "C" s32 CharaWeaponSeIdRemap_1fd430(s32 idx, s32 val)
{
    Obj *o;
    Info *a;
    Info *b;
    s32 v;
    Tbl9 t1 __attribute__((aligned(16)));
    Tbl9 t2 __attribute__((aligned(16)));

    if (!(idx >= 0 && idx < 12)) {
        return val;
    }
    if (idx == 8) {
        return val;
    }
    o = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->p14, idx);
    if (o == 0) {
        return val;
    }
    a = o->f388();
    b = o->f38C();
    if (a != 0 && val >= 0x46 && val < 0x55) {
        t1 = *(Tbl9 *)&D_0047E478;
        v = a->p10->val;
        if (idx >= 0 && idx < 10 && v >= 0x32) {
            v += t1.b[idx] - 0x32;
        }
        return val + v * 15;
    }
    if (b != 0 && val >= 0x1BD && val < 0x1CC) {
        t2 = *(Tbl9 *)&D_0047E488;
        v = b->p10->val;
        if (idx >= 0 && idx < 10 && v >= 0x32) {
            v += t2.b[idx] - 0x32;
        }
        return val + v * 15;
    }
    return val;
}

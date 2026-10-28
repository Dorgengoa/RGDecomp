#include "types.h"
#pragma opt_propagation off

struct Info001f3350 {
    s16 unk0;
    u8 pad2[6];
    s16 *unk8;
    u8 padC[0x2A - 0xC];
    s16 unk2A;
};

class Obj001f3350 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info001f3350 * slot33C() { return VCM0(Info001f3350 *, 0x33C); }
};

class V70_001f3350 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 slot70(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

struct Link001f3350 {
    u8 pad0[8];
    V70_001f3350 *unk8;
};

struct Mgr001f3350 {
    u8 pad0[0x40];
    Link001f3350 *unk40;
};

struct G001f3350 {
    u8 pad0[0x14];
    s32 unk14;
};

struct A0_001f3350 {
    s16 unk0;
    u8 pad2[4];
    u8 unk6;
    u8 pad7[0x64 - 0x7];
    s16 unk64;
};

extern "C" {
s32 CharaPcLoadRequest_1f4db0(s16 arg0, s16 arg1, s32 arg2);
G001f3350 *GetGameData_1fede0(void);
Mgr001f3350 *GetWorldDataMgr_1fedf0(void);
Obj001f3350 *CharaMgrPoolFindById_3a8c60(s32 arg0, s16 arg1);
}

extern "C" s32 CharaResLoadPcModel_1f3350(A0_001f3350 *arg0, s32 arg1)
{
    Obj001f3350 *o;
    Info001f3350 *info;
    s16 *p;
    Mgr001f3350 *m;
    s32 r;
    G001f3350 *g;
    s16 k;

    g = GetGameData_1fede0();
    k = arg0->unk0;
    o = CharaMgrPoolFindById_3a8c60(g->unk14, k);
    if (o == NULL) {
        return 0;
    }
    info = o->slot33C();
    if (info == NULL) {
        return 0;
    }
    p = info->unk8;
    if (p == NULL) {
        return 0;
    }
    m = GetWorldDataMgr_1fedf0();
    r = m->unk40->unk8->slot70((s16)arg1);
    if (r == 0) {
        r = m->unk40->unk8->slot70(info->unk2A);
        if (r == 0) {
            return 0;
        }
    }
    r = CharaPcLoadRequest_1f4db0(info->unk0, *p, r);
    if (r != 0) {
        arg0->unk6 &= 0x7F;
        arg0->unk64 = 2;
    }
    return r;
}

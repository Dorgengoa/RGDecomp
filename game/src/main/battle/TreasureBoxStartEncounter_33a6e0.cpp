/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef union Vec {
    u128 q;
    f32 f[4];
} Vec;

struct Ent {
    u8 pad0[0x180];
    u128 m180;
    u128 m190;
};

struct Pt {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    s32 pad;
};

struct Link {
    void *m0;
    s32 m4;
    f32 m8;
    f32 mC;
    f32 m10;
    f32 m14;
};

struct Obj {
    u8 pad0[0x18];
    s16 m18;
    s16 m1A;
    s16 m1C;
    u8 pad1E[0x44 - 0x1E];
    f32 m44;
    f32 m48;
    f32 m4C;
    f32 m50;
    u8 pad54[4];
    Pt m58[1];
    u8 pad6C[0x7C - 0x6C];
    s8 m7C_a : 5;
    s8 m7C_b : 3;
    u8 pad7D;
    s8 m7E_0 : 1;
    s8 m7E_1 : 1;
    s8 m7E_2 : 1;
    s8 m7E_3 : 5;
    u8 pad7F;
    Link *m80;
};

class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * get(s16 a0) { return VCM(void *, (void *, s16), 0x70, a0); }
};

struct TblA {
    u8 pad0[0xC];
    Tbl *mC;
};

struct TblB {
    u8 pad0[0x10];
    Tbl *m10;
};

struct Sys {
    u8 pad0[0x64];
    TblA *m64;
    u8 pad68[8];
    TblB *m70;
};

struct Chr {
    u8 pad0[0x18E];
    s16 m18E;
};

struct Ctx {
    u8 pad0[0x18];
    Chr *m18;
    u8 pad1C[4];
    s32 m20;
};

struct Arg {
    f32 m0;
    f32 m4;
    f32 m8;
    u8 padC[8];
    f32 m14;
};

struct Pkt {
    s64 m0;
    u8 pad8[0x10];
    Obj *m18;
    u8 pad1C[8];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 5;
    u8 pad25[3];
    s32 m28;
    u8 pad2C[0x44 - 0x2C];
    s16 m44;
    u8 pad46[4];
    s16 m4A;
    u8 pad4C[0x162 - 0x4C];
    s16 m162;
    s16 m164;
    s16 m166;
    u8 sub[0x68];
};

extern "C" {
s32 TreasureBoxIsOpened_33a240(Arg *);
Ctx *GetGameData_1fede0(void);
Sys *GetWorldDataMgr_1fedf0(void);
s32 GetActionMgr_1fdb50(void);
s32 GetCurrentScene_1f5be0(void);
s32 TreasureBoxIsEncounterBox_33aac0(Arg *);
s32 TreasureBoxGetEncounterId_33aa40(Arg *);
Ent *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 PartyCountExcludingLeader_3c2610(Chr *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Chr *, s32);
void BattleRecordReset_3a7fd0(void *);
void CharaStateReset_3a79b0(Pkt *, s32, s32, s32, s32);
void BattleSetupEncounter_3a3970(s32, Pkt *, s32);
}

static inline Obj *GetObj(Sys *s)
{
    return (Obj *)s->m70->m10->get(1);
}

extern "C" s32 TreasureBoxStartEncounter_33a6e0(Arg *arg) {
    Vec a1 __attribute__((aligned(16)));
    Vec a2 __attribute__((aligned(16)));
    Vec b1 __attribute__((aligned(16)));
    Vec b2 __attribute__((aligned(16)));
    Pkt pkt __attribute__((aligned(16)));
    Ctx *ctx;
    Sys *sys;
    s32 mgr;
    s32 idx;
    void *hit;
    Obj *obj;
    Ent *e;
    s32 n;
    s32 i;

    if (TreasureBoxIsOpened_33a240(arg) != 0) {
        return 0;
    }
    ctx = GetGameData_1fede0();
    if (ctx == 0) {
        return 0;
    }
    sys = GetWorldDataMgr_1fedf0();
    if (sys == 0) {
        return 0;
    }
    if (GetActionMgr_1fdb50() == 0) {
        return 0;
    }
    mgr = GetCurrentScene_1f5be0();
    if (mgr == 0) {
        return 0;
    }
    if (TreasureBoxIsEncounterBox_33aac0(arg) == 0) {
        return 1;
    }
    idx = TreasureBoxGetEncounterId_33aa40(arg);
    if (idx < 0) {
        return 1;
    }
    hit = sys->m64->mC->get(idx);
    if (hit == 0) {
        return 0;
    }
    obj = GetObj(sys);
    if (obj == 0) {
        return 0;
    }
    e = ObjRecGetLiveObject_1c4a90(mgr, ctx->m18->m18E);
    if (e != 0) {
        a1.q = e->m180;
        a2.q = e->m190;
        obj->m44 = a1.f[0];
        obj->m48 = a1.f[1];
        obj->m4C = a1.f[2];
        obj->m50 = a2.f[1];
    }
    n = PartyCountExcludingLeader_3c2610(ctx->m18, 1, 1);
    for (i = 0; i < n; i++) {
        e = ObjRecGetLiveObject_1c4a90(mgr, ((short)PartyGetNonLeaderId_3c2750(ctx->m18, i)));
        if (e != 0) {
            b1.q = e->m180;
            b2.q = e->m190;
            obj->m58[i].x = b1.f[0];
            obj->m58[i].y = b1.f[1];
            obj->m58[i].z = b1.f[2];
            obj->m58[i].w = b2.f[1];
        }
    }
    if (obj->m80 != 0) {
        obj->m7C_a = 1;
        obj->m80->m0 = hit;
        obj->m80->m8 = arg->m0;
        obj->m80->mC = arg->m4;
        obj->m80->m10 = arg->m8;
        obj->m80->m14 = arg->m14;
    }
    pkt.m0 = 0;
    BattleRecordReset_3a7fd0(pkt.sub);
    CharaStateReset_3a79b0(&pkt, 1, 1, 1, 1);
    pkt.m4A = idx;
    pkt.m28 = 1;
    pkt.m44 = 1;
    pkt.m18 = obj;
    pkt.m162 = obj->m18;
    pkt.m164 = obj->m1A;
    pkt.m166 = obj->m1C;
    pkt.b0 = obj->m7E_1 != 0;
    pkt.b1 = !obj->m7E_2;
    pkt.b2 = 1;
    BattleSetupEncounter_3a3970(ctx->m20, &pkt, 0);
    return 1;
}

/* rgp:protos */
#line 1
#include "types.h"

extern "C" {

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Tick(f32 dt) { VCM(void, (void *, f32), 0x10C, dt); }
    u8 pad4[2];
    s16 kind;
    u8 pad8[2];
    u8 b0 : 1;
    u8 skip : 1;
};

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Check(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
};

typedef struct Ctx {
    u8 d[0x28];
} Ctx;

typedef struct St {
    u8 pad0[4];
    s16 h4;
} St;

typedef struct Mgr4 {
    u8 pad0[0xC];
    u8 *pC;
} Mgr4;

typedef struct Party {
    u8 pad0[0x18E];
    s16 leader;
} Party;

typedef struct Mgr0 {
    u8 pad0[0x14];
    s32 w14;
    Party *p18;
    u8 pad1C[4];
    u8 *p20;
} Mgr0;

typedef struct Rec {
    u8 pad0[0x14];
    s16 h14;
    u8 b16 : 1;
} Rec;

typedef struct Q {
    u8 pad0[0x10];
    s16 *p10;
} Q;

typedef struct Obj {
    u8 pad0[0xC];
    s16 hC;
    u8 padE[2];
    s32 w10;
    u8 pad14[0x10];
    Q *p24;
    u8 pad28[4];
    s16 h2C;
    u8 b2E : 1;
    u8 pad2F[5];
    s16 h34;
    s16 h36;
    s16 h38;
    u8 pad3A[0x44];
    s16 h7E;
    s16 h80;
    s16 h82;
    u8 pad84[0x94];
    f64 d118;
    u8 pad120[4];
    f32 f124;
    u8 pad128[0x10];
    f32 f138;
    u8 pad13C[0x2C];
    void *p168;
    u8 pad16C[0x38];
    u8 b1A4 : 1;
    u8 pad1A5;
    s16 h1A6;
    s16 h1A8;
    u8 pad1AA[2];
    s32 w1AC;
    f32 f1B0;
    u8 pad1B4[0x4C58 - 0x1B4];
    f32 f4C58[2];
    f32 f4C60[2];
} Obj;

s32 DoubleGreater_100260(f64, double);
s64 fptodp(f32);
double dpmul(double, f64);
void MapMgrWarpMenuRelease_1e2d30(s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetMapMgr_201a90(void);
Ent *PoolGetUsedElem_36acb0(void *, s32);
void CharaSysEncounterDistRoll_3a59d0(u8 *, s32);
Unit *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 PartyCountMembers_3c2010(Party *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Party *, s32);
s16 *PartyFindEncounterForKeyMaybe_3c99e0(Obj *, s32, s32 *);
s32 SkillTriggerEvalMaybe_3e1200(Ctx *, Unit *);
void EventFireTriggers_3e2660(Ctx *, u8 *);
void ActionPacketInitEventTimer_3e2a30(Ctx *, s32, s32);
void ActionPacketInitTendencyMaybe_3e2c00(Ctx *, s32, s32, s32, f32);
void ActionPacketInitSpaceMenuMaybe_3e39f0(Ctx *, s32, s32, s32);
void ActionPacketReset_3e3d00(Ctx *);
u8 *WorldFindBgmEntry_3ed340(Mgr0 *, s32);
u8 *HandleEntryFindById_3f1600(Mgr4 *, s32);
u8 *HandleEntryFindById_3f2450(Mgr4 *, s32);
extern f32 D_0045B078[];
extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern s32 D_00465A38[];
extern s32 D_00465A40[];
extern s32 D_00465B50[];
extern Mgr0 *D_00483890;
extern Mgr4 *D_00483894;

static inline Unit *GetMember(s32 i)
{
    s32 k;

    Party *pp = D_00483890->p18;

    if (D_00483890 == 0) {
        return 0;
    }
    k = ((short)PartyGetNonLeaderId_3c2750(pp, i));
    if (k < 0) {
        return 0;
    }
    return CharaMgrPoolFindById_3a8c60(D_00483890->w14, k);
}

static inline void Dec(f32 *q, f32 d)
{
    *q -= d;
    if (*q < 0.0f) {
        *q = 0.0f;
    }
}

s32 PartyUpdateMaybe_3bfb60(Obj *o, f32 dt)
{
    u8 flag;
    s32 out;
    Unit *arr[3];
    Ctx c1 __attribute__((aligned(16)));
    Ctx c2 __attribute__((aligned(16)));
    Ctx c3 __attribute__((aligned(16)));
    s32 i;
    Ent *e;
    s16 k;
    St *st;
    u8 *r;
    bool a;
    bool b;
    bool c;
    s32 id;
    s16 *t;
    s32 n;
    s32 m;
    Unit *u;
    f32 old;
    f32 *p;
    s32 lo1;
    s32 hi1;
    s32 lo2;
    s32 hi2;
    s32 cnt;
    f64 d;
    f32 nw;

    if (o->p168 == 0) {
        return 0;
    }
    if (D_00483894 == 0 || D_00483890 == 0) {
        return 0;
    }
    o->d118 += (f64)(2.0 * dt);
    for (i = 0; i < D_00465B50[0]; i++) {
        e = PoolGetUsedElem_36acb0(o->p168, i);
        if (e == 0) {
            continue;
        }
        if (e->skip) {
            continue;
        }
        k = e->kind;
        if ((k >= D_00465A08[0] && k <= D_00465A10[0]) || (k >= D_00465A38[0] && k <= D_00465A40[0])) {
            e->Tick(dt);
        }
    }
    a = false;
    st = (St *)(D_00483894->pC + 0x1C);
    if (st != 0) {
        if (st->h4 == 3) {
            a = true;
        } else {
            o->h34 = 1;
        }
    } else {
        o->h34 = 1;
    }
    b = false;
    r = HandleEntryFindById_3f2450(D_00483894, o->hC);
    if (r != 0) {
        if (*(s16 *)(r + 0xC) == 3) {
            b = true;
        } else {
            o->h36 = 1;
        }
    } else {
        o->h36 = 1;
    }
    r = HandleEntryFindById_3f1600(D_00483894, o->w10);
    if (r != 0) {
        if (*(s16 *)(r + 8) != 3) {
            o->h38 = 1;
        }
    } else {
        o->h38 = 1;
    }
    c = false;
    if (a) {
        if (o->h34 != 3) {
            o->h34 = 3;
            c = true;
        }
    }
    a = false;
    if (b) {
        if (o->h36 != 3) {
            o->h36 = 3;
            a = true;
        }
    }
    if (c) {
        t = (o->p24 != 0) ? o->p24->p10 : 0;
        id = (t != 0) ? *t : -1;
        out = -1;
        t = PartyFindEncounterForKeyMaybe_3c99e0(o, id, &out);
        if (t != 0) {
            o->h7E = id;
            o->h80 = *t;
            o->h82 = out;
        } else {
            o->h7E = -1;
            o->h80 = -1;
            o->h82 = -1;
        }
        CharaSysEncounterDistRoll_3a59d0(D_00483890->p20, 0);
    }
    if (a) {
        if (o->h36 == 3) {
            r = WorldFindBgmEntry_3ed340(D_00483890, o->hC);
            if (r != 0) {
                o->h2C = *(s16 *)(r + 0x14);
                o->b2E = ((Rec *)r)->b16;
            } else {
                o->h2C = -1;
                o->b2E = 0;
            }
        }
    }
    if (o->f138 == 0.0f) {
        o->f124 += 2.0f * dt;
    } else if (((unsigned char)DoubleGreater_100260(o->f124, dpmul(__builtin_bit_cast(double, (long long)(0x4000000000000000LL)), D_0045B078[0])))) {
        m = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&c1);
        ActionPacketInitTendencyMaybe_3e2c00(&c1, m, 2, 1, 0.0f);
        n = PartyCountMembers_3c2010(D_00483890->p18, 1, 1);
        {
            Party *pp = D_00483890->p18;
            arr[0] = (D_00483890 == 0) ? 0 : CharaMgrPoolFindById_3a8c60(D_00483890->w14, pp->leader);
        }
        for (i = 1; i < n; i++) {
            arr[i] = GetMember(i - 1);
        }
        for (i = 0; i < n; i++) {
            u = arr[i];
            if (u == 0) {
                continue;
            }
            if (u->Check(0) == 0) {
                continue;
            }
            if ((((unsigned char)SkillTriggerEvalMaybe_3e1200(&c1, u)) & 0xFF) != 0) {
                break;
            }
        }
        o->f124 = 0.0f;
    }
    if (o->b1A4) {
        if (!(*(u8 *)(D_00483890->p20 + 0x24C) & 1)) {
            {
                f32 n = o->f1B0 - 2.0f * dt;
                old = *(volatile f32 *)&o->f1B0;
                o->f1B0 = n;
                if (n < 0.0f) {
                    o->f1B0 = 0.0f;
                }
            }
            nw = o->f1B0;
            if (!(old <= 0.0f) && nw <= 0.0f) {
                m = GetCurrentScene_1f5be0();
                ActionPacketReset_3e3d00(&c2);
                ActionPacketInitSpaceMenuMaybe_3e39f0(&c2, m, 0, 0);
                flag = 0;
                EventFireTriggers_3e2660(&c2, &flag);
                if (flag == 0 && o->b1A4) {
                    m = GetMapMgr_201a90();
                    if (m != 0) {
                        MapMgrWarpMenuRelease_1e2d30(m);
                    }
                    o->b1A4 = 0;
                    o->h1A6 = -1;
                    o->h1A8 = -1;
                    o->w1AC = 0;
                    o->f1B0 = 0.0f;
                }
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (o->f4C58[i] <= 0.0f) {
            continue;
        }
        if (o->f4C60[i] <= 0.0f) {
            continue;
        }
        p = &o->f4C60[i];
        Dec(&o->f4C60[i], dt);
        if (*p <= 0.0f) {
            *p = 0.0f;
            m = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(&c3);
            ActionPacketInitEventTimer_3e2a30(&c3, m, i);
            EventFireTriggers_3e2660(&c3, 0);
        }
    }
    return 1;
}

}

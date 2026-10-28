/* rgp:protos */
#line 1
#pragma optimization_level 3
#include "types.h"
#include "vec.h"

typedef struct Eff {
    u8 pad0[0x32];
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Eff;

class EffTbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Eff * get(s16 id) { return VCM(Eff *, (void *, s16), 0x70, id); }
};

typedef struct Mgr58 {
    u8 pad0[8];
    EffTbl *tbl;
} Mgr58;

typedef struct Mgr {
    u8 pad0[0x58];
    Mgr58 *x58;
} Mgr;

typedef struct Sys20 {
    u8 pad0[0x24C];
    u8 b24C;
} Sys20;

typedef struct Sys {
    u8 pad0[0x20];
    Sys20 *x20;
} Sys;

typedef struct Fx {
    u8 pad0[0x48];
    s64 d48;
    s64 d50;
    s64 d58;
    s64 d60;
    u8 pad68[0x90 - 0x68];
} Fx;

typedef struct Snd {
    u8 pad0[0x70];
} Snd;

typedef struct Who {
    u8 pad0[0x4CC];
    f32 f4CC;
} Who;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v44() { return VCM0(s32, 0x44); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vBC() { return VCM0(s32, 0xBC); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v128(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v1A0(s32 id, s32 a, s32 b) { VCM(void, (void *, s32, s32, s32), 0x1A0, id, a, b); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v27C(f32 dt) { VCM(void, (void *, f32), 0x27C, dt); }
    
    void v284(Fx *f) { VCM(void, (void *, Fx *), 0x284, f); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    f32 v2E4() { return VCM0(f32, 0x2E4); }
    
    
    
    f32 v2F4() { return VCM0(f32, 0x2F4); }
    
    
    
    f32 v304() { return VCM0(f32, 0x304); }
    u8 pad4[0xC - 4];
    s32 xC;
    u8 pad10[0x14 - 0x10];
    s32 x14;
    u16 h18;
    u8 pad1A[0x20 - 0x1A];
    u32 x20;
    u8 pad24[0xC8 - 0x24];
    s64 dC8;
    f32 fD0[32];
    s16 h150[32];
    u8 pad190[0x1A0 - 0x190];
    s32 x1A0;
    u16 h1A4;
    u8 pad1A6[2];
    s64 d1A8;
    s32 x1B0;
    u16 h1B4;
    u8 pad1B6[2];
    s64 d1B8;
    u8 pad1C0[0x1C8 - 0x1C0];
    u8 b1C8;
    u8 pad1C9[3];
    f32 f1CC;
    f32 f1D0;
    u8 pad1D4[0x1E0 - 0x1D4];
    f32 f1E0;
    f32 f1E4;
    f32 f1E8;
    f32 f1EC;
};

extern "C" {
f32 RandFloat_13c010(void);
double dpmul(double, double);
double fptodp(f32);
f32 dptofp(double);
Who *ObjRecGetLiveObject_1c4a90(s32, s32);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
void CharaRequestTint_213fd0(s32, s32, s32, f32, f32, f32, f32, f32);
s32 ActionMgrFindById_233b50(s32, s32);
s32 CharaGetNthAttachPointPos_238580(s32, s32, s32, Vec4 *);
void CharaGetPos_2388a0(s32, Vec4 *);
void DamagePopupSpawn_2d2da0(s32, s32, Vec4 *, f32 *, s32, s32, f32);
s32 GetDamagePopupList_2d9020(void);
void ActionResultSetupMaybe_3a6d70(Fx *, Snd *, s32, s32, s32, s32, f32);
void ActionResultClear_3a6e60(Fx *);
void ExecInfoInitFixedDamageMaybe_3a71d0(Snd *, s32, s32);
void ExecInfoInit_3a7940(Snd *);
s32 CharaIsPartyMember_3ae110(s32);
s32 ActorCastToChara_3b87b0(Chr *, int, int, int);
extern s64 D_0047D180;
extern f32 D_0047D1DC;
extern f32 D_0047D244;
extern f32 D_00480180;
extern f32 D_00480184;
extern f32 D_00480188;
extern f32 D_0048018C;
extern Sys *D_00483818;
extern Mgr *D_0048381C;

static inline s32 rrange(s32 lo, s32 hi)
{
    f32 l = (f32)lo;
    f32 r = 1.0f + ((f32)hi - l);
    return (s32)(l + r * RandFloat_13c010());
}

s32 UnitBaseUpdate_3b0bf0(Chr *o, f32 dt)
{
    Snd snd __attribute__((aligned(16)));
    Fx fx __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 at __attribute__((aligned(16)));
    f32 col[4] __attribute__((aligned(16)));
    s32 i;
    s32 n;
    s32 c;
    s32 w;
    s32 x;
    s32 p;
    Who *y;
    Eff *e;
    EffTbl *q;
    f32 *pv;
    f32 cur;
    f32 old;
    f32 k;
    f32 s;
    f32 a;
    f32 b;
    f32 cc;
    f32 step;
    s32 id;

    if (D_00483818 == 0) {
        return 0;
    }
    if (!(D_00483818->x20->b24C & 1)) {
        return 1;
    }
    o->f1EC = o->f1EC + (f32)(2.0f * dt);
    o->x1B0 = o->x1A0;
    o->h1B4 = o->h1A4;
    o->d1B8 = o->d1A8;
    o->x1A0 = o->x14;
    o->h1A4 = o->h18;
    o->d1A8 = o->dC8;
    if (o->vBC() != 0 && (o->b1C8 & 1)) {
        o->v27C(dt);
    }
    if (!(o->f1CC <= 0.0f)) {
        o->f1CC = o->f1CC - D_0047D1DC * dt * (f32)o->v128(1);
    }
    if (o->f1CC <= 0.0f) {
        o->f1CC = 0.0f;
    }
    if (!(o->f1D0 <= 0.0f)) {
        o->f1D0 = o->f1D0 - D_0047D1DC * dt;
    }
    if (o->f1D0 <= 0.0f) {
        o->f1D0 = 0.0f;
    }
    p = ActorCastToChara_3b87b0(o, 0, 0, 0);
    if (p != 0) {
        if (CharaIsPartyMember_3ae110(p) == 0) {
            return 1;
        }
    }
    for (i = 0; i < 32; i++) {
        pv = &o->fD0[i];
        old = *pv;
        if (old <= 0.0f) {
            continue;
        }
        cur = old - dt;
        id = o->h150[i];
        if (cur <= 0.0f) {
            cur = 0.0f;
        }
        *pv = cur;
        if (cur <= 0.0f) {
            o->v1A0(id, 0, 1);
            continue;
        }
        q = D_0048381C->x58->tbl;
        e = (q != 0) ? q->get(id) : 0;
        if (e == 0) {
            continue;
        }
        k = (f32)e->h38;
        if ((s32)(old / k) <= (s32)(cur / k)) {
            continue;
        }
        if (e->h32 == 0) {
            n = rrange(e->h34, e->h36);
        } else {
            s = (f32)o->x20 / 100.0f;
            n = rrange((s32)(s * (f32)e->h34), (s32)(s * (f32)e->h36));
        }
        if (n <= 0) {
            continue;
        }
        ExecInfoInit_3a7940(&snd);
        ExecInfoInitFixedDamageMaybe_3a71d0(&snd, n, 1);
        fx.d48 = 0;
        fx.d50 = 0;
        fx.d58 = 0;
        fx.d60 = 0;
        ActionResultClear_3a6e60(&fx);
        ActionResultSetupMaybe_3a6d70(&fx, &snd, o->xC, -1, 0, 0, 1.0f);
        o->v284(&fx);
        w = GetActionMgr_1fdb50();
        if (w == 0) {
            continue;
        }
        c = ActionMgrFindById_233b50(w, o->xC);
        if (c != 0) {
            CharaGetPos_2388a0(c, &pos);
            a = 40.0f;
            x = GetCurrentScene_1f5be0();
            y = 0;
            if (x != 0) {
                y = ObjRecGetLiveObject_1c4a90(x, o->xC);
            }
            if (y != 0) {
                a = dptofp(dpmul(__builtin_bit_cast(double, (long long)(D_0047D180)), fptodp(y->f4CC)));
            }
            pos.y += a;
            if (CharaGetNthAttachPointPos_238580(c, 0, 0, &at) == 0) {
                VecCopy_1cbe30(&at, &pos);
            }
            col[0] = D_00480180;
            col[1] = D_00480184;
            col[2] = D_00480188;
            col[3] = D_0048018C;
            if (o->v44() != 0) {
                DamagePopupSpawn_2d2da0(GetDamagePopupList_2d9020(), n, &at, col, 0, 0, 1.25f);
            } else {
                DamagePopupSpawn_2d2da0(GetDamagePopupList_2d9020(), n, &at, 0, 0, 0, 1.25f);
            }
        }
        CharaRequestTint_213fd0(c, 3, 2, 250.0f, 118.0f, 80.0f, 5.0f, 1.0f);
    }
    a = o->v2E4();
    b = o->v2F4();
    cc = o->v304();
    step = D_0047D244 * dt;
    if (o->f1E0 < a) {
        o->f1E0 += step;
        if (!(o->f1E0 < a)) {
            o->f1E0 = a;
        }
    }
    if (o->f1E4 < b) {
        o->f1E4 += step;
        if (!(o->f1E4 < b)) {
            o->f1E4 = b;
        }
    }
    if (o->f1E8 < cc) {
        o->f1E8 += step;
        if (!(o->f1E8 < cc)) {
            o->f1E8 = cc;
        }
    }
    return 1;
}
}

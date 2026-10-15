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
    virtual void u08();
    virtual void u0C();
    virtual void u10();
    virtual void u14();
    virtual void u18();
    virtual void u1C();
    virtual void u20();
    virtual void u24();
    virtual void u28();
    virtual void u2C();
    virtual void u30();
    virtual void u34();
    virtual void u38();
    virtual void u3C();
    virtual void u40();
    virtual void u44();
    virtual void u48();
    virtual void u4C();
    virtual void u50();
    virtual void u54();
    virtual void u58();
    virtual void u5C();
    virtual void u60();
    virtual void u64();
    virtual void u68();
    virtual void u6C();
    virtual Eff *get(s16 id);
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
    virtual void u008();
    virtual void u00C();
    virtual void u010();
    virtual void u014();
    virtual void u018();
    virtual void u01C();
    virtual void u020();
    virtual void u024();
    virtual void u028();
    virtual void u02C();
    virtual void u030();
    virtual void u034();
    virtual void u038();
    virtual void u03C();
    virtual void u040();
    virtual s32 v44();
    virtual void u048();
    virtual void u04C();
    virtual void u050();
    virtual void u054();
    virtual void u058();
    virtual void u05C();
    virtual void u060();
    virtual void u064();
    virtual void u068();
    virtual void u06C();
    virtual void u070();
    virtual void u074();
    virtual void u078();
    virtual void u07C();
    virtual void u080();
    virtual void u084();
    virtual void u088();
    virtual void u08C();
    virtual void u090();
    virtual void u094();
    virtual void u098();
    virtual void u09C();
    virtual void u0A0();
    virtual void u0A4();
    virtual void u0A8();
    virtual void u0AC();
    virtual void u0B0();
    virtual void u0B4();
    virtual void u0B8();
    virtual s32 vBC();
    virtual void u0C0();
    virtual void u0C4();
    virtual void u0C8();
    virtual void u0CC();
    virtual void u0D0();
    virtual void u0D4();
    virtual void u0D8();
    virtual void u0DC();
    virtual void u0E0();
    virtual void u0E4();
    virtual void u0E8();
    virtual void u0EC();
    virtual void u0F0();
    virtual void u0F4();
    virtual void u0F8();
    virtual void u0FC();
    virtual void u100();
    virtual void u104();
    virtual void u108();
    virtual void u10C();
    virtual void u110();
    virtual void u114();
    virtual void u118();
    virtual void u11C();
    virtual void u120();
    virtual void u124();
    virtual s32 v128(s32 a);
    virtual void u12C();
    virtual void u130();
    virtual void u134();
    virtual void u138();
    virtual void u13C();
    virtual void u140();
    virtual void u144();
    virtual void u148();
    virtual void u14C();
    virtual void u150();
    virtual void u154();
    virtual void u158();
    virtual void u15C();
    virtual void u160();
    virtual void u164();
    virtual void u168();
    virtual void u16C();
    virtual void u170();
    virtual void u174();
    virtual void u178();
    virtual void u17C();
    virtual void u180();
    virtual void u184();
    virtual void u188();
    virtual void u18C();
    virtual void u190();
    virtual void u194();
    virtual void u198();
    virtual void u19C();
    virtual void v1A0(s32 id, s32 a, s32 b);
    virtual void u1A4();
    virtual void u1A8();
    virtual void u1AC();
    virtual void u1B0();
    virtual void u1B4();
    virtual void u1B8();
    virtual void u1BC();
    virtual void u1C0();
    virtual void u1C4();
    virtual void u1C8();
    virtual void u1CC();
    virtual void u1D0();
    virtual void u1D4();
    virtual void u1D8();
    virtual void u1DC();
    virtual void u1E0();
    virtual void u1E4();
    virtual void u1E8();
    virtual void u1EC();
    virtual void u1F0();
    virtual void u1F4();
    virtual void u1F8();
    virtual void u1FC();
    virtual void u200();
    virtual void u204();
    virtual void u208();
    virtual void u20C();
    virtual void u210();
    virtual void u214();
    virtual void u218();
    virtual void u21C();
    virtual void u220();
    virtual void u224();
    virtual void u228();
    virtual void u22C();
    virtual void u230();
    virtual void u234();
    virtual void u238();
    virtual void u23C();
    virtual void u240();
    virtual void u244();
    virtual void u248();
    virtual void u24C();
    virtual void u250();
    virtual void u254();
    virtual void u258();
    virtual void u25C();
    virtual void u260();
    virtual void u264();
    virtual void u268();
    virtual void u26C();
    virtual void u270();
    virtual void u274();
    virtual void u278();
    virtual void v27C(f32 dt);
    virtual void u280();
    virtual void v284(Fx *f);
    virtual void u288();
    virtual void u28C();
    virtual void u290();
    virtual void u294();
    virtual void u298();
    virtual void u29C();
    virtual void u2A0();
    virtual void u2A4();
    virtual void u2A8();
    virtual void u2AC();
    virtual void u2B0();
    virtual void u2B4();
    virtual void u2B8();
    virtual void u2BC();
    virtual void u2C0();
    virtual void u2C4();
    virtual void u2C8();
    virtual void u2CC();
    virtual void u2D0();
    virtual void u2D4();
    virtual void u2D8();
    virtual void u2DC();
    virtual void u2E0();
    virtual f32 v2E4();
    virtual void u2E8();
    virtual void u2EC();
    virtual void u2F0();
    virtual f32 v2F4();
    virtual void u2F8();
    virtual void u2FC();
    virtual void u300();
    virtual f32 v304();
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
s64 dpmul(s64, s64);
s64 fptodp(f32);
f32 dptofp(s64);
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
s32 ActorCastToChara_3b87b0(Chr *);
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
    Snd snd;
    Fx fx;
    Vec4 pos;
    Vec4 at;
    f32 col[4];
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
    p = ActorCastToChara_3b87b0(o);
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
                a = dptofp(dpmul(D_0047D180, fptodp(y->f4CC)));
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

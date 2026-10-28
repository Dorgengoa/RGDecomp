/* rgp:protos */
#line 1
#include "types.h"

struct Item8 {
    u8 pad[3];
    s8 idx;
};

class Item {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Hp() { return VCM0(s32, 0x78); }
    s32 Mp() { return VCM0(s32, 0x7C); }
    f32 RateA() { return VCM0(f32, 0x80); }
    f32 RateB() { return VCM0(f32, 0x84); }
    
    f32 RateC() { return VCM0(f32, 0x8C); }
    s32 Res(s32 a0) { return VCM(s32, (void *, s32), 0x90, a0); }
    
    
    
    
    
    
    
    
    
    s32 Atk(s32 a0) { return VCM(s32, (void *, s32), 0xB8, a0); }
    
    s32 Def(s32 a0) { return VCM(s32, (void *, s32), 0xC0, a0); }
    u8 pad4[0xC];
    s16 *id;              /* 0x10 */
};

class Bag {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item8 * Find(s32 a0) { return VCM(Item8 *, (void *, s32), 0x70, a0); }

};

struct Mgr58 {
    u8 pad[8];
    Bag *bag;
};

struct Mgr {
    u8 pad[0x58];
    Mgr58 *m;
};

extern "C" {
s32 UnitBaseResetStatsToBase_3b82e0(void);
extern s32 D_00465BE8[];
extern s32 D_00465C00[];
extern s32 D_00465C08[];
extern s32 D_00465C18[];
extern s32 D_00465C20[];
extern s32 D_00465C28[];
extern s32 D_00465C30[];
extern f32 D_0047D240;
extern Mgr *D_0048381C;
}

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Kind() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * Weapon() { return VCM0(Item *, 0x388); }
    Item * Armor() { return VCM0(Item *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * AccA() { return VCM0(Item *, 0x3C4); }
    
    
    
    
    Item * AccB() { return VCM0(Item *, 0x3D8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Boosted() { return VCM0(s32, 0x460); }
    s32 pad4[6];
    s32 hpMax;            /* 0x1C */
    s32 hp;               /* 0x20 */
    u16 mpMax;            /* 0x24 */
    u16 mp;               /* 0x26 */
    s16 s28;
    s16 s2A;
    s16 s2C;
    s16 s2E;
    u16 atkBase;          /* 0x30 */
    u16 atk;              /* 0x32 */
    u16 defBase;          /* 0x34 */
    u16 def;              /* 0x36 */
    u16 magBase;          /* 0x38 */
    u16 mag;              /* 0x3A */
    f32 f3C;
    f32 f40;
    s32 s44;
    s32 s48;
    s32 s4C;
    s32 s50;
    s16 elem[5][2];       /* 0x54 */
    s16 res[7][2];        /* 0x68 */
    s16 st84[8][2];       /* 0x84 */
    s32 padA4;
    s16 stA8[4][2];       /* 0xA8 */
    u8 padB8[0x230 - 0xB8];
    u8 *data;             /* 0x230 */
    u8 pad234[0x248 - 0x234];
    s16 s248;
    s16 s24A;
    s16 s24C;
    s16 s24E;
    f32 f250;
    f32 f254;
    f32 pad258[2];
    f32 f260;
    f32 f264;
    f32 f268;
    f32 f26C;
    f32 pad270[4];
    f32 f280;
    f32 f284;
    f32 f288;
    f32 f28C;
    s32 r290[5][2];       /* 0x290 */
    s32 r2B8[5][2];       /* 0x2B8 */
    u8 pad2E0[0x4B4 - 0x2E0];
    u8 b0 : 1;
    bool flag : 1;
    u8 b7 : 6;
    s32 Recalc();

};

static inline f32 AddF(f32 f, f32 *p) {
    if (p != 0) f += *p;
    return f;
}
static inline s32 ClampMax(s32 v, s32 max) {
    if (max < v) v = max;
    return v;
}
static inline s32 Boost(s32 cur, u32 base) {
    return cur + (s32)(D_0047D240 * (f32)base);
}
static inline s32 AddHp(s32 v, Item *w, s32 max) {
    if (w != 0) {
        v += w->Hp();
        if (max < v) v = max;
    }
    return v;
}
static inline s32 AddMp(s32 v, Item *w, s32 max) {
    if (w != 0) {
        v += w->Mp();
        if (max < v) v = max;
    }
    return v;
}
static inline Item8 *FindIn(s32 n) {
    Bag *t = D_0048381C->m->bag;
    Item8 *r;
    if (t != 0) r = t->Find(n);
    else r = 0;
    return r;
}
static inline s32 AddMinMax(s32 v, s32 d, s32 min, s32 max) {
    if (d < 0) {
        v += d;
        if (v < min) return min;
        return v;
    } else if (d > 0) {
        v += d;
        if (v > max) v = max;
    }
    return v;
}

extern "C" s32 CharaRebuildEquipStatsMaybe_3aef80(Unit *u) {
    Item *w;
    Item *a;
    Item *c;
    Item *d;
    f32 *base;
    s32 i;
    s32 j;
    s32 t;
    s32 v;
    s32 sum;
    s32 lo;
    s32 hi;
    s32 k;
    s16 *p;
    f32 f;
    Item *it;
    Bag *bag;
    Item8 *e;
    s32 md;
    s32 cdef;
    s32 cmag;
    s32 m;
    s32 m2;
    s32 i1;
    s32 sum1;
    s32 lo1;
    s32 hi1;
    s32 j1;
    s32 i2;
    s32 sum2;
    s32 hi2;
    s32 lo2;
    s32 j2;

    if ((((unsigned char)UnitBaseResetStatsToBase_3b82e0()) & 0xFF) == 0) return 0;
    if (u->data == 0) return 0;
    base = (f32 *)(u->data + 0x14);
    w = u->Weapon();
    a = u->Armor();
    c = u->AccA();
    d = u->AccB();
    u->hp = u->hpMax;
    u->mp = u->mpMax;
    u->atk = u->atkBase;
    u->def = u->defBase;
    u->mag = u->magBase;
    u->s28 = 0;
    u->s2A = 0;
    if (u->Boosted()) {
        t = u->hp;
        f = D_0047D240 * (f32)(u32)u->hpMax;
        m = D_00465BE8[0];
        t += (s32)f;
        if (m < t) v = m; else v = t;
        u->hp = v;
        t = u->atk;
        f = D_0047D240 * (f32)(u32)u->atkBase;
        m2 = D_00465C00[0];
        t += (s32)f;
        if (m2 < t) v = m2; else v = t;
        u->atk = v;
        cdef = u->def;
        f = D_0047D240 * (f32)(u32)u->defBase;
        md = D_00465C08[0];
        cdef = (s32)(u32)cdef;
        if (md < cdef + (s32)f) v = md; else v = cdef + (s32)f;
        u->def = v;
        cmag = u->mag;
        f = D_0047D240 * (f32)(u32)u->magBase;
        cmag = (s32)(u32)cmag;
        cmag += (s32)f;
        if (m2 < cmag) v = m2; else v = cmag;
        u->mag = v;
    }
    v = u->atkBase;
    if (w != 0) {
        v += w->Hp();
        v = ClampMax(v, D_00465C00[0]);
    }
    u->s248 = v;
    u->s24A = v;
    v = u->magBase;
    if (a != 0) {
        v += a->Hp();
        v = ClampMax(v, D_00465C00[0]);
    }
    u->s24C = v;
    u->s24E = v;
    v = u->defBase;
    if (c != 0) {
        v += c->Mp();
        v = ClampMax(v, D_00465C08[0]);
    }
    u->s2C = v;
    u->s2E = v;
    f = 1.0f;
    if (w != 0) f += w->RateA();
    u->f250 = f;
    u->f254 = f;
    f = 1.0f;
    if (a != 0) f += a->RateA();
    u->f250 = f;
    u->f254 = f;
    f = 1.0f;
    if (w != 0) f += w->RateB();
    u->f260 = f;
    u->f264 = f;
    f = 1.0f;
    if (a != 0) f += a->RateB();
    u->f260 = f;
    u->f264 = f;
    f = 0.0f;
    if (w != 0) f += w->RateB();
    u->f260 = f;
    u->f264 = f;
    f = 0.0f;
    if (a != 0) f += a->RateB();
    u->f268 = f;
    u->f26C = f;
    f = 0.0f;
    if (w != 0) f += w->RateC();
    u->f280 = f;
    u->f284 = f;
    f = 0.0f;
    if (a != 0) f += a->RateC();
    u->f288 = f;
    u->f28C = f;
    for (i = 0; i < 5; i++) {
        f = 0.0f;
        if (w != 0) f += (f32)w->Res(i);
        t = (s32)f;
        u->r290[i][0] = t;
        u->r290[i][1] = t;
    }
    for (i = 0; i < 5; i++) {
        f = 0.0f;
        if (a != 0) f += (f32)a->Res(i);
        t = (s32)f;
        u->r2B8[i][0] = t;
        u->r2B8[i][1] = t;
    }
    f = AddF(0.0f, base);
    lo1 = D_00465C20[0];
    hi1 = D_00465C18[0];
    u->f3C = f;
    u->f40 = f;
    u->s44 = 0;
    u->s48 = 0;
    u->s4C = 0;
    u->s50 = 0;
    for (i1 = 0; i1 < 5; i1++) {
        sum1 = 0;
        for (j1 = 0; j1 < 2; j1++) {
            it = j1 == 0 ? d : c;
            if (it != 0) {
                sum1 = AddMinMax(sum1, it->Atk(i1), lo1, hi1);
            }
        }
        u->elem[i1][0] = sum1;
        u->elem[i1][1] = sum1;
    }
    if (u->Kind() == 0x2AFD) {
        t = u->elem[2][0] - 20;
        if (t < lo1) v = lo1; else v = t;
        u->elem[2][0] = v;
        u->elem[2][1] = v;
    }
    lo2 = D_00465C30[0];
    i2 = 0;
    hi2 = D_00465C28[0];
    for (; i2 < 8; i2++) {
        sum2 = 0;
        for (j2 = 0; j2 < 2; j2++) {
            it = j2 == 0 ? d : c;
            if (it != 0) {
                sum2 = AddMinMax(sum2, it->Def(i2), lo2, hi2);
            }
        }
        u->res[i2][0] = sum2;
        u->res[i2][1] = sum2;
    }
    if (u->Kind() == 0x2AFD) {
        e = FindIn(8);
        if (e != 0) {
            k = e->idx;
            p = (s16 *)(k * 4 - -(s32)u + 0x68);
            t = *p + 100;
            if (hi2 < t) v = hi2; else v = t;
            *p = v;
            k = (s32)k;
            u->res[k][1] = v;
        }
        e = FindIn(6);
        if (e != 0) {
            k = e->idx;
            p = (s16 *)(k * 4 - -(s32)u + 0x68);
            t = *p - 20;
            if (t < lo2) v = lo2; else v = t;
            *p = v;
            k = (s32)k;
            u->res[k][1] = v;
        }
    }
    if (u->Boosted()) {
        for (i = 0; i < 8; i++) {
            u->res[i][0] = 100;
            u->res[i][1] = 100;
        }
    }
    for (i = 1; i < 8; i++) {
        u->st84[i][0] = 0;
        u->st84[i][1] = 0;
    }
    for (i = 0; i < 4; i++) {
        u->stA8[i][0] = 0;
        u->stA8[i][1] = 0;
    }
    u->flag = false;
    if (d != 0 && *d->id == 0x42DA) u->flag = true;
    return 1;
}

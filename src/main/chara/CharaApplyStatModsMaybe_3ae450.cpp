#include "types.h"

struct Item {
    u8 pad[0x16];
    s16 h16;
    u8 pad18[2];
    s16 h1A;
    s16 h1C;
    s16 h1E;
    s8 c20[5];
    s8 c25[5];
    s8 c2A[8];
};
struct Skill {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s8 c8[5];
    s8 cD[5];
    s8 c12[8];
};
struct S16p { s16 v; s16 pad; };
struct S16b { s16 base; s16 v; };
struct R8 { s32 v; s32 pad; };
class ItemTbl {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual Item *Get(s16);
};
struct G58 { u8 pad[8]; ItemTbl *f8; };
struct G { u8 pad[0x58]; G58 *f58; };
class Unit {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual s32 Has(s32);
    u8 pad4[0x10];
    u32 f14;
    u16 h18;
    u8 pad1A[2];
    u32 f1C;
    u32 f20;
    u8 pad24[2];
    u16 h26;
    u8 pad28[2];
    s16 h2A;
    u16 h2C;
    u16 h2E;
    u8 pad30[0x26];
    S16p x56[5];
    S16p x6A[8];
    u8 pad8A[0x190 - 0x8A];
    s16 h190;
    s16 h192;
    s16 h194;
    u8 pad196[0x1DA - 0x196];
    s16 h1DA;
    u8 pad1DC[0x248 - 0x1DC];
    S16b x248[2];
    u8 pad250[0x294 - 0x250];
    R8 r294[2][5];
    u8 pad2E4[0x498 - 0x2E4];
    s32 f498;
};

extern "C" s32 UnitBaseApplyStatMods_3b82a0(void);
extern "C" s32 CharaGetNthLearnedAbility_3adba0(Unit *, s32, s32, s32, s32);
extern "C" Skill *AbilityDataGetKind1Rec_3f5de0(s32);
extern "C" s32 EquipSlotGetRecId_3a0760(s32);
extern const s32 D_00465BE8[];
extern const s32 D_00465BF0[];
extern const s32 D_00465C00[];
extern const s32 D_00465C08[];
extern const s32 D_00465C10[];
extern const s32 D_00465C18[];
extern const s32 D_00465C20[];
extern const s32 D_00465C28[];
extern const s32 D_00465C30[];
extern s32 D_00465900[];
extern s32 D_00465908[];
extern s32 D_00465910[];
extern s32 D_00465918[];
extern s32 D_00465920[];
extern s32 D_00465928[];
extern G *D_0048381C;

static inline Item *GetItem(s32 i) {
    ItemTbl *t = D_0048381C->f58->f8;
    Item *r;
    if (t != 0) r = t->Get(i);
    else r = 0;
    return r;
}
static inline s32 AddMax(s32 v, s32 d, s32 cmp, s32 max) {
    if (d < 0) {
        v += d;
        if (v < 0) return 0;
        return v;
    } else if (d > 0) {
        v += d;
        if (v > cmp) v = max;
    }
    return v;
}
static inline s32 AddNeg(s32 v, s32 d, s32 cmp, s32 min) {
    if (d > 0) {
        v += d;
        if (v > 0) return 0;
        return v;
    } else if (d < 0) {
        v += d;
        if (v < cmp) v = min;
    }
    return v;
}
static inline s32 AddMax2(s32 v, s32 d, s32 cmp, s32 max) {
    if (d < 0) {
        if (v + d < 0) return 0;
        return v + (s8)d;
    } else if (d > 0) {
        if (v + d > cmp) return max;
        return v + (s8)d;
    }
    return v;
}
static inline s32 AddMinMax(s32 v, s32 d, s32 cmin, s32 min, s32 cmax, s32 max) {
    if (d < 0) {
        v += d;
        if (v < cmin) v = min;
    } else if (d > 0) {
        v += d;
        if (v > cmax) v = max;
    }
    return v;
}

extern "C" s32 CharaApplyStatModsMaybe_3ae450(Unit *u) {
    s32 i;
    s32 j;
    s32 i2;
    s32 k;
    s32 max20;
    s32 min2A;
    s32 max24A;
    s32 max2E;
    s32 max294;
    s32 min56;
    s32 max56;
    s32 min6A;
    s32 max6A;
    s32 x;
    Skill *s;
    Item *it;
    s32 v;
    s32 d;
    s16 *p;
    s32 *q;
    s32 jb;

    if ((UnitBaseApplyStatMods_3b82a0() & 0xFF) == 0) return 0;
    i = 0;
    max20 = *(s32 *)&D_00465BE8[0];
    min2A = *(s32 *)&D_00465BF0[0];
    max24A = *(s32 *)&D_00465C00[0];
    max2E = *(s32 *)&D_00465C08[0];
    max294 = *(s32 *)&D_00465C10[0];
    min56 = *(s32 *)&D_00465C20[0];
    max56 = *(s32 *)&D_00465C18[0];
    min6A = *(s32 *)&D_00465C30[0];
    max6A = *(s32 *)&D_00465C28[0];
    for (; i < 0x40; i++) {
        x = CharaGetNthLearnedAbility_3adba0(u, i, 1, -1, 0);
        if (x == 0) break;
        s = AbilityDataGetKind1Rec_3f5de0(x);
        if (s == 0) continue;
        v = u->f20;
        v = AddMax(v, (s32)((f32)u->f1C * (s->h0 / 100.0f)), max20, max20);
        u->f20 = v;
        v = u->h2A;
        v = AddNeg(v, s->h2, min2A, min2A);
        u->h2A = v;
        j = 0;
        do {
            p = &u->x248[j].v;
            v = AddMax(*p, s->h4, max24A, max24A);
            j++;
            *p = v;
        } while (j < 2);
        v = u->h2E;
        v = AddMax(v, s->h6, max2E, max2E);
        u->h2E = v;
        for (k = 0; k < 5; k++) {
            d = s->c8[k];
            for (j = 0; j < 2; j++) {
                q = &(&u->r294[0][k])[j * 5].v;
                *q = AddMax2(*q, d, max294, max294);
            }
        }
        j = 0;
        do {
            p = &u->x56[j].v;
            v = AddMinMax(*p, s->cD[j], min56, min56, max56, max56);
            j++;
            *p = v;
        } while (j < 5);
        j = 0;
        do {
            p = &u->x6A[j].v;
            v = AddMinMax(*p, s->c12[j], min6A, min6A, max6A, max6A);
            j++;
            *p = v;
        } while (j < 8);
    }
    for (i2 = 2; i2 < 0x30; i2++) {
        if (u->Has(i2) == 0) continue;
        it = GetItem(i2);
        if (it == 0) continue;
        v = u->f20;
        v = AddMax(v, (s32)((f32)u->f1C * (it->h16 / 100.0f)), D_00465BE8[0], max20);
        u->f20 = v;
        v = u->h2A;
        v = AddNeg(v, it->h1A, D_00465BF0[0], min2A);
        u->h2A = v;
        jb = 0;
        do {
            p = &u->x248[jb].v;
            v = *p;
            v = AddMax(v, (s32)((f32)u->x248[jb].base * (it->h1C / 100.0f)), D_00465C00[0], max24A);
            jb++;
            *p = v;
        } while (jb < 2);
        v = u->h2E;
        v = AddMax(v, (s32)((f32)(u32)u->h2C * (it->h1E / 100.0f)), D_00465C08[0], max2E);
        u->h2E = v;
        for (j = 0; j < 5; j++) {
            d = it->c20[j];
            for (k = 0; k < 2; k++) {
                q = &(&u->r294[0][j])[k * 5].v;
                *q = AddMax2(*q, d, D_00465C10[0], max294);
            }
        }
        j = 0;
        do {
            p = &u->x56[j].v;
            v = AddMinMax(*p, it->c25[j], D_00465C20[0], min56, D_00465C18[0], max56);
            j++;
            *p = v;
        } while (j < 5);
        j = 0;
        do {
            p = &u->x6A[j].v;
            v = AddMinMax(*p, it->c2A[j], D_00465C30[0], min6A, D_00465C28[0], max6A);
            j++;
            *p = v;
        } while (j < 8);
    }
    u->h1DA = 0;
    if (u->f20 > (u32)max20) u->f20 = max20;
    if (u->h2A < min2A) u->h2A = min2A;
    for (j = 0; j < 2; j++) {
        if (u->x248[j].v > max24A) u->x248[j].v = max24A;
    }
    if (u->h2E > max2E) u->h2E = max2E;
    x = *(s32 *)&D_00465C10[0];
    for (j = 0; j < 2; j++) {
        for (k = 0; k < 5; k++) {
            if (u->r294[j][k].v > x) u->r294[j][k].v = max294;
        }
    }
    for (j = 0; j < 5; j++) {
        if (u->x56[j].v > max56) u->x56[j].v = max56;
        else if (u->x56[j].v < min56) u->x56[j].v = min56;
    }
    for (j = 0; j < 8; j++) {
        if (u->x6A[j].v > max6A) u->x6A[j].v = max6A;
        else if (u->x6A[j].v < min6A) u->x6A[j].v = min6A;
    }
    if (u->f14 > u->f20) u->f14 = u->f20;
    if ((s32)u->h18 < 0) u->h18 = 0;
    else if (u->h18 > u->h26) u->h18 = u->h26;
    k = -1;
    if (u->f498 != 0) k = EquipSlotGetRecId_3a0760(u->f498);
    if (k == 0x1AF) u->h190 = D_00465908[0];
    else if (k == 0x1B0) u->h190 = D_00465908[0];
    else u->h190 = D_00465900[0];
    if (k == 0x79) u->h192 = D_00465918[0];
    else if (k == 0x7A) u->h192 = D_00465918[0];
    else u->h192 = D_00465910[0];
    if (k == 0x6F) u->h194 = D_00465928[0];
    else if (k == 0x70) u->h194 = D_00465928[0];
    else if (k == 0x32B) u->h194 = D_00465928[0];
    else if (k == 0x32C) u->h194 = D_00465928[0];
    else u->h194 = D_00465920[0];
    return 1;
}
